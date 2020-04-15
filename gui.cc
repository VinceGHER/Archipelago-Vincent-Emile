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
#include "constantes.h"

using namespace std;

Gui::Gui():
	m_Box(Gtk::ORIENTATION_HORIZONTAL,10),
	
	m_Box_Buttons(Gtk::ORIENTATION_VERTICAL),
	
	m_Box_Drawing(Gtk::ORIENTATION_HORIZONTAL,10),

	m_Box_General(Gtk::ORIENTATION_VERTICAL),

	m_Frame_General("General"),

	m_Button_Exit("Exit"),
    m_Button_New("New"),
    m_Button_Open("Open"),
    m_Button_Save("Save")
	{
	
	Frame wd = {-dim_max,dim_max,-dim_max,dim_max};
	wd.ratio = (wd.xmax-wd.xmin)/(wd.ymax-wd.ymin);

	wd.height = default_drawing_size;
	wd.width = wd.height*wd.ratio;

	m_Area.setFrame(wd);
	m_Area.set_size_request(default_drawing_size,default_drawing_size);

	set_title("Drawing Area and Buttons");
	set_border_width(0);
  
	add(m_Box);
	
	m_Box.pack_start(m_Box_Buttons);
	m_Box.pack_start(m_Box_Drawing);

	m_Box_Buttons.pack_start(m_Frame_General);
	m_Frame_General.add(m_Box_General);
	m_Box_Drawing.pack_start(m_Area);

	//~ m_Area.set_size_request(200,200);
	//~ m_Box_General.pack_start(m_Area);

	m_Box_General.pack_start(m_Button_Exit,false,true);
	m_Box_General.pack_start(m_Button_New,false,true); 	
	m_Box_General.pack_start(m_Button_Open,false,true); 
	m_Box_General.pack_start(m_Button_Save,false,true);

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
void MyArea::setFrame(Frame x){
	graphic_gui::setFrame(x);
}
MyArea::MyArea(){}

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
