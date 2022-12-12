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
    demo.abs_move(160, 100, 0.3);
    demo.extrusion(1);

    demo.square(60, 600);
    

    demo.extrusion(-0.5);
    demo.abs_move(170, 150);
    demo.extrusion(0.5);
    Vector2D start = demo.position();

    for (int i = 0; i < 128; i++)
    {
        if (i == 1)
        {
            demo.fan(255);
            demo.set_bed_temperature(30, and_go);
        }

        if (i < 2)
            demo.schwartz_cube(3, 0.25, 400);
        else
            demo.schwartz_cube(3, 0.25, 1800);

        demo.next_layer(0.2);
        demo.abs_move(start);
    }

    demo.fan(0);
    demo.set_temperature(20, 0);
    return 0;
}
