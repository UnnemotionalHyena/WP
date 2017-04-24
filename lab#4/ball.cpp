#include "header.h"

void Object :: color_object(COLORREF clr)
{
    this -> color = clr;
}

void Object :: movement(HDC &hdc, RECT rect)
{

    HBRUSH brush = CreateSolidBrush(color);
    SelectObject(hdc, brush);
    colision(rect);
    center.x += x_speed + (x_speed/abs(x_speed))*acceleration;
    center.y += y_speed + (y_speed/abs(y_speed))*acceleration;

    if (acceleration > 10)
    {
        acceleration = 10;
    }

    if (square_check == false)
    {
        Ellipse(hdc, center.x - 25, center.y - 25, center.x + 25, center.y + 25);
    }
    else
    {
        Rectangle(hdc, center.x - 25, center.y - 25, center.x + 25, center.y + 25);
    }

    SelectObject(hdc, GetStockObject(WHITE_BRUSH));
    DeleteObject(brush);
    return;
}

void Object :: colision (RECT rect)
{
    if(center.x + 25 > rect.right - 1)
    {
        nr_object_hitted = 1001;
        square_check = true;
        x_speed =- abs(x_speed);
    }
    if(center.x - 25 < rect.left + 1)
    {
        square_check = true;
        nr_object_hitted = 1001;
        x_speed = abs(x_speed);
    }
    if(center.y + 25 > rect.bottom - 1)
    {
        nr_object_hitted = 1001;
        acceleration += 1;

        y_speed = -abs(y_speed);

    }
    if(center.y - 25 < rect.top + 10)
    {
        acceleration += 1;
        nr_object_hitted = 1001;
        y_speed = abs(y_speed);
    }

}

void interaction(Object &a, Object &b)
{
    int sign[] = {-1, 1};
    if (a.nr_object_hitted == b.nr_ball && a.nr_ball == b.nr_object_hitted)
    {
        return;
    }
    else
    {
        int R = rand() % 256;
        int G = rand() % 256;
        int B = rand() % 256;
        int R_2 = rand() % 256;
        int G_2 = rand() % 256;
        int B_2 = rand() % 256;
        int distance = sqrt(pow(abs(b.center.x - a.center.x), 2) + pow(abs(b.center.y - a.center.y), 2));
        if (distance <= 50)
        {
            if (a.square_check & b.square_check || !a.square_check & !b.square_check)
            {
                a.color = RGB(R, G, B);
                b.color = RGB (R_2, G_2, B_2);
            }

            a.nr_object_hitted = b.nr_ball;
            b.nr_object_hitted = a.nr_ball;
            a.x_speed = -a.x_speed;
            a.y_speed = -a.y_speed;

            b.x_speed = -b.x_speed;
            b.y_speed = -b.y_speed;
            return;
        }
    }

}
