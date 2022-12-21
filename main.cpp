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
    demo.abs_move(60, 120, 0.3);
    demo.extrusion(1);

    demo.square(85, 1, 2500);
    demo.next_layer(0.2);

    demo.extrusion(-0.5);
    demo.rel_move(3, -2);
    Vector2D start = demo.position();
    demo.extrusion(0.5);

    for (int i = 0; i < 55.5*2; i++)
    {
      //  demo.abs_move(100, 100);
      //  demo.schwartz(3,1,false);
      //  demo.abs_move(start);
        if (i == 0)
        {
            demo.fan(255);
            demo.set_bed_temperature(40, and_go);
        }

        if (i < 3)
            demo.schwartz_cube(7, 3.6, 900);
        else
            demo.schwartz_cube(7, 3.6, 1800);

        demo.next_layer(0.2);
        demo.abs_move(start);
    }

    demo.fan(0);
    demo.set_temperature(20, 0);
    return 0;
}
