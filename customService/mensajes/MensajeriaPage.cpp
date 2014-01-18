
#include "MensajeriaPage.h"


MensajeriaPage::MensajeriaPage(wxWindow *parent,string id) :panelGrid(parent,id){
	this->Init();
}


void MensajeriaPage::Reload(){

	this->grid->resetData();

	list<field_type> data = this->select(0,this->filter);
	this->grid->pushDataSet(data);
	list<field_type>::iterator it;
	int ind =0;
	for (it=data.begin(); it!=data.end(); ind++,it++){
		if ((*it)["state"] == "*"){
			this->grid->setColourRow(ind,wxColour(135,206,235)); //sky blue
		}
	}
}

void MensajeriaPage::OnLoad(){
// 	enum Calendar_ACT {ACT_newNote=321, ACT_editNote, ACT_delNote,ACT_addComment,ACT_editComment,ACT_delComment};

	this->addAction(ACT_newMessage, "Nuevo");
	this->addAction(ACT_Forwards, "Reenviar");
	this->addAction(ACT_Replay, "Responder");
	this->addAction(ACT_delMessage, "Eliminar");

	
}

void MensajeriaPage::actionsHandler(int action){
	switch (action){
		case ACT_newMessage:{
			mensajeriaCard* pop = new mensajeriaCard;
			pop->sendMode();
			pop->BuildPop(this);
			break;
		}
		case ACT_Forwards: // Reenviar
			if (checkSelectedRowsNumber()){
				wxArrayInt rows = this->grid->GetSelectedRows();
				this->curItem = this->grid->MygetRow(rows[0]);
				list<field_type> data= this->select(1,this->curItem);
				list<field_type>::iterator it = data.begin();
				this->curItem["content"]=(*it)["content"];
				this->curItem["subject"] = "Rnv:"+this->curItem["subject"];

				mensajeriaCard* pop = new mensajeriaCard;
				pop->sendMode();
				pop->BuildPop(this);
				pop->setValues(this->curItem);
			}
			break;
		case ACT_Replay:// Responder
			if (checkSelectedRowsNumber()){
				wxArrayInt rows = this->grid->GetSelectedRows();
				this->curItem = this->grid->MygetRow(rows[0]);

				mensajeriaCard* pop = new mensajeriaCard;
				pop->sendMode();
				pop->BuildPop(this);
				this->curItem["receiver"] = this->curItem["owner"];
				this->curItem["subject"] = "Res:"+this->curItem["subject"];
				pop->setValues(this->curItem);
			}
			break;
		case ACT_delMessage:
			if (checkSelectedRowsNumber()){
				wxArrayInt rows = this->grid->GetSelectedRows();
				this->curItem = this->grid->MygetRow(rows[0]);

				map<string,string> data;
				data["messageID"] = this->curItem["messageID"];
				this->completeActionsHandler(data);
			}
			break;
		case ACT_readMessage:
			if (checkSelectedRowsNumber()){
				wxArrayInt rows = this->grid->GetSelectedRows();
				this->curItem = this->grid->MygetRow(rows[0]);

				map<string,string> data;
				data["messageID"] = this->curItem["messageID"];
				data["notifyID"] = this->curItem["notifyID"];
				this->completeActionsHandler(data);

				list<field_type> selected= this->select(1,this->curItem);
				list<field_type>::iterator it = selected.begin();
				this->curItem["content"]=(*it)["content"];

				mensajeriaCard* pop = new mensajeriaCard;
				pop->readMode();
				pop->BuildPop(this);
				pop->setValues(this->curItem); // Indicar el modo(lectura)
			}
			break;
		default:
			cout << "default" << endl;
			break;
	}
	
}

void MensajeriaPage::OnLeftDbClick(wxGridEvent& event){
	this->curAction = ACT_readMessage;
	this->actionsHandler(this->curAction);
}

void MensajeriaPage::replayAction(string action,map<string,string>data){
	if ((action == "Reenviar") || (action == "Responder") ){
		if (action == "Reenviar")
			this->curAction = ACT_Forwards;
		else
			this->curAction = ACT_Replay;
		this->curItem = data;
		mensajeriaCard* pop = new mensajeriaCard;
		pop->sendMode();
		pop->BuildPop(this);
		pop->setValues(this->curItem);
	}
	else{
//		this->filter = data;
//		Reload();
		panelGrid::replayAction(action,data);
	}
}

void MensajeriaPage::buildQuery(){
// 	this->qry addField(string table, string field);
}

list<itemHeaderColumn> MensajeriaPage::headerGrid(){
	list<itemHeaderColumn> header;

	header.push_back(itemHeaderColumn("state",""));
	header.push_back(itemHeaderColumn("owner","De"));
	header.push_back(itemHeaderColumn("subject","Asunto"));
	header.push_back(itemHeaderColumn("messageID","ID"));
	header.push_back(itemHeaderColumn("notifyID","IDNoty"));
	return header;
}


void MensajeriaPage::OnFilter(){
	mensajeriaFilter* pop = new mensajeriaFilter;
	pop->BuildPop(this);
	pop->setValues(this->filter);
}


void MensajeriaPage::showList(Customcomunicate& block) {
}
