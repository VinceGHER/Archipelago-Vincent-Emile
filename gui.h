// Module Node (interface)
// Made by Vincent GHEROLD and Emile CAILLOL
// Version 2.1
// Architecture b1

#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <string>
#include <gtkmm.h>

#include "graphic_gui.h"
#include "city.h"

class Gui;
class MyArea;

class MyArea : public Gtk:: DrawingArea {
public:
	MyArea(){};
	virtual ~MyArea(){};
	void setFrame(Frame x);
	void refresh();

protected:
	//Override default signal handler:
	bool on_draw(const Cairo:: RefPtr<Cairo::Context>& cr) override;
	
};

class Gui : public Gtk:: Window {
public:
	Gui();
	virtual ~Gui(){};
	void refreshGuiAndDraw();
	
protected:
	//initialisation
	void createBoxStruct();
	void addButtonsToBox();
	void linkFunctionButtons();
	void createDrawingArea();
	
	//buttons functions
	void onExitButtonClicked();
	void onNewButtonClicked();
	void onOpenButtonClicked();
	void onSaveButtonClicked();
	void onPathButtonClicked();
	void onZinButtonClicked();
	void onZoutButtonClicked();
	void onResetButtonClicked();
	void onEditButtonClicked();
	// void onRadioHousingButtonClicked();
	// void onRadioTransportButtonClicked();
	// void onRadioProductionButtonClicked();
	
	std:: string fileSelection(bool open);
	
	Gtk:: Box m_Box;
	Gtk:: Box m_Box_Buttons;
	Gtk:: Box m_Box_Drawing;
	Gtk:: Box m_Box_General;
	Gtk:: Box m_Box_Display;
	Gtk:: Box m_Box_Editor;
	Gtk:: Box m_Box_Informations;
	
	Gtk:: Frame m_Frame_General;
	Gtk:: Frame m_Frame_Display;
	Gtk:: Frame m_Frame_Editor;
	Gtk:: Frame m_Frame_Informations;

	Gtk:: Button m_Button_Exit;
	Gtk:: Button m_Button_New;
	Gtk:: Button m_Button_Open;
	Gtk:: Button m_Button_Save;
	Gtk:: Button m_Button_Path;
	Gtk:: Button m_Button_Zin;
	Gtk:: Button m_Button_Zout;
	Gtk:: Button m_Button_Reset;
		
	Gtk:: ToggleButton m_TButton_Edit;
	
	Gtk:: RadioButtonGroup m_Radio_Type;
    Gtk:: RadioButton m_Radio_Housing;
    Gtk:: RadioButton m_Radio_Transport;
    Gtk:: RadioButton m_Radio_Production;

	Gtk:: Label m_Label_Zoom;
	Gtk:: Label m_Label_ENJ;
	Gtk:: Label m_Label_CI;
	Gtk:: Label m_Label_MTA;
	
	Gtk:: Box m_Box_Open;
	Gtk:: Button m_Button_File;
	Gtk:: Label m_Label_Open;

	MyArea m_Area;
	bool editLink;
};

#endif
