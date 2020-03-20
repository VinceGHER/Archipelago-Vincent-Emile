// Module Tools (implementation)
// made by Vincent GHEROLD and Emile CAILLOL
// version 1.0 

#include <cmath>

#include "tools.h"

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
bool tools::overlapBetweenCircles(Circle circle1, Circle circle2, double dist_min){
    double totalradius( circle1.radius + circle2.radius );
    if (distance(circle1.center, circle2.center) - totalradius < dist_min)
        return true;
    return false;
};
bool tools::overlapBetweenCircleSegment(Circle circle, Segment segment, 
                                        double dist_min){
    Vector segmentToCircle = {circle.center.x - segment.start.x, 
                              circle.center.y - segment.start.y};
    Vector segmentVector = {segment.end.x - segment.start.x,
                            segment.end.y - segment.start.y};
                            
    double segmentLength (distance(segment.start,segment.end));
    double distScal (scalarProduct(segmentVector, segmentToCircle)/segmentLength);

    if (distScal < 0 or distScal > segmentLength) return false;

    double distTest ( sqrt( pow(distance(segmentToCircle),2) - pow(distScal,2) ) );
    double distCercleTest (distTest - circle.radius);

    if (distCercleTest > dist_min) return false;

    return true;
};