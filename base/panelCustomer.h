// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html

#ifndef PANEL_CUSTOMER_H_
#define PANEL_CUSTOMER_H_

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

class panelCustomer : public myPanel
{
private:
	void BuildPage();
protected:
	wxGridBagSizer* customerBag;	

public:
	panelCustomer(wxWindow *parent, string id="customer");
};

#endif /* PANEL_CUSTOMER_H_ */
