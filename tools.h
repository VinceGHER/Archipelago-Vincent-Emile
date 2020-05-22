// Module Tools (interface)
// Made by Vincent GHEROLD and Emile CAILLOL
// Version 2.1
// Architechture b1

#ifndef TOOLS_H
#define TOOLS_H

#include "graphic_color.h"

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
    bool overlapBetweenCirclePoint(Circle circle, Point point);

    double distance(Point point1, Point point2);
    double distance(Vector vector);

    bool drawCircle(Circle circle);
    bool drawSegment(Segment segment);
    bool setColor(Color color);
}
#endif
