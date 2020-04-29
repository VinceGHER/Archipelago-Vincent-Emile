// Projet (fichier maitre)
// made by Vincent GHEROLD and Emile CAILLOL
// Version 2.1
// Architecture b1

#include <iostream>
#include <vector>
#include <gtkmm.h>
#include <string>

#include "city.h"
#include "gui.h"
#include "constantes.h"

using namespace std;
 

int main(int argc, char * argv[]){
	
	if(argc == 2){
		string filename(argv[1]);
		City::readFile(filename);
	}
	int argcFake(1);
	auto app = Gtk::Application::create(argcFake, argv, "org.gtkmm.example");
	
	Gui eventWindow;
	eventWindow.set_title("Archipelago Vincent-Emile");
	eventWindow.set_default_size(900, 900);
	
   return app->run(eventWindow);
	
}
