
#ifndef mensajeriaFilter_H_
#define mensajeriaFilter_H_


#include "../../base/popup.h"

class mensajeriaFilter : public  MyPopup
{
	
public:

	void createAction();
	void HandleEvent(string action);

// 	int ChangeMode(bool lookup=false);

// 	virtual list<row_type> getLookupQuery(string action,map<string,string> &header);
// 	virtual void setValues(map<string,string> values);


};

#endif /* mensajeriaFilter_H_ */
