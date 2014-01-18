#ifndef CONTACTOS_CTR_H_
#define CONTACTOS_CTR_H_

#include "../../controladores/ctrBase.h"
#include "events.h"

class ContactosCtr: public ctrBase {
protected:
	Customcomunicate HandleQuery(Customcomunicate block);
	Customcomunicate HandleActions(Customcomunicate block);
	Customcomunicate HandleFilter(Customcomunicate block);


	Customcomunicate HandleContactActions(Customcomunicate &block);
	Customcomunicate HandleCompanyActions(Customcomunicate &block);
	Customcomunicate HandleLawyerActions(Customcomunicate &block);
	Customcomunicate HandleAttorneyActions(Customcomunicate &block);

public:
	ContactosCtr();
	~ContactosCtr();

	virtual bool sendAction(string idFrame, int action,
			map<string, string> data, map<string, string> key); //{return false;}

};

#endif /*CONTACTOS_CTR_H_ */
