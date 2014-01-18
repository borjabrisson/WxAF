
#ifndef mensajeriaCard_H_
#define mensajeriaCard_H_


#include "../../base/popup.h"

class mensajeriaCard : public  MyPopup
{
	
public:

	void createAction();
	void HandleEvent(string action);

	void readMode();
	void sendMode();
// 	int ChangeMode(bool lookup=false);

// 	virtual list<row_type> getLookupQuery(string action,map<string,string> &header);
// 	virtual void setValues(map<string,string> values);


};

#endif /* mensajeriaCard_H_ */
