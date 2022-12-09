#include <iostream>
#include "./heads/GCode.hpp"

int main()
{
    gcode A("demo.gcode");

    for (int j = 0; j < 10; j++)
    {
        for (int i = 5; i < 10; i++)
        {
            A.print(Vector2D(30, 0), 1000);
            A.print(Vector2D(0, 5), 1000);
            A.print(Vector2D(-30, 0), 1000);
            A.print(Vector2D(0, 5), 1000);
        }
        A.next_layer();
        for (int i = 5; i < 10; i++)
        {
            A.print(Vector2D(0, -5), 1000);
            A.print(Vector2D(30, 0), 1000);
            A.print(Vector2D(0, -5), 1000);
            A.print(Vector2D(-30, 0), 1000);
        }
        A.next_layer();
    }
    return 0;
}
