// Module Node (interface)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0 

#include "graphic.h"
#include <cairomm/context.h>


//debug
#include <iostream>
using namespace std;
Graphic::Graphic():pCr(nullptr){}

void Graphic::setFrame(Frame x){
    initial = x;
    current = x;
}

void Graphic::initPCR(const Cairo::RefPtr<Cairo::Context>& cr){
    pCr = &cr;
}
 
bool Graphic::setColor(Color color) {
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
    case BLUE:
        red = 0;
        green = 0;
        blue = 1;
        break;
    }

    (*pCr)->set_source_rgb(red, green, blue);
    return true;
}
bool Graphic::drawSegment(double x1,double y1, double x2, double y2){
    if (pCr == nullptr) return false;
    (*pCr)->save();
    (*pCr)->move_to( ConvertX(x1,current.width), ConvertY(y1,current.height) );
    (*pCr)->line_to( ConvertX(x2,current.width), ConvertY(y2,current.height) );
    (*pCr)->restore();
    return true;
}
bool Graphic::drawCircle(double x,double y,double radius){
    if (pCr == nullptr) return false;
    (*pCr)->save();  
    int xc( ConvertX(x,current.width)   );
    int yc( ConvertY(y,current.height) );
    int startPointCircle ( ConvertX(x+radius,current.width));
    int radiusConverted(  startPointCircle-xc );
    (*pCr)->move_to(startPointCircle,yc);
    (*pCr)->arc(xc, yc, radiusConverted, 0.0, 2.0 * M_PI);
    (*pCr)->set_source_rgba(1.0, 1.0, 1.0, 1);
    (*pCr)->fill_preserve();
    (*pCr)->restore();
  //  (*pCr)->set_source_rgba(1.0, 1.0, 1.0, 0);

    return true;   
}

bool Graphic::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();
  current.width = width;
  current.height = height;
  initPCR(cr);
  double newFactor( (double)width/height);
  cout << endl;
  cout << "xmin: " << current.xmin << endl;
  cout << "xmax: " << current.xmax << endl;
  cout << "ymin: " << current.ymin << endl;
  cout << "ymax: " << current.ymax << endl;
  if (newFactor > initial.ratio){
    current.ymax = initial.ymax;
    current.ymin = initial.ymin;

	  double delta(initial.xmax - initial.xmin);
	  double mid((initial.xmax + initial.xmin)/2);

	  current.xmax = mid + 0.5*(newFactor/initial.ratio)*delta ;
	  current.xmin = mid - 0.5*(newFactor/initial.ratio)*delta ;		  	  
  

  }
   else
  { // keep xmax and xmin. Adjust ymax and ymin
	  current.xmax = initial.xmax ;
	  current.xmin = initial.xmin ;
	  	  
 	  double delta(initial.ymax - initial.ymin);
	  double mid((initial.ymax + initial.ymin)/2);

	  current.ymax = mid + 0.5*(initial.ratio/newFactor)*delta ;
	  current.ymin = mid - 0.5*(initial.ratio/newFactor)*delta ;		  	  
  }
    
    setColor(RED);
  drawSegment(0,0,5,5);  
  drawCircle(0,0,7.071);
  cr->stroke();

  return true;
}

int Graphic::ConvertX(double coord, double width)
{
 double prefactor = width / ( current.xmax - current.xmin ); 
 return ( coord - current.xmin ) * prefactor;	
}

int Graphic::ConvertY(double coord, double height)
{
 double prefactor = height / ( current.ymax - current.ymin ); 
 return ( current.ymax - coord ) * prefactor;	
}