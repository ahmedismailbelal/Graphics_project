#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif
#include<ALL.h>
#include <tchar.h>
#include<windows.h>
#include<cmath>
#include<iostream>
using namespace std;

#define LineMenu_DDA 1
#define LineMenu_Midpoint 2
#define LineMenu_parametric 3
#define CircleMenu_Direct 4
#define CircleMenu_Polar 5
#define CircleMenu_iterative_Polar 6
#define CircleMenu_midpoint 7
#define CircleMenu_modified_Midpoint 8
#define FillngMenu_Filling_Circle_with_line 9
#define FillngMenu_Filling_Circle_with_Circle 10
#define FillngMenu_Filling_Square_Hermit 11
#define FillngMenu_Filling_Rectangle_Bezier 12
#define FillngMenu_Filling_Convex 13
#define FillngMenu_Filling_NonConvex 14
#define FillngMenu_FloodFill_Recursive 15
#define FillngMenu_FloodFill_Non_Recursive 16
#define CurveMenu_Cardinal_Spline 17
#define ElliseMenu_Direct 18
#define ElliseMenu_polar 19
#define ElliseMenu_midpoint 20
#define ClippingMenu_Clipping_Rectangle_point 21
#define ClippingMenu_Clipping_Rectangle_line 22
#define ClippingMenu_Clipping_Rectangle_polygon 23
#define ClippingMenu_Clipping_Square_point 24
#define ClippingMenu_Clipping_Square_line 25
#define ClippingMenu_Clipping_Circle_point 26
#define ClippingMenu_Clipping_Circle_line 27
#define FILL_FIRST 28
#define FILL_SECOND 29
#define FILL_THIRD 30
#define FILL_FOURTH 31
#define clear_window 32
#define save_window 33
#define load_window 34
#define FILL_FIRSTLINE 35
#define FILL_SECONDLINE 36
#define FILL_THIRDLINE 37
#define FILL_FOURTHLINE 38
#define COLOR_YELLOW 39
#define COLOR_RED 40
#define COLOR_BLUE 41
#define COLOR_BLACK 42
#define COLOR_GREEN 43
#define COLOR_BROUWN 44


LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
void AddMenus(HWND);

HMENU Menu;
WNDCLASSW wc = {0};


/*int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR args ,int ncmdshow){

    //MessageBox(NULL,"keep going ","first",MB_YESNO);

    wc.hbrBackground = (HBRUSH) RGB(0, 0, 0);
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"window";
    wc.lpfnWndProc = WindowProcedure;
    if(!RegisterClassW(&wc)){return -1;}
    CreateWindowW(L"window",L"my window",WS_OVERLAPPEDWINDOW|WS_VISIBLE,100,100,500,500,NULL,NULL,NULL,NULL);

    MSG msg = {0};
    while(GetMessage(&msg,NULL,NULL,NULL))
    {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    }
    return 0;
}*/
/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               544,                 /* The programs width */
               375,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


int cx, cy, a, b, RR,RR2;
int counter = 0;
int  xc, yc, xr, yr;
int x2, y2, R;
int Q = 1;
static int input=0;
int Num_of_Points = 0;
POINT P[5];
static int first = 0;
static int counterRec = 0;
static int counterLine = 0;
ALL::Vector rec[2];
COLORREF usedColor = RGB(0, 0, 0);

int colorToInt()
{
    switch(usedColor)
    {
    case RGB(255,255,0):
        return 1;
    case RGB(255, 0, 0):
        return 2;
    case RGB(0, 255, 0):
        return 3;
    case RGB(0, 0, 255):
        return 4;
    case RGB(0, 0, 0):
        return 5;
    case RGB(102, 51, 0):
        return 6;
    default:
        return 5;
    }
}

COLORREF intToColor(int c)
{
    switch(c)
    {
    case 1:
        return RGB(255,255,0);
    case 2:
        return RGB(255, 0, 0);
    case 3:
        return RGB(0, 255, 0);
    case 4:
        return RGB(0, 0, 255);
    case 5:
        return RGB(0, 0, 0);
    default:
        return RGB(0, 0, 0);
    }
}


LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    ALL obj;
    static ALL::Vector squ[4];
    static ALL::Vector p[4];
    int v;
    static int index = 0;
    HDC hdc ;
    hdc = GetDC(hwnd);
    switch(msg)
    {
    /*---------------------------------------------------------*/
    case WM_COMMAND:
        switch(wp)
        {
        case COLOR_YELLOW:
            usedColor = RGB(255,255,0);
            cout<<"Color is Yellow now\n";
            break;
        case COLOR_RED:
            usedColor = RGB(255, 0, 0);
            cout<<"Color is Red now\n";
            break;
        case COLOR_GREEN:
            usedColor = RGB(0, 255, 0);
            cout<<"Color is Green now\n";
            break;
        case COLOR_BLUE:
            usedColor = RGB(0, 0, 255);
            cout<<"Color is Blue now\n";
            break;
        case COLOR_BLACK:
            usedColor = RGB(0, 0, 0);
            cout<<"Color is Black now\n";
            break;
        case COLOR_BROUWN:
            usedColor = RGB(102, 51, 0);
            cout<<"Color is Brouwn now\n";
            break;
        }
        switch(wp)
        {

        case LineMenu_DDA:
            cout<<"Shape is Direct Line\nplease enter 2 points for the line\n";
            input=0;
            break;

        case LineMenu_Midpoint:
            cout<<"Shape is midpoint Line\nplease enter 2 points for the line\n";
            input=1;
            break;

        case LineMenu_parametric:
            cout<<"Shape is parametric Line\nplease enter 2 points for the line\n";
            input=2;
            break;

        case CircleMenu_Direct:
            cout<<"Shape is Direct Circle\nplease enter center then point on the circle\n";
            input=3;
            break;

        case CircleMenu_Polar:
            cout<<"Shape is polar circle\nplease enter 2 points for the line\n";
            input=4;
            break;

        case CircleMenu_iterative_Polar:
            cout<<"Shape is iterative Polar circle\nplease enter 2 points for the line\n";
            input=5;
            break;

        case CircleMenu_midpoint:
            cout<<"Shape is midpoint circle\nplease enter 2 points for the line\n";
            input=6;
            break;

        case CircleMenu_modified_Midpoint:
            cout<<"Shape is modified midpoint circle\nplease enter 2 points for the line\n";
            input=7;
            break;

        case ClippingMenu_Clipping_Circle_line:
            cout<<"Shape is clipping circle with line\nplease enter 2 points for the line\n";
            input=8;
            break;

        case ClippingMenu_Clipping_Circle_point:
            cout<<"Shape is clipping circle with point\nplease enter 2 points for the line\n";
            input=9;
            break;

        case ClippingMenu_Clipping_Rectangle_line:
            cout<<"Shape is clipping Rectangle with line\nplease enter 2 points for the line\n";
            input=10;
            break;

        case ClippingMenu_Clipping_Rectangle_point:
            cout<<"Shape is clipping Rectangle with point\nplease enter 2 points for the line\n";
            input=11;
            break;

        case ClippingMenu_Clipping_Rectangle_polygon:
            cout<<"Shape is clipping Rectangle polygon\nplease enter 2 points for the line\n";
            input=12;
            break;

        case ClippingMenu_Clipping_Square_line:
            cout<<"Shape is clipping Square with line\nplease enter 2 points for the line\n";
            input=13;
            break;

        case ClippingMenu_Clipping_Square_point:
            cout<<"Shape is clipping Square with point\nplease enter 2 points for the line\n";
            input=14;
            break;

        case FillngMenu_Filling_Circle_with_Circle:
            cout<<"Shape is Filling circle with circle\nplease enter 2 points for the line\n";
            input=15;
            break;

        case FillngMenu_Filling_Circle_with_line:
            cout<<"Shape is Filling circle with line\nplease enter 2 points for the line\n";
            input=16;
            break;

        case FillngMenu_Filling_Convex:
            cout<<"Shape is Filling convex\nplease enter 2 points for the line\n";
            input=17;
            break;

        case FillngMenu_Filling_NonConvex:
            cout<<"Shape is Filling non convex\nplease enter 2 points for the line\n";
            input=18;
            break;

        case FillngMenu_Filling_Rectangle_Bezier:
            cout<<"Shape is Filling Rectangle bezier\nplease enter 2 points for the line\n";
            input=19;
            break;

        case FillngMenu_Filling_Square_Hermit:
            cout<<"Shape is Filling Square hermit\nplease enter 2 points for the line\n";
            input=20;
            break;

        case FillngMenu_FloodFill_Non_Recursive:
            cout<<"Shape is Filling non recursive\nplease enter 2 points for the line\n";
            input=21;
            break;

        case FillngMenu_FloodFill_Recursive:
            cout<<"Shape is Filling recursive\nplease enter 2 points for the line\n";
            input=22;
            break;

        case CurveMenu_Cardinal_Spline:
            cout<<"Shape is Spline curve\nplease enter 4 points for the line\n";
            input=23;
            break;

        case ElliseMenu_Direct:
            cout<<"Shape is Ellipse direct\nplease enter 2 points for the line\n";
            input=24;
            break;

        case ElliseMenu_midpoint:
            cout<<"Shape is Ellipse midpoint\nplease enter 2 points for the line\n";
            input=25;
            break;

        case ElliseMenu_polar:
            cout<<"Shape is Ellipse polar\nplease enter 2 points for the line\n";
            input=26;
            break;
        case save_window:
            obj.save(hwnd);
            cout<<"The window is saved";
            break;
        case load_window:
            cout<<"The window is loaded";
            obj.load(hwnd,hdc);
            break;
        case clear_window:
            InvalidateRect(hwnd, NULL, TRUE);
            cout<<"The window is cleared";
            break;

        case FILL_FIRST :
            input=28;
            break;
        case FILL_SECOND :
            input=29;
            break;
        case FILL_THIRD :
            input=30;
            break;
        case FILL_FOURTH :
            input=31;
            break;

        case FILL_FIRSTLINE :
            input=35;
            break;
        case FILL_SECONDLINE :
            input=36;
            break;
        case FILL_THIRDLINE :
            input=37;
            break;
        case FILL_FOURTHLINE :
            input=38;
            break;



        }
        break;
    case WM_CREATE:
        AddMenus(hwnd);
        break;
    case WM_LBUTTONDOWN:
        if(input==0)
        {

            p[index] = ALL::Vector(LOWORD(lp), HIWORD(lp));
            if (index == 1)
            {

                cx =p[0][0];
                cy =  p[0][1];
                a = p[1][0] ;
                b =  p[1][1] ;

                hdc = GetDC(hwnd);
                obj.DDALine(hdc,cx,cy,a,b,usedColor);
                ReleaseDC(hwnd, hdc);
                index=0;
            }
            else
            {
                index++;
            }

        }
        else if(input==1)
        {
            p[index] = ALL::Vector(LOWORD(lp), HIWORD(lp));
            if (index == 1)
            {

                cx =p[0][0];
                cy =  p[0][1];
                a = p[1][0] ;
                b =  p[1][1] ;

                hdc = GetDC(hwnd);
                obj.midpoint(hdc,cx,cy,a,b,usedColor);
                ReleaseDC(hwnd, hdc);
                index=0;
            }
            else
            {
                index++;
            }

        }
        else if(input==2)
        {

            p[index] = ALL::Vector(LOWORD(lp), HIWORD(lp));
            if (index == 1)
            {

                cx =p[0][0];
                cy =  p[0][1];
                a = p[1][0] ;
                b =  p[1][1] ;

                hdc = GetDC(hwnd);
                obj.parametric(hdc,cx,cy,a,b,usedColor);
                ReleaseDC(hwnd, hdc);
                index=0;
            }
            else
            {
                index++;
            }


        }
        else if(input==3)
        {

            p[index] = ALL::Vector(LOWORD(lp), HIWORD(lp));
            if (index == 1)
            {

                cx =p[0][0];
                cy =  p[0][1];
                a = p[1][0] - cx;
                b =  p[1][1] - cy;
                RR = sqrt(a * a + b * b);

                hdc = GetDC(hwnd);
                obj.DrawCircle1(hdc,cx, cy, RR,usedColor);
                ReleaseDC(hwnd, hdc);
                index=0;
            }
            else
            {
                index++;
            }


        }
        else if(input==4)
        {
            p[index] = ALL::Vector(LOWORD(lp), HIWORD(lp));
            if (index == 1)
            {

                cx =p[0][0];
                cy =  p[0][1];
                a = p[1][0] - cx;
                b =  p[1][1] - cy;
                RR = sqrt(a * a + b * b);

                hdc = GetDC(hwnd);
                obj.DrawCircle2(hdc,cx, cy, RR,usedColor);
                ReleaseDC(hwnd, hdc);
                index=0;
            }
            else
            {
                index++;
            }
        }
        else if(input==5)
        {
            p[index] = ALL::Vector(LOWORD(lp), HIWORD(lp));
            if (index == 1)
            {

                cx =p[0][0];
                cy =  p[0][1];
                a = p[1][0] - cx;
                b =  p[1][1] - cy;
                RR = sqrt(a * a + b * b);

                hdc = GetDC(hwnd);
                obj.DrawCircle3(hdc,cx, cy, RR,usedColor);
                index=0;
                ReleaseDC(hwnd, hdc);
            }
            else
            {
                index++;
            }
        }
        else if(input==6)
        {
            p[index] = ALL::Vector(LOWORD(lp), HIWORD(lp));
            if (index == 1)
            {

                cx =p[0][0];
                cy =  p[0][1];
                a = p[1][0] - cx;
                b =  p[1][1] - cy;
                RR = sqrt(a * a + b * b);

                hdc = GetDC(hwnd);
                obj.DrawCircle4(hdc,cx, cy, RR,usedColor);
                ReleaseDC(hwnd, hdc);
                index=0;
            }
            else
            {
                index++;
            }

        }
        else if(input==7)
        {
            p[index] = ALL::Vector(LOWORD(lp), HIWORD(lp));
            if (index == 1)
            {

                cx =p[0][0];
                cy =  p[0][1];
                a = p[1][0] - cx;
                b =  p[1][1] - cy;
                RR = sqrt(a * a + b * b);

                hdc = GetDC(hwnd);
                obj.DrawCircle5(hdc,cx, cy, RR,usedColor);
                ReleaseDC(hwnd, hdc);
                index=0;
            }
            else
            {
                index++;
            }
        }
        else if(input==8) {}
        else if(input==9)
        {
            if (first == 0)
            {

                rec[counterRec]= ALL::Vector(LOWORD(lp), HIWORD(lp));
                if (counterRec == 1)
                {
                    HDC hdc;
                    hdc = GetDC(hwnd);
                    obj.DrawRectangle(hdc, rec[0][0], rec[0][1], rec[1][0], rec[1][1], usedColor);
                    ReleaseDC(hwnd, hdc);
                    first++;
                    counterRec=0;
                }
                counterRec++;
            }

            break;

        }
        else if(input==10) {}
        else if(input==11) {}
        else if(input==12) {}
        else if(input==13) {}
        else if(input==14) {}
        else if(input==15)
        {
            p[index] = ALL::Vector(LOWORD(lp), HIWORD(lp));
            if (index == 1)
            {

                cx =p[0][0];
                cy =  p[0][1];
                a = p[1][0] - cx;
                b =  p[1][1] - cy;
                RR = sqrt(a * a + b * b);

                hdc = GetDC(hwnd);
                obj.DrawCircle1(hdc,cx, cy, RR,usedColor);
                obj.FillCircle1(hdc,cx, cy, RR,2,usedColor);
                ReleaseDC(hwnd, hdc);
                index=0;
            }
            else
            {
                index++;
            }

        }
        else if(input==16)
        {
            if (counter == 0)
            {
                xc = LOWORD(lp);
                yc = HIWORD(lp);
                counter++;
            }
            else if (counter == 1)
            {
                xr = LOWORD(lp);
                yr = HIWORD(lp);
                x2 = (xr - xc) * (xr - xc);
                y2 = (yr - yc) * (yr - yc);
                R = sqrt(x2 + y2);
                obj.iterativePolarCircle(hdc, xc, yc, obj.Round(R), 1, usedColor);
                counter++;
            }
            else
            {
                counter = 0;
            }

        }
        else if(input==17)
        {
            if (Num_of_Points == 0)
            {
                P[0].x = LOWORD(lp);
                P[0].y = HIWORD(lp);
                Num_of_Points++;
            }
            else if (Num_of_Points == 1)
            {
                P[1].x = LOWORD(lp);
                P[1].y = HIWORD(lp);
                Num_of_Points++;
            }
            else if (Num_of_Points == 2)
            {
                P[2].x = LOWORD(lp);
                P[2].y = HIWORD(lp);
                Num_of_Points++;
            }
            else if (Num_of_Points == 3)
            {
                P[3].x = LOWORD(lp);
                P[3].y = HIWORD(lp);
                Num_of_Points++;
            }
            else if (Num_of_Points == 4)
            {
                P[4].x = LOWORD(lp);
                P[4].y = HIWORD(lp);
                Num_of_Points++;
                //change pen color//
                SelectObject(hdc, GetStockObject(DC_PEN));
                SetDCPenColor(hdc, usedColor);

                Polygon(hdc, P, 5);
            }
            else if (Num_of_Points == 5)
            {
                obj.fillPolygon(hdc, P, 5, usedColor);
                Num_of_Points = 0;
            }

        }
        else if(input==18)
        {
            if (Num_of_Points == 0)
            {
                P[0].x = LOWORD(lp);
                P[0].y = HIWORD(lp);
                Num_of_Points++;
            }
            else if (Num_of_Points == 1)
            {
                P[1].x = LOWORD(lp);
                P[1].y = HIWORD(lp);
                Num_of_Points++;
            }
            else if (Num_of_Points == 2)
            {
                P[2].x = LOWORD(lp);
                P[2].y = HIWORD(lp);
                Num_of_Points++;
            }
            else if (Num_of_Points == 3)
            {
                P[3].x = LOWORD(lp);
                P[3].y = HIWORD(lp);
                Num_of_Points++;
            }
            else if (Num_of_Points == 4)
            {
                P[4].x = LOWORD(lp);
                P[4].y = HIWORD(lp);
                Num_of_Points++;
                //change pen color//
                SelectObject(hdc, GetStockObject(DC_PEN));
                SetDCPenColor(hdc, RGB(60, 239, 161));
                Polygon(hdc, P, 5);
            }
            else if (Num_of_Points == 5)
            {
                //fill polygon
                obj.fillPolygonnon(hdc, P, 5,usedColor);
                Num_of_Points = 0;
            }


        }
        else if(input==19) {}
        else if(input==20)
        {


            squ[index] = ALL::Vector(LOWORD(lp), HIWORD(lp));
            if (index == 1)
            {


                v = sqrt((squ[0][0] - squ[1][0]) * (squ[0][0] - squ[1][0]) + (squ[0][1] - squ[1][1]) * (squ[0][1] - squ[1][1]));
                p[0] = ALL::Vector(squ[1][0], squ[0][1]);
                p[1] = ALL::Vector(squ[1][0], squ[1][1]);
                p[2] = ALL::Vector(squ[1][0] + v, squ[1][1]);
                p[3] = ALL::Vector(squ[1][0] + v, squ[0][1]);


                ALL::Vector T3(3 * (p[2][0] - p[1][0]), 3 * (p[2][1] - p[1][1]));

                ALL::Vector T4(3 * (p[1][0] - p[2][0]), 3 * (p[1][1] - p[2][1]));





                obj.DrawLine(hdc, squ[0][0], squ[0][1], squ[0][0], squ[0][1]+v,usedColor );

                obj.DrawLine(hdc, squ[0][0], squ[0][1]+v, squ[0][0] + v, squ[0][1]+v, usedColor);

                obj.DrawLine(hdc, squ[0][0] + v, squ[0][1]+v, squ[0][0] + v, squ[0][1], usedColor);

                obj.DrawLine(hdc, squ[0][0] + v, squ[0][1], squ[0][0], squ[0][1], usedColor);

                obj.fillsqu(hdc, squ[0][0], squ[0][1]+v, squ[0][0]+v, squ[0][1]+v, usedColor, squ[0][0]+ v , squ[0][1], squ[0][0], squ[0][1]);

                ReleaseDC(hwnd, hdc);
                index = 0;
            }
            else
            {
                index++;
            }
        }
        else if(input==21)
        {

            if (counter == 0)
            {
                xc = LOWORD(lp);
                yc = HIWORD(lp);
                counter++;
            }
            else if (counter == 1)
            {
                xr = LOWORD(lp);
                yr = HIWORD(lp);
                x2 = (xr - xc) * (xr - xc);
                y2 = (yr - yc) * (yr - yc);
                R = sqrt(x2 + y2);
                obj.DrawCircle3(hdc, xc, yc, obj.Round(R), usedColor);
                counter++;
            }
            else
            {
                obj.nonRecursiveMyFill(hdc, xc, yc, usedColor,  usedColor);
                counter = 0;
            }
        }
        else if(input==22)
        {
            if (counter == 0)
            {
                xc = LOWORD(lp);
                yc = HIWORD(lp);
                counter++;
            }
            else if (counter == 1)
            {
                xr = LOWORD(lp);
                yr = HIWORD(lp);
                x2 = (xr - xc) * (xr - xc);
                y2 = (yr - yc) * (yr - yc);
                R = sqrt(x2 + y2);
                obj.DrawCircle3(hdc, xc, yc, obj.Round(R), usedColor);
                counter++;
            }
            else
            {
                obj.recursiveMyFill(hdc, xc, yc,  usedColor,  usedColor);
                counter = 0;
            }
        }
        else if(input==23)
        {
           /* p[index] = ALL::Vector(LOWORD(lp), HIWORD(lp));
            if (index == 3)
            {
                ALL::Vector T1(3 * (p[1][0] - p[0][0]), 3 * (p[1][1] - p[0][1]));
                ALL::Vector T2(3 * (p[3][0] - p[2][0]), 3 * (p[3][1] - p[2][1]));
                hdc = GetDC(hwnd);

                obj.DrawHermiteCurve2(hdc, p[0], T1, p[3], T2, usedColor);

                ReleaseDC(hwnd, hdc);
                index = 0;
            }
            else index++;*/
             p[index] = ALL::Vector(LOWORD(lp), HIWORD(lp));
             if (index == 3)
             {
                 hdc = GetDC(hwnd);
                 obj.DrawCardinalSpline(hdc, p, 4, 0.5, usedColor);
                 ReleaseDC(hwnd, hdc);
                 index = 0;
             }
             else index++;
        }
        else if(input==24)
        {

            p[index] = ALL::Vector(LOWORD(lp), HIWORD(lp));
            if (index == 2)
            {

                cx =p[0][0];
                cy =  p[0][1];
                a = p[1][0] - cx;
                b =  p[1][1] - cy;
                RR = sqrt(a * a + b * b);
                a = p[2][0] - cx;
                b =  p[2][1] - cy;
                RR2=sqrt(a * a + b * b);

                hdc = GetDC(hwnd);
                obj.DrawDirectEllipse(hdc, cx, cy, RR, RR2, usedColor);
                ReleaseDC(hwnd, hdc);
                index=0;
            }
            else
            {
                index++;
            }


        }
        else if(input==25)
        {

            p[index] = ALL::Vector(LOWORD(lp), HIWORD(lp));
            if (index == 2)
            {

                cx =p[0][0];
                cy =  p[0][1];
                a = p[1][0] - cx;
                b =  p[1][1] - cy;
                RR = sqrt(a * a + b * b);
                a = p[2][0] - cx;
                b =  p[2][1] - cy;
                RR2=sqrt(a * a + b * b);

                hdc = GetDC(hwnd);
                obj.DrawMidpointEllipse(hdc, cx, cy, RR, RR2, usedColor);
                ReleaseDC(hwnd, hdc);
                index=0;
            }
            else
            {
                index++;
            }


        }
        else if(input==26)
        {

            p[index] = ALL::Vector(LOWORD(lp), HIWORD(lp));
            if (index == 2)
            {

                cx =p[0][0];
                cy =  p[0][1];
                a = p[1][0] - cx;
                b =  p[1][1] - cy;
                RR = sqrt(a * a + b * b);
                a = p[2][0] - cx;
                b =  p[2][1] - cy;
                RR2=sqrt(a * a + b * b);

                hdc = GetDC(hwnd);
                obj.DrawPolarEllipse(hdc, cx, cy, RR, RR2, usedColor);
                ReleaseDC(hwnd, hdc);
                index=0;
            }
            else
            {
                index++;
            }

        }
        else if(input==28)
        {

            p[index] = ALL::Vector(LOWORD(lp), HIWORD(lp));
            if (index == 1)
            {

                cx =p[0][0];
                cy =  p[0][1];
                a = p[1][0] - cx;
                b =  p[1][1] - cy;
                RR = sqrt(a * a + b * b);

                hdc = GetDC(hwnd);
                obj.DrawCircle1(hdc,cx, cy, RR,usedColor);
                obj.FillCircle1(hdc,cx, cy, RR,1,RGB(255,255,0));
                ReleaseDC(hwnd, hdc);
                index = 0;
            }
            else
            {
                index++;
            }

        }
        else if(input==29)
        {

            p[index] = ALL::Vector(LOWORD(lp), HIWORD(lp));
            if (index == 1)
            {

                cx =p[0][0];
                cy =  p[0][1];
                a = p[1][0] - cx;
                b =  p[1][1] - cy;
                RR = sqrt(a * a + b * b);

                hdc = GetDC(hwnd);
                obj.DrawCircle1(hdc,cx, cy, RR,usedColor);
                obj.FillCircle1(hdc,cx, cy, RR,2,RGB(255,255,0));
                ReleaseDC(hwnd, hdc);
                index = 0;
            }
            else
            {
                index++;
            }

        }
        else if(input==30)
        {

            p[index] = ALL::Vector(LOWORD(lp), HIWORD(lp));
            if (index == 1)
            {

                cx =p[0][0];
                cy =  p[0][1];
                a = p[1][0] - cx;
                b =  p[1][1] - cy;
                RR = sqrt(a * a + b * b);

                hdc = GetDC(hwnd);
                obj.DrawCircle1(hdc,cx, cy, RR,usedColor);
                obj.FillCircle1(hdc,cx, cy, RR,3,RGB(255,255,0));
                ReleaseDC(hwnd, hdc);
                index = 0;
            }
            else
            {
                index++;
            }

        }
        else if(input==31)
        {

            p[index] = ALL::Vector(LOWORD(lp), HIWORD(lp));
            if (index == 1)
            {

                cx =p[0][0];
                cy =  p[0][1];
                a = p[1][0] - cx;
                b =  p[1][1] - cy;
                RR = sqrt(a * a + b * b);

                hdc = GetDC(hwnd);
                obj.DrawCircle1(hdc,cx, cy, RR,usedColor);
                obj.FillCircle1(hdc,cx, cy, RR,4,RGB(255,255,0));
                ReleaseDC(hwnd, hdc);
                index = 0;
            }
            else
            {
                index++;
            }

        }
        else if(input==35)
        {
            if (counter == 0)
            {
                xc = LOWORD(lp);
                yc = HIWORD(lp);
                counter++;
            }
            else if (counter == 1)
            {
                xr = LOWORD(lp);
                yr = HIWORD(lp);
                x2 = (xr - xc) * (xr - xc);
                y2 = (yr - yc) * (yr - yc);
                R = sqrt(x2 + y2);
                obj.iterativePolarCircle(hdc, xc, yc, obj.Round(R), 1, usedColor);
                counter++;
            }
            else
            {
                counter = 0;
            }
        }
        else if(input==36)
        {
            if (counter == 0)
            {
                xc = LOWORD(lp);
                yc = HIWORD(lp);
                counter++;
            }
            else if (counter == 1)
            {
                xr = LOWORD(lp);
                yr = HIWORD(lp);
                x2 = (xr - xc) * (xr - xc);
                y2 = (yr - yc) * (yr - yc);
                R = sqrt(x2 + y2);
                obj.iterativePolarCircle(hdc, xc, yc, obj.Round(R), 4, usedColor);
                counter++;
            }
            else
            {
                counter = 0;
            }
        }
        else if(input==37)
        {
            if (counter == 0)
            {
                xc = LOWORD(lp);
                yc = HIWORD(lp);
                counter++;
            }
            else if (counter == 1)
            {
                xr = LOWORD(lp);
                yr = HIWORD(lp);
                x2 = (xr - xc) * (xr - xc);
                y2 = (yr - yc) * (yr - yc);
                R = sqrt(x2 + y2);
                obj.iterativePolarCircle(hdc, xc, yc, obj.Round(R), 3, usedColor);
                counter++;
            }
            else
            {
                counter = 0;
            }
        }
        else if(input==38)
        {
            if (counter == 0)
            {
                xc = LOWORD(lp);
                yc = HIWORD(lp);
                counter++;
            }
            else if (counter == 1)
            {
                xr = LOWORD(lp);
                yr = HIWORD(lp);
                x2 = (xr - xc) * (xr - xc);
                y2 = (yr - yc) * (yr - yc);
                R = sqrt(x2 + y2);
                obj.iterativePolarCircle(hdc, xc, yc, obj.Round(R), 2,usedColor);
                counter++;
            }
            else
            {
                counter = 0;
            }
        }



        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hwnd, msg,wp, lp);
        /*---------------------------------------------------------*/
    }

}

void AddMenus(HWND hwnd)
{
    Menu = CreateMenu();
    HMENU LineMenu = CreateMenu();
    HMENU CircleMenu = CreateMenu();
    HMENU FillingMenu = CreateMenu();
    HMENU FillingcirclequarterMenu = CreateMenu();
    HMENU FillinglinequarterMenu = CreateMenu();
    HMENU FloodMenu = CreateMenu();
    HMENU ClippingMenu = CreateMenu();
    HMENU CurveMenu = CreateMenu();
    HMENU EllipseMenu = CreateMenu();
    HMENU FilesMenu = CreateMenu();
    HMENU ColorMenu = CreateMenu();



    /*****************************************************/
    /*Color menu*/
    /*****************************************************/
    AppendMenu(Menu,MF_POPUP,(UINT_PTR)ColorMenu,"Color");
    AppendMenu(ColorMenu,MF_STRING,COLOR_RED,"Red");
    AppendMenu(ColorMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(ColorMenu,MF_STRING,COLOR_GREEN,"Green");
    AppendMenu(ColorMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(ColorMenu,MF_STRING,COLOR_BLUE,"Blue");
    AppendMenu(ColorMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(ColorMenu,MF_STRING,COLOR_BLACK,"Black");
    AppendMenu(ColorMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(ColorMenu,MF_STRING,COLOR_YELLOW,"Yellow");
    AppendMenu(ColorMenu,MF_SEPARATOR,NULL,NULL);
    AppendMenu(ColorMenu,MF_STRING,COLOR_BROUWN,"Brouwn");
    AppendMenu(ColorMenu,MF_SEPARATOR,NULL,NULL);

    /*****************************************************/
    /*files menu*/
    /*****************************************************/
    AppendMenu(Menu,MF_POPUP,(UINT_PTR)FilesMenu,"File");
    AppendMenu(FilesMenu,MF_STRING,save_window,"save");
    AppendMenu(FilesMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(FilesMenu,MF_STRING,load_window,"load");
    AppendMenu(FilesMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(FilesMenu,MF_STRING,clear_window,"Clear");
    AppendMenu(FilesMenu,MF_SEPARATOR,NULL,NULL);

    /*******************/
    /*line menu*/
    /*******************/

    AppendMenu(Menu,MF_POPUP,(UINT_PTR)LineMenu,"Line");
    AppendMenu(LineMenu,MF_STRING,LineMenu_DDA,"DDA");
    AppendMenu(LineMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(LineMenu,MF_STRING,LineMenu_Midpoint,"Midpoint");
    AppendMenu(LineMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(LineMenu,MF_STRING,LineMenu_parametric,"parametric");
    AppendMenu(LineMenu,MF_SEPARATOR,NULL,NULL);

    /******************/
    /*Circle menu*/
    /*******************/

    AppendMenu(Menu,MF_POPUP,(UINT_PTR)CircleMenu,"Circle");

    AppendMenu(CircleMenu,MF_STRING,CircleMenu_Direct,"Direct");
    AppendMenu(CircleMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(CircleMenu,MF_STRING,CircleMenu_Polar,"Polar");
    AppendMenu(CircleMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(CircleMenu,MF_STRING,CircleMenu_iterative_Polar,"iterative Polar");
    AppendMenu(CircleMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(CircleMenu,MF_STRING,CircleMenu_midpoint,"midpoint");
    AppendMenu(CircleMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(CircleMenu,MF_STRING,CircleMenu_modified_Midpoint,"modified Midpoint");
    AppendMenu(CircleMenu,MF_SEPARATOR,NULL,NULL);
    /******************/
    /*Filling menu*/
    /*******************/

    AppendMenu(Menu,MF_POPUP,(UINT_PTR)FillingMenu,"Filling");

    AppendMenu(FillingMenu,MF_POPUP,(UINT_PTR)FillinglinequarterMenu,"line");
    AppendMenu(FillingMenu,MF_SEPARATOR,NULL,NULL);
    /**************************************************************/
    AppendMenu(FillinglinequarterMenu,MF_STRING,FILL_FIRSTLINE,"First");
    AppendMenu(FillinglinequarterMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(FillinglinequarterMenu,MF_STRING,FILL_SECONDLINE,"Second");
    AppendMenu(FillinglinequarterMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(FillinglinequarterMenu,MF_STRING,FILL_THIRDLINE,"Third");
    AppendMenu(FillinglinequarterMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(FillinglinequarterMenu,MF_STRING,FILL_FOURTHLINE,"Fourth");
    AppendMenu(FillinglinequarterMenu,MF_SEPARATOR,NULL,NULL);
    /**********************************************************/

    AppendMenu(FillingMenu,MF_POPUP,(UINT_PTR)FillingcirclequarterMenu,"Circle");
    AppendMenu(FillingMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(FillingcirclequarterMenu,MF_STRING,FILL_FIRST,"First");
    AppendMenu(FillingcirclequarterMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(FillingcirclequarterMenu,MF_STRING,FILL_SECOND,"Second");
    AppendMenu(FillingcirclequarterMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(FillingcirclequarterMenu,MF_STRING,FILL_THIRD,"Third");
    AppendMenu(FillingcirclequarterMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(FillingcirclequarterMenu,MF_STRING,FILL_FOURTH,"Fourth");
    AppendMenu(FillingcirclequarterMenu,MF_SEPARATOR,NULL,NULL);


    AppendMenu(FillingMenu,MF_STRING,FillngMenu_Filling_Convex,"convex");
    AppendMenu(FillingMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(FillingMenu,MF_STRING,FillngMenu_Filling_NonConvex,"Non convex");
    AppendMenu(FillingMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(FillingMenu,MF_STRING,FillngMenu_Filling_Rectangle_Bezier,"Rectangle");
    AppendMenu(FillingMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(FillingMenu,MF_STRING,FillngMenu_Filling_Square_Hermit,"Square");
    AppendMenu(FillingMenu,MF_SEPARATOR,NULL,NULL);



    AppendMenu(FillingMenu,MF_POPUP,(UINT_PTR)FloodMenu,"Flood Fill");

    AppendMenu(FloodMenu,MF_STRING,FillngMenu_FloodFill_Recursive,"Recursive");
    AppendMenu(FloodMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(FloodMenu,MF_STRING,FillngMenu_FloodFill_Non_Recursive,"Non Recursive");
    AppendMenu(FloodMenu,MF_SEPARATOR,NULL,NULL);

    /*******************/
    /*Clipping menu*/
    /*******************/
    AppendMenu(Menu,MF_POPUP,(UINT_PTR)ClippingMenu,"Clipping");

    AppendMenu(ClippingMenu,MF_STRING,ClippingMenu_Clipping_Circle_line,"Circle with line");
    AppendMenu(ClippingMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(ClippingMenu,MF_STRING,ClippingMenu_Clipping_Circle_point,"Circle with point");
    AppendMenu(ClippingMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(ClippingMenu,MF_STRING,ClippingMenu_Clipping_Rectangle_line,"Rectangle with line");
    AppendMenu(ClippingMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(ClippingMenu,MF_STRING,ClippingMenu_Clipping_Rectangle_point,"Rectangle with point");
    AppendMenu(ClippingMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(ClippingMenu,MF_STRING,ClippingMenu_Clipping_Rectangle_polygon,"Rectangle with polygon");
    AppendMenu(ClippingMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(ClippingMenu,MF_STRING,ClippingMenu_Clipping_Square_line,"Square with line");
    AppendMenu(ClippingMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(ClippingMenu,MF_STRING,ClippingMenu_Clipping_Square_point,"Square with point");
    AppendMenu(ClippingMenu,MF_SEPARATOR,NULL,NULL);

    /*******************/
    /*Curve menu*/
    /*******************/

    AppendMenu(Menu,MF_POPUP,(UINT_PTR)CurveMenu,"Curve");
    AppendMenu(CurveMenu,MF_STRING,CurveMenu_Cardinal_Spline,"Spline");
    AppendMenu(CurveMenu,MF_SEPARATOR,NULL,NULL);

    /*******************/
    /*Ellipse menu*/
    /*******************/

    AppendMenu(Menu,MF_POPUP,(UINT_PTR)EllipseMenu,"Ellipse");

    AppendMenu(EllipseMenu,MF_STRING,ElliseMenu_Direct,"Direct");
    AppendMenu(EllipseMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(EllipseMenu,MF_STRING,ElliseMenu_midpoint,"midpoint");
    AppendMenu(EllipseMenu,MF_SEPARATOR,NULL,NULL);

    AppendMenu(EllipseMenu,MF_STRING,ElliseMenu_polar,"polar");
    AppendMenu(EllipseMenu,MF_SEPARATOR,NULL,NULL);

    SetMenu(hwnd,Menu);



    //void DrawDirectEllipse(HDC hdc, int xc, int yc, int A, int B, COLORREF c);
    //void DrawPolarEllipse(HDC hdc, int xc, int yc, int A, int B, COLORREF c);
    //void DrawMidpointEllipse(HDC hdc, int xc, int yc, int A, int B, COLORREF color);
}
