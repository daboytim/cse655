/*
 * tokenizer.h
 *
 *  Created on: May 2, 2012
 *      Author: Derek Boytim
 *
 *  CSE 655
 *  Lab1
 */

#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include <stdio.h>
#include <ctype.h>
#include <string>
#include <map>

using namespace std;

const string specials[] = {"program", "begin", "end", "int", "if", "then", 
			   "else", "while", "loop", "read", "write", ";", 
			   ",", "=", "!", "[", "]", "&&", "||", "(", ")",
			   "+", "-", "*", "!=", "==", "<", ">", "<=", ">="};

class Tokenizer {
    map<string, int> tokens;
    FILE* file;
    int c, tokenNumber;
    string token;

    Tokenizer(char*);
    
    int skipWhitespace();
    int pullNextToken();

public:
    int error;
    
    ~Tokenizer();
    
    void skipToken();
    string getToken();
    int getTokenNumber();
    static void instance(char*);
};

Tokenizer* toke;

/*
 * Constructor: creates and initilizes a Tokenizer object
 *
 * @param: progFile - name of the file to tokenize
 */
Tokenizer::Tokenizer(char* progFile) {
    //put the specials into a map for easy lookup
    for (int i=1; i<31; i++) {
	tokens[specials[i-1]] = i;
    }
    file = fopen(progFile, "rb");
    if (file == NULL) {
	printf("%s\n", "error opening file");
	error = 1;
    } else {
	error = 0;
    }
    //load c with the first char
    c = fgetc(file);
    //grab the first token
    tokenNumber = pullNextToken();
}


/*
 * Destructor: uninitilizes the Tokenizer object
 */
Tokenizer::~Tokenizer() {
    fclose(file);
}


/*
 * instance(char*): creates an instance of a tokenizer object
 * and assigns its address to the global pointer "toke"; if
 * "toke" has already been initialized this function does
 * nothing
 *
 * @param: the name of the program file to tokenize
 */
void Tokenizer::instance(char* progFile) {
    if (toke == 0) {
	toke = new Tokenizer(progFile);
    }
}


/*
 * skipWhiteSpace(): reads and ignores all whitespace characters
 * in the file until a non-whiespace character is found or the
 * end of file has been reached
 *
 * @return: returns -1 if EOF has been reached, 0 otherwise
 */
int Tokenizer::skipWhitespace() {
    while (isspace(c) != 0) {
	if (feof(file) != 0) {
	    return -1;
	}
	c = fgetc(file);
    }
    return 0;
}


/*
 * pullNextToken(): reads characters from the file to form the
 * longest token possible; stops reading characters when a
 * character has been read that does not form a token with the
 * previous characters
 *
 * @return: returns the number associated with the legal token
 * that was read; returns -1 if the characters read did not form
 * a legal token
 */
int Tokenizer::pullNextToken() {
    token = "";
    //skip any/all whitespace chars
    if (skipWhitespace() != 0) {
	//reached end of file
	token = "EOF";
	return 33;
    }
    //c is the next non-whitespace char in the input prog
    //check for reserved word
    if (islower(c)) {
	do {
	    token += c;
	    c=fgetc(file);
	} while (islower(c));
	//reserved word must be followed by a punct, whitespace or EOF
	if (ispunct(c) || isspace(c) || feof(file) != 0) {
	    map<string, int>::iterator it = tokens.find(token);
	    if (it != tokens.end()) {
		return it->second;
	    }
	}
	//error
	token += c;
	printf("Error: %s is not a legal token\n", token.c_str());
	return -1;
    }
    //check for special character
    else if (ispunct(c)) {
	map<string, int>::iterator it;
	//punct can be two chars so be greedy and see if the current
	//char and next char form a valid punct
	token += c;
	c=fgetc(file);
	token += c;
	it = tokens.find(token);
	if (it != tokens.end()) {
	    //both chars form a valid punct so put the next char in c
	    c=fgetc(file);
	    return it->second;
	}
	//they didnt form a valid punct together, so check if only
	//the first char is a valid punct
	token.resize(token.size()-1);
	it = tokens.find(token);
	if (it != tokens.end()) {
	    //first char is a valid punct
	    return it->second;
	}
	//error; punct not found
	printf("Error: %s is not a legal token\n", token.c_str());
	return -1;
    }
    //check for integer
    else if (isdigit(c)) {
	do {
	    token += c;
	    c=fgetc(file);
	} while (isdigit(c));
	//integer must be followed by a punct, whitespace or EOF
	if (ispunct(c) || isspace(c) || feof(file) != 0) {
	    return 31;
	}
	//error
	token += c;
	printf("Error: %s is not a legal token\n", token.c_str());
	return -1;
    }
    //check for identifier
    else if (isupper(c)) {
	do {
	    token += c;
	    c=fgetc(file);
	} while (isupper(c));
	while (isdigit(c)) {
	    token += c;
	    c=fgetc(file);
	}
	//identifier must be followed by a punct, whitespace or EOF
	if (ispunct(c) || isspace(c) || feof(file) != 0) {
	    return 32;
	}
	//error
	token += c;
	printf("Error: %s is not a legal token\n", token.c_str());
	return -1;
    }
    //check end of file
    if (feof(file) != 0) {
	token = "EOF";
	return 33;
    }
    //otherwise it's an error
    token += c;
    printf("Error: %c is not a legal token\n", c);
    return -1;
}


/*
 * skipToken(): skips the current token by reading the next
 * token from the file
 */
void Tokenizer::skipToken() {
    tokenNumber = pullNextToken();
}


/*
 * getToken(): returns a string representation of the current token
 *
 * @return: the current token
 */
string Tokenizer::getToken() {
    return token;
}


/*
 * getTokenNumber(): returns the number corresponding to the current
 * token
 *
 * @return: the current token number or -1 if the current token is
 * illegal
 */
int Tokenizer::getTokenNumber() {
    return tokenNumber;
}

#endif /* TOKENIZER_H_ */
