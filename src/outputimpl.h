/*
 * outputimpl.h
 *
 *  Created on: May 17, 2012
 *      Author: boytim
 */

#ifndef OUTPUTIMPL_H_
#define OUTPUTIMPL_H_

Output::Output() {
    idl = 0;
}

Output::~Output() {
    if (idl != 0)
	delete idl;
}

bool Output::parse() {
    if (toke->getTokenNumber() != 11) {
	printf("%s%s'\n", "Error: expected 'write', found '", toke->getToken().c_str());
	return false;
    }
    toke->skipToken();
    idl = new IdList();
    if (!idl->parse()) {
	return false;
    }
    if (toke->getTokenNumber() != 12) {
	printf("%s%s'\n", "Error: expected ';', found '", toke->getToken().c_str());
	return false;
    }
    toke->skipToken();
    return true;
}

void Output::print(int spaces) {
    for (int i=0; i<spaces; i++) {
	printf("%c", ' ');
    }
    printf("%s", "write ");
    idl->print();
    printf("%c\n", ';');
}

void Output::exec() {
    std::vector<std::string> idlist;
    idl->exec(idlist);
    for (int i=0; i<idlist.size(); i++) {
	if (!(*(idTable->ids))[idlist[i]]->init) {
	    printf("%s%s%s\n", "Error: id '", idlist[i].c_str(), "' not initialized");
	    printf("%s\n", "Program execution may be unpredictable");
	}
	printf("%s = %d\n", idlist[i].c_str(), (*(idTable->ids))[idlist[i]]->value);
    }
}


#endif /* OUTPUTIMPL_H_ */
