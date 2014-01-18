
#include "myCtr.h"


myCtr::myCtr() : ctrBase() {
}

myCtr::~myCtr(){
}


bool myCtr::sendAction(string idFrame,string action, map<string,string> data, map<string,string> key){
	push_Debug("myCtr::sendAction.# idFrame: "+idFrame+". Action: "+action);
	return this->conector->procedure("test","call prueba(\"121\",\"554\",\"0\");");
}