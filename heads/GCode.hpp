#ifndef PH
#define PH

#include "Vector2D.hpp"
#include <fstream>
#include <string>

enum
{
    and_go = false,
    wait = true
};

const double Pi = 3.1415926535;
const double radian = Pi/180;

class gcode
{
private:
    Vector2D pos;
    double z;
    double f_pos; // filament position
    int speed;
    bool two_extruders;
    unsigned int extruder;

    int nozzle_temp;
    unsigned int layer;
    double layer_hight;

    double minimum_line_length = 0.54;

    std::ofstream out;

public:
    gcode(std::string file_name);
    Vector2D position() {return pos;};

    void set_extruder(unsigned int extr_number);
    void set_temperature(unsigned int temperature, unsigned int extr, bool and_wait = false);
    void set_bed_temperature(unsigned int temperature, bool and_wait = false);
    void clean_extruder(unsigned int extr_number);
    void extrusion(double how_much);
    //    void change_extruder();
    void move_to_origin();
    void fan(int fan_speed); // 0..255
    void comment(std::string comentar);

    void abs_move(Vector2D where, int spd = 3600);
    void abs_move(double x, double y, int spd = 3600);
    void abs_move(double x, double y, double z, int spd = 3600);
    void rel_move(double x, double y, int spd = 3600);


    void next_layer(double next_layer_hight);
    //    void print_3d(double x,double y,double z);
    //    void print_bringe(Vector2D where);

    void line(Vector2D where, int spd = 0);
    void line(double x, double y, int spd = 0);
    void abs_line(double x, double y, int spd = 0);
    void arc(double radius,double angle, double arc_angle = 90.0,  int spd = 0);

    void schwartz( double mashtab = 1, int spd = 0);

    void square(double a, int spd = 0);

    ~gcode();
};

#endif
