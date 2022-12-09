#include "../heads/GCode.hpp"
#include <iomanip>

using std::endl;

gcode::gcode(std::string file_name)
{
    std::string gcode_str = ".gcode";
    out.open(file_name + gcode_str);
}

gcode::~gcode()
{
    out << "M82" << std::endl;
    out.close();
}

void gcode::set_bed_temperature(unsigned int temperature, bool and_wait)
{
    if (and_wait)
    {
        out << "M190 "
            << "S" << temperature << endl;
        return;
    }

    out << "M140 "
        << "S" << temperature << endl;
}

void gcode::move_to_origin() // wrong
{
    out << "M82" << endl;
    out << "G28" << endl;
    pos.x = 0;
    pos.y = 0;
    z = layer_hight;
    layer = 1;
}

void gcode::set_extruder(unsigned int extr_number)
{
    if (extr_number >= 2)
    {
        std::cout << "Wrong extruder number!" << std::endl;
        return;
    }
    extruder = extr_number;
    out << "T" << extr_number << std::endl;
}

void gcode::set_temperature(unsigned int temperature, unsigned int extr, bool and_wait)
{
    if (and_wait)
        out << "M109 ";
    else
        out << "M104 ";

    if (extr != extruder)
        out << "T" << extr << " ";

    out << "S" << temperature << endl;
}

void gcode::clean_extruder(unsigned int extr_number)
{
    out << "G92 E0" << endl
        << "T1" << extr_number << " I5 S1 R1 P1" << endl
        << "G92 E0" << endl;
    f_pos = 0;
}

void gcode::extrusion(double how_much)
{
    f_pos = f_pos + how_much;
    out << "G1 F1200 E" << std::setprecision(5) << f_pos << endl;
    speed = 1200;
}

void gcode::fan(int fan_speed) // 0..255
{
    if (!fan_speed)
    {
        out << "M107" << endl;
        return;
    }
    out << "M106 S" << fan_speed << endl;
}

void gcode::rel_print(double x, double y, int spd)
{
    Vector2D wher(x, y);
    rel_print(wher, spd);
}

void gcode::rel_print(Vector2D where, int spd)
{
    double extr = where.abs() * 0.06236;
    f_pos += extr;
    pos = pos + where;
    out << "G1";
    if (spd != speed)
        out << " F" << spd;
    speed = spd;
    out << std::setprecision(5) << " X" << pos.x << " Y" << pos.y << std::setprecision(5) << " E" << f_pos << std::endl;
}

void gcode::next_layer(double next_layer_hight)
{
    layer++;
    z = z + next_layer_hight;
    speed = 600;
    out << std::setprecision(3) << "G0 F" << 600 << " X" << pos.x << " Y" << pos.y << " Z" << z << std::endl;
}

void gcode::abs_move(Vector2D where, int spd)
{
    pos = where;
    out << "G0";
    if (spd != speed)
        out << " F" << spd;
    speed = spd;
    out << std::setprecision(3) << " X" << pos.x << " Y" << pos.y << endl;
}

void gcode::abs_move(int x, int y, int spd)
{
    Vector2D wher(x, y);
    abs_move(wher, spd);
}

void gcode::abs_move(int x, int y, double z_pos, int spd)
{
    pos.x = x;
    pos.y = y;
    z = z_pos;
    out << "G0";
    if (spd != speed)
        out << " F" << spd;
    speed = spd;
    out << std::setprecision(3) << " X" << pos.x << " Y" << pos.y << " Z" << z << endl;
}

void gcode::square(double a, int spd)
{
    rel_print(a, 0, spd);
    rel_print(0, a , spd);
    rel_print(-a, 0, spd);
    rel_print(0, -a, spd);

}