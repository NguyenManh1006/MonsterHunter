#ifndef COMMONFUNCTION_H_INCLUDED
#define COMMONFUNCTION_H_INCLUDED

#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <vector>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

const int FRAME_PER_SECOND = 25;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0Xff;

#define TILE_SIZE 64
#define BLANK_TILE 0
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define STATE_MONEY 4

typedef struct Input {
    int left_ , right_ , up_ , down_ , jump_;

};

typedef struct Map {
    int start_x_;
    int start_y_;

    int max_x;
    int max_y;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;
    };

typedef struct ColorData
{
public:
    ColorData(Uint8 r, Uint8 g, Uint8 b)
    {
        red_ = r, green_ = g, blue_ = b;
    }
    Uint8 red_;
    Uint8 green_;
    Uint8 blue_;
};


namespace SDLCommonFunction {
   bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
   int ShowMenu(SDL_Renderer* g_screen, TTF_Font* font,
                      const std::string& menu1,
                      const std::string& menu2,
                      const std::string& img_name);

}
#endif // COMMONFUNCTION_H_INCLUDED
