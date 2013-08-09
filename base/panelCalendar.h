// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html

#ifndef PANEL_CALENDAR_H_
#define PANEL_CALENDAR_H_

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/string.h>
#include <wx/object.h> 
#include <wx/gbsizer.h>

#include <wx/datetime.h>
#include <wx/calctrl.h>
#include <wx/datectrl.h>
#include <wx/event.h>
#include <wx/listctrl.h>


#include <map>
#include <iostream>
#include <string>
#include <list>

// #include "popup.h"
#include "panelBaseGrid.h"
#include "mygrid.h"

// #include "../controladores/query.h"

using namespace std;

// enum PnlCalendarTypes { CHANGE_DAY, CHAMGE_MONTH ,CHANGE_YEAR}; // Panel Calendar Types.


enum PnlCalendarTypes // Panel Calendar Types.
{
	EVT_SEL_CHANGED=10201, 
	EVT_DAY_CHANGED ,
	EVT_MONTH_CHANGED,
	EVT_YEAR_CHANGED,
	EVT_DOUBLECLICKED,
	EVT_WEEKDAY_CLICKED		
};


class panelCalendar : public panelBaseGrid
{
private:

	#define STYLE_CLEAR_NOTE new wxCalendarDateAttr( wxCAL_BORDER_NONE,wxNullColour)
	#define STYLE_ADD_NOTE new wxCalendarDateAttr( wxCAL_BORDER_ROUND,wxColour( _T( "blue" ) ))

	#define STYLE_HOLIDAYS new wxCalendarDateAttr( wxColour(_T("red")), wxColour(_T("white")) )

// 	#define strToint(str) (atoi(str.c_str()))

	void handleCalendarEvent(wxCalendarEvent& event);
	
	void loadCalendarConfig();

	void BuildPage();

protected:
	wxDateTime curDate;
	
	wxCalendarCtrl* calendar;
	MyGrid* noteList;
	wxDatePickerCtrl* picker;
	
	virtual void Init();
	void setCalendarEvent(wxCalendarCtrl *calendar);

// Calendar Event Handler
	
	virtual void OnWeekday_Clicked(wxDateTime date){}
	virtual void OnSel_Changed(wxDateTime date){}
	virtual void OnDoubleClicked(wxDateTime date){}

	virtual void OnYear_Changed(wxDateTime date){}
	virtual void OnMonth_Changed(wxDateTime date){}
	virtual void OnDay_Changed(wxDateTime date){}


	void setDate(wxDateTime date);
	void setDate(unsigned short day,unsigned short month,unsigned short year);

	void clearNotes();

	void addNotes(int day);
	
	
public:
	panelCalendar(wxWindow *parent, string id="calendar");
	~panelCalendar();
	void weekChange(wxCalendarEvent& event);
};

#endif /* PANEL_CALENDAR_H_ */
