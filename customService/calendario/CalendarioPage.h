// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html

#ifndef CalendarioPage_H_
#define CalendarioPage_H_

#include "../../base/panelCalendar.h"
#include "CalendarioCard.h"

#include "events.h"
// #include "../../controladores/query.h"

class CalendarioPage : public panelCalendar
{
private:
	void buildQuery();
// 	void OnLoad();  // virtual y protected
// 	void OnAction(string action); // virtual y protected
// 	map<string,string> headerGrid();

	void loadNoteMark();
	void loadNoteList();
protected:
	void actionsHandler(int action);
 	void completeActionsHandler(map<string,string>data);
	void OnLoad();

// 	void OnSel_Changed(wxDateTime date);
	void OnDoubleClicked(wxDateTime date);

	void OnYear_Changed(wxDateTime date);
	void OnMonth_Changed(wxDateTime date);
	void OnDay_Changed(wxDateTime date);

	list<itemHeaderColumn> headerGrid();
	void showList(Customcomunicate& block);

// 	void completeActionsHandler(map<string,string>data);

// 	bool checkSelectedRowsNumber();

public:
// 	query qry;
	CalendarioPage(wxWindow *parent,string id="calendario");
	void Reload();
// 	void replayAction(string action,map<string,string>data);


};

#endif /* CalendarioPage_H_ */
