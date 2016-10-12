/*
 * idvaltable.h
 *
 *  Created on: May 15, 2012
 *      Author: boytim
 */

#ifndef IDVALTABLE_H_
#define IDVALTABLE_H_

#include <string>
#include <map>

class Entry {
public:
    int value;
    bool init;

    Entry() {
	init = false;
    }
};

class IdValTable {
    IdValTable();
public:
    std::map<std::string, Entry*>* ids;

    ~IdValTable();

    static void instance();
};

IdValTable* idTable=0;

IdValTable::IdValTable() {
    ids = new std::map<std::string, Entry*>();
}

IdValTable::~IdValTable() {
    delete ids;
}

void IdValTable::instance() {
    if (idTable == 0) {
	idTable = new IdValTable();
    }
}

#endif /* IDVALTABLE_H_ */
