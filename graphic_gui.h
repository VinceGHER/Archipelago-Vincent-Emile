// Module Node (interface)
// Made by Vincent GHEROLD and Emile CAILLOL
// Version 2.1
// Architecture b1


#ifndef GRAPHIC_GUI_H
#define GRAPHIC_GUI_H

#include <gtkmm/drawingarea.h>

struct Frame {
  double xmin;
  double xmax;
  double ymin;
  double ymax;
  double ratio;
  int height;
  int width;
};

namespace graphic_gui {
  void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr);
  void setFrame(Frame x);
  void updateFrameSize(int width, int height);
}

#endif
