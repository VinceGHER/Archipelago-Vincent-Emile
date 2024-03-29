// Module Node (interface)
// Made by Vincent GHEROLD and Emile CAILLOL
// Version 2.1
// Architecture b1

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>

#include "gui.h"
#include "graphic_gui.h"
#include "city.h"
#include "constantes.h"

using namespace std;

// ========== Class MyArea ==========

MyArea::MyArea(Gui& gui):
	currentZoom(1.),
	shortestPath(false),
	ptrSelectedNode(&gui.getSelectedNode()){};
void MyArea::setFrame(Frame x){
	graphic_gui::setFrame(x);
}
void MyArea::zoomFrame(bool zooming){
	double newZoom(currentZoom);

	if (zooming) 
		newZoom+=delta_zoom;
	else newZoom-=delta_zoom;

	if (newZoom <= (max_zoom+epsil_zero) and
		newZoom >= (min_zoom-epsil_zero)){
		currentZoom = newZoom;
		refresh();
	}
}
void MyArea::zoomReset(){
	currentZoom = 1.;
	refresh();
}
double MyArea::getZoom(){
	return currentZoom;
}
void MyArea::setShortestPath(bool path){
	shortestPath = path;
}
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

	graphic_gui::graphic_set_context(cr);
	graphic_gui::updateFrameSize(width,height,currentZoom);
	City::updateDraw(shortestPath,*ptrSelectedNode);
	return true;
}

// ========== Class Gui ==========
Gui::Gui():	
	m_Box(Gtk::ORIENTATION_HORIZONTAL),
	m_Box_Buttons(Gtk::ORIENTATION_VERTICAL,5),
	m_Box_Drawing(Gtk::ORIENTATION_HORIZONTAL),
	m_Box_General(Gtk::ORIENTATION_VERTICAL,3),
	m_Box_Display(Gtk::ORIENTATION_VERTICAL,3),
	m_Box_Editor(Gtk::ORIENTATION_VERTICAL,3),
	m_Box_Informations(Gtk::ORIENTATION_VERTICAL,3),
	m_Frame_General("General"),
	m_Frame_Display("Display"),
	m_Frame_Editor("Editor"),
	m_Frame_Informations("Informations - criteria"),
	m_Button_Exit("exit"),         
	m_Button_New("new"),
    m_Button_Open("open"),
    m_Button_Save("save"),
    m_Button_Zin("zoom in"),
	m_Button_Zout("zoom out"),
	m_Button_Reset("zoom reset"),
	m_TButton_Edit("edit link"),
	m_TButton_Path("shortest path"),
	m_Radio_Housing (m_Radio_Type, "housing"),
	m_Radio_Transport (m_Radio_Type, "transport"),
	m_Radio_Production (m_Radio_Type, "production"),
	m_Label_Zoom(),
	m_Label_ENJ(),
	m_Label_CI(),
	m_Label_MTA(),
	firstClickPosition(Point{0,0}),
	isResizingNode(false),
	m_Area(*this),
	editLink(false),
	type(HOUSING),
	selectedNode(nullptr){	
		set_title("Drawing Area and Buttons");
		set_border_width(0);
		createBoxStruct();
		createDrawingArea();
		addButtonsToBox();
		linkFunctionButtons();
		refreshGuiAndDraw();
		show_all_children();
}

// === initialisation ===
void Gui::createBoxStruct(){

	add(m_Box);

	m_Box.pack_start(m_Box_Buttons,false,false);
	m_Box.pack_start(m_Box_Drawing,true,true);

	m_Box_Buttons.pack_start(m_Frame_General,false,false);
	m_Box_Buttons.pack_start(m_Frame_Display,false,false);
	m_Box_Buttons.pack_start(m_Frame_Editor,false,false);
	m_Box_Buttons.pack_start(m_Frame_Informations,true,true);
	
	m_Frame_General.add(m_Box_General);
	m_Frame_Display.add(m_Box_Display);
	m_Frame_Editor.add(m_Box_Editor);
	m_Frame_Informations.add(m_Box_Informations);
}
void Gui::addButtonsToBox(){
	
	m_Box_General.pack_start(m_Button_Exit,false,false);
	m_Box_General.pack_start(m_Button_New,false,false); 	
	m_Box_General.pack_start(m_Button_Open,false,false); 
	m_Box_General.pack_start(m_Button_Save,false,false);
	
	m_Box_Display.pack_start(m_TButton_Path,false,false);
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
void Gui::linkFunctionButtons(){
	
	m_Button_Exit.signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui:: onExitButtonClicked) );	  
	m_Button_New.signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui:: onNewButtonClicked) );
	m_Button_Open.signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui:: onOpenButtonClicked) );
	m_Button_Save.signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui:: onSaveButtonClicked) );	  
	m_TButton_Path.signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui:: onPathButtonClicked) );
	m_Button_Zin.signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui:: onZinButtonClicked) );
	m_Button_Zout.signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui:: onZoutButtonClicked) );
	m_Button_Reset.signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui:: onResetButtonClicked) );
	m_TButton_Edit.signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui:: onEditButtonClicked) );
	m_Radio_Housing.signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui:: onHousingButtonClicked) );
	m_Radio_Transport.signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui:: onTransportButtonClicked) );
	m_Radio_Production.signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui:: onProductionButtonClicked) );		  
}
void Gui::createDrawingArea(){
	Frame wd = {-dim_max,dim_max,-dim_max,dim_max};
	wd.ratio = (wd.xmax-wd.xmin)/(wd.ymax-wd.ymin);
	
	wd.height = default_drawing_size;
	wd.width = wd.height*wd.ratio;

	m_Area.setFrame(wd);
	m_Area.set_size_request(default_drawing_size,default_drawing_size);

	m_Box_Drawing.pack_start(m_Area);
}

// === buttons functions ===
void Gui::onExitButtonClicked(){
	emptyCity();
	exit(0);
}
void Gui::onNewButtonClicked(){
	emptyCity();
	refreshGuiAndDraw();
}
void Gui::onOpenButtonClicked(){
	string filename ( fileSelection(true) );
	if (not (filename == "")){
		emptyCity();
		City::readFile(filename);
		refreshGuiAndDraw();
		refreshZoom();
	}
}
void Gui::onSaveButtonClicked(){
	string filename ( fileSelection(false) );
	if (not (filename == "")) 
		City::save(filename);
}
void Gui::onPathButtonClicked(){
	m_Area.setShortestPath(m_TButton_Path.get_active());
	refreshGuiAndDraw();
}
void Gui::onZinButtonClicked(){
	m_Area.zoomFrame(true);
	refreshZoom();
}
void Gui::onZoutButtonClicked(){
	m_Area.zoomFrame(false);
	refreshZoom();
}
void Gui::onResetButtonClicked(){
	m_Area.zoomReset();
	refreshZoom();
}
void Gui::onEditButtonClicked(){
	editLink = m_TButton_Edit.get_active();
	if (editLink and selectedNode == nullptr){
		cout << "please select first a node to edit" << endl;
		m_TButton_Edit.set_active(false);
	}

}
void Gui::onHousingButtonClicked(){
	type = HOUSING;
}
void Gui::onTransportButtonClicked(){
	type = TRANSPORT;
}
void Gui::onProductionButtonClicked(){
	type = PRODUCTION;
}

string Gui::fileSelection(bool open){	
	string textInfo("");
	string state("");

	auto action (Gtk::FILE_CHOOSER_ACTION_OPEN);
	if (open){
		state = "Open";
		textInfo = "Please choose a file";
	} else {
		state = "Save";
		textInfo = "Name";
		action = Gtk::FILE_CHOOSER_ACTION_SAVE;
	}

	Gtk::FileChooserDialog dialog(textInfo,action);
	dialog.set_transient_for(*this);
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_"+state, Gtk::RESPONSE_OK); 

	int result = dialog.run();
	string filename("");
	
	switch(result){	
	case(Gtk::RESPONSE_OK):
		filename = dialog.get_filename(); 
		break;
	case(Gtk::RESPONSE_CANCEL) :
		break;
	default:
		cout << "Unexpected button clicked." << endl;
		break;
	}
	return filename;
}

// === refresh functions ===
void Gui::refreshGuiAndDraw(){

	m_Area.refresh();

	string ENJText ("ENJ: " + (City::criteriaENJ()));
	string CIText ("CI: " + (City::criteriaCI()));
	string MTAText ("MTA: " + (City::criteriaMTA()));

	m_Label_ENJ.set_text(ENJText);
	m_Label_CI.set_text(CIText);
	m_Label_MTA.set_text(MTAText);
	
}
void Gui::refreshZoom(){
	stringstream balance("");
	balance << "zoom: x" << fixed << setprecision(2) << m_Area.getZoom();
	m_Label_Zoom.set_text(balance.str());
}

// === mouse event signal handlers ===
bool Gui::on_button_press_event(GdkEventButton * event){
	if(event->type == GDK_BUTTON_PRESS){
		
		double clicX = event->x ;
		double clicY = event->y ;
		
		double originX = m_Area.get_allocation().get_x();
		double originY = m_Area.get_allocation().get_y();
	
		double width = m_Area.get_allocation().get_width();
		double height= m_Area.get_allocation().get_height();
	
		if(clicX >= originX && clicX <= originX + width &&
		   clicY >= originY && clicY <= originY + height) {
			
			Point pWindow({clicX - originX, clicY - originY});
			
			Point pModel = {graphic_gui::convertWindowToModelX(pWindow.x),
							graphic_gui::convertWindowToModelY(pWindow.y)};
			
			if(event->button == 1){ //left mouse button
				if (editLink) 
					clicPressAreaWithEdit(pModel);
				else 
					clicPressAreaWithoutEdit(pModel);
				
			} else if (event->button == 3){ //right mouse button
				if (selectedNode != nullptr) 
					City::moveNode(pModel,selectedNode);
			}
			refreshGuiAndDraw();
		}
	}
	return true;
}
bool Gui::on_button_release_event(GdkEventButton * event){
	
	if(event->type == GDK_BUTTON_RELEASE){
		//raw mouse coordinates in the window frame
		double clicX = event->x;
		double clicY= event->y;

		//origin of the drawing area
		double originX = m_Area.get_allocation().get_x();
		double originY = m_Area.get_allocation().get_y();
		
		//get width and height of drawing area
		double width = m_Area.get_allocation().get_width();
		double height= m_Area.get_allocation().get_height();
		
		//retain only mouse events located within the drawing area
		if(clicX >= originX && clicX <= originX + width &&
		   clicY >= originY && clicY <= originY + height){ 

			Point pWindow({clicX - originX, clicY - originY});
			
			Point pModel = {graphic_gui::convertWindowToModelX(pWindow.x),
							graphic_gui::convertWindowToModelY(pWindow.y)};

			if (event->button == 1 and 
				isResizingNode and
				selectedNode != nullptr) //left mouse button
				clicReleaseAreaWithEdit(pModel);
		}
	}
	return true;
}
void Gui::clicPressAreaWithoutEdit(Point pos){
	Node* clickedNode( City::getClickedNode(pos,selectedNode) );

	//resizing node
	if (clickedNode == nullptr and selectedNode != nullptr){
		isResizingNode = true;
		firstClickPosition = pos;
		return;
	}
	//select node
	if (clickedNode != nullptr and selectedNode == nullptr){
		selectedNode = clickedNode;
		return;
	}
	//create node
	if (clickedNode == nullptr and selectedNode == nullptr){
		City::addNode(pos,type, dist_min);
		return;
	}
	//delete node
	if (clickedNode == selectedNode and clickedNode != nullptr){
		City::deleteNode(clickedNode);
		selectedNode = nullptr;
		return;
	}
	//switch selected node
	if (clickedNode != nullptr and selectedNode != nullptr and
		clickedNode !=  selectedNode){
		selectedNode = clickedNode;
		return;
		}

}
void Gui::clicPressAreaWithEdit(Point pos){

	Node* clickedNode( City::getClickedNode(pos, selectedNode) );
	if (clickedNode == nullptr or
		selectedNode == nullptr) 
		return;
	if (clickedNode == selectedNode) 
		return;
	
	City::updateLink(selectedNode,clickedNode, dist_min);
	return;
}
void Gui::clicReleaseAreaWithEdit(Point pos){

	City::resizeNode(selectedNode,firstClickPosition,pos);
	selectedNode = nullptr;
	isResizingNode = false;
	refreshGuiAndDraw();
				
}

// === keyboard signal handler ===
bool Gui::on_key_press_event(GdkEventKey * key_event){
	if(key_event->type == GDK_KEY_PRESS){
		switch(gdk_keyval_to_unicode(key_event->keyval)){
		case 'i':
			m_Area.zoomFrame(true);	
			break;
		case 'o':
			m_Area.zoomFrame(false);
			break;
		case 'r':
			m_Area.zoomReset();
			break;
		}
	}
	return Gtk::Window::on_key_press_event(key_event);
}

// === empty city ===
void Gui::emptyCity(){
	m_TButton_Path.set_active(false);
	m_TButton_Edit.set_active(false);
	m_Area.zoomReset();
	selectedNode = nullptr;
	City::emptyNodeGroup();
}
