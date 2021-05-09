#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

using namespace std;

// ------------ DO NOT CHANGE -----------
class Circle{
public:
	Point center;
	float radius;
	Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

// return 1 if point in the circle, otherwise 0
int checkIfPointInCircle(Circle c, Point p);

Circle createCircleFromTwoPoints(Point p1, Point p2);

Circle createCircleFromThreePoints(Point p1, Point p2, Point p3);

Circle handleBaseCases(vector<Point> boundery_points);

Circle findMinCircleRecursion(Point **&points, size_t size, vector<Point> boundery_points);

Circle findMinCircle(Point **points, size_t size);

#endif /* MINCIRCLE_H_ */