// Projet (fichier maitre)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0

#include <iostream>
#include <vector>
#include <gtkmm.h>

#include "city.h"
#include "gui.h"

using namespace std;
 

	#include "constantes.h"

int main(int argc, char * argv[]){

	if(argc == 2) City::readFile(argv[1]);
	/// temporaire ce qui suit
	int argcFake (1);
	auto app_gui = Gtk::Application::create(argcFake, argv, "org.gtkmm.example_gui");

	Gui eventWindow;
	eventWindow.set_default_size(900, 900);
	//eventWindow.set_resizable(false);

   return app_gui->run(eventWindow);
	
}
