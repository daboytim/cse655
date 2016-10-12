/*
 * int.h
 *
 *  Created on: May 15, 2012
 *      Author: boytim
 */

#ifndef INT_H_
#define INT_H_

#include <stdlib.h>

class Int {
    int val;
public:
    Int();
    ~Int();

    bool parse();
    void print();
    int exec();
};

Int::Int() {

}

Int::~Int() {

}

bool Int::parse() {
    if (toke->getTokenNumber() == 31) {
	val = atoi(toke->getToken().c_str());
	toke->skipToken();
    } else {
	printf("%s%s'\n", "Error: expected '<integer>', found '", toke->getToken().c_str());
	return false;
    }
    return true;
}

void Int::print() {
    printf("%d", val);
}

int Int::exec() {
    return val;
}



#endif /* INT_H_ */
