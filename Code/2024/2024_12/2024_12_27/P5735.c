#include <stdio.h>
#include <math.h>

double calculate_distance(double x1, double y1, double x2, double y2);

int main() {
    double x1, y1, x2, y2, x3, y3;
    
    scanf("%lf %lf", &x1, &y1);
    scanf("%lf %lf", &x2, &y2);
    scanf("%lf %lf", &x3, &y3);
    
    double side1 = calculate_distance(x1, y1, x2, y2);
    double side2 = calculate_distance(x2, y2, x3, y3);
    double side3 = calculate_distance(x3, y3, x1, y1);

    double p = side1 + side2 + side3;
    
    printf("%.2lf\n", p);
    
    return 0;
}

double calculate_distance(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}