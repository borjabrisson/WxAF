
#ifndef facturaPop_H_
#define facturaPop_H_


#include "../../base/popup.h"

class CalendarioCard : public  MyPopup
{
	
public:

	void createAction();
	void HandleEvent(string action);
// 	int ChangeMode(bool lookup=false);

// 	virtual list<row_type> getLookupQuery(string action,map<string,string> &header);
// 	virtual void setValues(map<string,string> values);


};

#endif /* facturaPop_H_ */
