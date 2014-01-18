/*
 * parser.cpp
 *
 *  Created on: 24/09/2013
 *      Author: borja
 */

#include "parser.h"

parser::parser() {
	// TODO Auto-generated constructor stub

}

parser::~parser() {
	// TODO Auto-generated destructor stub
}


string parser::filter(string field,string filterToParser){
	filterToken token;
	int type = parser2(filterToParser,token);
	switch (type){
		case 1:
			return field + " = " + token.rightToken;
		break;
		case 2: case 3:
			return field + " " + token.operation + " " + token.rightToken;
		break;
		case 4:
			return field + " >=" + token.leftToken + " and "+ field + "<=" + token.rightToken;
		break;
	}
	return "";
}

string encapsular(string token){
	return "'" + token + "'";
}
int parser::parser2(string input, filterToken& output) {
	string token2;
	int size = input.size();
	int state = 0;
	if (size == 0) return 0; // El caso de tener un elemento vacío
	if (input[0] == '=') state=1;
	else{
		if ((input[0] == '<') || (input[0] == '>') ){
			state=2;
			output.operation = input[0];
		}
		if (input[1] == '=') {
			state=3;
			output.operation += '=';
		}
	}

	switch (state){
		case 0:{
			int pos = token(-1,input,token2);
			output.leftToken = encapsular(token2);
			if (pos<0) return pos;
			if (pos != size){
				if ( (input[pos] == '.') && (input[pos+1] == '.') ){
					state = 4;
					string second = input.substr(pos+2);
					pos = token(-1,second,token2);
					if (pos<0) return pos;
					output.rightToken = encapsular(token2);
					return 4;
				}
			}
			else{
				output.rightToken = encapsular(token2);
				return 1;
			}
			break;
		}
		case 1:{
			string second = input.substr(1);
			int pos = token(-1,second,token2);
			if (pos<0) return pos;
			output.rightToken = encapsular(token2);
			return 1;
			}
			break;
		case 2:{
			string second = input.substr(1);
			int pos = token(-1,second,token2);
			if (pos<0) return pos;
			output.rightToken = encapsular(token2);
			return 2;
			}
			break;
		case 3:{
			string second = input.substr(2);
			int pos = token(-1,second,token2);
			if (pos<0) return pos;
			output.rightToken = encapsular(token2);
			return 3;
			}
			break;

	}
	return -4;
}



int parser::token(int pos, string& input, string& output) {
	int size = input.size();
	char sep='\0';
	if (pos != -1){
		sep = input[pos];
	}
	for (int i = pos + 1; i < size; i++) {
		if (input[i] == '\\') {
			if ( (i + 1) == size )return -2;
			if (input[i] == sep)i++;
			continue;
		}

		if (input[i] == sep) {
			output = input.substr(pos + 1, i - pos-1);
			return i+1;
		}
		if ((input[i] == '\'') || (input[i] == '"')) {
			if ((pos == -1) && (i > 0)) return -3; // Nos evitamos el caso en que paraezcan comillas en medio del token, es decir: Hola"amigo", esto se considera inválido.
			pos = token(i, input, output);
			if (pos < 0)return pos;
			return pos;
		}
		if ((input[i] == '.') && (pos == -1)) {
			if ( (i + 1) == size )continue;
			if (input[i+1] == '.'){
				output = input.substr(pos + 1, i - pos-1);
				return i;
			}
		}
	}

	if (pos == -1) {
		output = input.substr(pos + 1, size);
		return size;
	}

	return -1;
}


