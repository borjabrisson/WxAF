// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html
#ifndef baseApp_H_
#define baseApp_H_

#include "skeletonApp.h"
#include "../frameContainer.h"

#include "popup.h"

#include "panelCustomer.h"
#include "panelCalendar.h"

#include "../configuracion/configuracion.h"
#include "timer.h"


class baseApp : public skeletonApp
{
protected:
	frameContainer *frame;
	
	wxTextCtrl *userInput;
	wxTextCtrl *passInput;
	wxDialog *popLogin;

	timer* time;
	timer* autoRefresh;
		
	virtual bool OnInit();
	void Login();

	virtual void AceptLogin(wxCommandEvent& WXUNUSED(event));
	virtual void CancelLogin(wxCommandEvent& WXUNUSED(event));


	virtual void createframeContainer(){}
	virtual void loadControllers(){}

public:
	baseApp(){}
	~baseApp(){}
	
// 	bool procedure(string bd,string procedure,list<string> values);
	string getMsgError(string idFrame);
	
	virtual list<field_type> select(string idFrame,int type,map<string,string> filter);
// 	virtual list<field_type>  select(string idFrame,query clause){return this->ctr->select(clause);}


	bool sendAction(string idFrame,int action, map<string,string> data, map<string,string> key);
	map<string,string> filter(string idFrame,int type,map<string,string> &filter);

	Customcomunicate sendAction(Customcomunicate block);

	virtual void wakeUp(int action);
};
#endif /* baseApp_H_ */
