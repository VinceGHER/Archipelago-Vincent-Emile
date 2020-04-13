// Projet (fichier maitre)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0

#include <iostream>
#include <vector>
#include <gtkmm.h>

#include "city.h"
#include "gui.h"

using namespace std;

int main(int argc, char * argv[]){

	if(argc == 2) City::readFile(argv[1]);

	int argcFake (1);
	auto app = Gtk::Application::create(argcFake, argv, "org.gtkmm.example");

	Frame wd = {-2000,2000,-2000,2000};
	wd.ratio = (wd.xmax-wd.xmin)/(wd.ymax-wd.ymin);

	wd.height = 720;
	wd.width = wd.height*wd.ratio;

	Gtk::Window win;
	win.set_title("DrawingArea");
	win.set_default_size(wd.width, wd.height);

	MyArea area(wd);
	win.add(area);
	area.show();

	return app->run(win);

}
