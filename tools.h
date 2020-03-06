// Module Tools (interface)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0

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
    Vector vector; 
};
bool overlapBetweenCircles(Circle circle1, Circle circle2, double dist_min);
bool overlapBetweenCircleSegment(Circle circle, Segment segment, double dist_min);