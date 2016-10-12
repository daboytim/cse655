/*
 * fac.h
 *
 *  Created on: May 15, 2012
 *      Author: boytim
 */

#ifndef FAC_H_
#define FAC_H_

class Op;

class Fac {
    Op* op;
    Fac* fac;
public:
    Fac();
    ~Fac();

    bool parse();
    void print();
    int exec();
};


#endif /* FAC_H_ */
