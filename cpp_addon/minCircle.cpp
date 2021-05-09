#include "minCircle.h"

int checkIfPointInCircle(Circle c, Point p)
{
	float distance = sqrt(pow(c.center.x - p.x, 2) +
						  pow(c.center.y - p.y, 2));
	if (distance <= c.radius)
	{
		return 1;
	}
	return 0;
}

Circle createCircleFromTwoPoints(Point p1, Point p2)
{
	float distance = sqrt(pow(p1.x - p2.x, 2) +
						  pow(p1.y - p2.y, 2));
	float x = (p2.x + p1.x) / 2;
	float y = (p2.y + p1.y) / 2;
	return Circle(Point(x, y), distance / 2);
}

Circle createCircleFromThreePoints(Point p1, Point p2, Point p3)
{
	float m_p1p2 = (p1.y - p2.y) / (p1.x - p2.x);
	float m_p2p3 = (p2.y - p3.y) / (p2.x - p3.x);

	float ver_m_p1p2 = -1 / m_p1p2;
	float ver_m_p2p3 = -1 / m_p2p3;

	Point middle_p1p2((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
	Point middle_p2p3((p2.x + p3.x) / 2, (p2.y + p3.y) / 2);

	float b_ver_p1p2 = (-ver_m_p1p2 * middle_p1p2.x) + middle_p1p2.y;
	float b_ver_p2p3 = (-ver_m_p2p3 * middle_p2p3.x) + middle_p2p3.y;

	float center_x = (b_ver_p1p2 - b_ver_p2p3) / (ver_m_p2p3 - ver_m_p1p2);
	float center_y = (ver_m_p1p2 * center_x) + b_ver_p1p2;

	float radius = sqrt(pow(p1.x - center_x, 2) +
						pow(p1.y - center_y, 2));

	return Circle(Point(center_x, center_y), radius);
}

Circle handleBaseCases(vector<Point> boundery_points)
{
	if (boundery_points.size() == 0)
	{
		return Circle({0, 0}, 0);
	}
	if (boundery_points.size() == 1)
	{
		return Circle(boundery_points[0], 0);
	}
	if (boundery_points.size() == 2)
	{
		return createCircleFromTwoPoints(boundery_points[0], boundery_points[1]);
	}
	if (boundery_points.size() == 3)
	{
		return createCircleFromThreePoints(boundery_points[0],boundery_points[1],boundery_points[2]);
	}
	return Circle(Point(0, 0), 0);
}

Circle findMinCircleRecursion(Point **&points, size_t size, vector<Point> boundery_points)
{
	// base cases
	if (boundery_points.size() == 3 || size == 0)
	{
		return handleBaseCases(boundery_points);
	}
	Point point = *(points[size - 1]);
	Circle c = findMinCircleRecursion(points, size - 1, boundery_points);
	if (checkIfPointInCircle(c, point))
	{
		return c;
	}
	boundery_points.push_back(point);
	return findMinCircleRecursion(points, size - 1, boundery_points);
}

Circle findMinCircle(Point **points, size_t size)
{
	vector<Point> boundery_points;
	return findMinCircleRecursion(points, size, boundery_points);
}