/*
 * interpreter.cpp
 *
 *  Created on: May 2, 2012
 *      Author: Derek Boytim
 *
 *  CSE 655
 *  Lab1
 */
#include <stdio.h>
#include <iostream>
#include <fstream>

std::ifstream* fin;

#include "tokenizer.h"
#include "program.h"

int main(int argc, char** argv) {
    if (argc != 3) {
	printf("%s\n", "usage: % interpreter <program file> <input file>");
	return 0;
    }
    Tokenizer::instance(argv[1]);
    if (toke->error != 0) {
	return 0;
    }

    std::ifstream in(argv[2]);
    fin = &in;
    
    Program* prog = new Program();
    if (!prog->parse()) {
	printf("%s\n", "Fatal error while parsing");
	return -1;
    }
    prog->print();
    prog->exec();
    
    delete toke;
    in.close();
    return 0;
}

