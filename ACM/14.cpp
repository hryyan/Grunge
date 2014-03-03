#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double parabola[3];
double straight[2];

typedef struct point
{
    double x;
    double y;
}point;

double getdet2(double *c1, double *c2)
{
    //printf("Begin get det2\n");
    return c1[0]*c2[1] - c1[1]*c2[0];
}

double getdet3(double *c1, double *c2, double *c3)
{
    //printf("Begin get det3\n");
    return c1[0]*c2[1]*c3[2]+c1[1]*c2[2]*c3[0]+c1[2]*c2[0]*c3[1]\
    -c1[0]*c2[2]*c3[1]-c1[1]*c2[0]*c3[2]-c1[2]*c2[1]*c3[0];
}

void getParabola(const point &p1, const point &p2, const point &p3)
{
    //printf("Begin get parabola\n");
    double *c1, *c2, *c3, *c4;
    double d, d1, d2, d3;
    c1 = (double*)malloc(sizeof(double)*3);
    c2 = (double*)malloc(sizeof(double)*3);
    c3 = (double*)malloc(sizeof(double)*3);
    c4 = (double*)malloc(sizeof(double)*3);
    c1[0] = pow(p1.x, 2); c1[1] = pow(p2.x, 2); c1[2] = pow(p3.x, 2);
    c2[0] = p1.x;         c2[1] = p2.x;         c2[2] = p3.x;
    c3[0] = 1;            c3[1] = 1;            c3[2] = 1;
    c4[0] = p1.y;         c4[1] = p2.y;         c4[2] = p3.y;
    d = getdet3(c1, c2, c3);
    d1 = getdet3(c4, c2, c3);
    d2 = getdet3(c1, c4, c3);
    d3 = getdet3(c1, c2, c4);
    free(c1);
    free(c2);
    free(c3);
    free(c4);
    parabola[0] = d1/d;   parabola[1] = d2/d;   parabola[2] = d3/d;
    // printf("%f, %f, %f\n", parabola[0], parabola[1], parabola[2]);
}

void getStraight(const point &p2, const point &p3)
{
    //printf("Begin get straight\n");
    double *c1, *c2, *c3;
    double d, d1, d2;
    c1 = (double*)malloc(sizeof(double)*2);
    c2 = (double*)malloc(sizeof(double)*2);
    c3 = (double*)malloc(sizeof(double)*2);
    c1[0] = p2.x;   c1[1] = p3.x;
    c2[0] = 1;      c2[1] = 1;
    c3[0] = p2.y;   c3[1] = p3.y;
    d = getdet2(c1, c2);
    d1 = getdet2(c3, c2);
    d2 = getdet2(c1, c3);
    free(c1);
    free(c2);
    free(c3);
    straight[0] = d1/d;     straight[1] = d2/d;
    // printf("%f, %f\n", straight[0], straight[1]);
}

double f(double x)
{
    return parabola[0]*pow(x,2)+x*parabola[1]+parabola[2];
}

double g(double x)
{
    return x*straight[0]+straight[1]; 
}

double getIntegral(double a, double b, int n)
{
    double sum = 0.0;
    double gaps = (b - a)/double(n);
    for (int i = 0; i < n; ++i)
    {
        sum += (gaps/2.0)*(f(a+i*gaps)-g(a+i*gaps)+f(a+(i+1)*gaps)-g(a+(i+1)*gaps));
    }
    return sum;
}

int main()
{
    // freopen("14.input", "r", stdin);
    int n;
    point p1, p2, p3;
    double area;
    scanf("%d", &n);
    while(n--)
    {
        //printf("Begin\n");
        scanf("%lf %lf", &p1.x, &p1.y);
        scanf("%lf %lf", &p2.x, &p2.y);
        scanf("%lf %lf", &p3.x, &p3.y);
        getParabola(p1, p2, p3);
        getStraight(p2, p3);
        area = getIntegral(p2.x, p3.x, 10000);
        printf("%.2lf\n", area);
    }
}