#ifndef MYCTR_H_
#define MYCTR_H_

#include "../controladores/ctrBase.h"

class myCtr: public ctrBase {
protected:

public:
	myCtr();
	~myCtr();

	virtual bool sendAction(string idFrame,string action, map<string,string> data, map<string,string> key);//{return false;}
};

#endif /* MYCTR_H_ */
