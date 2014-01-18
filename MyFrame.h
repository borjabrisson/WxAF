// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html
#ifndef MyFrame_H_
#define MyFrame_H_

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

#include "base/popup.h"
#include "MyApp.h"

#include <wx/datetime.h>
#include <wx/calctrl.h>
#include "frameContainer.h"


class MyFrame : public frameContainer
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
	void OnClick(wxCommandEvent& event);
	void buildFrame();
protected:
		
		wxToolBar* ToolBar1;
        wxNotebook* Notebook1;
        wxButton* Button1;
        wxPanel* Panel1;
//         MyGrid* Grid1;
        wxButton* Button2;
        wxMenu Menu3;
        wxStatusBar* StatusBar1;
		wxMenuBar* MenuBar1;

		wxMenuBar* menuBar;
		wxMenu *menuFile;

		ctrBase	ctr;
		procedPanel *panelito;

		baseApp* app;
		
		
		MyPopup *popbox;
};

enum
{
    ID_Quit=1,
    ID_About,
	ID_Size
};

#endif /* MyFrame_H_ */
