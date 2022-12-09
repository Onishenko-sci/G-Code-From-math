#ifndef PH
#define PH

#include"Vector2D.hpp"
#include<fstream>
#include<string>

class gcode
{
private:
    Vector2D pos;
    double f_pos; // filament position
    double speed;
    bool two_extruders;
    unsigned int extruder;

    int nozzle_temp;
    unsigned int layer;

    std::ofstream out;


public:
    gcode(std::string file_name);

    void set_extruder(unsigned int extr_number);
    void set_temperature(unsigned int temperature, unsigned int extr , bool and_wait = false );
    void clean_extruder(unsigned int extr_number);
    void retract(int how_much);

    void fan(int fan_speed);

    void abs_move(Vector2D where);
    void abs_move(Vector2D where,int speed);

    void rel_move(Vector2D where);
    void print(Vector2D where);
    void print(Vector2D where, int speed);
    
    void print_3d(double x,double y,double z);
    void print_bringe(Vector2D where);
    void next_layer();
    void change_extruder();
    
    ~gcode();
};

#endif

