#include <iostream>
#include "./heads/GCode.hpp"

enum extruders
{
    left = 0,
    right = 1
};

int main()
{
    // start
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
    // start

    // schwartz

    int periods = 2;
    double a = 30;
    double height = 60;
    double layer_hght = 0.2;
    Vector2D start = demo.position();

    demo.square(a + 2, 1, 2500);
    demo.extrusion(-0.5);
    demo.next_layer(layer_hght);
    demo.abs_move(start);
    demo.rel_move(1, 1);
    demo.rel_move(0, a);

    double mashtab = (a / periods) / Pi;
    std::cout << mashtab;
    int steps = height / layer_hght - 1;

    start = demo.position();
    demo.extrusion(0.5);

    for (int i = 0; i < steps; i++)
    {
        if (i == 0)
        {
            demo.fan(255);
            demo.set_bed_temperature(40, and_go);
        }

        if (i < 3)
            demo.schwartz_cube(periods, mashtab, 900);
        else
            demo.schwartz_cube(periods, mashtab, 1800);

        demo.next_layer(layer_hght);
        demo.abs_move(start);
    }

    demo.fan(0);
    demo.set_temperature(20, 0);
    return 0;
}
