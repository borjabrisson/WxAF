
#ifndef PeopleContactCard_H_
#define PeopleContactCard_H_


#include "../../base/popup.h"
#include "events.h"

class PeopleContactCard : public  MyPopup
{
protected:
	int type;
public:
	PeopleContactCard();
	PeopleContactCard(int type);
	void createAction();
	void HandleEvent(string action);

	void readMode();
	void sendMode();
// 	int ChangeMode(bool lookup=false);

// 	virtual list<row_type> getLookupQuery(string action,map<string,string> &header);
// 	virtual void setValues(map<string,string> values);


};

#endif /* PeopleContactCard_H_ */
