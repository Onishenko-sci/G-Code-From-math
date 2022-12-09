#include "../heads/GCode.hpp"
#include <iomanip>

gcode::gcode(std::string file_name)
{
    out.open(file_name);
    nozzle_temp = 30;
    pos.x = 0;
    pos.y = 0;
    two_extruders = false;
    extruder = 0;
    layer = 1;
    out << std::setprecision(3);
    out << "T0" << std::endl
        << "M104 S" << nozzle_temp << std::endl
        << "M109 S" << nozzle_temp << std::endl
        << "M82" << std::endl
        << "G28" << std::endl
        << "G92 E0" << std::endl
        << "T10 I5 S1 R1 P1" << std::endl
        << "G92 E0" << std::endl
        << "M107" << std::endl
        << "M140 S" << 50 << std::endl
        << "G0 F3600 X" << start_pos.x << " Y" << start_pos.y << " Z0.3" << std::endl;
    f_pos = 0;
}

gcode::~gcode()
{
    out << "M107" << std::endl
        << "M82" << std::endl
        << "M104 0" << std::endl;
    out.close();
}

void gcode::print(Vector2D where)
{
    double extr = where.abs() * 0.06236;
    f_pos += extr;
    pos = pos + where;

    out << std::setprecision(3) << "G1 X" << pos.x << " Y" << pos.y << std::setprecision(5) << " E" << f_pos << std::endl;
}

void gcode::print(Vector2D where, int spd)
{
    double extr = where.abs() * 0.06236;
    f_pos += extr;
    pos = pos + where;

    out << std::setprecision(3) << "G1 F" << spd << " X" << pos.x << " Y" << pos.y << std::setprecision(5) << " E" << f_pos << std::endl;
}

void gcode::next_layer()
{
    layer++;
    out << std::setprecision(3) << "G0 F" << 600 << " X" << pos.x << " Y" << pos.y  << " Z" << layer*0.25 << std::endl;
}