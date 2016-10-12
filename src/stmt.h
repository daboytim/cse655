/*
 * stmt.h
 *
 *  Created on: May 15, 2012
 *      Author: boytim
 */

#ifndef STMT_H_
#define STMT_H_

#include "assign.h"
#include "if.h"
#include "loop.h"
#include "input.h"
#include "output.h"

class Stmt {
    Assign* assign;
    If* fi;
    Loop* loop;
    Input* input;
    Output* output;
public:
    Stmt();
    ~Stmt();

    bool parse();
    void print(int);
    void exec();
};

Stmt::Stmt() {
    assign = 0;
    fi = 0;
    loop = 0;
    input = 0;
    output = 0;
}

Stmt::~Stmt() {
    if (assign != 0)
	delete assign;
    if (fi != 0)
	delete fi;
    if (loop != 0)
	delete loop;
    if (input != 0)
	delete input;
    if (output != 0)
	delete output;
}

bool Stmt::parse() {
    int tn = toke->getTokenNumber();
    switch (tn) {
    case 32:
	assign = new Assign();
	return assign->parse();
    case 5:
	fi = new If();
	return fi->parse();
    case 8:
	loop = new Loop();
	return loop->parse();
    case 10:
	input = new Input();
	return input->parse();
    case 11:
	output = new Output();
	return output->parse();
    }
    return false;
}

void Stmt::print(int spaces) {
    if (assign != 0) {
	assign->print(spaces);
    } else if (fi != 0) {
	fi->print(spaces);
    } else if (loop != 0) {
	loop->print(spaces);
    } else if (input != 0) {
	input->print(spaces);
    } else if (output != 0) {
	output->print(spaces);
    }
}

void Stmt::exec() {
    if (assign != 0) {
	assign->exec();
    } else if (fi != 0) {
	fi->exec();
    } else if (loop != 0) {
	loop->exec();
    } else if (input != 0) {
	input->exec();
    } else if (output != 0) {
	output->exec();
    }
}



#endif /* STMT_H_ */
