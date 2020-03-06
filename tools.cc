// Module Tools (implementation)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0 

#include "tools.h"
#include <cmath>
// Private Function
double distance(Point point1, Point point2);
double distance(Vector vector);
double scalarProduct(Vector v1, Vector v2);

double distance(Point point1, Point point2){
    return sqrt( pow((point1.x-point2.x),2) + pow((point1.y-point2.y),2) );
}
double distance(Vector vector){
    return sqrt( pow((vector.x),2) + pow((vector.y),2) );
}
double scalarProduct(Vector v1, Vector v2){
    return v1.x*v2.x + v1.y*v2.y; 
}
// Function

bool overlapBetweenCircles(Circle circle1, Circle circle2, double dist_min){
    double totalradius( circle1.radius + circle2.radius );
    if (distance(circle1.center, circle2.center) - totalradius < dist_min)
        return true;
    return false;
};

bool overlapBetweenCircleSegment(Circle circle, Segment segment, double dist_min){
    Vector segmentToCircle = {circle.center.x - segment.start.x, 
                              circle.center.y - segment.start.y};
    double segmentLength (distance(segment.vector));
    double distScal (scalarProduct(segment.vector, segmentToCircle)/segmentLength);
    double distTest ( sqrt( pow(distance(segmentToCircle),2) - pow(distScal,2)));
    if (distTest - circle.radius < dist_min) return true;
    return false;
};