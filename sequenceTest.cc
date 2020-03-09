#include <iostream>
#include <string>
#include "tools.h"
#include "node.h"
using namespace std;
int main(){
     #define T_NODE
     // ============= TEST ON THE MODULE TOOLS =============
     #ifdef T_TOOLS
          Circle circle1 = {Point{1,1}, 1};
          Circle circle2 = {Point{3,1}, 0.5};
          Segment segment1 = {Point{1,2}, Point{4,0}};
          cout << "Collision test between circle1 and circle2 " 
               << tools::overlapBetweenCircles(circle1,circle2, 0.5)
               << endl;
          cout << "Collision test between circle2 and segment1 " 
               << tools::overlapBetweenCircleSegment(circle2,segment1, -0.3)
               << endl;
     #endif 

     // ============= TEST ON THE MODULE NODE =============
     #ifdef T_NODE

          Circle circle1 = {Point{-110,-110}, 5};
          Circle circle2 = {Point{2000, 2000}, 5}; 
          Circle circle3 = {Point{4000,0}, 5};
          // Node::addNode(circle1,100000,LOGEMENT,0);
          // Node::addNode(circle2,1000,TRANSPORT,2);
          // Node::addNode(circle3,1000,TRANSPORT,3);
          string lineTest("  1  10   1000   1000");
          if(not Node::read(lineTest,LOGEMENT)) cout << "error"<<endl;
          string lineTest3("  2  222 222   1000");
          if(not Node::read(lineTest3,LOGEMENT)) cout << "error"<<endl;
          string lineTest4("  1  3000 222   1000");
          if(not Node::read(lineTest3,LOGEMENT)) cout << "error"<<endl;

          string lineTest2("1  2   1000   1000"); 
          if(not Node::read(lineTest2,LINK)) cout << "error"<<endl;
          Node::showNodeGroup();  

     #endif
    
    return 0;
};