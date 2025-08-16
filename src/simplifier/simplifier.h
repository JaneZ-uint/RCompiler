#pragma once

/*
Mainly read files,separate lines.
Move blank and comments.
*/

#include <cstdio>
#include <ostream>
#include <string>
#include <iostream>
#include <fstream>
#include <system_error>
#include <vector>

namespace JaneZ{
class Simplifier{
private:
    std::vector<std::string> tokens;
    std::string fileName;

    std::string result;

    void getTokens(){
        std::ifstream file(fileName);
        if(file.is_open()){
            std::string line;
            while(std::getline(file,line)){
                line += '\n';
                tokens.push_back(line);
            }
            file.close();
        }else{
            std::cerr << "Failed to open "<< fileName << std::endl;
        }
    }

    void simplify(){
        result = "";
        bool isSingle = false;// is in ''
        bool isDouble = false;// is in ""
        //bool trans = false;// is in trans /
        bool isBlank = false;// is in blank
        int multi_comment_cnt = 0;//is in /* */
        for(int i = 0;i < tokens.size();i ++){
            std::string current = tokens[i];
            for(int j = 0;j < current.size();j ++){
                char nextChar;
                if(j == current.size() - 1){
                    nextChar = '\0';
                }else{
                    nextChar = current[j + 1];
                }
                if(multi_comment_cnt == 0){
                    if(isDouble){
                        result += current[j];
                        if(current[j] == '"'){
                            isDouble = false;
                        }
                    }else if(isSingle){
                        result += current[j];
                        if(current[j] == '\''){
                            isSingle = false;
                        }
                    }else {
                        if(current[j] == '/' && nextChar == '/'){
                            break;
                        }else if(current[j] == '/' && nextChar == '*') {
                            multi_comment_cnt ++;
                            j ++;
                        }else if(current[j] == '"'){
                            isDouble = true;
                            result += current[j];
                        }else if(current[j] == '\''){
                            isSingle = true;
                            result += current[j];
                        }else{
                            if(isBlank){
                                if(current[j] != ' ' && current[j] != '\t' && current[j] != '\n'){
                                    result += current[j];
                                    isBlank = false;
                                }else{
                                    isBlank = true;
                                }
                            }else{
                                if(current[j] == ' '){
                                    isBlank = true;
                                    result += ' ';
                                }else if(current[j] == '\t'){
                                    isBlank = true;
                                    result += ' ';
                                }else if(current[j] != '\n'){
                                    isBlank = false;
                                    result += current[j];
                                }
                            }
                        }
                    }
                    
                }else{ //multi_comment_case
                    if(current[j] == '*' && nextChar == '/'){
                        multi_comment_cnt --;
                        j ++;
                    }
                    if(multi_comment_cnt == 0){ // add " "
                        if(!result.empty() && result.back() != ' '){
                            result += ' ';
                        }
                    }
                    if(current[j] == '/' && nextChar == '*'){
                        multi_comment_cnt ++;
                        j ++;
                    }
                }
            }
        }
        size_t start = result.find_first_not_of(" \t");
        if(start == std::string::npos) {
            start = 0;
        }
        size_t end = result.find_last_not_of(" \t");
        result = result.substr(start, end - start + 1);
    }

public:
    Simplifier(const std::string filename):fileName(filename){
        getTokens();
    }

    ~Simplifier(){
        tokens.clear();
    }

    std::string work(){
        simplify();
        return result;
    }

    //debug function
    void print(){
        std::cout << "Simplify Program Below:" << std::endl;
        std::cout << result;
    }
};

}