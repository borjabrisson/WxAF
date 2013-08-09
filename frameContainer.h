// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html
#ifndef frameContainer_H_
#define frameContainer_H_

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
#include <wx/popupwin.h>
#include <wx/filedlg.h>
#include <wx/textdlg.h>
#include <wx/dialog.h>

#include <wx/gbsizer.h>

#include "base/mypanel.h"
// #include "base/baseApp.h"

class frameContainer : public wxFrame
{
public:
    frameContainer(const wxString& title, const wxPoint& pos, const wxSize& size);
    virtual void OnQuit(wxCommandEvent& event){}
    virtual void OnAbout(wxCommandEvent& event){}
	virtual void OnClick(wxCommandEvent& event){}
	virtual void buildFrame(){}
	virtual void RefreshData();

protected:
	map<string,myPanel*> contenedor;
	skeletonApp* app;
	wxNotebook* note;

	void addPage(string id,string tab, myPanel *page);
	virtual void Init();


// 	wxToolBar* ToolBar1;
// 	wxStatusBar* StatusBar1;

	wxMenuBar* menuBar;

	#define setPage(class,id,caption) this->addPage(id,caption,new class(this->note,id));

};


#endif /* frameContainer_H_ */
