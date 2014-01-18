// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html

#ifndef MensajeriaPage_H_
#define MensajeriaPage_H_

#include "../../base/panelGrid.h"
#include "MensajeriaCard.h"
#include "MensajeriaFilter.h"
#include "events.h"


// #include "../controladores/query.h"

class MensajeriaPage : public panelGrid
{
private:
	void buildQuery();

	void loadMessageList();
protected:
	void actionsHandler(int action);
// 	void completeActionsHandler(map<string,string>data);
	void OnLoad();

	list<itemHeaderColumn> headerGrid();
	void OnLeftDbClick(wxGridEvent& event);

	void showList(Customcomunicate& block);

public:
// 	query qry;
	MensajeriaPage(wxWindow *parent,string id="mensajeria");
	void Reload();
	void replayAction(string action,map<string,string>data);

	void OnFilter();


};

#endif /* MensajeriaPage_H_ */
