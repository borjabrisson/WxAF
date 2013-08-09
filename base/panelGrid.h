// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html

#ifndef PANEL_GRID_H_
#define PANEL_GRID_H_

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
#include "panelBaseGrid.h"
#include "mygrid.h"

// #include "../controladores/query.h"

using namespace std;

class panelGrid : public panelBaseGrid
{
private:
	void BuildPage();
	
public:
	virtual void Reload();
// 	MyGrid* grid;
	panelGrid(wxWindow *parent, string id="grid");
};

#endif /* PANEL_GRID_H_ */
