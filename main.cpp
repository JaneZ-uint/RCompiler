#include "src/ast/root.h"
#include "src/lexer/lexer.h"
#include "src/parser/parser.h"
#include "src/simplifier/simplifier.h"
#include "src/token/token.h"
#include "src/ast/PrintVisitor.h"
#include "src/semantic/globalScope.h"
#include "src/semantic/NameResolver.h"
#include "src/semantic/checker.h"
#include <filesystem>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <regex>
#include <map>

namespace fs = std::filesystem;

// ============================================================
// 辅助函数：自然排序比较器
// ============================================================
bool natural_less(const std::string &a, const std::string &b) {
    size_t i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (std::isdigit(a[i]) && std::isdigit(b[j])) {
            size_t i_end = i;
            while (i_end < a.size() && std::isdigit(a[i_end])) i_end++;
            size_t j_end = j;
            while (j_end < b.size() && std::isdigit(b[j_end])) j_end++;

            int num_a = std::stoi(a.substr(i, i_end - i));
            int num_b = std::stoi(b.substr(j, j_end - j));

            if (num_a != num_b)
                return num_a < num_b;

            i = i_end;
            j = j_end;
        } else {
            char ca = std::tolower(a[i]);
            char cb = std::tolower(b[j]);
            if (ca != cb)
                return ca < cb;
            i++;
            j++;
        }
    }
    return a.size() < b.size();
}

std::string trim(const std::string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

// ============================================================
// 从 expected.txt 读取正确结果 -> map<name, status>
// ============================================================
std::map<std::string, std::string> read_expected(const std::string &filename) {
    std::ifstream fin(filename);
    std::map<std::string, std::string> result;
    std::string line;
    std::regex pattern(R"(^\s*([A-Za-z0-9_]+)\s*[：:\s]\s*(✔|❌|OK|FAIL))");

    if (!fin.is_open()) {
        std::cerr << "Warning: 无法打开 " << filename << " ，跳过对拍。\n";
        return result;
    }

    while (std::getline(fin, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;

        std::smatch m;
        if (std::regex_search(line, m, pattern)) {
            result[m[1]] = m[2];
        }
    }

    return result;
}

// ============================================================
// 从测试输出 map<name, status> 生成对拍
// ============================================================
void compare_results(const std::map<std::string, std::string> &expected,
                     const std::map<std::string, std::string> &actual) {
    if (expected.empty()) {
        std::cout << "\n⚠️  未提供 expected.txt，跳过对拍。\n";
        return;
    }

    int match = 0, mismatch = 0, missing = 0, extra = 0;

    std::cout << "\n=========================================\n";
    std::cout << "           对拍结果对比 (expected.txt)   \n";
    std::cout << "=========================================\n";

    for (const auto &[name, exp_status] : expected) {
        auto it = actual.find(name);
        if (it == actual.end()) {
            std::cout << name << ": ⚠️ 未在实际输出中找到\n";
            missing++;
        } else if (it->second == exp_status) {
            std::cout << name << ": 一致 (" << exp_status << ")\n";
            match++;
        } else {
            std::cout << name << ": ❌ 不一致 (期望 " << exp_status << ", 实际 " << it->second << ")\n";
            mismatch++;
        }
    }

    for (const auto &[name, act_status] : actual) {
        if (expected.find(name) == expected.end()) {
            std::cout << name << ": ⚠️ 实际输出中多出 (" << act_status << ")\n";
            extra++;
        }
    }

    std::cout << "\n============== 对拍总结 ==============\n";
    std::cout << "匹配: " << match << "\n";
    std::cout << "不匹配: " << mismatch << "\n";
    std::cout << "缺失: " << missing << "\n";
    std::cout << "多余: " << extra << "\n";
    std::cout << "=====================================\n";
}

// ============================================================
// 主函数
// ============================================================
int main() {
    std::string base_dir = "../RCompiler-Testcases/semantic-1";
    int passed = 0, failed = 0, total = 0;

    std::cout << "=========================================\n";
    std::cout << "     Running semantic testcases...       \n";
    std::cout << "     Base directory: " << base_dir << "\n";
    std::cout << "=========================================\n";

    std::vector<fs::path> test_dirs;
    for (auto &entry : fs::directory_iterator(base_dir)) {
        if (fs::is_directory(entry))
            test_dirs.push_back(entry.path());
    }

    std::sort(test_dirs.begin(), test_dirs.end(),
              [](const fs::path &a, const fs::path &b) {
                  return natural_less(a.filename().string(), b.filename().string());
              });

    std::map<std::string, std::string> actual_result;

    for (const auto &dir : test_dirs) {
        fs::path rx_path = dir / (dir.filename().string() + ".rx");
        if (!fs::exists(rx_path)) continue;

        total++;
        std::string name = dir.filename().string();
        std::cout << "Testing " << rx_path << " ..." << std::endl;

        try {
            JaneZ::Simplifier simplifier(rx_path.string());
            std::string source_code = simplifier.work();

            JaneZ::Lexer lexer(source_code);
            auto tokens = lexer.work();

            JaneZ::Parser parser(tokens);
            auto root = parser.parse();

            JaneZ::GlobalScopeBuilder global_scope_builder;
            JaneZ::NameResolver name_resolver;
            JaneZ::Checker checker;

            checker.semantic_check(global_scope_builder, name_resolver, *root);

            std::cout << "  ✅ Passed" << std::endl;
            actual_result[name] = "OK";
            passed++;
        } catch (const std::exception &e) {
            std::cout << "  ❌ Failed: " << e.what() << std::endl;
            actual_result[name] = "FAIL";
            failed++;
        } catch (...) {
            std::cout << "  ❌ Failed: unknown error" << std::endl;
            actual_result[name] = "FAIL";
            failed++;
        }
    }

    std::cout << "\n=========================================\n";
    std::cout << "             Test Summary                \n";
    std::cout << "=========================================\n";
    std::cout << "Total: " << total << "\n";
    std::cout << "Passed: " << passed << "\n";
    std::cout << "Failed: " << failed << "\n";
    std::cout << "=========================================\n";

    // ============================================================
    // 追加：读取 expected.txt 并对拍
    // ============================================================
    auto expected = read_expected("expected.txt");
    compare_results(expected, actual_result);

    return failed == 0 ? 0 : 1;
}
