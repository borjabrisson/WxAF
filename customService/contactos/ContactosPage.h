// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html

#ifndef ContactosPage_H_
#define ContactosPage_H_

#include "../../base/panelGrid.h"
#include "PeopleContactCard.h"
#include "CompanyContactCard.h"
#include "events.h"
#include <wx/choice.h>


// #include "../controladores/query.h"

class ContactosPage : public panelGrid
{
private:
	int lastItemSelected;
	wxChoice *choice;
	void buildQuery();

	void loadMessageList();
	void OnClickChoiseItem(wxCommandEvent& event);
protected:
	void actionsHandler(int action);
// 	void completeActionsHandler(map<string,string>data);
	void OnLoad();

	list<itemHeaderColumn> headerGrid();
	void OnLeftDbClick(wxGridEvent& event);

	list<itemHeaderColumn> getHeaderGrid();
	void showList(Customcomunicate &block);

public:
// 	query qry;
	ContactosPage(wxWindow *parent,string id="mensajeria");
	void Reload();
	//void replayAction(string action,map<string,string>data);

	void OnFilter();


};

#endif /* ContactosPage_H_ */
