#include <iostream>
#include "./heads/GCode.hpp"

enum extruders
{
    left = 0,
    right = 1
};

int main()
{
    gcode demo("demo1");
    demo.set_extruder(left);
    demo.set_bed_temperature(40, wait);
    demo.set_bed_temperature(50, and_go);
    demo.set_temperature(220, left, wait);
    demo.set_bed_temperature(50, wait);
    demo.move_to_origin();
    demo.clean_extruder(left);
    demo.extrusion(-1);
    demo.fan(0);
    demo.set_temperature(215, left);
    demo.abs_move(160, 120, 0.3);
    demo.extrusion(1);

    demo.line(50.5, 0, 600);
    demo.line(0, 50.5, 600);

    demo.extrusion(-0.5);
    demo.abs_move(180, 160);
    demo.extrusion(0.5);

    Vector2D start = demo.position();
    Vector2D next = Vector2D(0, Pi / 0.25);
    Vector2D next_r = Vector2D(Pi / 0.25, 0);

    for (int i = 0; i < 100; i++)
    {
        if (i == 1)
        {
            demo.fan(255);
            demo.set_bed_temperature(30);
        }

        for (int j = 1; j < 5; j++)
        {

            if (i < 2)
                for (int n = 0; n < j; n++)
                {
                    demo.schwartz(0.25, 600);
                }
            else
                for (int n = 0; n < j; n++)
                {
                    demo.schwartz(0.25, 1200);
                }
            demo.abs_move(start - next * j);
        }

        demo.next_layer(0.2);
        demo.abs_move(start);
    }

    demo.fan(0);
    demo.set_temperature(20, 0);
    return 0;
}
