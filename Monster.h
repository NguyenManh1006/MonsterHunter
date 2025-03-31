#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED

#define MONSTER_NUM 8
#define MONSTER_GRAVITY_SPEED 0.8
#define MONSTER_MAX_FALL_SPEED 10
#define MONSTER_SPEED 5

#include "BaseObject.h"
#include "CommonFunction.h"
#include "MainObject.h"

class Monster :  public BaseObject {
public:
    Monster();
    ~Monster();

    enum TypeMove {
        STATIC_MONSTER = 0,
        MOVE_MONSTER = 1,

    };

    void set_x_val(const float& x_val) {x_val_ = x_val;}
    void set_y_val(const float& y_val) {y_val_ = y_val;}
    void set_x_pos(const float& x_pos) {x_pos_ = x_pos;}
    void set_y_pos(const float& y_pos) {y_pos_ = y_pos;}
    float get_x_pos() const {return x_pos_;}
    float get_y_pos() const {return y_pos_;}
    void SetMapXY(const int& mp_x, const int& mp_y) {map_x_ = mp_x; map_y_ = mp_y;}

    void set_clips();
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    int get_width_frame() const {return width_frame_;}
    int get_height_frame() const {return height_frame_;}
    void DoPlayer(Map&  g_map);
    void CheckToMap(Map& g_map);

    void set_move(const int& typeMove) {type_move = typeMove;}
    void setAnimation(const int& pos_a, const int& pos_b) {max_a = pos_a; max_b = pos_b;}
    void set_input_left(const int& inputleft) {input_type.left_= inputleft;};
    void ImpMoveType(SDL_Renderer* screen);
    void InitMonster();



private:
    int frame_;
    int width_frame_;
    int height_frame_;
    SDL_Rect frame_clip_[MONSTER_NUM];
    bool on_ground_;
    int come_back_time_;
    float x_pos_, y_pos_;
    float x_val_, y_val_;
    int map_x_, map_y_;


    int type_move;
    int max_a;
    int max_b;
    Input input_type;



};




#endif // MONSTER_H_INCLUDED
