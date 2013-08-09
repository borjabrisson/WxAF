#include "skeletonApp.h"

bool skeletonApp::OnInit(){return true;}


// void skeletonApp::Login(){}
// 
// 
// void skeletonApp::AceptLogin(wxCommandEvent& WXUNUSED(event)){}
// 
// void skeletonApp::CancelLogin(wxCommandEvent& WXUNUSED(event)){}

bool skeletonApp::sendAction(string idFrame,int action, map<string,string> data, map<string,string> key){
	return true;
}

string skeletonApp::getMsgError(string idFrame){
	return this->ctr->getMsgError();
}

list<field_type> skeletonApp::select(string idFrame,int type,map<string,string> filter){
	list<field_type> data;
	return data;
}