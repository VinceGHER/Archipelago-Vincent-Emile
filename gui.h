// Module Node (interface)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0 

#ifndef GUI_H
#define GUI_H

#include <gtkmm.h>

class HelloWorld : public Gtk::Window
{

public:
  HelloWorld();
  virtual ~HelloWorld();

protected:
  //Signal handlers:
  void on_button_clicked();

  //Member widgets:
  Gtk::Button m_button;
};

#endif // GTKMM_EXAMPLE_HELLOWORLD_H
