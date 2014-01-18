/*
 * basePanel.cpp
 *
 *  Created on: 14/11/2013
 *      Author: borja
 */

#include "basePanel.h"

basePanel::basePanel(wxWindow *parent, string id) :
		wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize) {
	this->id = id;
// 	&this->app =  wxGetApp();
}

void basePanel::setApp(skeletonApp *app) {
	this->app = app;
}

Customcomunicate basePanel::sendAction2(int action) {
	return this->app->sendAction(
			createMsgblock(BKCM_Action, action, -1, NULL, NULL));
}

Customcomunicate basePanel::sendAction2(int action, map<string, string> *data) {
	return this->app->sendAction(
			createMsgblock(BKCM_Action, action, -1, data, NULL));
}

Customcomunicate basePanel::sendAction(int action, int subType,
		map<string, string> *data) {
	return this->app->sendAction(
			createMsgblock(BKCM_Action, action, subType, data, NULL));

}

Customcomunicate basePanel::sendQuery(int action) {
	return this->app->sendAction(
			createMsgblock(BKCM_Query, action, -1, NULL, NULL));
}

Customcomunicate basePanel::sendQuery(int action, map<string, string> *data) {
	return this->app->sendAction(
			createMsgblock(BKCM_Query, action, -1, data, NULL));
}

Customcomunicate basePanel::sendQuery(int action, int subType,
		map<string, string> *data) {
	return this->app->sendAction(
			createMsgblock(BKCM_Query, action, subType, data, NULL));
}

Customcomunicate basePanel::sendFilter(int action) {
	return this->app->sendAction(
			createMsgblock(BKCM_Filter, action, -1, NULL, NULL));
}

Customcomunicate basePanel::sendFilter(int action, map<string, string> *data) {
	return this->app->sendAction(
			createMsgblock(BKCM_Filter, action, -1, data, NULL));
}

Customcomunicate basePanel::sendFilter(int action, int subType,
		map<string, string> *data) {
	return this->app->sendAction(
			createMsgblock(BKCM_Filter, action, subType, data, NULL));
}

Customcomunicate basePanel::createMsgblock(int type, int action, int subType,
		map<string, string>* data, list<field_type>* dataset) {
	Customcomunicate obj;
	obj.panelID = this->id;
	obj.type = type;	obj.actionID = action;
	obj.data = data;	obj.dataset = dataset;

	return obj;
}

void basePanel::handleMessage(Customcomunicate &block) {
	switch (block.actionID) {
	case C2V_showList:
		this->showList(block);
		break;
	case C2V_showMsg:
		showMessege(block);
		break;
	case C2V_actionOK:
		actionOK(block);
		break;
	case C2V_actionDeny:
		actionDeny(block);
		break;
	}
	if (block.data != NULL)
		delete block.data;
	if (block.dataset != NULL)
		delete block.dataset;

}

void basePanel::actionDeny(Customcomunicate& block) {
}

void basePanel::actionOK(Customcomunicate& block) {
}

void basePanel::showList(Customcomunicate& block) {
}

void basePanel::showMessege(Customcomunicate& block) {
}


