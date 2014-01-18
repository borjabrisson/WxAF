#ifndef ContactosEvents_H_
#define ContactosEvents_H_

enum ACT_Contactos{
	ACT_changeTypeContact=510,
	ACT_newContact,
	ACT_editContact,
	ACT_deleteContact,
	ACT_viewContact,
	ACT_newPhone,
	ACT_editPhone,
	ACT_deletePhone
};

enum TYPE_Contactos{
	type_Empresas=0,
	type_Clientes,
	type_Abogados,
	type_Procuradores
};


#endif /* ContactosEvents_H_ */
