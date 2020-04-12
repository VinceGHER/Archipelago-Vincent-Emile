// Module Node (interface)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0 

#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <gtkmm/drawingarea.h>

enum Color {RED,GREEN,BLUE};

namespace graphic {
  bool drawSegment(double x1,double y1, double x2, double y2);
  bool drawCircle(double x,double y,double radius);
  bool setColor(Color color);
}

#endif
