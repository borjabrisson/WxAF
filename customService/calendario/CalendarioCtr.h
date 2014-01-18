#ifndef CALENDARIO_CTR_H_
#define CALENDARIO_CTR_H_

#include "../../controladores/ctrBase.h"
#include "events.h"

class calendarioCtr: public ctrBase {
protected:

public:
	calendarioCtr();
	~calendarioCtr();
protected:
	Customcomunicate HandleQuery(Customcomunicate block);
	Customcomunicate HandleActions(Customcomunicate block);
	Customcomunicate HandleFilter(Customcomunicate block);
};

#endif /*CALENDARIO_CTR_H_ */
