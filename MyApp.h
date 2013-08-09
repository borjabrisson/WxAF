// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html
#ifndef MyApp_H_
#define MyApp_H_


#include "base/baseApp.h"

#include "general/procedPanel.h"
#include "general/pruebaPanel.h"

#include "general/calendario/CalendarioPage.h"
#include "general/calendario/CalendarioCtr.h"

#include "general/mensajes/MensajeriaPage.h"
#include "general/mensajes/MensajeriaCtr.h"


#include "general/myCtr.h"

// http://docs.wxwidgets.org/trunk/classwx_list_ctrl.html
// http://docs.wxwidgets.org/trunk/classwx_list_box.html

class MyApp : public baseApp
{

protected:
	void createframeContainer();
	void loadControllers();

public:
	 void OnTimer(wxTimerEvent & event);
// 	 void wakeUp(int action);

};
DECLARE_APP(MyApp)

class MyFrame : public frameContainer
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
	void OnClick(wxCommandEvent& event);
	void buildFrame();
	

protected:
	procedPanel *panelito;

	MyPopup *popbox;
	void Init();
};

enum
{
    ID_Quit=1,
    ID_About,
	ID_Size
};

#endif /* MyApp_H_ */
