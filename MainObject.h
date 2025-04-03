#ifndef MAINOBJECT_H_INCLUDED
#define MAINOBJECT_H_INCLUDED

#include "CommonFunction.h"
#include "BaseObject.h"
#include <vector>
#include "BulletObject.h"

#define GRAVITY_SPEED 1.2
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 10
#define JUMP_FORCE 25

class MainObject : public BaseObject {
public:
    MainObject();
    ~MainObject();

    enum WalkType {
        WALK_RIGHT = 0,
        WALK_LEFT = 1,
    };

   bool LoadImg(std::string path , SDL_Renderer* screen);
 //  bool LoadFireImage(std::string path, SDL_Renderer* screen);
   void Show(SDL_Renderer* des);
   void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
   void set_clips();

   void DoPlayer(Map& map_data);
   void CheckToMap(Map& map_data);
   void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y;}

   void set_bullet_list(std::vector<BulletObject*> bullet_list) {
        p_bullet_list = bullet_list;
   }
   std::vector<BulletObject*>  get_bullet_list() const {return p_bullet_list;}

   void HandleBullet(SDL_Renderer* des);
   void RemoveBullet(const int& ind);

   void CenterEntityOnMap(Map& map_data);
   void IncreaseMoney();

   void showPauseScreen(SDL_Renderer* renderer);




private:

    int money_count;

    std::vector<BulletObject*> p_bullet_list;

    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[8];
    Input input_type_;
    int frame_;
    int status_;
    bool on_ground_;
    int current_status_;

    int map_x_;
    int map_y_;

    int come_back_time;

    Mix_Chunk* bullet_sound;
};



#endif // MAINOBJECT_H_INCLUDED
