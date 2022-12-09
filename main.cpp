#include <iostream>
#include "./heads/GCode.hpp"

int main()
{
    gcode demo("demo1");
    demo.set_extruder(0);
    demo.set_bed_temperature(50, true);
    demo.set_temperature(220, 0, true);
    demo.move_to_origin();
    demo.clean_extruder(0);
    demo.extrusion(-1);
    demo.fan(0);
    demo.set_temperature(215, 0);
    demo.abs_move(160, 120, 0.3, 3600);
    demo.extrusion(1);

    demo.rel_print(50.5, 0, 600);
    demo.rel_print(0, 50.5, 600);
    demo.extrusion(-0.5);
    demo.abs_move(180, 160, 3600);
    demo.extrusion(0.5);

    for (int i = 0; i < 30; i++)
    {
        if (i == 1)
        {
            demo.fan(254);
            demo.set_bed_temperature(30);
        }

        if (i == 0 || i ==1 )
        {
            demo.square(17.5,600);
            demo.next_layer(0.2);
        }
        else
        {
            demo.square(18.0-double(i)/3,1200);
            demo.next_layer(0.2);
        }
    }

    demo.fan(0);
    demo.set_temperature(20, 0);
    return 0;
}
