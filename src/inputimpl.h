/*
 * inputimpl.h
 *
 *  Created on: May 17, 2012
 *      Author: boytim
 */

#ifndef INPUTIMPL_H_
#define INPUTIMPL_H_

Input::Input() {
    idl = 0;
}

Input::~Input() {
    if (idl != 0)
	delete idl;
}

bool Input::parse() {
    if (toke->getTokenNumber() != 10) {
	printf("%s%s'\n", "Error: expected 'read', found '", toke->getToken().c_str());
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

void Input::print(int spaces) {
    for (int i=0; i<spaces; i++) {
	printf("%c", ' ');
    }
    printf("%s", "read ");
    idl->print();
    printf("%c\n", ';');
}

void Input::exec() {
    std::vector<std::string> idlist;
    idl->exec(idlist);
    for (int i=0; i<idlist.size(); i++) {
	int x;
	(*fin) >> (*(idTable->ids))[idlist[i]]->value;
	(*(idTable->ids))[idlist[i]]->init = true;
    }
}


#endif /* INPUTIMPL_H_ */
