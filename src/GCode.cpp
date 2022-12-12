#include "../heads/GCode.hpp"
#include <iomanip>
#include <cmath>

using std::endl;

gcode::gcode(std::string file_name)
{
    std::string gcode_str = ".gcode";
    out.open(file_name + gcode_str);
    out << std::fixed << std::showpoint;
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
    if (fan_speed > 255)
        fan_speed = 255;

    if (!fan_speed)
    {
        out << "M107" << endl;
        return;
    }
    out << "M106 S" << fan_speed << endl;
}

void gcode::line(double x, double y, int spd)
{
    Vector2D wher(x, y);
    line(wher, spd);
}

void gcode::abs_line(double x, double y, int spd)
{
    Vector2D wher(x, y);
    wher = wher - pos;
    line(wher, spd);
}

void gcode::line(Vector2D where, int spd)
{
    double extr = where.abs() * 0.06236;
    f_pos += extr;
    pos = pos + where;
    out << "G1";
    if (spd && spd != speed)
    {
        out << " F" << spd;
        speed = spd;
    }
    out << std::setprecision(3) << " X" << pos.x << " Y" << pos.y << std::setprecision(5) << " E" << f_pos << std::endl;
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

void gcode::abs_move(double x, double y, int spd)
{
    Vector2D wher(x, y);
    abs_move(wher, spd);
}

void gcode::rel_move(double x, double y, int spd)
{
    Vector2D wher(x, y);
    wher = pos + wher;
    abs_move(wher, spd);
}
void gcode::rel_move(Vector2D where, int spd)
{
    where = pos + where;
    abs_move(where, spd);
}

void gcode::abs_move(double x, double y, double z_pos, int spd)
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
    line(a, 0, spd);
    line(0, a, spd);
    line(-a, 0, spd);
    line(0, -a, spd);
}

void gcode::arc(double radius, double angle, double arc_angle, int spd)
{
    angle = (angle - 90.0) * radian;
    double arc_len = radian * radius * arc_angle;
    int steps = abs(arc_len / minimum_line_length);
    double angle_step = arc_angle / steps * radian;
    Vector2D circle_center = pos - Vector2D(radius * cos(angle), radius * sin(angle));

    out << ";arc " << endl;
    for (int i = 1; i <= steps; i++)
        abs_line(circle_center.x + radius * cos(angle + angle_step * i), circle_center.y + radius * sin(angle + angle_step * i), spd);
}

void gcode::schwartz(double mashtab, int spd)
{
    double min_sell_len = sqrt(2.0) * Pi / mashtab;
    int steps = min_sell_len / minimum_line_length;
    double dx = (Pi / mashtab) / steps;

    Vector2D start = pos;
    double ctz = -1 / tan(mashtab * z);

    if (ctz > 0)
        start.y = start.y - Pi / (mashtab);

    for (int i = 1; i <= steps; i++)
    {
        double y = (atan(ctz / tan(mashtab * dx * i)) + Pi / 2) / mashtab;
        abs_line(start.x + dx * i, start.y + y, spd);
    }

    //    if (ctz > 0)
    //        rel_move(0, Pi / (mashtab));
}

void gcode::schwartz_cube(int a, double mashtab, int spd)
{
    double ctz = -1 / tan(mashtab * z);
    Vector2D start = pos;
    Vector2D down(0, -Pi / mashtab);
    Vector2D right(Pi / mashtab, 0);
    if (ctz <= 0)
    {
        for (int j = 1; j <= a; j++)
        {   
            rel_move(down, spd*2);
            abs_move(start + j * down,spd*2);
            for (int n = 0; n < j; n++)
                schwartz(mashtab, spd);
        }
        rel_move(a*down, spd*2 );
        abs_move(start + a * down, spd*2);
        start = pos;
        for (int j = 1; j <= (a - 1); j++)
        {
            abs_move(start + j * right, spd*2);
            for (int n = 0; n < a - j; n++)
                schwartz(mashtab, spd);
        }
    }
    else
    {
        for (int j = 1; j <= a; j++)
        {
            abs_move(start - j * down + a * down);
            for (int n = 0; n < j; n++)
                schwartz(mashtab, spd);
        }
        abs_move(start + a * down);
        start = pos;
        for (int j = 1; j <= (a - 1); j++)
        {
            abs_move(start + j * right - a * down);
            for (int n = 0; n < a - j; n++)
                schwartz(mashtab, spd);
        }
    }
}

void gcode::comment(std::string comentar)
{
    out << "; " << comentar << endl;
}