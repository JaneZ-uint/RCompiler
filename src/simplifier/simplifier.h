#pragma once

/*
Mainly read files,separate lines.
Move blank and comments.
*/

#include <ostream>
#include <string>
#include <iostream>
#include <fstream>
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
        bool trans = false;// is in trans /
        int multi_comment_cnt = 0;//is in /* */
        for(int i = 0;i < tokens.size();i ++){
            std::string current = tokens[i];
            for(int j = 0;j < current.size();j ++){
                char nextChar;
                if(j == current.size()){
                    nextChar = '\0';
                }else{
                    nextChar = current[j + 1];
                }
                if(multi_comment_cnt == 0){
                    if(isDouble){
                        result += current[j];
                        if(trans){
                            trans = false;
                        }else {
                            if(current[j] == '"'){
                                isDouble = false;
                            }else if(current[j] == '\\'){
                                trans = true;
                            }
                        }
                    }else if(isSingle){
                        result += current[j];
                        if(trans){
                            trans = false;
                        }else{
                            if(current[j] == '\''){
                                isSingle = false;
                            }else if(current[j] == '\\') {
                                trans = true;
                            }
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
                        }
                    }
                    
                }else{ //muti_comment_case

                }
            }
        }
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
        for(int i = 0;i < result.size();i ++){
            std::cout << result[i];
            if(result[i] == ';'){
                std::cout << std::endl;
            }
        }
    }
};

}