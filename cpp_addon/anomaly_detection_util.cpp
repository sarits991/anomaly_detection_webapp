#include <math.h>
#include "anomaly_detection_util.h"

// calculate the average of the numbers in array.
float avg(float* arr,int size){
    //sum all the numbers
    float sum=0;
     for (int i = 0; i < size; i++)
    {
       sum+=arr[i];
    }
    return sum/(float)size;
}

// returns the variance of X and Y
float var(float* x, int size){

    //the average of the numbers in the array (u)
    float average = avg(x,size);

    // for each number in the array substarct the average and square the result
    float sumSquared=0;
    for (int i = 0; i < size; i++)
    {
        sumSquared+=(x[i]-average)*(x[i]-average);
    }

    return sumSquared/(float)size;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){

    // the average of x array
    float xAverage=avg(x,size);
     // the average of y array
    float yAverage=avg(y,size);

    // for each number in the x and y array substarct the average and square the result
    float sumSquared=0;
    for (int i = 0; i < size; i++)
    {
        sumSquared+=(x[i]-xAverage)*(y[i]-yAverage);
    }

    return sumSquared/(float)size;
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){

    // get covariance
    float covariance=cov(x,y,size);
    // get variance
    float x_variance=var(x,size);
    float y_variance=var(y,size);

    // sqrt to variance
    float x_var_sqrt=sqrt(x_variance);
    float y_var_sqrt=sqrt(y_variance);
    return (covariance / (x_var_sqrt*y_var_sqrt));
}

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size){

    // split the points array to x values and y values
    float* x_points=new float[size];
    float* y_points=new float[size];
    for (int i = 0; i < size; i++)
    {
        Point* point=points[i];
        x_points[i]=point->x;
        y_points[i]=point->y;
    }

    // calculate "a" in the line
    float a= (cov(x_points,y_points,size) / var(x_points,size));

    // the average of x points
    float x_average=avg(x_points,size);
    // the average of y points
    float y_average=avg(y_points,size);

    // calculate "b" in the line
    float b = y_average-(a*x_average);

    // free memory
    delete(x_points);
    delete(y_points);

    return Line(a,b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){

    // create line from the points
    Line line = linear_reg(points,size);
    // using the second dev function to calculate distance
    float distance = dev(p,line);
    return distance;
}

// returns the deviation between point p and the line
float dev(Point p,Line l){

    // find the y value on the line with the x value point
    float point_on_line=l.f(p.x);

    // substract the value on line and the 'real' value
    return fabs(point_on_line-p.y);
}
