// Module Node (interface)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0 

#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <gtkmm.h>

class Gui : public Gtk::Window
{

public:
	Gui();
	virtual ~Gui();

protected:
	void on_button_clicked();
	
	Gtk::Box m_Box_Top, m_Box_General;
	
	Gtk::Button m_Button_Exit;
	Gtk::Button m_Button_New;
	Gtk::Button m_Button_Open;
	Gtk::Button m_Button_Save;
};

#endif // GTKMM_EXAMPLE_HELLOWORLD_H
