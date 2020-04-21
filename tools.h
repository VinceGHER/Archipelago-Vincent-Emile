// Module Tools (interface)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0
#ifndef TOOLS_H
#define TOOLS_H

#include "graphic.h"

typedef unsigned int ID;

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
    double distance(Point point1, Point point2);
    double distance(Vector vector);

    bool drawCircle(Circle circle);
    bool drawSegment(Segment segment);
    bool setColor(Color color);
}

#endif