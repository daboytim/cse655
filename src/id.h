/*
 * id.h
 *
 *  Created on: May 15, 2012
 *      Author: boytim
 */

#ifndef ID_H_
#define ID_H_

#include <string>

class Id {
    std::string id;
public:
    Id();
    ~Id();

    int parse();
    void print();
    std::string exec();
    std::string getId();
};

Id::Id() {

}

Id::~Id() {
    
}

int Id::parse() {
    if (toke->getTokenNumber() == 32) {
	id = toke->getToken();
	if (!parseDsDone) {
	    if (idTable->ids->find(id) == idTable->ids->end()) {
		(*(idTable->ids))[id] = new Entry();
	    } else {
		printf("%s%s%s\n", "Error: id '", id.c_str(), "' already declared");
		return false;
	    }
	} else {
	    if (idTable->ids->find(id) == idTable->ids->end()) {
		printf("%s%s%s\n", "Error: id '", id.c_str(), "' not declared");
		return false;
	    }	
	}
	toke->skipToken();
    } else {
	printf("%s%s'\n", "Error: expected '<id>', found '", toke->getToken().c_str());
	return false;
    }
    return true;
}

void Id::print() {
    printf("%s", id.c_str());
}

std::string Id::exec() {
    if ( (*(idTable->ids))[id]->init ) {
	return id;
    }
    printf("%s%S%S\n", "Error: id '", id.c_str(), "' not initialized");
    return "";
}

std::string Id::getId() {
    return id;
}


#endif /* ID_H_ */
