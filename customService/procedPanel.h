// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html

#ifndef Proc_PANEL_H_
#define Proc_PANEL_H_

#include "../base/panelGrid.h"
#include "../base/popup.h"


class procedPanel : public panelGrid
{
private:
	void buildQuery();
	void OnLoad();  // virtual y protected
	
	void actionsHandler(int action); // virtual y protected
	void completeActionsHandler(map<string,string>data);
	
	list<itemHeaderColumn> headerGrid();

	
public:
// 	query qry;
	procedPanel(wxWindow *parent,string id="proced");
// 	void replayAction(string action,map<string,string>data);


};

#endif /* Proc_PANEL_H_ */
