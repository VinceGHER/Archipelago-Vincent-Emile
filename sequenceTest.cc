#include <iostream>
#include <string>
#include "tools.h"
#include "node.h"
#include "city.h"

#include "graphic.h"
#include "gui.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

using namespace std;
int main(int argc, char** argv){
     cout << "----------------------" << endl;
     cout << "Test erreur numero 1" << endl;
     City::readFile("./fichiersTest/final_tests/e01.txt");
     cout << "----------------------" << endl;
     cout << endl;
     cout << "----------------------" << endl;
     cout << "Test erreur numero 2" << endl;
     City::readFile("./fichiersTest/final_tests/e02.txt");
     cout << "----------------------" << endl;
     cout << endl;
     cout << "----------------------" << endl;
     cout << "Test erreur numero 3" << endl;
     City::readFile("./fichiersTest/final_tests/e03.txt");
     cout << "----------------------" << endl;
     cout << endl;
     cout << "----------------------" << endl;
     cout << "Test erreur numero 4" << endl;
     City::readFile("./fichiersTest/final_tests/e04.txt");
     cout << "----------------------" << endl;
     cout << endl;
     cout << "----------------------" << endl;
     cout << "Test erreur numero 5" << endl;
     City::readFile("./fichiersTest/final_tests/e05.txt");
     cout << "----------------------" << endl;
     cout << endl;
     cout << "----------------------" << endl;
     cout << "Test erreur numero 6" << endl;
     City::readFile("./fichiersTest/final_tests/e06.txt");
     cout << "----------------------" << endl;
     cout << endl;
     cout << "----------------------" << endl;
     cout << "Test erreur numero 7" << endl;
     City::readFile("./fichiersTest/final_tests/e07.txt");
     cout << "----------------------" << endl;
     cout << endl;
     cout << "----------------------" << endl;
     cout << "Test erreur numero 8" << endl;
     City::readFile("./fichiersTest/final_tests/e08.txt");
     cout << "----------------------" << endl;
     cout << endl;
     cout << "----------------------" << endl;
     cout << "Test erreur numero 9" << endl;
     City::readFile("./fichiersTest/final_tests/e09.txt");
     cout << "----------------------" << endl;
     cout << endl;
     cout << "----------------------" << endl;
     cout << "Test erreur numero 10" << endl;
     City::readFile("./fichiersTest/final_tests/e10.txt");
     cout << "----------------------" << endl;
     cout << "Test erreur numero 11" << endl;
     City::readFile("./fichiersTest/final_tests/s01.txt");
     cout << "----------------------" << endl;
     cout << endl;
     cout << "----------------------" << endl;
     cout << "Test erreur numero 12" << endl;
     City::readFile("./fichiersTest/final_tests/s02.txt");
     cout << "----------------------" << endl;
     cout << endl;
     cout << "----------------------" << endl;
     cout << "Test erreur numero 13" << endl;
     City::readFile("./fichiersTest/final_tests/s03.txt");
     cout << "----------------------" << endl;
     cout << endl;
     cout << "----------------------" << endl;
     cout << "Test erreur numero 14" << endl;
     City::readFile("./fichiersTest/final_tests/s04.txt");
     cout << "----------------------" << endl;
     cout << endl;
     cout << "----------------------" << endl;
     cout << "Test erreur numero 15" << endl;
     City::readFile("./fichiersTest/final_tests/s05.txt");
     cout << "----------------------" << endl; 
     cout << "Test erreur numero 16" << endl;
     City::readFile("./fichiersTest/final_tests/s06.txt");
     cout << "----------------------" << endl;
     cout << endl;
     cout << "----------------------" << endl;
     cout << "Test erreur numero 17" << endl;
     City::readFile("./fichiersTest/final_tests/s07.txt");
     cout << "----------------------" << endl;
     cout << endl;
     cout << "----------------------" << endl;
     cout << "Test erreur numero 18" << endl;
     City::readFile("./fichiersTest/final_tests/success.txt");
     cout << "----------------------" << endl;
     cout << endl;
     cout << "----------------------" << endl;
     cout << "Test erreur numero 19" << endl;
     City::readFile("./fichiersTest/final_tests/e05-2.txt");
     cout << "----------------------" << endl;
     cout << endl;
     cout << "----------------------" << endl;
     cout << "Test erreur numero 20" << endl;
     City::readFile("./fichiersTest/final_tests/e06-2.txt");
     cout << "----------------------" << endl;
    // if(argc == 2) City::readFile(argv[1]);

    // Frame wd = {-1000,1000,-1000,1000};
    // wd.ratio = (wd.xmax-wd.xmin)/(wd.ymax-wd.ymin);

    // wd.height = 720;
    // wd.width = wd.height*wd.ratio;
    // int argc1 (1);
    // auto app = Gtk::Application::create(argc1, argv, "org.gtkmm.example");

    // Gtk::Window win;
    // win.set_title("DrawingArea");
    // win.set_default_size(wd.width, wd.height);

    // MyArea area(wd);
    // win.add(area);
    // area.show();

    // return app->run(win);

};