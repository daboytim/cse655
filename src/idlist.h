/*
 * idlist.h
 *
 *  Created on: May 15, 2012
 *      Author: boytim
 */

#ifndef IDLIST_H_
#define IDLIST_H_

#include "id.h"

class IdList {
    Id* id;
    IdList* idl;
public:
    IdList();
    ~IdList();

    bool parse();
    void print();
    void exec(std::vector<std::string>&);
};

IdList::IdList() {
    id = 0;
    idl = 0;
}

IdList::~IdList() {
    if (id != 0)
	delete id;
    if (idl != 0)
	delete idl;
}

bool IdList::parse() {
    id = new Id();
    if (!id->parse()) {
	return false;
    }
    if (toke->getTokenNumber() == 13) {
	toke->skipToken();
	idl = new IdList();
	return idl->parse();
    }
    return true;
}

void IdList::print() {
    id->print();
    if (idl != 0) {
	printf("%s", ", ");
	idl->print();
    }
}

void IdList::exec(std::vector<std::string>& idlist) {
    idlist.push_back(id->getId());
    if (idl != 0)
	idl->exec(idlist);
}


#endif /* IDLIST_H_ */
