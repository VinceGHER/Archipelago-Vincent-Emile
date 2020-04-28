// Module Node (interface)
// Made by Vincent GHEROLD and Emile CAILLOL
// Version 2.1 
// Architechture b1

#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <gtkmm/drawingarea.h>

#include "graphic_color.h"

namespace graphic {
  bool drawSegment(double x1,double y1, double x2, double y2);
  bool drawCircle(double x,double y,double radius);
  bool setColor(Color color);
}

#endif
