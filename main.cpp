#include <iostream>
#include "./heads/GCode.hpp"

enum extruders
{
    left = 0,
    right = 1
};

int main()
{
    // Initializing g-code file
    gcode demo("demo1");

    // Getting ready to print
    demo.set_extruder(left);
    demo.set_bed_temperature(55, wait);
    demo.set_bed_temperature(60, and_go);
    demo.set_temperature(220, left, wait);
    demo.set_bed_temperature(60, wait);
    demo.move_to_origin();
    demo.clean_extruder(left);
    demo.extrusion(-0.5);
    demo.fan(0);
    demo.set_temperature(215, left);
    demo.abs_move(120, 30, 0.3);
    demo.extrusion(0.5);

    // Schwartz cube parameters
    int periods = 21;
    double a = 30;
    double skirt = 4;
    double height = 60;
    double layer_hght = 0.2;
    Vector2D start = demo.position();

    // Skirt printing
    demo.square(a + skirt, 1, 1700);
    demo.next_layer(layer_hght);
    demo.abs_move(start);
    demo.rel_move(skirt / 2, skirt / 2);
    demo.rel_move(0, a);

    //Calculaiting mashtab to fit the number of periods into a given value of the side of the square
    double mashtab = (a / periods) / Pi;
    std::cout << "Mashtab:" << mashtab;
    int steps = height / layer_hght - 1;

    // Creating start printing point
    start = demo.position();
    demo.extrusion(0.5);

    // Layer printing
    for (int i = 0; i < steps; i++)
    {
        if (i == 0)
        {
            demo.fan(255);
            demo.set_bed_temperature(55, and_go);
        }

        if (i < 3)
        {
            demo.schwartz_cube(periods, mashtab, 1200);
        }
        else
        {
            demo.schwartz_cube(periods, mashtab, 3500);
        }

        demo.next_layer(layer_hght);
        demo.abs_move(start);
    }

    //End of printing
    demo.fan(0);
    demo.set_temperature(20, 0);
    return 0;
}
