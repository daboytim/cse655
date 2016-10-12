/*
 * assign.h
 *
 *  Created on: May 15, 2012
 *      Author: boytim
 */

#ifndef ASSIGN_H_
#define ASSIGN_H_

#include "tokenizer.h"
#include "id.h"
#include "exp.h"

class Assign {
    Id* id;
    Exp* exp;
public:
    Assign();
    ~Assign();

    bool parse();
    void print(int);
    void exec();
};

Assign::Assign() {
    id = 0;
    exp = 0;
}

Assign::~Assign() {
    if (id != 0)
	delete id;
    if (exp != 0)
	delete exp;
}

bool Assign::parse() {
    id = new Id();
    if (!id->parse()) {
	return false;
    }
    if (toke->getTokenNumber() != 14) {
	printf("%s%s'\n", "Error: expected '=', found '", toke->getToken().c_str());
	return false;
    }
    toke->skipToken();
    exp = new Exp();
    if (!exp->parse()) {
	return false;
    }
    if (toke->getTokenNumber() != 12) {
	printf("%s%s'\n", "Error: expected ';', found '", toke->getToken().c_str());
	return false;
    }
    toke->skipToken();
    return true;
} 

void Assign::print(int spaces) {
    for (int i=0; i <spaces; i++) {
	printf("%c", ' ');
    }
    id->print();
    printf("%s", " = ");
    exp->print();
    printf("%s", ";\n");
}

void Assign::exec() {
    (*(idTable->ids))[id->getId()]->value = exp->exec();
    (*(idTable->ids))[id->getId()]->init = true;
}



#endif /* ASSIGN_H_ */
