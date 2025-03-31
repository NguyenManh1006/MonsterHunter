#include "CommonFunction.h"
#include "BaseObject.h"
#include "game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "Monster.h"
#include "TextObject.h"



BaseObject g_background;
TTF_Font* font_time=NULL;
TTF_Font* g_font_MENU = NULL;
Mix_Music* g_music = NULL;
bool InitData() {                       //Tạo môi trường//
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret<0) return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);    //Tạo cửa sổ//

    if(g_window == NULL) success = false;
    else {
        g_screen =SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);  //Tạọ renderer//
        if(g_screen == NULL) success = false;
        else {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);    //màu vẽ//
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags))
                success = false ;
        }
            if(TTF_Init()==-1) {
        success = false;
    }
   font_time = TTF_OpenFont("font//dlxfont_.ttf", 15);
    if(font_time == NULL) {
        success = false;
    }
    g_font_MENU = TTF_OpenFont("font//dlxfont_.ttf", 28); // Thay đổi kích thước font nếu cần
        if (g_font_MENU == NULL) {
            success = false;
}
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        success =  false;
    }
          return success;
    }
}

bool LoadBackground() {                                                             //In ra khung nền
    bool ret = g_background.LoadImg("img//background.png", g_screen );
    if(ret==false) return false;
        return true;
}

void close() {
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

std::vector<Monster*> MonsterList() {                                        //spawn quái vật
    std::vector<Monster*> list_monster;


        Monster* monsterleft = new Monster[20];
    for(int i=0;i<20;i++) {
        Monster* p_monster = (monsterleft + i);
        if(p_monster != NULL) {
            p_monster->LoadImg("img//monster_left.png", g_screen);
            p_monster->set_clips();
            int randomX = rand() % 25100 +500;                                 //vị trí ngẫu nhiên
            p_monster->set_x_pos(randomX);
            p_monster->set_y_pos(250);
            list_monster.push_back(p_monster);
        }
    }

    Monster* monsters = new Monster[20];
    for(int i=0;i<20;i++) {
        Monster* p_monster = (monsters + i);
        if(p_monster != NULL) {
            p_monster->LoadImg("img//monster.png", g_screen);
            p_monster->set_clips();
            int randomX = rand() % 25100 +500;
            p_monster->set_x_pos(randomX);
            p_monster->set_y_pos(250);
            list_monster.push_back(p_monster);
        }
    }
    return list_monster;
}

void spawnNewMonster(std::vector<Monster*> &list_monster, SDL_Renderer* g_screen) {         //spawn thêm quái vật khi có con bị tiêu diệt
    Monster* new_monster = new Monster();
    int random_monster_type = rand() % 2; // 0 for left, 1 for right
    if (random_monster_type == 0) {
        new_monster->LoadImg("img//monster_left.png", g_screen);
    } else {
        new_monster->LoadImg("img//monster.png", g_screen);
    }
    new_monster->set_clips();
    int randomX = rand() % 25100 + 500;
    new_monster->set_x_pos(randomX);
    new_monster->set_y_pos(250);
    list_monster.push_back(new_monster);
}


bool loadAndPlayMusic(const std::string& filepath) {
    g_music = Mix_LoadMUS(filepath.c_str());                                                     //tải nhạc lên
    if (g_music == NULL) {
        return false;
    }

    if (Mix_PlayMusic(g_music, -1) == -1) {                                                         //phát nhạc vô tận
        return false;
    }

    return true;
}


int main(int argc, char* argv[]) {

    ImpTimer fps_timer;                                //chỉ số fps

    if(InitData() == false) return -1;

    if(LoadBackground() == false) return -1;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        return -1;

    GameMap game_map;                                  //load map
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTiles(g_screen);

    MainObject p_player;                                   // nhân vật điều khiển
    p_player.LoadImg("img//player_right.png", g_screen);
    p_player.set_clips();

    std::vector<Monster*> list_monster = MonsterList();

    TextObject time_game;                                     // đếm thời gian
    time_game.setColor(TextObject::WHITE_TEXT);

    TextObject mark_game;
    mark_game.setColor(TextObject::WHITE_TEXT);
    UINT mark_val = 0;

    bool  is_quit = false;
    bool is_pause = false;

    if (!loadAndPlayMusic("music/background.mp3")) { // Thay đổi đường dẫn nhạc nếu cần
 ;
    }

    int ret_menu = SDLCommonFunction::ShowMenu(g_screen, g_font_MENU, "Play Game", "Exit", "img//MENU.png");     // Menu bắt đầu chơi
    if(ret_menu==1) is_quit=true;

    while(!is_quit){
            fps_timer.start();
        while(SDL_PollEvent(&g_event) != 0) {
            if(g_event.type == SDL_QUIT) {
                is_quit = true;
            }
            if(g_event.type == SDL_KEYDOWN) {
                if(g_event.key.keysym.sym == SDLK_ESCAPE) {
                    is_pause = !is_pause;
                }
            }



            p_player.HandleInputAction(g_event, g_screen);
        }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR,RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR) ;
        SDL_RenderClear(g_screen);
        g_background.Render(g_screen,NULL);

        Map map_data = game_map.getMap();

        p_player.SetMapXY(map_data.start_x_,map_data.start_y_);
        p_player.HandleBullet(g_screen);
        p_player.DoPlayer(map_data);
        p_player.Show(g_screen);

        game_map.SetMap(map_data);


        game_map.DrawMap(g_screen);

        for(int i=0;i<list_monster.size();i++) {
            Monster* p_monster = list_monster.at(i);
            if(p_monster != NULL) {
                p_monster->SetMapXY(map_data.start_x_,map_data.start_y_);
                p_monster->ImpMoveType(g_screen);
                p_monster->DoPlayer(map_data);
                p_monster->Show(g_screen);
            }
        }

        std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
        for(int r=0;r < bullet_arr.size(); r++) {
            BulletObject* p_bullet = bullet_arr.at(r);
            if(p_bullet != NULL) {
                for(int m=0;m < list_monster.size() ; m++) {
                    Monster* objectmons = list_monster.at(m);
                    if(objectmons!= NULL) {
                        SDL_Rect mRect;
                        mRect.x = objectmons->GetRect().x;
                        mRect.y = objectmons->GetRect().y;
                        mRect.w = objectmons->get_width_frame();
                        mRect.h = objectmons->get_height_frame();

                        SDL_Rect bRect = p_bullet->GetRect();

                        bool hit = SDLCommonFunction::CheckCollision(mRect,bRect);
                        if(hit) {
                                mark_val++;
                            p_player.RemoveBullet(r);
                            objectmons->Free();
                            list_monster.erase(list_monster.begin() + m);

                            spawnNewMonster(list_monster,g_screen);
                        }
                    }
                }
            }
        }

        std::string str_time = "Time: ";
        Uint32 time_val = SDL_GetTicks()/1000;
        if(is_pause) time_val =0;
        Uint32 val_time = 30;
        val_time -= time_val;

        std::string val_str_mark = std::to_string(mark_val);
        std::string  strMark  = "Mark: ";
        strMark += val_str_mark;

        mark_game.SetText(strMark);
        mark_game.loadFromRenderedText(font_time,g_screen);
        mark_game.RenderText(g_screen,SCREEN_WIDTH*0.5-50,15);

        if(val_time>0) {
            std::string  str_val = std::to_string(val_time);
            str_time += str_val;

            time_game.SetText(str_time);
            time_game.loadFromRenderedText(font_time,g_screen);
            time_game.RenderText(g_screen, SCREEN_WIDTH-200, 15);
        }

        else {
            int pause_menu = SDLCommonFunction::ShowMenu(g_screen, g_font_MENU, strMark, "Exit", "img//MENU.png");
            if(pause_menu==1) is_quit =true;
        }

        if(is_pause) {
            int pause_menu = SDLCommonFunction::ShowMenu(g_screen, g_font_MENU, " ", "Resume", "img//MENU.png");
            if(pause_menu==1) is_pause =false;
        }

        SDL_RenderPresent(g_screen);

        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND;   //ms

        if(real_imp_time < time_one_frame) {
            int delay_time = time_one_frame - real_imp_time;
            if(delay_time>=0) {
                SDL_Delay(delay_time);
            }
        }

    }

    close();
return 0;
}
