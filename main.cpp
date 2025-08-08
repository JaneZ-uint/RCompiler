# include "src/simplifier/simplifier.h"
#include <iostream>

int main(){
    JaneZ::Simplifier simplifier("helloworld.rs");
    simplifier.work();
    simplifier.print();
}