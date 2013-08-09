// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html

#ifndef PANEL_BASE_GRID_H_
#define PANEL_BASE_GRID_H_

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/string.h>
#include <wx/object.h> 
#include <wx/gbsizer.h>

#include <map>
#include <iostream>
#include <string>
#include <list>

// #include "popup.h"
#include "mypanel.h"
#include "mygrid.h"

// #include "../controladores/query.h"

using namespace std;

enum PanelGridEventTypes // Panel Calendar Types.
{
	EVT_GRID_CELL_LEFT_CLICK=10208,
	EVT_GRID_CELL_RIGHT_CLICK ,
	EVT_GRID_CELL_LEFT_DCLICK,
	EVT_GRID_CELL_RIGHT_DCLICK,
	EVT_GRID_COL_MOVE=10219
};

class panelBaseGrid : public myPanel
{
private:
	void handleGridEvent(wxGridEvent& event);
protected:
	MyGrid* grid;
	void setGridEvent(MyGrid *grid);

	virtual void OnLeftClick(wxGridEvent& event);
	virtual void OnRightClick(wxGridEvent& event){}
	virtual void OnRightDbClick(wxGridEvent& event){}
	virtual void OnLeftDbClick(wxGridEvent& event){}

	virtual void OnColumnMove(wxGridEvent& event){}
	virtual list<itemHeaderColumn> headerGrid();

	virtual bool checkSelectedRowsNumber();
	
public:
	panelBaseGrid(wxWindow *parent, string id="customer");
};

#endif /* PANEL_BASE_GRID_H_ */
