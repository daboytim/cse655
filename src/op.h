/*
 * op.h
 *
 *  Created on: May 15, 2012
 *      Author: boytim
 */

#ifndef OP_H_
#define OP_H_

#include "int.h"
#include "id.h"

class Exp;

class Op {
    Int* tni;
    Id* id;
    Exp* exp;
public:
    Op();
    ~Op();

    bool parse();
    void print();
    int exec();
};


#endif /* OP_H_ */
