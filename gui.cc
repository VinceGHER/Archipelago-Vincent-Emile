// Module Node (interface)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0 

#include <iostream>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm.h>

#include "gui.h"

using namespace std;

Gui::Gui(){
	//~ auto app = Gtk::Application::create();
	//~ m_Box_Top(Gtk::ORIENTATION_VERTICAL);
	//~ m_Box_General(Gtk::ORIENTATION_VERTICAL);
	
	//~ m_Button_Exit("Hello");
	//~ m_Button_New("Bonjour");
	//~ m_Button_Open("Monsieur");
	//~ m_Button_Save("Madame");
}
	
void Gui::on_button_clicked()
{
	cout << "Hello World" << endl;
}

Gui::~Gui()
{
}

//~ return app->run();
