#ifndef MENSAJERIA_CTR_H_
#define MENSAJERIA_CTR_H_

#include "../../controladores/ctrBase.h"
#include "events.h"

class MensajeriaCtr: public ctrBase {
protected:

public:
	MensajeriaCtr();
	~MensajeriaCtr();

	list<field_type> select(string idFrame, int type,
			map<string, string> filter);
	list<field_type> select(query clause);
	virtual bool sendAction(string idFrame, int action,
			map<string, string> data, map<string, string> key); //{return false;}
protected:
	Customcomunicate HandleQuery(Customcomunicate block);
	Customcomunicate HandleActions(Customcomunicate block);
	Customcomunicate HandleFilter(Customcomunicate block);
};

#endif /*MENSAJERIA_CTR_H_ */
