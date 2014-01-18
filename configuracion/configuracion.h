#ifndef CONFIG_H_
#define CONFIG_H_

#include <map>
#include <iostream>
#include <string>
#include <list>
#include <set>
#include <sstream>

#include "actions.h"

using namespace std;


#define ERROR_OUT
#define DEBUG_OUT

inline void push_Error(string msg){
	#ifdef ERROR_OUT
		cout << "ERROR: "<< msg << endl;
	#endif
}

inline void push_Debug(string msg){
	#ifdef DEBUG_OUT
		cout << "DEBUG: "<<msg << endl;
	#endif
}

inline void push_test(stringstream msg){
	#ifdef DEBUG_OUT
		cout << "DEBUG: "<<msg << endl;
	#endif
}

typedef struct structItemHeaderColumn{
	string fieldID;
	string description;
	structItemHeaderColumn(string field,string desc){fieldID=field;description=desc;}; // Declaración del constructor
}itemHeaderColumn;


#define SGBD_USER_DEFAULT ""
#define SGBD_PASS_DEFAULT ""
#define SGBD_HOST_DEFAULT "127.0.0.1"
#define SGBD_DB_DEFAULT "agosal2"

#define Enable_login 70000
#define Enable_autoRefresh 20000

#define strToint(str) (atoi(str.c_str()))

#define wxDateToString(date)  (date.FormatISODate()).utf8_str()

#define wxStringToStdString(WXstr)  WXstr.utf8_str()

#define StdStringTowxString(str)  wxString(str.c_str(), wxConvUTF8)

#define DIR_CERT "/etc/mysql/cert/ca-cert.pem"

#endif /* CONFIG_H_ */
