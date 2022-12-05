#include <iostream>
#include "./heads/print_head.hpp"

int main()
{
    print_head A("demo.gcode", Vector2D(160,160));

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
