#ifndef ALL_H
#define ALL_H
#include<windows.h>
#include <tchar.h>
#include<cmath>
#include<iostream>
#include <fstream>
#include <stack>
#include <list>
#include <algorithm>
using namespace std;


class ALL
{
public:
    ALL();

    void swap(int&, int&, int&, int& );
    int Round(double );

    struct Vector
    {
        int v[2];
        Vector(int x = 0, int y = 0)
        {
            v[0] = x;
            v[1] = y;
        }
        int& operator[](int i)
        {
            return v[i];
        }
    };
    struct vertex
    {
        int x;
        int y;
        vertex(int x, int y)
        {
            this->x = x;
            this->y = y;
        }

    };
    struct Edgerec
    {
        double x, ymax, minv;
        Edgerec(double x = 0.0, double ymax = 0.0, double minv = 0.0) :x(x), ymax(ymax), minv(minv) {}
    };
    typedef struct
    {
        int xleft, xright;
    } EdgeTable[800];
    typedef list<Edgerec> EdgeTablenon[800];
    void Draw4Points(HDC hdc, int xc, int yc, int a, int b, COLORREF color);
    void DrawDirectEllipse(HDC hdc, int xc, int yc, int A, int B, COLORREF c);
    void DrawPolarEllipse(HDC hdc, int xc, int yc, int A, int B, COLORREF c);
    void DrawMidpointEllipse(HDC hdc, int xc, int yc, int A, int B, COLORREF color);

    void DrawHermiteCurve(HDC hdc, Vector& p1, Vector& T1, Vector& p2, Vector& T2, COLORREF c,int xx);

    void DrawHermiteCurve2(HDC hdc, Vector& p1, Vector& T1, Vector& p2, Vector& T2, COLORREF c);
    void parametric(HDC hdc,int x1,int y1,int x2,int y2,COLORREF C);

    void DDALine(HDC hdc,int xs,int ys,int xe,int ye,COLORREF c);
    void midpoint(HDC hdc,int x1,int y1,int x2,int y2,COLORREF C);

    void DrawCardinalSpline(HDC hdc, Vector P[], int n, double c, COLORREF C);

    void fillsqu(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c, int x3, int y3, int x4, int y4);

    bool HDCToFile(const char* FilePath, HDC Context, RECT Area, uint16_t BitsPerPixel);

    void load(HWND hWnd, HDC &hdc);

    void save(HWND &hWnd);

    void Draw8Points(HDC,int, int, int, int,COLORREF  );
//Direct Circle algorithm
    void DrawCircle1(HDC,int, int, int,COLORREF );
//Polar Circle algorithm
    void DrawCircle2(HDC,int, int, int,COLORREF );
//Iterative Polar Circle algorithm
    void DrawCircle3(HDC,int, int, int,COLORREF );

    double f(double, double, double );
//Midpoint Circle algorithm
    void DrawCircle4(HDC,int, int, int,COLORREF);
//Modified Midpoint Circle algorithm
    void DrawCircle5(HDC,int, int, int,COLORREF);



    void FillFourth(HDC,int, int, int, int,COLORREF );
    void FillThird(HDC,int, int, int, int,COLORREF );
    void FillSecond(HDC,int, int, int, int,COLORREF );
    void FillFirst(HDC,int, int, int, int,COLORREF );
    void FillCircle1(HDC,int, int, double,int,COLORREF);



    void DrawLine(HDC, int, int, int, int, COLORREF );
//void fillsqu(HDC , int , int , int , int , COLORREF , Vector& , Vector& , Vector& , Vector& );

    void iterativePolarCircle(HDC hdc, int xc, int yc, int R, int Quarter, COLORREF c);

    void fillQuarter(HDC hdc, int xc, int yc, int a, int b, int Quarter, COLORREF c);

    void recursiveMyFill(HDC hdc, int x, int y, COLORREF bc, COLORREF fc);

    void nonRecursiveMyFill(HDC hdc, int& x, int& y, COLORREF bc, COLORREF fc);


    void SwapPoints(POINT& v1, POINT& v2);
    void InitEdgeTable(EdgeTable tbl);

    void scanEdge(POINT p1, POINT p2,EdgeTable tbl);
    void polygon2Table(POINT p[],int n,EdgeTable tbl) ;
    void table2Screen(HDC hdc, EdgeTable tbl, COLORREF c);

    void fillPolygon(HDC hdc, POINT p[], int n, COLORREF c);


    void scanEdgenon(POINT v1, POINT v2, EdgeTablenon tbl) ;
    void polygon2tablenon(POINT p[], int n, EdgeTablenon tbl);
    void table2screennon(HDC hdc, EdgeTablenon tbl, COLORREF c);
    void fillPolygonnon(HDC hdc, POINT p[], int n, COLORREF c);




    void DrawRectangle(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c);
    DWORD WINAPI clippingPoint(void* lp);
    void VIntersect(double xs, double ys, double xe, double ye, int x, double* xi, double* yi);
    void HIntersect(double xs, double ys, double xe, double ye, int y, double* xi, double* yi);
    DWORD WINAPI clippingLine(void* lp);

};

#endif // ALL_H
