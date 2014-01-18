// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html

#ifndef PruebaPanel_H_
#define PruebaPanel_H_

#include "../base/panelGrid.h"
#include "facturaPop.h"

// #include "../controladores/query.h"

class pruebaPanel : public panelGrid
{
private:
	void buildQuery();
	void OnLoad();  // virtual y protected
	void completeActionsHandler(map<string,string>data);
	void actionsHandler(int action); // virtual y protected
	list<itemHeaderColumn> headerGrid();

	
public:
// 	query qry;
	pruebaPanel(wxWindow *parent,string id="prueba");
// 	void replayAction(string action,map<string,string>data);


};

#endif /* PruebaPanel_H_ */
