#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>

#define ID_TIMER 100

class Object
{
public:
    COLORREF color;
    POINT center;
    int speed;

    Object()
    {
        color = RGB(0,0,0);
        center.x = 0;
        center.y = 0;
        speed = 0;
    };
    Object(POINT center, int speed)
    {
        this -> center.x = center.x;
        this -> center.y = center.y;
        this -> speed = speed;
        color = RGB(0,0,0);
    };
    void acceleration (int delta_speed);
    void color_object (COLORREF clr);
    void collision(RECT rect);
    void movement(HDC &hdc, RECT rect, HBRUSH &brush);
    void get_pos(POINT co0rdinates);
    void colision(RECT rect);
};

