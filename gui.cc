// Module Node (interface)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0 

#include <iostream>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm.h>

#include "gui.h"
#include "graphic_gui.h"
#include "city.h"

using namespace std;

Gui::Gui(){
	m_Box_General(Gtk::ORIENTATION_VERTICAL);
	
    Gtk::Button m_Button_Exit("Exit");
    Gtk::Button m_Button_New("New");
    Gtk::Button m_Button_Open("Open");
    Gtk::Button m_Button_Save("Save");
    
	set_title("Drawing Area and Buttons");
	set_border_width(0);
  
	add(m_Box);
	
	m_Box.pack_start(m_Box_General);
	m_Box.pack_start(m_Box_General);

	//~ m_Area.set_size_request(200,200);
	//~ m_Box_General.pack_start(m_Area);

	m_Box_General.pack_start(m_Button_Exit,false,false);
	m_Box_General.pack_start(m_Button_New,false,false); 	
	m_Box_General.pack_start(m_Button_Open,false,false); 
	m_Box_General.pack_start(m_Button_Save,false,false);

	m_Button_Exit.signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui::on_button_clicked) );


	// Show all children of the window
	show_all_children();
}

	
void Gui::on_button_clicked()
{
	cout << "Hello World" << endl;
}

Gui::~Gui()
{
}


//============= Class MyArea ===========
MyArea::MyArea(Frame x){
	graphic_gui::setFrame(x);
}

MyArea::~MyArea(){}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();
	
	graphic_gui::graphic_set_context(cr);
	graphic_gui::updateFrameSize(width,height);
	City::updateDraw();
	return true;
}
