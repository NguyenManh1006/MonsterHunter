#ifndef BULLETOBJECT_H_INCLUDED
#define BULLETOBJECT_H_INCLUDED

#include "CommonFunction.h"
#include "BaseObject.h"

class BulletObject : public BaseObject {
public:
    BulletObject();
    ~BulletObject();

    enum BulletDir {
        DIR_RIGHT = 20,
        DIR_LEFT = 21,
    };

    void set_x_val(const int& x_val) {x_val_ = x_val;}
    void set_y_val(const int& y_val) {y_val_ = y_val;}
    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}

    void set_bullet_dir(const unsigned int& bullet_dir) {bullet_dir_= bullet_dir;}
    int get_bullet_dir() const {return bullet_dir_;}

    void set_is_move( bool is_move) {is_move_ = is_move;}
    bool get_is_move()  {return is_move_;}

    void HandleMove(const int& x_border, const int& y_border);
private:
    int x_val_;
    int y_val_;
    bool is_move_;
    unsigned int bullet_dir_;
};


#endif // BULLETOBJECT_H_INCLUDED
