// Module Node (interface)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0 

#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <gtkmm.h>

// #include <gtkmm/drawingarea.h>
// #include <gtkmm/button.h>
#include "graphic_gui.h"

class MyArea : public Gtk::DrawingArea {
public:
  MyArea();
  void setFrame(Frame x);
  virtual ~MyArea();

protected:
  //Override default signal handler:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};

class Gui : public Gtk::Window {
public:
	Gui();
	virtual ~Gui();

protected:
	void on_button_clicked();
	
	Gtk:: Box m_Box;
	Gtk:: Box m_Box_Buttons;
	Gtk:: Box m_Box_Drawing;
	Gtk:: Box m_Box_General;
	
	Gtk::Frame m_Frame_General;

	Gtk::Button m_Button_Exit;
	Gtk::Button m_Button_New;
	Gtk::Button m_Button_Open;
	Gtk::Button m_Button_Save;

	

	MyArea m_Area;
	
	
private:
	void draw();
};

#endif // GTKMM_EXAMPLE_HELLOWORLD_H
