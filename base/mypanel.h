// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html

#ifndef MY_PANEL_H_
#define MY_PANEL_H_

#include "basePanel.h"

typedef  map<string,string> temp;

class myPanel : public basePanel
{
	
protected: // atributos de la clase
	wxGridBagSizer* gridBagSizer;
	wxGridBagSizer* actionBag;	
	map<string,string> curItem;
	map<string,string> filter;

	query qry;

	int curAction;
	
	map<int, int> actions;
	map<int, wxControl *> buttons;
protected:
	// Genera todas las estruturas necesarias para la correcta construcción del panel. Utiliza las distitnas funciones virtuales de configuración para recrear  el panel personalizado-
	virtual void Init();
	
	// Añade una nueva acción a la lista, indicando su identificador y el título a mostrar.
	void addAction(int id, string caption);
	void addAction(int id,wxControl  *obj);
	
	virtual void buildQuery();//{} Esta función será implementada en la clase final a utilizar, realizando la inicialización de la query a realizar.
	virtual void OnLoad();  //{} Realizará la definición de acciones del panel e inicialización de los distintos atributos o variables necesarios.
	virtual void BuildPage();//{} Función virtual utilizada por las distintas clases heredadas para la construcción del panel/pagina

	// Cada clase final deberá implementar su propio manejador de eventos, indicando que evento fue lanzado a través de su código. Estas acciones corresponden a las definidas por el usuario mediante
	// el uso de la función addAction.
	virtual void actionsHandler(int action); //{}

	// Será llamada por la ficha (popUp) responsable de obtener todos los datos necesarios para la realización de la acción. Solo será llamada cuando la tarea sea confirmada ( a realizar).
	// El usuario dispondrá de los datos insertamos mediante el parámetro data. Además el atributo curAction indicará a que acción le corresponden.
	virtual void completeActionsHandler(map<string,string>data); //{}
	
	void select(query);

	virtual list<temp> select(int type,map<string,string> filter);//{list<temp> a; return a;}
	bool procedure(string bd,string procedure,list<string> values);

	
	bool sendAction(int action, map<string,string> data,map<string,string> key);

	map<string,string> getFilter();
	void setFilter(map<string,string> &data);

	// Mostrará un diálogo con el mensaje y cabecera indicados.
	void showMessage(string msg,string header="Atención");

	// Devuelve el mensaje obtenido tras la ejecución de la sentencia SQL.
	string getMsgError();

	virtual wxGridBagSizer* buildActionSizer();

public:
	// Lleva a cabo la actualización de los datos del panel. Si el usuario desea hacer uso de la conexión al SGBD deberá realizar aqui las consultas necesarias y todas las
	// comprobaciones relacionadas.
	virtual void Reload();

	myPanel(wxWindow *parent,string id="main");

	// Hace de comunicación entre el popUp lanzado y el panel pader. Indica si la acción fue validada o cancelada. En el caso de ser aceptada se adjuntan los datos insertados.
	virtual void replayAction(string action,map<string,string>data);

	virtual void OnFilter(){
		this->curAction = SEvt_Filter;
	}
private:
	// función auziliar del sistema utilizada para capturar y redirigir los eventos de las acciones definidas.
	void OnClickActionButton(wxCommandEvent& event);

};

#endif /* MY_PANEL_H_ */
