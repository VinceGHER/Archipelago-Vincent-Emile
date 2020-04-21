// Module Node (interface)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0 

#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <gtkmm.h>

#include "graphic_gui.h"
#include "city.h"

class MyArea;
class Timer;
class Gui;

class MyArea : public Gtk:: DrawingArea {
public:
	MyArea();
	void setFrame(Frame x);
	virtual ~MyArea();
	void refresh();

protected:
	//Override default signal handler:
	bool on_draw(const Cairo:: RefPtr<Cairo::Context>& cr) override;
	
};

class Timer {
public:
	Timer(Gui& gui,int timeoutValueRef);
	bool startTimer();
	bool stopTimer();
	bool onTimeout();

private:
	bool timerAdded;
	bool disconnect;
	const int timeoutValue;
	Gui& guiRef;
};


class Gui : public Gtk:: Window {
public:
	Gui();
	virtual ~Gui();
	void updateText();

protected:
	
	void onExitButtonClicked();
	void onNewButtonClicked();
	void onOpenButtonClicked();
	void onSaveButtonClicked();
	void onUselessButtonClicked();
	
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
		
	Gtk:: ToggleButton m_Button_Edit;
	
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
	Timer  timer;
	
};
#endif
