// Module Node (interface)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0 

#include <iostream>
#include <string>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm.h>

#include "gui.h"
#include "graphic_gui.h"
#include "city.h"
#include "constantes.h"

using namespace std;

//=== Class Gui ===
Gui::Gui():
	
	m_Box(Gtk::ORIENTATION_HORIZONTAL),
	
	m_Box_Buttons(Gtk::ORIENTATION_VERTICAL),
	
	m_Box_Drawing(Gtk::ORIENTATION_HORIZONTAL),

	m_Box_General(Gtk::ORIENTATION_VERTICAL),
	m_Box_Display(Gtk::ORIENTATION_VERTICAL),
	m_Box_Editor(Gtk::ORIENTATION_VERTICAL),
	m_Box_Informations(Gtk::ORIENTATION_VERTICAL),

	m_Frame_General("General"), m_Frame_Display("Display"),
	m_Frame_Editor("Editor"),   m_Frame_Informations("Informations"),

	m_Button_Exit("exit"),          m_Button_New("new"),
    m_Button_Open("open"),          m_Button_Save("save"),
    m_Button_Path("shortest path"), m_Button_Zin("zoom in"),
	m_Button_Zout("zoom out"),      m_Button_Reset("zoom reset"),
	m_TButton_Edit("edit link"),
	
	m_Radio_Housing (m_Radio_Type, "housing"),
	m_Radio_Transport (m_Radio_Type, "transport"),
	m_Radio_Production (m_Radio_Type, "production"),
	
	m_Label_Zoom(),   m_Label_ENJ(),
	m_Label_CI(),     m_Label_MTA()
	 {
		
		creationBoxFrame();
		creationPackStart();
		creationClicked();
		bool edit(0);
		refreshGuiAndDraw();
		
		show_all_children();
}

void Gui::creationBoxFrame(){
	Frame wd = {-dim_max,dim_max,-dim_max,dim_max};
	wd.ratio = (wd.xmax-wd.xmin)/(wd.ymax-wd.ymin);
	
	wd.height = default_drawing_size;
	wd.width = wd.height*wd.ratio;

	m_Area.setFrame(wd);
	m_Area.set_size_request(default_drawing_size,default_drawing_size);

	set_title("Drawing Area and Buttons");
	set_border_width(0);
  
	add(m_Box);
	
	m_Box.pack_start(m_Box_Buttons,false,false);
	m_Box.pack_start(m_Box_Drawing,false,false);

	m_Box_Buttons.pack_start(m_Frame_General,false,false);
	m_Box_Buttons.pack_start(m_Frame_Display,false,false);
	m_Box_Buttons.pack_start(m_Frame_Editor,false,false);
	m_Box_Buttons.pack_start(m_Frame_Informations,false,false);
	
	m_Frame_General.add(m_Box_General);
	m_Frame_Display.add(m_Box_Display);
	m_Frame_Editor.add(m_Box_Editor);
	m_Frame_Informations.add(m_Box_Informations);
}

void Gui::creationPackStart(){

	m_Box_Drawing.pack_start(m_Area);
	
	m_Box_General.pack_start(m_Button_Exit,false,false);
	m_Box_General.pack_start(m_Button_New,false,false); 	
	m_Box_General.pack_start(m_Button_Open,false,false); 
	m_Box_General.pack_start(m_Button_Save,false,false);
	
	m_Box_Display.pack_start(m_Button_Path,false,false);
	m_Box_Display.pack_start(m_Button_Zin,false,false);
	m_Box_Display.pack_start(m_Button_Zout,false,false);
	m_Box_Display.pack_start(m_Button_Reset,false,false);
	m_Box_Display.pack_start(m_Label_Zoom,false,false);
	
	m_Box_Editor.pack_start(m_TButton_Edit,false,false);
	m_Box_Editor.pack_start(m_Radio_Housing,false,false);
	m_Box_Editor.pack_start(m_Radio_Transport,false,false);
	m_Box_Editor.pack_start(m_Radio_Production,false,false);
	
	m_Box_Informations.pack_start(m_Label_ENJ,false,false);
	m_Box_Informations.pack_start(m_Label_CI,false,false);
	m_Box_Informations.pack_start(m_Label_MTA,false,false);
}

void Gui::creationClicked(){
	
	m_Button_Exit.signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui:: onExitButtonClicked) );	  
	m_Button_New.signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui:: onNewButtonClicked) );
	m_Button_Open.signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui:: onOpenButtonClicked) );
	m_Button_Save.signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui:: onSaveButtonClicked) );
			  
	m_Button_Path.signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui:: onPathButtonClicked) );
	m_Button_Zin.signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui:: onZinButtonClicked) );
	m_Button_Zout.signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui:: onZoutButtonClicked) );
	m_Button_Reset.signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui:: onResetButtonClicked) );
	m_TButton_Edit.signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui:: onEditButtonClicked) );
}
	
void Gui::onExitButtonClicked(){
	City::emptyNodeGroup();
	exit(0);
}
void Gui::onNewButtonClicked(){
	City::emptyNodeGroup();
	refreshGuiAndDraw();
}
void Gui::onOpenButtonClicked(){
	City::emptyNodeGroup();
	City::readFile(fileSelection(true));
	refreshGuiAndDraw();
}
void Gui::onSaveButtonClicked(){
	City::save(fileSelection(false));
}
void Gui::onPathButtonClicked(){
	cout << "INFO: Boutton << Shortest path >> cliqué." << endl;
}
void Gui::onZinButtonClicked(){
	cout << "INFO: Boutton << Zoom in >> cliqué." << endl;
}
void Gui::onZoutButtonClicked(){
	cout << "INFO: Boutton << Zoom out >> cliqué." << endl;
}
void Gui::onResetButtonClicked(){
	cout << "INFO: Boutton << Reset zoom >> cliqué." << endl;
}
void Gui::onEditButtonClicked(){
    if (edit == 0) {
        cout << "INFO: Boutton Toggle << Edit path >> cliqué." << endl;
        edit = 1;
    }
    else {
        cout << "INFO: Boutton Toggle << Edit link >> relaché." << endl;
        edit = 0;
    }
}

// void Gui::updateText(){
// }
void Gui::refreshGuiAndDraw(){
	m_Area.refresh();
	
	string ZoomText ("zoom: x1.00");
	string ENJText ("ENJ: " + (City::criteriaENJ()));
	string CIText ("CI: " + (City::criteriaCI()));
	string MTAText ("MTA: " + (City::criteriaMTA()));

	m_Label_Zoom.set_text(ZoomText);
	m_Label_ENJ.set_text(ENJText);
	m_Label_CI.set_text(CIText);
	m_Label_MTA.set_text(MTAText);
}

string Gui::fileSelection(bool choice){
	// choice == true => open a file
	// choice == false => save a file
	
	string textDialog(" ");
	string textOk(" ");
	if (choice == true) {
		textOk = "_Open";
		textDialog = "Please select a file to open";
	}
	else {
		textOk = "_Save";
		textDialog = "Please choose a file to save";
	}
	Gtk::FileChooserDialog dialog(textDialog,
		  Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_transient_for(*this);
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button(textOk, Gtk::RESPONSE_OK); 
	m_Label_Open.set_text("choosing a file");
	
	if (choice == false) {
		dialog.add_button("_New File", Gtk::RESPONSE_CANCEL);
	}
	int result = dialog.run();
	string filename(" ");
	m_Label_Open.set_text("Done choosing a file");

	switch(result){
		
		case(Gtk::RESPONSE_OK):{
			cout << "Open/Save clicked." << endl;
			filename = dialog.get_filename(); 
			cout << "File selected: " <<  filename << endl;
			break;
		}
		case(Gtk::RESPONSE_CANCEL):{
		    cout << "Cancel clicked." << endl;
		    break;
		}
		default:{
		    cout << "Unexpected button clicked." << endl;
		    break;
		}
	}
	return filename;
}

Gui::~Gui()
{
}


//=== Class MyArea ===
void MyArea::setFrame(Frame x){
	graphic_gui::setFrame(x);
}
MyArea::MyArea(){}

MyArea::~MyArea(){}

void MyArea::refresh(){
	auto win = get_window();
	if(win){
		Gdk::Rectangle r(0,0, get_allocation().get_width(),
		get_allocation().get_height());
		win->invalidate_rect(r,false);
	}
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){
	Gtk::Allocation allocation = get_allocation();
	const int width  = allocation.get_width();
	const int height = allocation.get_height();
	
	graphic_gui:: graphic_set_context(cr);
	graphic_gui:: updateFrameSize(width,height);
	City::updateDraw();
	return true;
}

//=== CLass Timer ===
// Timer::Timer(Gui& gui,int timeoutValueRef)
// :timerAdded(false),disconnect(false),timeoutValue(timeoutValueRef),
// guiRef(gui){}

// bool Timer::startTimer(){
	
// 	if(not timerAdded){
// 		Glib::signal_timeout().connect( sigc::mem_fun(*this, &Timer::onTimeout),
// 									  timeoutValue);
// 		timerAdded = true;
	
// 		return true;
// 	} else return false;
	
// }
// bool Timer::stopTimer(){
// 	if (not timerAdded){
// 		return false;
// 	} else {
// 		disconnect  = true;   
//     	timerAdded = false;
// 		return true;
// 	}
// }
// bool Timer::onTimeout(){

// 	if (disconnect){
// 		disconnect = false;
// 		return false;
// 	}
	
// //	guiRef.updateText();

// 	return true;
// }
