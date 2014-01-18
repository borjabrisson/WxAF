// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html
#ifndef skeletonApp_H_
#define skeletonApp_H_

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

#include "../controladores/ctrBase.h"
#include "../controladores/Customcomunicate.h"
#include "../controladores/query.h"
#include "../conector/sgbd_conector.h"

#include <wx/datetime.h>
#include <wx/calctrl.h>


class skeletonApp : public wxApp
{
protected:
	string msgError; // Indica de donde procede el error para obtenerlo finalmente.

	ctrBase*	ctr;
	map<string,ctrBase*> ctrContainer;
	map<string,string> ctrVSpanel;
	sgbd_conector* conector; // ¿?
	
	virtual bool OnInit();

	#define setController(class,id) this->ctrContainer.insert(pair<string,ctrBase*>(id,new class));
	#define setControllerPage(idController,idPage) this->ctrVSpanel.insert(pair<string,string>(idPage,idController));

	
public:
	skeletonApp(){}
	~skeletonApp(){}
	
	virtual bool procedure(string bd,string procedure,list<string> values){return true;}
	virtual string getMsgError(string idFrame);
	
	virtual list<field_type> select(string idFrame,int type,map<string,string> filter);

	// 	virtual list<field_type>  select(string idFrame,query clause){return this->ctr->select(clause);}

	virtual bool sendAction(string idFrame,int action, map<string,string> data, map<string,string> key);
	virtual field_type filter(string idFrame,int type,map<string,string> &filter);
	string attr;

	virtual Customcomunicate sendAction(Customcomunicate block){
		Customcomunicate a;
		return a;
	}

	virtual void wakeUp(int action){}
};

#endif /* skeletonApp_H_ */
