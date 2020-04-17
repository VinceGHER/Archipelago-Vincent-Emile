// Module Node (interface)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0 

#include <iostream>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
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

	m_Box_General(Gtk::ORIENTATION_VERTICAL,true,true),
	m_Box_Display(Gtk::ORIENTATION_VERTICAL),
	m_Box_Editor(Gtk::ORIENTATION_VERTICAL),
	m_Box_Informations(Gtk::ORIENTATION_VERTICAL),

	m_Frame_General("General"),
	m_Frame_Display("Display"),
	m_Frame_Editor("Editor"),
	m_Frame_Informations("Informations"),

	m_Button_Exit("exit"),
    m_Button_New("new"),
    m_Button_Open("open"),
    m_Button_Save("save"),
    m_Button_Path("shortest path"),
	m_Button_Zin("zoom in"),
	m_Button_Zout("zoom out"),
	m_Button_Reset("zoom reset"),
	m_Button_Edit("edit link"),
	
	m_Radio_Housing(m_Radio_Type, "housing"),
	m_Radio_Transport(m_Radio_Type, "transport"),
	m_Radio_Production(m_Radio_Type, "production")
	
	m_Label_Zoom("zoom: "),
	m_Label_ENJ("ENJ: "),
	m_Label_CI("CI: "),
	m_Label_MTA("MTA:")
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
	m_Box_Buttons.pack_start(m_Frame_Display);
	m_Box_Buttons.pack_start(m_Frame_Editor);
	m_Box_Buttons.pack_start(m_Frame_Informations);
	
	m_Frame_General.add(m_Box_General);
	m_Frame_Display.add(m_Box_Display);
	m_Frame_Editor.add(m_Box_Editor);
	m_Frame_Informations.add(m_Box_Informations);
	m_Box_Drawing.pack_start(m_Area);
	
	m_Box_General.pack_start(m_Button_Exit,false,true);
	m_Box_General.pack_start(m_Button_New,false,true); 	
	m_Box_General.pack_start(m_Button_Open,false,true); 
	m_Box_General.pack_start(m_Button_Save,false,true);
	
	m_Box_Display.pack_start(m_Button_Path,false,true);
	m_Box_Display.pack_start(m_Button_Zin,false,true);
	m_Box_Display.pack_start(m_Button_Zout,false,true);
	m_Box_Display.pack_start(m_Button_Reset,false,true);
	m_Box_Display.pack_start(m_Label_Zoom,false,true);
	
	m_Box_Editor.pack_start(m_Button_Edit,false,true);
	
	m_Box_Informations.pack_start(m_Label_ENJ,false,true);
	m_Box_Informations.pack_start(m_Label_CI,false,true);
	m_Box_Informations.pack_start(m_Label_MTA,false,true);

	m_Button_Exit.signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui::on_exit_button_clicked) );
			  
			  
	
	show_all_children();
}

	
void Gui::on_exit_button_clicked(){
	cout << "Exit" << endl;
}
void Gui::on_new_button_clicked(){
	cout << "New" << endl;
}
void Gui::on_open_button_clicked(){
	cout << "Open" << endl;
}
void Gui::on_save_button_clicked(){
	cout << "Save" << endl;
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
