#include "header.h"

void Object :: acceleration(int delta_speed)
{
    speed  += delta_speed;
}

void Object :: color_object(COLORREF clr)
{
    this -> color = clr;
}

void Object :: movement(HDC &hdc, RECT rect, HBRUSH &brush)
{
    brush = CreateSolidBrush(RGB(0,0,0));
    SelectObject(hdc, brush);
    colision(rect);
    center.x += speed;
    center.y += speed;
    Ellipse(hdc, center.x - 25, center.y - 25, center.x + 25, center.y + 25);
    SelectObject(hdc, GetStockObject(WHITE_BRUSH));
    DeleteObject(brush);
return;
}

void Object :: get_pos(POINT coordinates)
{
    this -> center.x = coordinates.x;
    this -> center.y = coordinates.y;
}

void Object :: colision (RECT rect)
{
    if(center.x+25 > rect.right-1)
    {
        speed =- abs(speed);
    }
    if(center.x-25 < rect.left+1)
    {
        speed = abs(speed);
    }

}
