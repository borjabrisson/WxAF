/*
 * basePanel.h
 *
 *  Created on: 14/11/2013
 *      Author: borja
 */
#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/string.h>
#include <wx/object.h>
#include <wx/gbsizer.h>
#include <wx/control.h>

// #include "popup.h"
#include "skeletonApp.h"
#include "../controladores/Customcomunicate.h"

// #include "../MyApp.h"
#include "../controladores/query.h"
#include "sysEvent.h"

#include <map>
#include <iostream>
#include <string>
#include <list>
using namespace std;

#ifndef BASEPANEL_H_
#define BASEPANEL_H_

class basePanel : public wxPanel {
protected:
	string id;

public:
	skeletonApp *app;  // es necesario que sea publica para su uso en los popUp (de momento)
	basePanel(wxWindow *parent,string id="main");

	// Le atribuye al panel la aplicación gestora.
	void setApp(skeletonApp *app);
protected:

	Customcomunicate sendAction2(int action);
	Customcomunicate sendAction2(int action,map<string,string> *data);
	Customcomunicate sendAction(int action,int subType,map<string,string> *data);

	Customcomunicate sendQuery(int action);
	Customcomunicate sendQuery(int action,map<string,string> *data);
	Customcomunicate sendQuery(int action,int subType,map<string,string> *data);

	Customcomunicate sendFilter(int action);
	Customcomunicate sendFilter(int action,map<string,string> *data);
	Customcomunicate sendFilter(int action,int subType,map<string,string> *data);

	Customcomunicate createMsgblock(int type,int action,int subType,map<string,string> *data,list<field_type> *dataset);
	// handleMessage
	virtual void handleMessage(Customcomunicate &block);


/* #############################################################################################################################
 *  											Aciones Base del sistema.
 * #############################################################################################################################*/

	virtual void actionDeny(Customcomunicate &block);
	virtual void actionOK(Customcomunicate &block);
	virtual void showList(Customcomunicate &block);
	virtual void showMessege(Customcomunicate &block);
};

#endif /* BASEPANEL_H_ */
