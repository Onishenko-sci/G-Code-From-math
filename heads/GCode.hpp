#ifndef PH
#define PH

#include"Vector2D.hpp"
#include<fstream>
#include<string>

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

    std::ofstream out;


public:
    gcode(std::string file_name);

    void set_extruder(unsigned int extr_number);
    void set_temperature(unsigned int temperature, unsigned int extr , bool and_wait = false );
    void set_bed_temperature(unsigned int temperature, bool and_wait = false);
    void clean_extruder(unsigned int extr_number);
    void extrusion(double how_much);
    void move_to_origin();

    void fan(int fan_speed); // 0..255

    void abs_move(Vector2D where,int spd);
    void abs_move(int x, int y,int spd);
    void abs_move(int x, int y, double z, int spd);

    void rel_move(Vector2D where);

    void rel_print(Vector2D where, int spd);
    void rel_print(double x, double y, int spd);
    
    void print_3d(double x,double y,double z);
    void print_bringe(Vector2D where);
    void next_layer(double next_layer_hight);
    void change_extruder();
    
    void square(double a, int spd);

    ~gcode();
};

#endif

