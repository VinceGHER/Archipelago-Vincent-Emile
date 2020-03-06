#include <iostream>
using namespace std;

//test du module tools 
#include "tools.h"

int main(){
    // ============= TEST ON THE MODULE TOOLS =============
    Circle circle1 = {Point{1,1}, 1};
    Circle circle2 = {Point{3,1}, 0.5};
    Segment segment1 = {Point{1,2}, Vector{3,0}};
    cout << "Collision test between circle1 and circle2 " 
         << overlapBetweenCircles(circle1,circle2, 0.51)
         << endl;
    cout << "Collision test between circle2 and segment1 " 
         << overlapBetweenCircleSegment(circle2,segment1, 0.5)
         << endl;

    // ============= TEST ON THE MODULE        =============
    return 0;
};