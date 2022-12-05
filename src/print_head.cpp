#include "../heads/print_head.hpp"
#include <iomanip>

print_head::print_head(std::string file_name, Vector2D start_pos, int nozzle_Temp, bool two_extr)
{
    out.open(file_name);
    nozzle_temp = nozzle_Temp;
    pos.x = start_pos.x;
    pos.y = start_pos.y;
    two_extruders = two_extr;
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

print_head::~print_head()
{
    out << "M107" << std::endl
        << "M82" << std::endl
        << "M104 0" << std::endl;
    out.close();
}

void print_head::print(Vector2D where)
{
    double extr = where.abs() * 0.06236;
    f_pos += extr;
    pos = pos + where;

    out << std::setprecision(3) << "G1 X" << pos.x << " Y" << pos.y << std::setprecision(5) << " E" << f_pos << std::endl;
}

void print_head::print(Vector2D where, int spd)
{
    double extr = where.abs() * 0.06236;
    f_pos += extr;
    pos = pos + where;

    out << std::setprecision(3) << "G1 F" << spd << " X" << pos.x << " Y" << pos.y << std::setprecision(5) << " E" << f_pos << std::endl;
}

void print_head::next_layer()
{
    layer++;
    out << std::setprecision(3) << "G0 F" << 600 << " X" << pos.x << " Y" << pos.y  << " Z" << layer*0.25 << std::endl;
}