#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#define ID_TIMER 100

class Object
{
public:
    COLORREF color;
    POINT center;
    int x_speed, y_speed, nr_ball, nr_object_hitted;
    int acceleration;
    bool square_check;

    Object()
    {
        color = RGB(0, 0, 0);
        center.x = 0;
        center.y = 0;
        x_speed = 0;
        y_speed = 0;
    };
    Object(POINT center, int speed, COLORREF color, int nr_ball)
    {
        this -> center.x = center.x;
        this -> center.y = center.y;
        x_speed = speed;
        y_speed = speed;
        this -> color = color;
        this -> nr_ball = nr_ball;
        nr_object_hitted = nr_ball;
        square_check = false;
        acceleration = 0;
    };
    void color_object (COLORREF clr);
    void collision(RECT rect);
    void movement(HDC &hdc, RECT rect);
    void colision(RECT rect);
};

void interaction(Object &a, Object &b);

