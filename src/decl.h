/*
 * decl.h
 *
 *  Created on: May 15, 2012
 *      Author: boytim
 */

#ifndef DECL_H_
#define DECL_H_

#include "idlist.h"

class Decl {
    IdList* idl;
public:
    Decl();
    ~Decl();

    bool parse();
    void print();
};

Decl::Decl() {
    idl = 0;
}

Decl::~Decl() {
    if (idl != 0)
	delete idl;
}

bool Decl::parse() {
    if (toke->getTokenNumber() == 4) {
	toke->skipToken();
	idl = new IdList();
	if (!idl->parse()) {
	    return false;
	}
    } else {
	printf("%s%s'\n", "Error: expected 'int', found '", toke->getToken().c_str());
	return false;
    }
    if (toke->getTokenNumber() != 12) {
	printf("%s%s'\n", "Error: expected ';', found '", toke->getToken().c_str());
	return false;
    }
    toke->skipToken();
    return true;
}

void Decl::print() {
    for (int i=0; i<INDENT; i++) {
	printf("%c", ' ');
    }
    printf("%s", "int ");
    idl->print();
    printf("%s", ";\n");
}


#endif /* DECL_H_ */
