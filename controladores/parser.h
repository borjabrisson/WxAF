/*
 * parser.h
 *
 *  Created on: 24/09/2013
 *      Author: borja
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <string>
using namespace std;
typedef struct filterToken_Struct{
	string leftToken;
	string rightToken;
	string operation;
}filterToken;


class parser {

public:
	parser();
	~parser();
	string filter(string field,string filterToParser);
protected:
	int token(int pos, string &input, string &output);
	int parser2(string input, filterToken &output);

};

#endif /* PARSER_H_ */
