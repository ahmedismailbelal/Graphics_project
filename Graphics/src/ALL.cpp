#include "ALL.h"
#include<cmath>
#include<windows.h>
#include <tchar.h>
#include<cmath>
#include<iostream>
#include <fstream>
#include <stack>
#include <list>
#include <algorithm>
#include <gl\GL.h>
#include <gl\GLu.h>
#pragma comment(lib,"opengl32")
#pragma comment(lib,"glu32")
ALL::ALL()
{
    //ctor
}

void ALL::parametric(HDC hdc,int x1,int y1,int x2,int y2,COLORREF C)
{

    int dx=x2-x1;
    int dy=y2-y1;
    double dt=1.0 / max(dx,dy);
    for(double t=0; t<1; t+=dt)
    {
        double x=x1+t*dx;
        double y=y1+t*dy;
        SetPixel(hdc,Round(x),Round(y),C);

    }
}

void ALL::DDALine(HDC hdc,int xs,int ys,int xe,int ye,COLORREF color)
{
    int dx=xe-xs;
    int dy=ye-ys;
    SetPixel(hdc,xs,ys,color);
    if(abs(dx)>=abs(dy))
    {
        int x=xs,xinc= dx>0?1:-1;
        double y=ys,yinc=(double)dy/dx*xinc;
        while(x!=xe)
        {
            x+=xinc;
            y+=yinc;
            SetPixel(hdc,x,round(y),color);
        }
    }
    else
    {
        int y=ys,yinc= dy>0?1:-1;
        double x=xs,xinc=(double)dx/dy*yinc;
        while(y!=ye)
        {
            x+=xinc;
            y+=yinc;
            SetPixel(hdc,round(x),y,color);

        }
    }
}

void ALL::midpoint(HDC hdc,int x1,int y1,int x2,int y2,COLORREF C)
{
    int x=x1;
    int y=y1;
    SetPixel(hdc,x,y,C);
    int dx=x2-x1;
    int dy=y2-y1;
    if(abs(dx)>=abs(dy))
    {
        int d=dx-2*dy;
        int d1=2*dx-2*dy;
        int d2=-2*dy;

        while(x<x2)
        {
            if(d>0)
            {
                d+=d2;
                x++;
            }
            else
            {
                d+=d1;
                x++;
                y++;
            }
            SetPixel(hdc,x,y,C);

        }

    }
    else
    {
        int d=2*dx-dy;
        int d1=2*dx-2*dy;
        int d2=2*dx;
        while(y<y2)
        {
            int x=x1;
            int y=y1;
            if(d>0)
            {
                d+=d1;
                y++;
            }
            else
            {
                d+=d2;
                y++;
                x++;
            }
            SetPixel(hdc,x,y,C);

        }
    }
}


void ALL::Draw4Points(HDC hdc, int xc, int yc, int a, int b, COLORREF color)
{

    SetPixel(hdc, xc + a, yc + b, color);
    SetPixel(hdc, xc - a, yc + b, color);
    SetPixel(hdc, xc - a, yc - b, color);
    SetPixel(hdc, xc + a, yc - b, color);
}
void ALL::DrawDirectEllipse(HDC hdc, int xc, int yc, int A, int B, COLORREF c)
{

    int x = 0;
    double y = B;
    Draw4Points(hdc, xc, yc, 0, B, c);

    while (x * B * B < y * A * A)
    {
        x++;
        y = B * sqrt(1 - (double)x * x / (A * A));
        Draw4Points(hdc, xc, yc, x, Round(y), c);
    }
    int x1 = A;
    double y1 = 0;
    Draw4Points(hdc, xc, yc, A, 0, c);

    while (x1 * B * B > y1 * A * A)
    {
        y1++;
        x1 = A * sqrt(1 - (double)y1 * y1 / (B * B));
        Draw4Points(hdc, xc, yc, Round(x1), y1, c);
    }

}
void ALL::DrawPolarEllipse(HDC hdc, int xc, int yc, int A, int B, COLORREF c)
{

    double theta = 0, x = A, y = 0;


    while (x > y)
    {
        theta += 1.0 / max(A, B);
        x = A * cos(theta);
        y = B * sin(theta);
        Draw4Points(hdc, xc, yc, Round(x), Round(y), c);
    }
    while (x < y)
    {
        theta += 1.0 / max(A, B);
        x = A * cos(theta);
        y = B * sin(theta);
        Draw4Points(hdc, xc, yc, Round(x), Round(y), c);
    }
}

void ALL::DrawMidpointEllipse(HDC hdc, int xc, int yc, int A, int B, COLORREF color)
{


    float dx, dy, d1, d2, x, y;
    x = 0;
    y = B;
    d1 = (B * B) - (A * A * B) + (0.25 * A * A);
    dx = 2 * B * B * x;
    dy = 2 * A * A * y;
    while (dx < dy)
    {
        Draw4Points(hdc, xc, yc, x, y, color);
        if (d1 < 0)
        {
            x++;
            dx = dx + (2 * B * B);
            d1 = d1 + dx + (B * B);
        }
        else
        {
            x++;
            y--;
            dx = dx + (2 * B * B);
            dy = dy - (2 * A * A);
            d1 = d1 + dx - dy + (B * B);
        }
    }
    d2 = ((B * B) * ((x + 0.5) * (x + 0.5))) +
         ((A * A) * ((y - 1) * (y - 1))) -
         (A * A * B * B);
    while (y >= 0)
    {
        Draw4Points(hdc, xc, yc, x, y, color);
        if (d2 > 0)
        {
            y--;
            dy = dy - (2 * A * A);
            d2 = d2 + (A * A) - dy;
        }
        else
        {
            y--;
            x++;
            dx = dx + (2 * B * B);
            dy = dy - (2 * A * A);
            d2 = d2 + dx - dy + (A * A);
        }
    }

}

bool ALL::HDCToFile(const char* FilePath, HDC Context, RECT Area, uint16_t BitsPerPixel = 24)
{
    uint32_t Width = Area.right - Area.left;
    uint32_t Height = Area.bottom - Area.top;
    BITMAPINFO Info;
    BITMAPFILEHEADER Header;
    memset(&Info, 0, sizeof(Info));
    memset(&Header, 0, sizeof(Header));
    Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    Info.bmiHeader.biWidth = Width;
    Info.bmiHeader.biHeight = Height;
    Info.bmiHeader.biPlanes = 1;
    Info.bmiHeader.biBitCount = BitsPerPixel;
    Info.bmiHeader.biCompression = BI_RGB;
    Info.bmiHeader.biSizeImage = Width * Height * (BitsPerPixel > 24 ? 4 : 3);
    Header.bfType = 0x4D42;
    Header.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    char* Pixels = NULL;
    HDC MemDC = CreateCompatibleDC(Context);
    HBITMAP Section = CreateDIBSection(Context, &Info, DIB_RGB_COLORS, (void**)&Pixels, 0, 0);
    DeleteObject(SelectObject(MemDC, Section));
    BitBlt(MemDC, 0, 0, Width, Height, Context, Area.left, Area.top, SRCCOPY);
    DeleteDC(MemDC);
    std::fstream hFile(FilePath, std::ios::out | std::ios::binary);
    if (hFile.is_open())
    {
        hFile.write((char*)&Header, sizeof(Header));
        hFile.write((char*)&Info.bmiHeader, sizeof(Info.bmiHeader));
        hFile.write(Pixels, (((BitsPerPixel * Width + 31) & ~31) / 8) * Height);
        hFile.close();
        DeleteObject(Section);
        return true;
    }
    DeleteObject(Section);
    return false;
}
void ALL::load(HWND hWnd, HDC &hdc)
{
    string fileName = "picture.bmp";
    if (fileName == "")
        return ;
    HBITMAP hBitmap;
    hBitmap = (HBITMAP)::LoadImage(NULL, fileName.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HDC hLocalDC;
    hLocalDC = CreateCompatibleDC(hdc);
    BITMAP qBitmap;
    int iReturn = GetObject(reinterpret_cast<HGDIOBJ>(hBitmap), sizeof(BITMAP),reinterpret_cast<LPVOID>(&qBitmap));
    HBITMAP hOldBmp = (HBITMAP)SelectObject(hLocalDC, hBitmap);
    BOOL qRetBlit = BitBlt(hdc, 0, 0, qBitmap.bmWidth, qBitmap.bmHeight,hLocalDC, 0, 0, SRCCOPY);
    SelectObject (hLocalDC, hOldBmp);
    DeleteDC(hLocalDC);
    DeleteObject(hBitmap);
}
void ALL::save(HWND &hWnd)
{
    HDC hdc = GetDC(hWnd);
    string fileName = "picture.bmp";
    if (fileName == "")
        return ;
    int windowWidth ;
    int windowHeight;
    RECT rect;
    if(GetWindowRect(hWnd, &rect))
    {
        windowWidth = rect.right - rect.left;
        windowHeight = rect.bottom - rect.top;
    }
    RECT rect1 = {0, 0, windowWidth, windowHeight};
    HDCToFile(fileName.c_str(),hdc,rect1);
}

static ALL::Vector squ[4];
static ALL::Vector p[4];

void ALL::DrawHermiteCurve(HDC hdc, Vector& p1, Vector& T1, Vector& p2, Vector& T2, COLORREF c,int xx)
{
//ALL obj;
    double a0 = p1[0], a1 = T1[0],
           a2 = -3 * p1[0] - 2 * T1[0] + 3 * p2[0] - T2[0],
           a3 = 2 * p1[0] + T1[0] - 2 * p2[0] + T2[0];
    double b0 = p1[1], b1 = T1[1],
           b2 = -3 * p1[1] - 2 * T1[1] + 3 * p2[1] - T2[1],
           b3 = 2 * p1[1] + T1[1] - 2 * p2[1] + T2[1];
    for (double t = 0; t <= 1; t += 0.001)
    {
        double t2 = t * t, t3 = t2 * t;
        double x = a0 + a1 * t + a2 * t2 + a3 * t3;
        double y = b0 + b1 * t + b2 * t2 + b3 * t3;

        if(x>xx+0.5)
        {
            SetPixel(hdc, Round(x), Round(y), c);
        }


    }
}
void ALL::DrawHermiteCurve2(HDC hdc, Vector& p1, Vector& T1, Vector& p2, Vector& T2, COLORREF c)
{
//ALL obj;
    double a0 = p1[0], a1 = T1[0],
           a2 = -3 * p1[0] - 2 * T1[0] + 3 * p2[0] - T2[0],
           a3 = 2 * p1[0] + T1[0] - 2 * p2[0] + T2[0];
    double b0 = p1[1], b1 = T1[1],
           b2 = -3 * p1[1] - 2 * T1[1] + 3 * p2[1] - T2[1],
           b3 = 2 * p1[1] + T1[1] - 2 * p2[1] + T2[1];
    for (double t = 0; t <= 1; t += 0.001)
    {
        double t2 = t * t, t3 = t2 * t;
        double x = a0 + a1 * t + a2 * t2 + a3 * t3;
        double y = b0 + b1 * t + b2 * t2 + b3 * t3;

        SetPixel(hdc, Round(x), Round(y), c);
    }
}
void ALL::DrawCardinalSpline(HDC hdc, Vector P[], int n, double c, COLORREF C)
{
    double c1 =(double) 1 - c;
    Vector T0 = c1 * ((double)(P[2][0] - P[0][0]),(double)(P[2][1] - P[0][1]));
    for (int i = 0; i < n - 1; i++)
    {
        Vector T1=c1 * ((double)(P[i + 1][0] - P[i - 1][0]),(double)(P[i + 1][1] - P[i - 1][1]));
        DrawHermiteCurve2(hdc, P[i], T0, P[i+1], T1, C);
        T0 = T1;
    }


}
void ALL:: fillsqu(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c, int x3, int y3, int x4, int y4)
{
	Vector sq[2];
	int xx,xx2;
	int dx = x2 - x1;
	int dy = y2 - y1;
	int dx2 = x4 - x3;
	int dy2 = y4 - y3;
		if (x1 > x2)swap(x1, y1, x2, y2);
		xx = x1;
		int x11 = x1;
		if (x3 > x4)swap(x3, y3, x4, y4);
		xx2 = x3;
		int x33 = x3;
		while (x11 < x2)
		{
			x11++;
			x33++;
			double y11 = y1 + (double)(x11 - x1) * dy / dx;
			double y33 = y3 + (double)(x33 - x3) * dy2 / dx2;
			sq[0] = Vector(x11-1,y11-1);
			sq[1] = Vector(x33 - 1, y33 - 1);

			Vector T1(0.5 * (x33 - x11), 0.5 * (y33 - y11));
			Vector T2(0.5 * (x11 - x33), 0.5 * (y11 - y33));
			DrawHermiteCurve(hdc,sq[0] , T2, sq[1], T1, c,xx);

		}



}


void ALL:: swap(int& x1, int& y1, int& x2, int& y2)
{
    int tmp = x1;
    x1 = x2;
    x2 = tmp;
    tmp = y1;
    y1 = y2;
    y2 = tmp;
}
int ALL:: Round(double x)
{
    return (int)(x + 0.5);
}

void ALL::Draw8Points(HDC hdc,int xc, int yc, int x, int y,COLORREF c)
{

    SetPixel(hdc,xc + x, yc + y,c);
    SetPixel(hdc,xc + x, yc - y,c);
    SetPixel(hdc,xc - x, yc - y,c);
    SetPixel(hdc,xc - x, yc + y,c);
    SetPixel(hdc,xc + y, yc + x,c);
    SetPixel(hdc,xc + y, yc - x,c);
    SetPixel(hdc,xc - y, yc - x,c);
    SetPixel(hdc,xc - y, yc + x,c);


}
//Direct Circle algorithm
void ALL:: DrawCircle1(HDC hdc,int xc, int yc, int R,COLORREF c)
{
    int x = 0;
    double y = R;
    Draw8Points(hdc,xc, yc, 0, R,c);
    while (x < y)
    {
        x++;
        y = sqrt((double)R * R - x * x);
        Draw8Points(hdc,xc, yc, x, Round(y),c);
    }
}
//Polar Circle algorithm
void ALL:: DrawCircle2(HDC hdc,int xc, int yc, int R,COLORREF c)
{
    double x = R;
    int y = 0;
    double theta = 0;
    Draw8Points(hdc,xc, yc, R, 0,c);
    while (x > y)
    {
        theta +=(double) 1/R;
        x = R * cos(theta);

        y = R * sin(theta);
        Draw8Points(hdc,xc, yc, Round(x), Round(y),c);
    }
}
//Iterative Polar Circle algorithm
void ALL:: DrawCircle3(HDC hdc,int xc, int yc, int R,COLORREF c)
{
    double x = R;
    double y = 0;
    double dtheta = (double)1 / R;
    double h= (double)cos(dtheta);
    double s= (double)sin(dtheta);
    Draw8Points(hdc,xc, yc, R, 0,c);
    while (x > y)
    {

        double x1 = (x * h - y * s);

        y = (x * s + y * h);
        x = x1;
        Draw8Points(hdc,xc, yc, Round(x), Round(y),c);
    }

}
double ALL:: f(double x, double y, double r)
{

    double d = x * x + y * y - r * r;
    return (double)d;
}
//Midpoint Circle algorithm
void ALL:: DrawCircle4(HDC hdc,int xc, int yc, int R,COLORREF c)
{

    double x = 0;
    double y = R;
    Draw8Points(hdc,xc, yc, 0, R,c);
    while (x < y)
    {
        double d = f(x + 1, y - (1 / 2), R);
        if (d < 0)
        {
            x++;
        }
        else
        {
            x++;
            y--;
        }
        Draw8Points(hdc,xc, yc, x, y,c);
    }

}
//Modified Midpoint Circle algorithm
void ALL:: DrawCircle5(HDC hdc,int xc, int yc, int R,COLORREF c)
{

    double x = 0;
    double y = R;
    double d = 1 - R;
    Draw8Points(hdc,xc, yc, 0, R,c);
    while (x < y)
    {
        if (d < 0)
        {
            d += 2 * x + 3;
            x++;
        }
        else
        {
            d += 2 * (x-y) + 5;
            x++;
            y--;
        }
        Draw8Points(hdc,xc, yc, x, y,c);
    }


}

void ALL:: FillFourth(HDC hdc,int xc, int yc, int x, int y,COLORREF c)
{
    SetPixel(hdc,xc + x, yc + y,c);
    SetPixel(hdc,xc + y, yc + x,c);
}

void ALL:: FillThird(HDC hdc,int xc, int yc, int x, int y,COLORREF c)
{


    SetPixel(hdc,xc - x, yc + y,c);
    SetPixel(hdc,xc - y, yc + x,c);
}
void ALL:: FillSecond(HDC hdc,int xc, int yc, int x, int y,COLORREF c)
{

    SetPixel(hdc,xc - x, yc - y,c);
    SetPixel(hdc,xc - y, yc - x,c);
}
void ALL:: FillFirst(HDC hdc,int xc, int yc, int x, int y,COLORREF c)
{

    SetPixel(hdc,xc + x, yc - y,c);

    SetPixel(hdc,xc + y, yc - x,c);
}


void ALL:: FillCircle1(HDC hdc,int xc, int yc, double R,int o,COLORREF c)
{

    if (o == 1)
    {
        while (R > 0)
        {
            int x = 0;
            double y = R;
            FillFirst(hdc,xc, yc, 0, R,c);
            while (x < y)
            {
                x++;
                y = sqrt((double)R * R - x * x);

                FillFirst(hdc,xc, yc, x, Round(y),c);

            }
            R = (double)R - 0.1;
        }

    }
    else if (o == 2)
    {
        while (R > 0)
        {
            int x = 0;
            double y = R;
            FillSecond(hdc,xc, yc, 0, R,c);
            while (x < y)
            {
                x++;
                y = sqrt((double)R * R - x * x);
                FillSecond(hdc,xc, yc, x, Round(y),c);

            }
            R =(double) R - 0.1;
        }

    }
    else if (o == 3)
    {
        while (R > 0)
        {
            int x = 0;
            double y = R;
            FillThird(hdc,xc, yc, 0, R,c);
            while (x < y)
            {
                x++;
                y = sqrt((double)R * R - x * x);
                FillThird(hdc,xc, yc, x, Round(y),c);

            }
            R = (double)R - 0.1;
        }

    }
    else if (o == 4)
    {
        while (R > 0)
        {
            int x = 0;
            double y = R;
            FillFourth(hdc,xc, yc, 0, R,c);
            while (x < y)
            {
                x++;
                y = sqrt((double)R * R - x * x);
                FillFourth(hdc,xc, yc, x, Round(y),c);

            }
            R = (double)R - 0.1;
        }

    }

}








void ALL:: DrawLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{

    int dx = x2 - x1;
    int dy = y2 - y1;
    if (abs(dy) <= abs(dx))
    {
        if (x1 > x2)swap(x1, y1, x2, y2);
        SetPixel(hdc, x1, y1, c);
        int x = x1;
        while (x < x2)
        {
            x++;
            double y = y1 + (double)(x - x1) * dy / dx;
            SetPixel(hdc, x, Round(y), c);

        }
    }
    else
    {
        if (y1 > y2)swap(x1, y1, x2, y2);
        SetPixel(hdc, x1, y1, c);
        int y = y1;
        while (y < y2)
        {
            y++;
            double x = x1 + (double)(y - y1) * dx / dy;
            SetPixel(hdc, Round(x), y, c);


        }
    }

}


void ALL:: fillQuarter(HDC hdc, int xc, int yc, int a, int b, int Quarter, COLORREF c)
{
    if (Quarter == 1)
    {
        //First quarter: x is +ve and y is -ve
        DrawLine(hdc, xc, yc, xc + a, yc - b, c);
        DrawLine(hdc, xc, yc, xc + b, yc - a, c);


    }
    else if (Quarter == 2)
    {

        //Second quarter: x is +ve and y is +ve
        DrawLine(hdc, xc, yc, xc + a, yc + b, c);
        DrawLine(hdc, xc, yc, xc + b, yc + a, c);

    }
    else if (Quarter == 3)
    {

        //Third quarter: x is -ve and y is +ve
        DrawLine(hdc, xc, yc, xc - a, yc + b, c);
        DrawLine(hdc, xc, yc, xc - b, yc + a, c);

    }
    else if (Quarter == 4)
    {
        //Fourth quarter: x is -ve and y is -ve
        DrawLine(hdc, xc, yc, xc - b, yc - a, c);
        DrawLine(hdc, xc, yc, xc - a, yc - b, c);

    }


}

void  ALL:: iterativePolarCircle(HDC hdc, int xc, int yc, int R, int Quarter, COLORREF c)
{

    double x = R, y = 0;
    double dtheta = (double)1 / R;
    double st = sin(dtheta), ct = cos(dtheta);
    while (x > y)
    {
        double x1 = x * ct - y * st;
        y = x * st + y * ct;
        x = x1;
        Draw8Points(hdc, xc, yc, Round(x), Round(y), c);
        fillQuarter(hdc, xc, yc, Round(x), Round(y), Quarter, c);

    }

}

void ALL:: recursiveMyFill(HDC hdc, int x, int y, COLORREF bc, COLORREF fc)
{
    COLORREF c = GetPixel(hdc, x, y);
    if (c == bc || c == fc) return;

    SetPixel(hdc, x, y, fc);
    recursiveMyFill(hdc, x + 1, y, bc, fc);
    recursiveMyFill(hdc, x - 1, y, bc, fc);
    recursiveMyFill(hdc, x, y + 1, bc, fc);
    recursiveMyFill(hdc, x, y - 1, bc, fc);
}

void ALL:: nonRecursiveMyFill(HDC hdc, int& x, int& y, COLORREF bc, COLORREF fc)
{
    stack<vertex> s;
    vertex v(x, y);
    //s.push(v(x,y));
    s.push(v);
    while (!s.empty())
    {
        vertex p = s.top();
        s.pop();
        COLORREF c = GetPixel(hdc, p.x, p.y);
        if (c == bc || c==fc ) continue;
        else
        {
            SetPixel(hdc, p.x, p.y, fc);
            vertex p2(p.x, p.y - 1);
            s.push(p2);
            vertex p3(p.x, p.y + 1);
            s.push(p3);
            vertex p4(p.x + 1, p.y);
            s.push(p4);
            vertex p5(p.x - 1, p.y);
            s.push(p5);

        }
    }

}

void ALL:: SwapPoints(POINT& v1, POINT& v2)
{
    POINT tmp = v1;
    v1 = v2;
    v2 = tmp;
}
//Initialize EdgeTable with Max and Min
void ALL:: InitEdgeTable(EdgeTable tbl)
{
    for (int i = 0; i < 800; i++)
    {
        tbl[i].xleft = 10000000;
        tbl[i].xright = -10000000;
    }
}

void ALL:: scanEdge(POINT p1, POINT p2,EdgeTable tbl)
{
    //Check if edge is horizontal
    if (p1.y == p2.y) return;
    if (p1.y > p2.y) SwapPoints(p1, p2);//Because program will not work
    double minv = (p2.x - p1.x) / (double)(p2.y - p1.y);
    double x = p1.x; //X is double because it will increment with minv
    int y = p1.y; //y is int because it will increment pixel by pixel (y++)
    while (y < p2.y)
    {
        if (x < tbl[y].xleft) tbl[y].xleft = ceil(x);
        if (x > tbl[y].xright) tbl[y].xright = floor(x);
        y++;
        x += minv;
    }//end while

}//end scanEdge

//polygon is array of vertixes p[], n is size of arr
void ALL:: polygon2Table(POINT p[],int n,EdgeTable tbl)
{
//we want to scan the polygon and send each two points to scanEdge() function
//v2 and v1 ---> First and Last point of each edge
    POINT v1 = p[n - 1];//Last point
    for (int i = 0; i < n; i++)
    {
        POINT v2 = p[i];//First point
        scanEdge(v1, v2, tbl);
        v1 = v2;
    }
}
void ALL:: table2Screen(HDC hdc, EdgeTable tbl, COLORREF c)
{
    for (int i = 0; i < 800; i++)
    {
        if (tbl[i].xleft < tbl[i].xright)
            DrawLine(hdc,tbl[i].xleft,i,tbl[i].xright,i,c);
    }
}

void ALL:: fillPolygon(HDC hdc, POINT p[], int n, COLORREF c)
{
    EdgeTable tbl;
    InitEdgeTable(tbl);
    polygon2Table(p,n,tbl);
    table2Screen(hdc,tbl,c);
}





void ALL:: scanEdgenon(POINT v1, POINT v2, EdgeTablenon tbl)
{
    if (v1.y == v2.y) return;//Horizontal edge
    if (v1.y > v2.y) SwapPoints(v1, v2);//Because program will not work
    Edgerec rec(v1.x, v2.y, (double)(v2.x - v1.x) / (v2.y - v1.y));
    tbl[v1.y].push_back(rec);//go to index y and append rec to the linked list at this index
}

//Scan each edge in the array and send it to Edge Table
void ALL:: polygon2tablenon(POINT p[], int n, EdgeTablenon tbl)
{
    POINT v1 = p[n - 1]; //Last point in the polygon
    for (int i = 0; i < n; i++)
    {
        POINT v2 = p[i];
        scanEdgenon(v1, v2, tbl);
        v1 = v2;//Bec in next edge..our last point will be the first point
    }
}
void ALL:: table2screennon(HDC hdc, EdgeTablenon tbl, COLORREF c)
{
    int y = 0;
    //loop over edge table until we find a not null

    list<Edgerec>::iterator it;

    while (tbl[y].size() == 0) y++;
    list<Edgerec> activeList = tbl[y];
    while (activeList.size() != 0)  //Or: activeList !=NULL
    {
        //1- Sort activeList according to x

        activeList.sort([](Edgerec& a, Edgerec& b)
        {
            return a.x < b.x;
        });
        //2-For each pair of successive nodes in active (no overlapping)...Draw line from node1 to node2
        for (it = activeList.begin(); it != activeList.end(); it++)
        {
            Edgerec& node1 = *it;
            it++;
            if (it == activeList.end()) break;
            Edgerec& node2 = *it;
            DrawLine(hdc, ceil(node1.x), y, floor(node2.x), y, c);
        }
        //3-Move to next scanline
        y++;
        //4-For each node N in activeList...If N.ymax==y...remove N from active
        for (it = activeList.begin(); it != activeList.end();)
        {
            if (it->ymax == y)
            {
                it = activeList.erase(it);
            }
            else it++;
        }
        //5-for each node N in activeList, update N.x=N.x+N.minv
        for (it = activeList.begin(); it != activeList.end(); it++)
        {
            it->x = it->x + it->minv;
        }
        //6-Append tbl[y] to activeList if tbl[y] is not empty
        if (tbl[y].size() != 0)
        {
            activeList.splice(activeList.end(), tbl[y]);
        }
    }
}

void ALL:: fillPolygonnon(HDC hdc, POINT p[], int n, COLORREF c)
{
    EdgeTablenon tbl;

    polygon2tablenon(p, n, tbl);
    table2screennon(hdc, tbl, c);

}





static ALL:: Vector rec[2];
static float xl;
static float xr;
static float yt;
static float yb;
void ALL:: DrawRectangle(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{
    DrawLine(hdc, x1, y1, x2, y1, RGB(255, 0, 0));
    DrawLine(hdc, x2, y1, x2, y2, RGB(255, 0, 0));
    DrawLine(hdc, x2, y2, x1, y2, RGB(255, 0, 0));
    DrawLine(hdc, x1, y2, x1, y1, RGB(255, 0, 0));
    xl = min(x1,x2);
    xr =max(x1, x2);
    yt = max(y1, y2);
    yb = min(y1,y2);
}
//for point
//**************************************
static ALL:: Vector P[1];
DWORD WINAPI ALL::clippingPoint(void *lp)
{
    HWND hwnd = (HWND)lp;
    HDC hdc;

    hdc = GetDC(hwnd);
    int x = P[0][0];
    int y = P[0][1];
    if (x >= xl && x <= xr && y >= yb && y <= yt)
    {
        SetPixel(hdc, x, y, RGB(255, 0, 0));
    }

    ReleaseDC(hwnd, hdc);
    return 0;
}
//***************************************

//for line
//***************************************

union OutCode
{
    unsigned  All : 4;
    struct
    {
        unsigned left : 1,top : 1,right : 1,bottom : 1;
    };
};


OutCode GetOutCode(double x, double y, int xleft, int ytop, int xright, int ybottom)
{
    OutCode out;
    out.All = 0;
    if (x < xleft)out.left = 1;
    else if (x > xright)out.right = 1;
    if (y > ytop)out.top = 1;
    else if (y < ybottom)out.bottom = 1;
    return out;
}
void ALL:: VIntersect(double xs, double ys, double xe, double ye, int x, double* xi, double* yi)
{
    *xi = x;
    *yi = ys + (x - xs) * (ye - ys) / (xe - xs);
}
void ALL:: HIntersect(double xs, double ys, double xe, double ye, int y, double* xi, double* yi)
{
    *yi = y;
    *xi = xs + (y - ys) * (xe - xs) / (ye - ys);
}
void CohenSuth(HDC hdc, int xs, int ys, int xe, int ye, int xleft, int ytop, int xright, int ybottom)
{
    ALL O;
    double x1 = xs, y1 = ys, x2 = xe, y2 = ye;
    OutCode out1 = GetOutCode(x1, y1, xleft, ytop, xright, ybottom);
    OutCode out2 = GetOutCode(x2, y2, xleft, ytop, xright, ybottom);
    if (out1.All & out2.All) return;
    if (!out1.All && !out2.All)
    {
        O.DrawLine(hdc, O.Round(x1), O.Round(y1), O.Round(x2), O.Round(y2), RGB(255, 0, 0));
        return;
    }
    while ((out1.All || out2.All) && !(out1.All & out2.All))
    {
        double xi, yi;
        if (out1.All)
        {
            if (out1.left)O.VIntersect(x1, y1, x2, y2, xleft, &xi, &yi);
            else if (out1.top)O.HIntersect(x1, y1, x2, y2, ytop, &xi, &yi);
            else if (out1.right)O.VIntersect(x1, y1, x2, y2, xright, &xi, &yi);
            else O.HIntersect(x1, y1, x2, y2, ybottom, &xi, &yi);
            x1 = xi;
            y1 = yi;
            out1 = GetOutCode(x1, y1, xleft, ytop, xright, ybottom);
        }
        else
        {
            if (out2.left)O.VIntersect(x1, y1, x2, y2, xleft, &xi, &yi);
            else if (out2.top)O.HIntersect(x1, y1, x2, y2, ytop, &xi, &yi);
            else if (out2.right)O.VIntersect(x1, y1, x2, y2, xright, &xi, &yi);
            else O.HIntersect(x1, y1, x2, y2, ybottom, &xi, &yi);
            x2 = xi;
            y2 = yi;
            out2 = GetOutCode(x2, y2, xleft, ytop, xright, ybottom);
        }
    }
    if (!out1.All && !out2.All)
    {
        O.DrawLine(hdc, O.Round(x1), O.Round(y1), O.Round(x2), O.Round(y2), RGB(255, 0, 0));

    }

}
static ALL:: Vector l[2];
DWORD clippingLine(void* lp)
{
    HWND hwnd = (HWND)lp;
    HDC hdc;
    hdc = GetDC(hwnd);
    CohenSuth(hdc, l[0][0], l[0][1], l[1][0], l[1][1], xl, yt, xr, yb);
    ReleaseDC(hwnd, hdc);
    return 0;
}

