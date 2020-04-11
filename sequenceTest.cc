#include <iostream>
#include <string>
#include "tools.h"
#include "node.h"
#include "city.h"

#include "graphic.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

using namespace std;
int main(int argc, char** argv){
    //  cout << "----------------------" << endl;
    //  cout << "Test erreur numero 1" << endl;
    //  City::readFile("./fichiersTest/error/e01.txt");
    //  cout << "----------------------" << endl;
    //  cout << endl;
    //  cout << "----------------------" << endl;
    //  cout << "Test erreur numero 2" << endl;
    //  City::readFile("./fichiersTest/error/e02.txt");
    //  cout << "----------------------" << endl;
    //  cout << endl;
    //  cout << "----------------------" << endl;
    //  cout << "Test erreur numero 3" << endl;
    //  City::readFile("./fichiersTest/error/e03.txt");
    //  cout << "----------------------" << endl;
    //  cout << endl;
    //  cout << "----------------------" << endl;
    //  cout << "Test erreur numero 4" << endl;
    //  City::readFile("./fichiersTest/error/e04.txt");
    //  cout << "----------------------" << endl;
    //  cout << endl;
    //  cout << "----------------------" << endl;
    //  cout << "Test erreur numero 5" << endl;
    //  City::readFile("./fichiersTest/error/e05.txt");
    //  cout << "----------------------" << endl;
    //  cout << endl;
    //  cout << "----------------------" << endl;
    //  cout << "Test erreur numero 6" << endl;
    //  City::readFile("./fichiersTest/error/e06.txt");
    //  cout << "----------------------" << endl;
    //  cout << endl;
    //  cout << "----------------------" << endl;
    //  cout << "Test erreur numero 7" << endl;
    //  City::readFile("./fichiersTest/error/e07.txt");
    //  cout << "----------------------" << endl;
    //  cout << endl;
    //  cout << "----------------------" << endl;
    //  cout << "Test erreur numero 8" << endl;
    //  City::readFile("./fichiersTest/error/e08.txt");
    //  cout << "----------------------" << endl;
    //  cout << endl;
    //  cout << "----------------------" << endl;
    //  cout << "Test erreur numero 9" << endl;
    //  City::readFile("./fichiersTest/error/e09.txt");
    //  cout << "----------------------" << endl;
    //  cout << endl;
    //  cout << "----------------------" << endl;
    //  cout << "Test erreur numero 10" << endl;
    //  City::readFile("./fichiersTest/error/e10.txt");
    //  cout << "----------------------" << endl;

    Frame wd = {-10,10,-10,10};
    wd.ratio = (wd.xmax-wd.xmin)/(wd.ymax-wd.ymin);

    wd.height = 720;
    wd.width = wd.height*wd.ratio;
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    Gtk::Window win;
    win.set_title("DrawingArea");
    win.set_default_size(wd.width, wd.height);

    Graphic area;
    area.setFrame(wd);
    win.add(area);
    area.show();
    return app->run(win);

};