#ifndef PH
#define PH

#include"Vector2D.hpp"
#include<fstream>

class print_head
{
private:
    Vector2D pos;
    double f_pos; // filament position
    double speed;
    unsigned int exntruder;
    unsigned int layer;
    std::ofstream* out;
public:
    print_head();
    void abs_move(Vector2D where);
    void rel_move(Vector2D where);
    void print(Vector2D where);
    void print_3d(double x,double y,double,z);
    void print_bringe(Vector2D where);
    void next_layer();
    void change_extruder();
    
    ~print_head();
};

#endif

