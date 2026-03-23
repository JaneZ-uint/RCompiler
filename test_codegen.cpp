#include <iostream>
#include <memory>
#include <vector>
#include "src/ir/IRRoot.h"
#include "src/ir/IRFunction.h"
#include "src/ir/IRBlock.h"
#include "src/ir/IRReturn.h"
#include "src/ir/IRBinaryop.h"
#include "src/ir/IRLiteral.h"
#include "src/ir/IRVar.h"
#include "src/ir/IRType.h"
#include "src/codegen/codegen.h"

using namespace JaneZ;

// Define the global counter
long long int ir_cnt = 0;

int main() {
    std::cout << "Starting Codegen Test..." << std::endl;

    // 1. Create a dummy IRRoot
    auto root = std::make_shared<IRRoot>();

    // 2. Create a simple function: int main() { return 1 + 2; }
    // Use IRIntType for integer type
    auto retType = std::make_shared<IRIntType>(32); 
    auto func = std::make_shared<IRFunction>(retType, "main", nullptr, nullptr);
    
    // Create function body block
    auto body = std::make_shared<IRBlock>();
    func->body = body;

    // Create IR instructions: 
    // %1 = 1
    // %2 = 2
    // %3 = %1 + %2
    // ret %3

    auto typeInt = std::make_shared<IRIntType>(32);
    // Correct IRVar constructor: type, name, rename
    auto var1 = std::make_shared<IRVar>(typeInt, "v1", "v1_ir");
    auto var2 = std::make_shared<IRVar>(typeInt, "v2", "v2_ir");
    auto var3 = std::make_shared<IRVar>(typeInt, "v3", "v3_ir");

    // Correct IRLiteral constructor: type, intVal, boolVal
    auto lit1 = std::make_shared<IRLiteral>(IRLiteralType::INT_LITERAL, 1);
    auto lit2 = std::make_shared<IRLiteral>(IRLiteralType::INT_LITERAL, 2);

    auto binOp = std::make_shared<IRBinaryop>();
    binOp->op = IROp::ADD;
    binOp->leftValue = lit1;
    binOp->rightValue = lit2;
    binOp->result = var3;

    body->instrList.push_back(binOp);

    // Correct IRReturn constructor: type, value
    auto retOp = std::make_shared<IRReturn>(retType, var3);
    body->instrList.push_back(retOp);

    root->children.push_back(func);

    // 3. Run Codegen
    codegen cg;
    cg.generate(root);

    std::cout << "Codegen Test Finished." << std::endl;
    return 0;
}
