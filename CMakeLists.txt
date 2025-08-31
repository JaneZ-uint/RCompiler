cmake_minimum_required(VERSION 3.10)
project(RCompiler)

set(CMAKE_CXX_STANDARD 17)

add_executable(RCompiler 
    main.cpp
    src/parser/Parser.cpp
    src/parser/ParseItem.cpp
    src/parser/ParsePattern.cpp
    src/parser/ParsePath.cpp
    src/parser/ParseStmt.cpp
    src/parser/ParseType.cpp
    src/parser/PrattParser.cpp

    )