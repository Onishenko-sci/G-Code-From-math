#ifndef PH
#define PH

#include"Vector2D.hpp"
#include<fstream>
#include<string>

class print_head
{
private:
    Vector2D pos;
    double f_pos; // filament position
    double speed;
    bool two_extruders;
    unsigned int exntruder;

    int nozzle_temp;
    unsigned int layer;

    std::ofstream out;


public:
    print_head(std::string file_name, Vector2D start_pos = Vector2D(120,120) , int nozzle_temp = 215 , bool two_extr = false);

    void abs_move(Vector2D where);
    void abs_move(Vector2D where,int speed);

    void rel_move(Vector2D where);
    void print(Vector2D where);
    void print(Vector2D where, int speed);
    
    void print_3d(double x,double y,double z);
    void print_bringe(Vector2D where);
    void next_layer();
    void change_extruder();
    
    ~print_head();
};

#endif

