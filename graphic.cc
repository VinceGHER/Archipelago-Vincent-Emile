// Module Node (interface)
// Made by Vincent GHEROLD and Emile CAILLOL
// Version 2.1
// Architecture b1

#include <iostream>

#include "graphic_gui.h"
#include "graphic.h"

using namespace std;

namespace {
    Frame initial;
    Frame current; 
    const Cairo::RefPtr<Cairo::Context>* pCr(nullptr);
    double currentZoom;
}

//private function prototypes
int convertX(double coord); 
int convertY(double coord);

//private functions
int convertX(double coord){
    double prefactor = current.width / ( current.xmax - current.xmin ); 
    return ( coord - current.xmin ) * prefactor;	
}
int convertY(double coord){
    double prefactor = current.height / ( current.ymax - current.ymin ); 
    return ( current.ymax - coord ) * prefactor;	
}
// === externals functions ====

//functions for gui module
void graphic_gui::graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr){
    pCr = &cr;
}
void graphic_gui::setFrame(Frame x){
    initial = x;
    current = x;
}
void graphic_gui::updateFrameSize(int width, int height, double zoom){
    
    currentZoom = zoom;
    double newFactor( (double)width/height);
    
    if (newFactor > initial.ratio){
        current.ymax = initial.ymax;
        current.ymin = initial.ymin;

        double delta(initial.xmax - initial.xmin);
        double mid((initial.xmax + initial.xmin)/2);

        current.xmax = mid + 0.5*(newFactor/initial.ratio)*delta;
        current.xmin = mid - 0.5*(newFactor/initial.ratio)*delta;		  	  

    } else { // keep xmax and xmin. Adjust ymax and ymin
        current.xmax = initial.xmax ;
        current.xmin = initial.xmin ;
            
        double delta(initial.ymax - initial.ymin);
        double mid((initial.ymax + initial.ymin)/2);

        current.ymax = mid + 0.5*(initial.ratio/newFactor)*delta;
        current.ymin = mid - 0.5*(initial.ratio/newFactor)*delta;		  	  
    }
    current.xmin /= zoom;
    current.xmax /= zoom;
    current.ymin /= zoom;
    current.ymax /= zoom;

    //Update width and height
    current.width = width;
    current.height = height;
}

double graphic_gui::convertWindowToModelX(double x){
    double prefactor = current.width / ( current.xmax - current.xmin );
    if (prefactor == 0) return 0;
    return (x/prefactor)+current.xmin;
}
double graphic_gui::convertWindowToModelY(double y){
    double prefactor = current.height / ( current.ymax - current.ymin ); 
    if (prefactor == 0) return 0;
    return -((y/prefactor)-current.ymax);
}

//functions for tools module

bool graphic::drawSegment(double x1,double y1, double x2, double y2){
    if (pCr == nullptr) return false;
    (*pCr)->save();
    (*pCr)->move_to( convertX(x1), convertY(y1) );
    (*pCr)->line_to( convertX(x2), convertY(y2) );
    (*pCr)->restore();
    (*pCr)->stroke();
    return true;
}
bool graphic::drawCircle(double x,double y,double radius){
    if (pCr == nullptr) return false;
    (*pCr)->save();  
    int xc( convertX(x) );
    int yc( convertY(y) );
    int startPointCircle ( convertX(x+radius) );
    int radiusConverted(  startPointCircle-xc );
    (*pCr)->move_to(startPointCircle,yc);
    (*pCr)->arc(xc, yc, radiusConverted, 0.0, 2.0 * M_PI);
    (*pCr)->set_source_rgba(1.0, 1.0, 1.0, 1);
    (*pCr)->fill_preserve();
    (*pCr)->restore();
    (*pCr)->stroke();

    return true;   
}
bool graphic::setColor(Color color) {
    if (pCr == nullptr) return false;
    double red(0),green(0),blue(0);
    
    switch (color){
        case RED:
            red = 1;
            green = 0;
            blue = 0;
            break;
        case GREEN:
            red = 0;
            green = 1;
            blue = 0;
            break;
        case BLACK:
            red = 0;
            green = 0;
            blue = 0;
            break;
    }
    (*pCr)->set_source_rgb(red, green, blue);
    return true;
}

