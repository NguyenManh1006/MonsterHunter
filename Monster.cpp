#include "Monster.h"


Monster::Monster() {
    width_frame_ =0;
    height_frame_ =0;
    x_val_ =0.0;
    y_val_ =0.0;
    x_pos_ =0.0;
    y_pos_ =0.0;
    on_ground_ = false;
    come_back_time_ =0;
    frame_ =0;
    max_a=0;
    max_b=0;
    input_type.left_=0;
    type_move = STATIC_MONSTER;


}

Monster::~Monster(){

}

bool Monster::LoadImg(std::string path, SDL_Renderer* screen) {
    bool ret = BaseObject::LoadImg(path, screen);
    if(ret) {
        width_frame_=rect_.w/MONSTER_NUM;
        height_frame_=rect_.h;

    }
    return ret;
}

 void Monster::set_clips() {
    if(width_frame_>0 && height_frame_>0) {
        for(int i=0;i<8;i++) {
            frame_clip_[i].x = i*width_frame_;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
 }

 void Monster::Show(SDL_Renderer* des) {
    if(come_back_time_==0) {
        rect_.x = x_pos_- map_x_;
        rect_.y = y_pos_ - map_y_;
        frame_++;
        if(frame_>=8) {
        frame_=0;
        }
        SDL_Rect* currentClip = &frame_clip_[frame_];
        SDL_Rect renderquad = {rect_.x, rect_.y, width_frame_, height_frame_};
        SDL_RenderCopy(des, p_object_, currentClip, &renderquad);
    }
 }

 void Monster::DoPlayer(Map& g_map)  {
    if(come_back_time_==0) {
        x_val_ = 0;
        y_val_ +=MONSTER_GRAVITY_SPEED;
        if(y_val_>=MONSTER_MAX_FALL_SPEED) {
            y_val_ = MONSTER_MAX_FALL_SPEED;

            if(input_type.left_== 1) {
                x_val_ -= MONSTER_SPEED;
            }
            else if(input_type.right_==1) {
                x_val_ += MONSTER_SPEED;
            }
        }
        CheckToMap(g_map);
    }
    else if(come_back_time_>0) {
        come_back_time_--;
        if(come_back_time_==0) {
            InitMonster();
        }
    }
}

void Monster::InitMonster() {
            x_val_=0;
            y_val_=0;
            if(x_pos_>256) {

            x_pos_-=256;
            max_a-=256;
            max_b -=256;
            }
            else {
                x_pos_=0;
            }
            y_pos_=0;
            come_back_time_=0;
            input_type.left_=1;

}

void Monster::CheckToMap(Map& map_data) {
    int x1 =0, x2=0, y1=0, y2=0;

    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;     //Check chặn tường chiều ngang//

    x1 = (x_pos_ + x_val_)/TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_-1)/TILE_SIZE;

    y1 = (y_pos_)/TILE_SIZE;
    y2 = (y_pos_+height_min-1)/TILE_SIZE;

    if(x1>=0 && x2< MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
        if(x_val_ > 0 ) {

            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];


                if((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY)) {
                    x_pos_ = x2*TILE_SIZE;
                    x_pos_ -= width_frame_+1;
                    x_val_=0;
                }


        }
        else if(x_val_ < 0) {

            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];


            if((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY)) {
                x_pos_ = (x1+1)*TILE_SIZE;
                x_val_=0;
        }
    }
}

    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;    //check chặn tường chiều dọc//
    x1 = (x_pos_)/TILE_SIZE;
    x2 =  (x_pos_+width_min)/TILE_SIZE;

    y1 = (y_pos_ + y_val_)/TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_-1)/TILE_SIZE;

    if(x1>=0 && x2< MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
        if(y_val_ > 0 ) {

            int val1 = map_data.tile[y2][x2];
            int val2 = map_data.tile[y2][x1];



            if((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY)) {
                y_pos_ = y2*TILE_SIZE;
                y_pos_ -= height_frame_+1;
                y_val_=0;
                on_ground_ = true;
            }
        }
        else if(y_val_ < 0) {

             int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];


            if((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY)) {
                y_pos_ = (y1+1)*TILE_SIZE;
                y_val_=0;
            }
        }
    }
    y_pos_ += y_val_;
    x_pos_ += x_val_;

    if(x_pos_<0) {
        x_pos_=0;
    }
    else if(x_pos_+width_frame_ > map_data.max_x) {
        x_pos_= map_data.max_x - width_frame_ -1;
    }

    if(y_pos_>map_data.max_y) {
        come_back_time_ = 30;
    }
}

void Monster::ImpMoveType(SDL_Renderer* screen) {
    if(type_move == STATIC_MONSTER) {
        ;
    }
    else {

        if(on_ground_) {

            if(x_pos_>max_b) {
                input_type.left_=1;
                input_type.right_=0;
                LoadImg("img//monster_left.png",screen);
            }
            else if(x_pos_<max_a) {
                input_type.left_=0;
                input_type.right_=1;
                LoadImg("img//monster_right.png" , screen);
            }
        }
        else {
            if(input_type.left_==1) {
                LoadImg("img//monster_left.png",screen);
            }

    }


}


}



