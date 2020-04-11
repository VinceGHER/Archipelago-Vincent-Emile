// Module Node (interface)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0 

#ifndef GRAPHIC_H
#define GRAPHIC_H

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

enum Color {RED,GREEN,BLUE};

class Graphic: public Gtk::DrawingArea {
public:
    Graphic();
    bool setColor(Color color);
    void setFrame(Frame x); 
    void initPCR(const Cairo::RefPtr<Cairo::Context>& cr);
    bool drawSegment(double x1,double y1, double x2, double y2);
    bool drawCircle(double x,double y,double radius);
protected:
    int ConvertX(double coord, double width); 
    int ConvertY(double coord, double height);
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

    Frame initial;
    Frame current; 
    const Cairo::RefPtr<Cairo::Context>* pCr;
};

#endif
