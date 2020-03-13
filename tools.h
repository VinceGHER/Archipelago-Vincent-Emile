// Module Tools (interface)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0
#ifndef TOOLS_H
#define TOOLS_H
    typedef unsigned int ID;

    struct Pair {
        unsigned int pair1;
        unsigned int pair2;
    };
    struct Point {
        double x;
        double y;
    };
    struct Vector {
        double x;
        double y;
    };

    struct Circle {
        Point center;
        double radius;
    };
    struct Segment {
        Point start;
        Point end; 
    };
namespace tools {
    bool overlapBetweenCircles(Circle circle1, Circle circle2, double dist_min);
    bool overlapBetweenCircleSegment(Circle circle, Segment segment, double dist_min);
}
#endif