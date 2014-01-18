
#ifndef CompanyContactCard_H_
#define CompanyContactCard_H_


#include "../../base/popup.h"

class CompanyContactCard : public  MyPopup
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

#endif /* CompanyContactCard_H_ */
