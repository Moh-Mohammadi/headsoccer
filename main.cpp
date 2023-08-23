#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfx.h>
#include <string>
#include <cmath>
#include <ctime>
#include <vector>
using namespace std;


vector <string> player_str;
vector <int> player_score;
string player1 = "", player2 = "";

void texture(SDL_Renderer *m_renderer,int xp,int yp,string addressOfImage,int width,int height);
void left_barfiller(time_t*player1_passed_time,int win_w,SDL_Renderer*m_renderer);
void right_barfiller(time_t*player2_passed_time,int win_w,SDL_Renderer*m_renderer);
void play_page(SDL_Renderer*m_renderer,int*player1_goal_number,int*player2_goal_number,
    time_t*player1_passed_time,time_t*player2_passed_time,time_t*start_time1,time_t*start_time2,int rand_pow1,int rand_pow2);

int start_page(SDL_Renderer *m_renderer, int songNumber);
int call_play_page(SDL_Renderer *m_renderer);
int settings_page(SDL_Renderer *m_renderer, int &songNumber);
int scoreboard_page(SDL_Renderer *m_renderer);
void ball_hit_ground(int *vy_ball_ptr ,int *y_ball_ptr , int y_ground);
void ball_hit_sides(int*vx_ball_ptr,int*x_ball_ptr,int win_w,int rad_ball);

void player1_jump(int*vy_player1,int*y_player1_head,int height_player1_head,int*y_player1_body,int height_player1_body
    ,int*y_player1_foot,int height_player1_foot,int y_ground,int gravity);
void player2_jump(int*vy_player2,int*y_player2_head,int height_player2_head,int*y_player2_body,int height_player2_body
    ,int*y_player2_foot,int height_player2_foot,int y_ground,int gravity);

bool ball_hit_player1_head(int*vy_ball_ptr,int*vx_ball_ptr,int*x_player1_head_ptr,int*x_player1_body_ptr,int*x_player1_foot_ptr
    ,int*y_player1_head_ptr,int*y_player1_body_ptr,int*y_player1_foot_ptr,int*x_ball_ptr,int*y_ball_ptr,int rad_ball,int width_player1_head,int height_player1_head,bool act_pow1);
void ball_hit_player1_body(int*vy_ball_ptr,int*vx_ball_ptr,int*x_player1_head_ptr,int*x_player1_body_ptr,int*x_player1_foot_ptr
    ,int*y_player1_head_ptr,int*y_player1_body_ptr,int*y_player1_foot_ptr,int*x_ball_ptr,int*y_ball_ptr,int rad_ball,int width_player1_body,int height_player1_body,bool act_pow1,bool arg);
void ball_hit_player1_foot(int*vy_ball_ptr,int*vx_ball_ptr,int*x_player1_head_ptr,int*x_player1_body_ptr,int*x_player1_foot_ptr
    ,int*y_player1_head_ptr,int*y_player1_body_ptr,int*y_player1_foot_ptr,int*x_ball_ptr,int*y_ball_ptr,int rad_ball,int width_player1_foot,int height_player1_foot,bool act_pow1);

bool ball_hit_player2_head(int*vy_ball_ptr,int*vx_ball_ptr,int*x_player2_head_ptr,int*x_player2_body_ptr,int*x_player2_foot_ptr
    ,int*y_player2_head_ptr,int*y_player2_body_ptr,int*y_player2_foot_ptr,int*x_ball_ptr,int*y_ball_ptr,int rad_ball,int width_player2_head,int height_player2_head);
void ball_hit_player2_body(int*vy_ball_ptr,int*vx_ball_ptr,int*x_player2_head_ptr,int*x_player2_body_ptr,int*x_player2_foot_ptr
    ,int*y_player2_head_ptr,int*y_player2_body_ptr,int*y_player2_foot_ptr,int*x_ball_ptr,int*y_ball_ptr,int rad_ball,int width_player2_body,int height_player2_body,bool arg);
void ball_hit_player2_foot(int*vy_ball_ptr,int*vx_ball_ptr,int*x_player2_head_ptr,int*x_player2_body_ptr,int*x_player2_foot_ptr
    ,int*y_player2_head_ptr,int*y_player2_body_ptr,int*y_player2_foot_ptr,int*x_ball_ptr,int*y_ball_ptr,int rad_ball,int width_player2_foot,int height_player2_foot);

bool Goal_checker(SDL_Renderer *m_renderer,int*x_ball_ptr,int*y_ball_ptr,int x_left_goal,int y_both_goal,int x_right_goal,int width,int height,int*player1_goal_number
    ,int*player2_goal_number,time_t*player1_passed_time,time_t*player2_passed_time,time_t*start_time1,time_t*start_time2,int*vx_ball,int rand_pow1,int rand_pow2);

bool player1_power_use(SDL_Renderer*m_renderer,time_t*player1_passed_time_ptr,time_t*start_time1,int*x_player1_head_ptr,int*x_player1_body_ptr,
    int*x_player1_foot_ptr,int*y_player1_head_ptr,int*y_player1_body_ptr,int*y_player1_foot_ptr,int width_player1_head,int height_player1_head,
    int width_player1_body,int height_player1_body,int width_player1_foot,int height_player1_foot,bool act_click,int player);                  // triple clone

void player2_power_use(int*vy_ball_ptr,int*vx_ball_ptr,int*x_player2_head_ptr,int*x_player2_body_ptr,int*x_player2_foot_ptr,int*y_player2_head_ptr,
    int*y_player2_body_ptr,int*y_player2_foot_ptr,int*x_ball_ptr,int*y_ball_ptr,int rad_ball,int width_player2_head,int height_player2_head,
    int width_player2_body,int height_player2_body,int width_player2_foot,int height_player2_foot,bool*act_click2,int*x_player1_head_ptr,
    int*x_player1_body_ptr,int*x_player1_foot_ptr,int*y_player1_head_ptr,int*y_player1_body_ptr,int*y_player1_foot_ptr,
    int width_player1_head,int height_player1_head,int width_player1_body,int height_player1_body,int width_player1_foot,int height_player1_foot,int*gravity,time_t*start_time2);

int main(int argc,char*argv[])
{

    //SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    //Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
    //Mix_Music *backgroundSound = Mix_LoadMUS("09 Break My Heart.m4a");
    //Initialization of SDL windows
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER ;
    Uint32 WND_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS ;

    int win_w = 1280, win_h = 800;
    SDL_Window * m_window;
    SDL_Renderer * m_renderer;
    //Mix_PlayMusic(backgroundSound,-1);
    //SDL_Delay(10000);
    //Mix_FreeMusic(backgroundSound);
    //Texture for loading image

    int img_w, img_h;
    SDL_Rect img_rect;


    SDL_Init( SDL_flags );
    SDL_CreateWindowAndRenderer( win_w, win_h, WND_flags, &m_window, &m_renderer );
    //Pass the focus to the drawing window
    SDL_RaiseWindow(m_window);
    //Get screen resolution
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    int W = DM.w;
    int H = DM.h;

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);


    int songNumber = 1;



    int flag = 0;

    while(flag != -1){
        if(flag == 0){
            flag = start_page(m_renderer, songNumber);
        }
        if(flag == 1){
            flag = call_play_page(m_renderer);
        }
        if(flag == 2){
            flag = scoreboard_page(m_renderer);
        }
        if(flag == 3){
            flag = settings_page(m_renderer, songNumber);
        }

    }


    //Finalize and free resources
    SDL_DestroyWindow( m_window );
    SDL_DestroyRenderer( m_renderer );
	IMG_Quit();
	SDL_Quit();
    return 0;
}

int start_page(SDL_Renderer *m_renderer, int songNumber)
{
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    int W = DM.w;
    int H = DM.h;

    ifstream in;
    in.open("score.txt");

    int i = 0;
    string str_name, str_score;
    string line;
    getline( in, line);
        while(in && line != "")
        {
            in >> str_name;
            player_str.push_back(str_name);
            in >> str_score;
            player_score.push_back(stoi(str_score));
        }
    in.close();
    string musicName;

    if(songNumber == 1)
    {
        musicName =  "05. Crossfire  (Instrumental).mp3";
    }
    if(songNumber == 2)
    {
        musicName = "06. Deadly Sting Suite (Instrumental).mp3";
    }


    Mix_Music *backgroundSound = Mix_LoadMUS(musicName.c_str());
    Mix_PlayMusic(backgroundSound, -1);

    //background declaration

    int win_w = 1280, win_h = 800;
    int background_w, background_h;
    SDL_Texture* background = NULL;
    SDL_Rect background_rect;
    background = IMG_LoadTexture(m_renderer, "pictures\\background.jpg");

    SDL_QueryTexture(background, NULL, NULL, &background_w, &background_h);
    background_rect.x = 0;
    background_rect.y = 0 ;
    background_rect.w = win_w;
    background_rect.h = win_h;
    texture(m_renderer, 0, 0, "pictures\\background.jpg", W, H);

    // start button declaration
    int start_button_radius = 150, start_button_radius_change = 10;
    const char * start_button_text ="Play!";

    //setting icon declaration
    int setting_icon_w, setting_icon_h;
    SDL_Texture* setting_icon = NULL;
    SDL_Rect setting_icon_rect;
    setting_icon = IMG_LoadTexture(m_renderer, "pictures\\setting_icon.png");

    SDL_QueryTexture(setting_icon, NULL, NULL, &setting_icon_w, &setting_icon_h);
    setting_icon_rect.x = (win_w * 99) / 100 - setting_icon_w * 0.12 ;
    setting_icon_rect.y = (win_h * 98) / 100 - setting_icon_h * 0.12 ;
    setting_icon_rect.w = setting_icon_w * 0.12;
    setting_icon_rect.h = setting_icon_h * 0.12;

    //store icon declaration
    int store_icon_w, store_icon_h;
    SDL_Texture* store_icon = NULL;
    SDL_Rect store_icon_rect;
    store_icon = IMG_LoadTexture(m_renderer, "pictures\\store_icon.png");

    SDL_QueryTexture(store_icon, NULL, NULL, &store_icon_w, &store_icon_h);
    store_icon_rect.x = (win_w * 1) / 100  ;
    store_icon_rect.y = (win_h * 92) / 100 - store_icon_h * 0.08 ;
    store_icon_rect.w = store_icon_w * 0.23;
    store_icon_rect.h = store_icon_h * 0.23;

    //      ***       THE MAIN PARTS START FROM HERE !!!!    ***  ///

    int cursor_x, cursor_y;
    SDL_Event ev;

    while(1)
    {

        //initializing screen
        SDL_PollEvent(&ev);

        if(ev.button.button == SDL_BUTTON_LEFT)
        {

            int x_settings_middle=(((win_w * 99)/100-setting_icon_w*0.12+setting_icon_w*0.12)+((win_w*99)/100-setting_icon_w*0.12))/2;
            int y_settings_middle=(((win_h * 98)/100-setting_icon_h*0.12+setting_icon_h*0.12)+((win_h*98)/100-setting_icon_h*0.12))/2;
            int x_score_middle=(((win_w*1)/100+((win_w*1)/100+store_icon_w*0.13))/2);
            int y_score_middle=(((win_h*92)/100-store_icon_h*0.08)+((win_h*92)/100-store_icon_h*0.08+store_icon_h*0.13))/2;
            SDL_GetMouseState(&cursor_x,&cursor_y);
            if( (cursor_x - win_w/2 )*(cursor_x - win_w/2) + (cursor_y - win_h/2)*(cursor_y - win_h/2) <= start_button_radius*start_button_radius)
                return 1;
            else if((abs(cursor_x - x_settings_middle) < setting_icon_w * 0.13/2.0) && (abs(cursor_y - y_settings_middle) < store_icon_h * 0.13/2.0) )
                return 3;

            else if(abs(cursor_x - x_score_middle) < store_icon_w * 0.23 && abs(cursor_y - y_score_middle) < store_icon_h * 0.23)
                return 2;

        }



        //back ground
        SDL_RenderCopy(m_renderer,background,NULL,&background_rect);

        //start button
        start_button_radius+=start_button_radius_change;
        if((start_button_radius>=200)||(start_button_radius<=150))
        {
            start_button_radius_change*=-1;
        }
        filledCircleRGBA(m_renderer,win_w/2,win_h/2,start_button_radius,127,170,229,205);
        textRGBA(m_renderer,win_w/2-45,win_h/2-15,start_button_text,2,38,127,227,222,255);

        //setting icon presentation
        SDL_RenderCopy(m_renderer,setting_icon,NULL,&setting_icon_rect);

        //store icon presentation
        SDL_RenderCopy(m_renderer,store_icon,NULL,&store_icon_rect);

        SDL_Delay(100);
        SDL_RenderPresent(m_renderer);
    }

    return -1;
}
int call_play_page(SDL_Renderer *m_renderer)
{
        int counter = 1;
    SDL_Event *ev = new SDL_Event();

    SDL_StartTextInput();


        while(counter <= 50){
            SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
            SDL_RenderClear(m_renderer);
            texture( m_renderer, 0, 0, "pictures\\name_background.png", 1280, 800);

            SDL_PollEvent(ev);

             if(ev->type == SDL_TEXTINPUT || ev->type == SDL_KEYDOWN){

                if(counter == 1){
                    if(ev->type == SDL_KEYDOWN && ev->key.keysym.sym == SDLK_BACKSPACE && player1.length() > 0){
                        player1.pop_back();
                    }
                    else if(ev ->type == SDL_TEXTINPUT){
                        player1 += ev->text.text;
                    }
                }
                if(1 < counter ){
                    if(ev->type == SDL_KEYDOWN && ev->key.keysym.sym == SDLK_BACKSPACE && player2.length() > 0){
                        player2.pop_back();
                    }
                    else if(ev ->type == SDL_TEXTINPUT){
                        player2 += ev->text.text;
                    }
                }
             }
            if( player1.length() != 0){
                textRGBA( m_renderer, 180, 600, player1.c_str(), 2, 40, 255, 0, 0, 255);
            }
            if(player2.length() != 0){
                 textRGBA( m_renderer, 960, 600, player2.c_str(), 2, 40, 255, 120, 250, 255);
            }

            SDL_RenderPresent(m_renderer);
            if(ev -> key.keysym.sym == SDLK_RETURN){
                counter++;
            }
             ev->type = 0;
        }
    SDL_StopTextInput();

     srand(time(0));
    int pl1 = rand()%3+1;
    int pl2 = rand()%3+2;

    time_t player1_passed_time = 0,player2_passed_time = 0 , *player1_passed_time_ptr=&player1_passed_time,*player2_passed_time_ptr=&player2_passed_time;
    time_t start_time1 = time(0) , *start_time1_ptr=&start_time1 , start_time2 = time(0) , *start_time2_ptr=&start_time2;
    int player1_goal_number=0,player2_goal_number=0;
    int*player1_goal_number_ptr=&player1_goal_number,*player2_goal_number_ptr=&player2_goal_number;
    play_page(m_renderer,player1_goal_number_ptr,player2_goal_number_ptr,player1_passed_time_ptr,player2_passed_time_ptr,start_time1_ptr,start_time2_ptr,pl1,pl2);

    return 0;

}

void play_page(SDL_Renderer*m_renderer,int*player1_goal_number,int*player2_goal_number
    ,time_t*player1_passed_time,time_t*player2_passed_time,time_t*start_time1,time_t*start_time2,int rand_pow1,int rand_pow2)
{
    SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
    SDL_RenderClear(m_renderer);

    int win_w = 1280, win_h = 800;
    // definitions for player locations
    int x_player1_head = 200 , y_player1_head = 560 , *y_player1_head_ptr = &y_player1_head , *x_player1_head_ptr = &x_player1_head;
    int width_player1_head = 44 , height_player1_head = 44;

    int x_player1_body = x_player1_head , y_player1_body = y_player1_head+width_player1_head , *x_player1_body_ptr = &x_player1_body , *y_player1_body_ptr = &y_player1_body;
    int width_player1_body = 44 , height_player1_body = 66;

    int x_player1_foot = x_player1_head , y_player1_foot = y_player1_body + height_player1_body , *x_player1_foot_ptr = &x_player1_foot , *y_player1_foot_ptr = &y_player1_foot;
    int width_player1_foot = 88 , height_player1_foot = 44;

    int x_player2_head = 980 , y_player2_head = 560 , *y_player2_head_ptr = &y_player2_head , *x_player2_head_ptr = &x_player2_head;
    int width_player2_head = 44 , height_player2_head = 44;

    int x_player2_body = x_player2_head , y_player2_body = y_player2_head+width_player2_head , *x_player2_body_ptr = &x_player2_body , *y_player2_body_ptr = &y_player2_body;
    int width_player2_body = 44 , height_player2_body = 66;

    int x_player2_foot = x_player2_head - 44, y_player2_foot = y_player2_body + height_player2_body , *x_player2_foot_ptr = &x_player2_foot , *y_player2_foot_ptr = &y_player2_foot;
    int width_player2_foot = 88 , height_player2_foot = 44;

    int vy_player1 = 0 , vy_player2 = 0 , *vy_player1_ptr = &vy_player1 , *vy_player2_ptr = &vy_player2;

    int x_ball = win_w/2, y_ball = 0 , *x_ball_ptr = &x_ball , *y_ball_ptr = &y_ball;
    int width_ball = 40 , height_ball = 40;
    int x_center_ball = x_ball + width_ball/2 , y_center_ball = y_ball + height_ball/2 , rad_ball = width_ball;
    int vx_ball= 0 , vy_ball = 0 , *vy_ball_ptr = &vy_ball , *vx_ball_ptr = &vx_ball;
    int gravity = 3 , *gravity_ptr = &gravity;
    const Uint8 * keystate = SDL_GetKeyboardState(NULL);
    time_t current_time = time(0);
    time_t invis_timer = 0 , st_time = time(0);

    bool act_click11 = false;
    bool act_pow11 = false;
    bool act_click12 = false , *act_click12_ptr = &act_click12;
    bool act_click13 = false , t_bool = false;
    bool act_click14 = false;

    bool act_click21 = false;
    bool act_pow21 = false;
    bool act_click22 = false , *act_click22_ptr = &act_click22;
    bool act_click23 = false;
    bool act_click24 = false;

    bool isRunning = true;


    while(1)
    {
        bool arg = false;
        string goal1 = to_string(*player1_goal_number) , goal2 = to_string(*player2_goal_number);
        char const *goal_player1 = goal1.c_str() , *goal_player2 = goal2.c_str();  //use char const* as target type

        current_time = time(0);


        // injaaaaaaaaaaa

        *player1_passed_time = (current_time-*start_time1);
        *player2_passed_time = (current_time-*start_time2);
        ball_hit_ground(vy_ball_ptr , y_ball_ptr , (win_h*9)/10-height_ball);
        player1_jump(vy_player1_ptr,y_player1_head_ptr,height_player1_head,y_player1_body_ptr,height_player1_body,y_player1_foot_ptr,height_player1_foot,(9*win_h)/10,gravity);
        player2_jump(vy_player2_ptr,y_player2_head_ptr,height_player2_head,y_player2_body_ptr,height_player2_body,y_player2_foot_ptr,height_player2_foot,(9*win_h)/10,gravity);
        ball_hit_sides(vx_ball_ptr,x_ball_ptr,win_w,rad_ball);
        *vy_ball_ptr += gravity;
        *y_ball_ptr += *vy_ball_ptr;
        *x_ball_ptr += *vx_ball_ptr;

        arg = ball_hit_player1_head(vy_ball_ptr,vx_ball_ptr,x_player1_head_ptr,x_player1_body_ptr
            ,x_player1_foot_ptr,y_player1_head_ptr,y_player1_body_ptr,y_player1_foot_ptr,x_ball_ptr,y_ball_ptr,rad_ball,width_player1_head,height_player1_head,act_pow11);
        ball_hit_player1_body(vy_ball_ptr,vx_ball_ptr,x_player1_head_ptr,x_player1_body_ptr
            ,x_player1_foot_ptr,y_player1_head_ptr,y_player1_body_ptr,y_player1_foot_ptr,x_ball_ptr,y_ball_ptr,rad_ball,width_player1_body,height_player1_body,act_pow11,arg);
        ball_hit_player1_foot(vy_ball_ptr,vx_ball_ptr,x_player1_head_ptr,x_player1_body_ptr
            ,x_player1_foot_ptr,y_player1_head_ptr,y_player1_body_ptr,y_player1_foot_ptr,x_ball_ptr,y_ball_ptr,rad_ball,width_player1_foot,height_player1_foot,act_pow11);

        arg = ball_hit_player2_head(vy_ball_ptr,vx_ball_ptr,x_player2_head_ptr,x_player2_body_ptr
            ,x_player2_foot_ptr,y_player2_head_ptr,y_player2_body_ptr,y_player2_foot_ptr,x_ball_ptr,y_ball_ptr,rad_ball,width_player2_head,height_player2_head);
        ball_hit_player2_body(vy_ball_ptr,vx_ball_ptr,x_player2_head_ptr,x_player2_body_ptr
            ,x_player2_foot_ptr,y_player2_head_ptr,y_player2_body_ptr,y_player2_foot_ptr,x_ball_ptr,y_ball_ptr,rad_ball,width_player2_body,height_player2_body,arg);
        ball_hit_player2_foot(vy_ball_ptr,vx_ball_ptr,x_player2_head_ptr,x_player2_body_ptr
            ,x_player2_foot_ptr,y_player2_head_ptr,y_player2_body_ptr,y_player2_foot_ptr,x_ball_ptr,y_ball_ptr,rad_ball,width_player2_foot,height_player2_foot);

        SDL_PumpEvents();
        texture(m_renderer , 0 , 0 , "pictures\\play_page\\stadium.jpg" , win_w , win_h);                                                                      // general background
        if(keystate[SDL_SCANCODE_W])
        {
            y_player1_body -= 30;
            y_player1_head -= 30;
            y_player1_foot -= 30;
        }
        if(keystate[SDL_SCANCODE_D])
        {
            x_player1_body += 10;
            x_player1_head += 10;
            x_player1_foot += 10;
            if(x_player1_head+width_player1_foot>x_player2_head+width_player2_head-width_player2_foot)
            {
                x_player1_body -= 10;
                x_player1_head -= 10;
                x_player1_foot -= 10;
            }
        }
        if(keystate[SDL_SCANCODE_A]){
            x_player1_body -= 10;
            x_player1_head -= 10;
            x_player1_foot -= 10;
        }
        if(keystate[SDL_SCANCODE_UP]){
            y_player2_body -= 30;
            y_player2_head -= 30;
            y_player2_foot -= 30;
        }
        if(keystate[SDL_SCANCODE_RIGHT])
        {
            x_player2_body += 10;
            x_player2_head += 10;
            x_player2_foot += 10;
        }
        if(keystate[SDL_SCANCODE_LEFT]){
            x_player2_body -= 10;
            x_player2_head -= 10;
            x_player2_foot -= 10;
            if(x_player1_head+width_player1_foot>x_player2_head+width_player2_head-width_player2_foot)
            {
                x_player2_body += 10;
                x_player2_head += 10;
                x_player2_foot += 10;
            }
        }
        if(keystate[SDL_SCANCODE_ESCAPE])
        {
            return;
        }
        if(keystate[SDL_SCANCODE_O])
        {
            if(*player1_passed_time>=30)
            {
                if(rand_pow1 == 1)
                {
                    act_click11 = true;
                    *start_time1 = time(0);
                    *player1_passed_time = (current_time-*start_time1);
                }
                else if(rand_pow1 == 2)
                {
                    act_click13 = true;
                    *start_time1 = time(0);
                    *player1_passed_time = (current_time-*start_time1);
                    invis_timer = 0;
                    t_bool = true;
                }
                else if(rand_pow1 == 3)
                {
                    int ran = rand()%2+1;
                    if(ran == 1)
                    {
                        act_click11 = true;
                        *start_time1 = time(0);
                        *player1_passed_time = (current_time-*start_time1);
                    }
                    else if(ran == 2)
                    {
                        act_click13 = true;
                        *start_time1 = time(0);
                        *player1_passed_time = (current_time-*start_time1);
                        invis_timer = 0;
                        t_bool = true;
                    }
                }
            }
        }
        rand_pow2 = 2;
        if(keystate[SDL_SCANCODE_P])
        {
            if(*player2_passed_time>=30)
            {
                if(rand_pow2 == 2)
                {
                    act_click22 = true;
                    //*start_time2 = time(0);
                    *player2_passed_time = (current_time-*start_time2);
                }
                else if(rand_pow2 == 3)
                {
                    act_click23 = true;
                    *start_time2 = time(0);
                    *player2_passed_time = (current_time-*start_time2);
                    invis_timer = 0;
                    t_bool = true;
                }
                else if(rand_pow2 == 4)
                {
                    int ran = rand()%2+3;
                    if(ran == 2)
                    {
                        act_click22 = true;
                        *start_time2 = time(0);
                        *player2_passed_time = (current_time-*start_time2);
                    }
                    else if(ran == 3)
                    {
                        act_click13 = true;
                        *start_time2 = time(0);
                        *player2_passed_time = (current_time-*start_time2);
                        invis_timer = 0;
                        t_bool = true;
                    }
                }
            }
        }

        act_pow11 = player1_power_use(m_renderer,player1_passed_time,start_time1,x_player1_head_ptr,x_player1_body_ptr,x_player1_foot_ptr,y_player1_head_ptr,y_player1_body_ptr
            ,y_player1_foot_ptr,width_player1_head,height_player1_head,width_player1_body,height_player1_body,width_player1_foot,height_player1_foot,act_click11,0);

        /*player2_power_use(vy_ball_ptr,vx_ball_ptr,x_player1_head_ptr,x_player1_body_ptr,x_player1_foot_ptr,y_player1_head_ptr,y_player1_body_ptr
                ,y_player1_foot_ptr,x_ball_ptr,y_ball_ptr,rad_ball,width_player1_head,height_player1_head,width_player1_body,height_player1_body,
                width_player1_foot,height_player1_foot,act_click22_ptr,x_player2_head_ptr,x_player2_body_ptr,x_player2_foot_ptr,y_player2_head_ptr,y_player2_body_ptr
                ,y_player2_foot_ptr,width_player2_head,height_player2_head,width_player2_body,height_player2_body,
                width_player2_foot,height_player2_foot,gravity_ptr,direction);*/

        player2_power_use(vy_ball_ptr,vx_ball_ptr,x_player2_head_ptr,x_player2_body_ptr,x_player2_foot_ptr,y_player2_head_ptr,y_player2_body_ptr
                ,y_player2_foot_ptr,x_ball_ptr,y_ball_ptr,rad_ball,width_player2_head,height_player2_head,width_player2_body,height_player2_body,
                width_player2_foot,height_player2_foot,act_click22_ptr,x_player1_head_ptr,x_player1_body_ptr,x_player1_foot_ptr,y_player1_head_ptr,y_player1_body_ptr
                ,y_player1_foot_ptr,width_player1_head,height_player1_head,width_player1_body,height_player1_body,
                width_player1_foot,height_player1_foot,gravity_ptr,start_time2);

        texture(m_renderer,win_w/4-5,0,"pictures\\play_page\\bar.png",win_w/4,40);                                                                             // left power bar
        texture(m_renderer,win_w/2+5,0,"pictures\\play_page\\bar.png",win_w/4,40);                                                                             // right power bar
        boxRGBA(m_renderer,win_w/2-5,0,win_w/2+5,50,100,100,100,255);                                                                                          // bar seperator
        left_barfiller(player1_passed_time,win_w,m_renderer);                                                                                                  // filling left power bar
        right_barfiller(player2_passed_time,win_w,m_renderer);                                                                                                 // filling right power bar
        texture(m_renderer , 0 , (win_h*6)/10 , "pictures\\play_page\\left.goal.png" , (win_w)/10 , (win_h*3)/10);                                             // left goal
        texture(m_renderer , (win_w*18)/20 , (win_h*6)/10 , "pictures\\play_page\\right.goal.png" , (win_w)/10 , (win_h*3)/10);                                // right goal
        texture(m_renderer , x_player1_head , y_player1_head , "pictures\\play_page\\player1_head.png" , width_player1_head , height_player1_head);            // first player head
        texture(m_renderer , x_player1_body , y_player1_body , "pictures\\play_page\\player1_body.png" , width_player1_body , height_player1_body);            // first player body
        texture(m_renderer , x_player1_foot , y_player1_foot , "pictures\\play_page\\player1_shoe.png" , width_player1_foot , height_player1_foot);            // first player foot picture
        texture(m_renderer , x_player2_head , y_player2_head , "pictures\\play_page\\player2_head.png" , width_player2_head , height_player2_head);            // second player head
        texture(m_renderer , x_player2_body , y_player2_body , "pictures\\play_page\\player2_body.png" , width_player2_body , height_player2_body);            // second player body
        texture(m_renderer , x_player2_foot , y_player2_foot , "pictures\\play_page\\player2_shoe.png" , width_player2_foot , height_player2_foot);            // second player foot picture
        if((!act_click13 && !act_click23)|| invis_timer>3)
        {
            invis_timer = current_time - st_time;
            texture(m_renderer , x_ball ,y_ball , "pictures\\play_page\\ball4.png" , width_ball , height_ball);                                                // ball picture
        }
        if(t_bool)
        {
            st_time = time(0);
            t_bool = false;
        }
        invis_timer = current_time - st_time;
        textRGBA(m_renderer,win_w/5+20,1,goal_player1,2,50,234,123,12,255);
        textRGBA(m_renderer,4*win_w/5-45,1,goal_player2,2,50,234,123,12,255);
        isRunning = Goal_checker(m_renderer,x_ball_ptr,y_ball_ptr,0,(win_h*6)/10,(win_w*18)/20,(win_w)/10,(win_h*3)/10,player1_goal_number
                ,player2_goal_number,player1_passed_time,player2_passed_time,start_time1,start_time2,vx_ball_ptr,rand_pow1,rand_pow2);                         // goal and celebration checker0222222222222222222222222222222666202
        if(isRunning == false){
           ofstream myOut("score.txt");

            int temp1, temp2;
            bool plr1_find = false, plr2_find = false;
           for(int i = 0; i < player_str.size(); i++){
                if(player1 == player_str[i]){
                    temp1 = i;
                    plr1_find = true;
                }
                if(player2 == player_str[i]){
                    temp2 = i;
                    plr2_find = true;
                }
           }


           if(plr1_find == false){
                player_str.push_back(player1);

               player_score.push_back(*player1_goal_number);
           }
           else{
                 player_score[temp1] += *player1_goal_number;
           }

           if(plr2_find == false){
                player_str.push_back(player2);

               player_score.push_back(*player2_goal_number);
           }
           else{
                player_score[temp2] += *player2_goal_number;
           }

            for(int i = 0; i < player_str.size(); i++){
                myOut << player_str[i]  << " " << player_score[i] << endl;
            }

            myOut.close();
            return;
        }
        SDL_RenderPresent(m_renderer);

    }
    return;
}
void player2_power_use(int*vy_ball_ptr,int*vx_ball_ptr,int*x_player2_head_ptr,int*x_player2_body_ptr,int*x_player2_foot_ptr,int*y_player2_head_ptr,
    int*y_player2_body_ptr,int*y_player2_foot_ptr,int*x_ball_ptr,int*y_ball_ptr,int rad_ball,int width_player2_head,int height_player2_head,
    int width_player2_body,int height_player2_body,int width_player2_foot,int height_player2_foot,bool*act_click2,int*x_player1_head_ptr,
    int*x_player1_body_ptr,int*x_player1_foot_ptr,int*y_player1_head_ptr,int*y_player1_body_ptr,int*y_player1_foot_ptr,
    int width_player1_head,int height_player1_head,int width_player1_body,int height_player1_body,int width_player1_foot,int height_player1_foot,int*gravity,time_t*start_time2)
{
    if(abs(*x_ball_ptr-*x_player2_foot_ptr)<90&&abs(*y_ball_ptr-*y_player2_foot_ptr)<90&&*act_click2)
    {
        *vx_ball_ptr = -60;
        *vy_ball_ptr = 0;
        *gravity = 0;
        *start_time2 = time(0);
        //*player2_passed_time = time(0);
    }

    SDL_Rect ball;
    ball.x = *x_ball_ptr;
    ball.y = *y_ball_ptr;
    ball.w = rad_ball;
    ball.h = rad_ball;

    SDL_Rect player1_head_and_body;
    player1_head_and_body.x = *x_player1_head_ptr;
    player1_head_and_body.y = *y_player1_head_ptr;
    player1_head_and_body.w = max(width_player1_head,width_player1_body);
    player1_head_and_body.h = height_player1_head+height_player1_body;

    SDL_Rect player1_foot;
    player1_foot.x = *x_player1_foot_ptr;
    player1_foot.y = *y_player1_foot_ptr;
    player1_foot.w = width_player1_foot;
    player1_foot.h = height_player1_foot;

    SDL_bool collision1 = SDL_HasIntersection(&ball,&player1_head_and_body);
    SDL_bool collision3 = SDL_HasIntersection(&ball,&player1_foot);

    if((collision1 || collision3)&&*act_click2)
    {
        *x_player1_head_ptr -= 200;
        *x_player1_body_ptr -= 200;
        *x_player1_foot_ptr -= 200;
        *gravity = 3;
        *act_click2 = false;
    }
    else if(abs(*vx_ball_ptr)>30)
    {
        if(*vx_ball_ptr>0)
            *vx_ball_ptr -= 2;
        else
            *vx_ball_ptr += 2;
    }
}
bool player1_power_use(SDL_Renderer*m_renderer,time_t*player1_passed_time_ptr,time_t*start_time1,int*x_player1_head_ptr,int*x_player1_body_ptr,
    int*x_player1_foot_ptr,int*y_player1_head_ptr,int*y_player1_body_ptr,int*y_player1_foot_ptr,int width_player1_head,int height_player1_head,
    int width_player1_body,int height_player1_body,int width_player1_foot,int height_player1_foot,bool act_click1,int player)
{
    if(*player1_passed_time_ptr<8 && act_click1 && player == 0)
    {
        texture(m_renderer,*x_player1_head_ptr-70,*y_player1_head_ptr,"pictures\\play_page\\player1_head.png",width_player1_head,height_player1_head);
        texture(m_renderer,*x_player1_body_ptr-70,*y_player1_body_ptr,"pictures\\play_page\\player1_body.png",width_player1_body,height_player1_body);
        texture(m_renderer,*x_player1_foot_ptr-70,*y_player1_foot_ptr,"pictures\\play_page\\player1_shoe.png",width_player1_foot,height_player1_foot);
        texture(m_renderer,*x_player1_head_ptr+70,*y_player1_head_ptr,"pictures\\play_page\\player1_head.png",width_player1_head,height_player1_head);
        texture(m_renderer,*x_player1_body_ptr+70,*y_player1_body_ptr,"pictures\\play_page\\player1_body.png",width_player1_body,height_player1_body);
        texture(m_renderer,*x_player1_foot_ptr+70,*y_player1_foot_ptr,"pictures\\play_page\\player1_shoe.png",width_player1_foot,height_player1_foot);
        return true;
    }
    /*else if(*player1_passed_time_ptr<8 && act_click1 && player == 1)
    {
        texture(m_renderer,*x_player1_head_ptr-70,*y_player1_head_ptr,"pictures\\play_page\\player2_head.png",width_player1_head,height_player1_head);
        texture(m_renderer,*x_player1_body_ptr-70,*y_player1_body_ptr,"pictures\\play_page\\player2_body.png",width_player1_body,height_player1_body);
        texture(m_renderer,*x_player1_foot_ptr-70,*y_player1_foot_ptr,"pictures\\play_page\\player2_shoe.png",width_player1_foot,height_player1_foot);
        texture(m_renderer,*x_player1_head_ptr+70,*y_player1_head_ptr,"pictures\\play_page\\player2_head.png",width_player1_head,height_player1_head);
        texture(m_renderer,*x_player1_body_ptr+70,*y_player1_body_ptr,"pictures\\play_page\\player2_body.png",width_player1_body,height_player1_body);
        texture(m_renderer,*x_player1_foot_ptr+70,*y_player1_foot_ptr,"pictures\\play_page\\player2_shoe.png",width_player1_foot,height_player1_foot);
        return true;
    }*/
    return false;
}
bool ball_hit_player1_head(int*vy_ball_ptr,int*vx_ball_ptr,int*x_player1_head_ptr,int*x_player1_body_ptr,int*x_player1_foot_ptr
    ,int*y_player1_head_ptr,int*y_player1_body_ptr,int*y_player1_foot_ptr,int*x_ball_ptr,int*y_ball_ptr,int rad_ball,int width_player1_head,int height_player1_head,bool act_pow1)
{
    // making 2 structures and checking if there is intersection or not
    SDL_Rect ball;
    ball.x = *x_ball_ptr;
    ball.y = *y_ball_ptr;
    ball.w = rad_ball;
    ball.h = rad_ball;

    SDL_Rect player11_head;
    SDL_Rect player12_head;
    SDL_Rect player13_head;

    player11_head.x = *x_player1_head_ptr-70;
    player11_head.y = *y_player1_head_ptr;
    player11_head.w = width_player1_head;
    player11_head.h = height_player1_head;

    player12_head.x = *x_player1_head_ptr;
    player12_head.y = *y_player1_head_ptr;
    player12_head.w = width_player1_head;
    player12_head.h = height_player1_head;

    player13_head.x = *x_player1_head_ptr+70;
    player13_head.y = *y_player1_head_ptr;
    player13_head.w = width_player1_head;
    player13_head.h = height_player1_head;

    SDL_bool collision1 = SDL_HasIntersection(&ball,&player11_head);
    SDL_bool collision2 = SDL_HasIntersection(&ball,&player12_head);
    SDL_bool collision3 = SDL_HasIntersection(&ball,&player13_head);

    if(collision2)
    {
        *x_player1_head_ptr += *vx_ball_ptr/10;
        *y_player1_head_ptr += *vy_ball_ptr/10;
        *x_player1_body_ptr += *vx_ball_ptr/10;
        *y_player1_body_ptr += *vy_ball_ptr/10;
        *x_player1_foot_ptr += *vx_ball_ptr/10;
        *y_player1_foot_ptr += *vy_ball_ptr/10;
        *vx_ball_ptr *= -1;
        *vy_ball_ptr *= -1;
    }
    else if(act_pow1)
    {
        if(collision1)
        {
            *x_player1_head_ptr += *vx_ball_ptr/10;
            *y_player1_head_ptr += *vy_ball_ptr/10;
            *x_player1_body_ptr += *vx_ball_ptr/10;
            *y_player1_body_ptr += *vy_ball_ptr/10;
            *x_player1_foot_ptr += *vx_ball_ptr/10;
            *y_player1_foot_ptr += *vy_ball_ptr/10;
            *vx_ball_ptr *= -1;
            *vy_ball_ptr *= -1;
        }
        else if(collision3)
        {
            *x_player1_head_ptr += *vx_ball_ptr/10;
            *y_player1_head_ptr += *vy_ball_ptr/10;
            *x_player1_body_ptr += *vx_ball_ptr/10;
            *y_player1_body_ptr += *vy_ball_ptr/10;
            *x_player1_foot_ptr += *vx_ball_ptr/10;
            *y_player1_foot_ptr += *vy_ball_ptr/10;
            *vx_ball_ptr *= -1;
            *vy_ball_ptr *= -1;
        }
    }
    if(collision1 || collision2 || collision3)
        return true;
    return false;
}
bool ball_hit_player2_head(int*vy_ball_ptr,int*vx_ball_ptr,int*x_player2_head_ptr,int*x_player2_body_ptr,int*x_player2_foot_ptr
    ,int*y_player2_head_ptr,int*y_player2_body_ptr,int*y_player2_foot_ptr,int*x_ball_ptr,int*y_ball_ptr,int rad_ball,int width_player2_head,int height_player2_head)
{
    // making 2 structures and checking if there is intersection or not
    SDL_Rect ball;
    SDL_Rect player2_head;
    ball.x = *x_ball_ptr;
    ball.y = *y_ball_ptr;
    ball.w = rad_ball;
    ball.h = rad_ball;
    player2_head.x = *x_player2_head_ptr;
    player2_head.y = *y_player2_head_ptr;
    player2_head.w = width_player2_head;
    player2_head.h = height_player2_head;
    SDL_bool collision = SDL_HasIntersection(&ball,&player2_head);
    if(collision)
    {
        *x_player2_head_ptr += *vx_ball_ptr/10;
        *y_player2_head_ptr += *vy_ball_ptr/10;
        *x_player2_body_ptr += *vx_ball_ptr/10;
        *y_player2_body_ptr += *vy_ball_ptr/10;
        *x_player2_foot_ptr += *vx_ball_ptr/10;
        *y_player2_foot_ptr += *vy_ball_ptr/10;
        *vx_ball_ptr *= -1;
        *vy_ball_ptr *= -1;
    }
    if(collision)
        return true;
    return false;
}
void ball_hit_player1_body(int*vy_ball_ptr,int*vx_ball_ptr,int*x_player1_head_ptr,int*x_player1_body_ptr,int*x_player1_foot_ptr
    ,int*y_player1_head_ptr,int*y_player1_body_ptr,int*y_player1_foot_ptr,int*x_ball_ptr,int*y_ball_ptr,int rad_ball,int width_player1_body,int height_player1_body,bool act_pow1,bool arg)
{
    if(!arg)
    {
        // making 2 structures and checking if there is intersection or not
        SDL_Rect ball;

        SDL_Rect player11_body;
        SDL_Rect player12_body;
        SDL_Rect player13_body;

        ball.x = *x_ball_ptr;
        ball.y = *y_ball_ptr;
        ball.w = rad_ball;
        ball.h = rad_ball;

        player11_body.x = *x_player1_body_ptr-70;
        player11_body.y = *y_player1_body_ptr;
        player11_body.w = width_player1_body;
        player11_body.h = height_player1_body;

        player12_body.x = *x_player1_body_ptr;
        player12_body.y = *y_player1_body_ptr;
        player12_body.w = width_player1_body;
        player12_body.h = height_player1_body;

        player13_body.x = *x_player1_body_ptr+70;
        player13_body.y = *y_player1_body_ptr;
        player13_body.w = width_player1_body;
        player13_body.h = height_player1_body;

        SDL_bool collision1 = SDL_HasIntersection(&ball,&player11_body);
        SDL_bool collision2 = SDL_HasIntersection(&ball,&player12_body);
        SDL_bool collision3 = SDL_HasIntersection(&ball,&player13_body);

        if(collision2)
        {
            *x_player1_head_ptr += *vx_ball_ptr/10;
            *y_player1_head_ptr += *vy_ball_ptr/10;
            *x_player1_body_ptr += *vx_ball_ptr/10;
            *y_player1_body_ptr += *vy_ball_ptr/10;
            *x_player1_foot_ptr += *vx_ball_ptr/10;
            *y_player1_foot_ptr += *vy_ball_ptr/10;
            *vx_ball_ptr *= -1;
            *vy_ball_ptr *= -1;
        }
        else if(act_pow1)
        {
            if(collision1)
            {
                *x_player1_head_ptr += *vx_ball_ptr/10;
                *y_player1_head_ptr += *vy_ball_ptr/10;
                *x_player1_body_ptr += *vx_ball_ptr/10;
                *y_player1_body_ptr += *vy_ball_ptr/10;
                *x_player1_foot_ptr += *vx_ball_ptr/10;
                *y_player1_foot_ptr += *vy_ball_ptr/10;
                *vx_ball_ptr *= -1;
                *vy_ball_ptr *= -1;
            }
            else if(collision3)
            {
                *x_player1_head_ptr += *vx_ball_ptr/10;
                *y_player1_head_ptr += *vy_ball_ptr/10;
                *x_player1_body_ptr += *vx_ball_ptr/10;
                *y_player1_body_ptr += *vy_ball_ptr/10;
                *x_player1_foot_ptr += *vx_ball_ptr/10;
                *y_player1_foot_ptr += *vy_ball_ptr/10;
                *vx_ball_ptr *= -1;
                *vy_ball_ptr *= -1;
            }
        }
    }
}
void ball_hit_player2_body(int*vy_ball_ptr,int*vx_ball_ptr,int*x_player2_head_ptr,int*x_player2_body_ptr,int*x_player2_foot_ptr
    ,int*y_player2_head_ptr,int*y_player2_body_ptr,int*y_player2_foot_ptr,int*x_ball_ptr,int*y_ball_ptr,int rad_ball,int width_player2_body,int height_player2_body,bool arg)
{
    if(!arg)
    {
        // making 2 structures and checking if there is intersection or not
        SDL_Rect ball;
        SDL_Rect player2_body;
        ball.x = *x_ball_ptr;
        ball.y = *y_ball_ptr;
        ball.w = rad_ball;
        ball.h = rad_ball;
        player2_body.x = *x_player2_body_ptr;
        player2_body.y = *y_player2_body_ptr;
        player2_body.w = width_player2_body;
        player2_body.h = height_player2_body;
        SDL_bool collision = SDL_HasIntersection(&ball,&player2_body);
        if(collision)
        {
            *x_player2_head_ptr += *vx_ball_ptr/10;
            *y_player2_head_ptr += *vy_ball_ptr/10;
            *x_player2_body_ptr += *vx_ball_ptr/10;
            *y_player2_body_ptr += *vy_ball_ptr/10;
            *x_player2_foot_ptr += *vx_ball_ptr/10;
            *y_player2_foot_ptr += *vy_ball_ptr/10;
            *vx_ball_ptr *= -1;
            *vy_ball_ptr *= -1;
        }
    }
}
void ball_hit_player1_foot(int*vy_ball_ptr,int*vx_ball_ptr,int*x_player1_head_ptr,int*x_player1_body_ptr,int*x_player1_foot_ptr
    ,int*y_player1_head_ptr,int*y_player1_body_ptr,int*y_player1_foot_ptr,int*x_ball_ptr,int*y_ball_ptr,int rad_ball,int width_player1_foot,int height_player1_foot,bool act_pow1)
{
    SDL_Rect ball;

    SDL_Rect player11_foot;
    SDL_Rect player12_foot;
    SDL_Rect player13_foot;

    ball.x = *x_ball_ptr;
    ball.y = *y_ball_ptr;
    ball.w = rad_ball;
    ball.h = rad_ball;

    player11_foot.x = *x_player1_foot_ptr-70;
    player11_foot.y = *y_player1_foot_ptr;
    player11_foot.w = width_player1_foot;
    player11_foot.h = height_player1_foot;

    player12_foot.x = *x_player1_foot_ptr;
    player12_foot.y = *y_player1_foot_ptr;
    player12_foot.w = width_player1_foot;
    player12_foot.h = height_player1_foot;

    player13_foot.x = *x_player1_foot_ptr+70;
    player13_foot.y = *y_player1_foot_ptr;
    player13_foot.w = width_player1_foot;
    player13_foot.h = height_player1_foot;

    SDL_bool collision1 = SDL_HasIntersection(&ball,&player11_foot);
    SDL_bool collision2 = SDL_HasIntersection(&ball,&player12_foot);
    SDL_bool collision3 = SDL_HasIntersection(&ball,&player13_foot);

    if(collision2)
    {
        *x_player1_head_ptr += *vx_ball_ptr/10;
        *y_player1_head_ptr += *vy_ball_ptr/10;
        *x_player1_body_ptr += *vx_ball_ptr/10;
        *y_player1_body_ptr += *vy_ball_ptr/10;
        *x_player1_foot_ptr += *vx_ball_ptr/10;
        *y_player1_foot_ptr += *vy_ball_ptr/10;
        if(*y_ball_ptr+rad_ball<*y_player1_foot_ptr+height_player1_foot)
        {
            *vy_ball_ptr=-30;
            *vx_ball_ptr=30;
        }
        else if(*y_ball_ptr+2*rad_ball<*y_player1_foot_ptr+height_player1_foot)
        {
            *vy_ball_ptr=11;
            if(*vx_ball_ptr>0)
                *vx_ball_ptr=-40;
            else
                *vx_ball_ptr=40;
        }
        else if(*y_ball_ptr<*y_player1_foot_ptr+height_player1_foot)
        {
            *vy_ball_ptr=30;
            *vx_ball_ptr=30;
        }
    }
    else if(act_pow1)
    {
        if(collision1)
        {
            *x_player1_head_ptr += *vx_ball_ptr/10;
            *y_player1_head_ptr += *vy_ball_ptr/10;
            *x_player1_body_ptr += *vx_ball_ptr/10;
            *y_player1_body_ptr += *vy_ball_ptr/10;
            *x_player1_foot_ptr += *vx_ball_ptr/10;
            *y_player1_foot_ptr += *vy_ball_ptr/10;
            if(*y_ball_ptr+rad_ball<*y_player1_foot_ptr+height_player1_foot)
            {
                *vy_ball_ptr=-30;
                *vx_ball_ptr=30;
            }
            else if(*y_ball_ptr+2*rad_ball<*y_player1_foot_ptr+height_player1_foot)
            {
                *vy_ball_ptr=11;
                if(*vx_ball_ptr>0)
                    *vx_ball_ptr=-40;
                else
                    *vx_ball_ptr=40;
            }
            else if(*y_ball_ptr<*y_player1_foot_ptr+height_player1_foot)
            {
                *vy_ball_ptr=30;
                *vx_ball_ptr=30;
            }
        }
        else if(collision3)
        {
            *x_player1_head_ptr += *vx_ball_ptr/10;
            *y_player1_head_ptr += *vy_ball_ptr/10;
            *x_player1_body_ptr += *vx_ball_ptr/10;
            *y_player1_body_ptr += *vy_ball_ptr/10;
            *x_player1_foot_ptr += *vx_ball_ptr/10;
            *y_player1_foot_ptr += *vy_ball_ptr/10;
            if(*y_ball_ptr+rad_ball<*y_player1_foot_ptr+height_player1_foot)
            {
                *vy_ball_ptr=-30;
                *vx_ball_ptr=30;
            }
            else if(*y_ball_ptr+2*rad_ball<*y_player1_foot_ptr+height_player1_foot)
            {
                *vy_ball_ptr=11;
                if(*vx_ball_ptr>0)
                    *vx_ball_ptr=-40;
                else
                    *vx_ball_ptr=40;
            }
            else if(*y_ball_ptr<*y_player1_foot_ptr+height_player1_foot)
            {
                *vy_ball_ptr=30;
                *vx_ball_ptr=30;
            }
        }
    }
}
void ball_hit_player2_foot(int*vy_ball_ptr,int*vx_ball_ptr,int*x_player2_head_ptr,int*x_player2_body_ptr,int*x_player2_foot_ptr
    ,int*y_player2_head_ptr,int*y_player2_body_ptr,int*y_player2_foot_ptr,int*x_ball_ptr,int*y_ball_ptr,int rad_ball,int width_player2_foot,int height_player2_foot)
{
    SDL_Rect ball;
    SDL_Rect player2_foot;
    ball.x = *x_ball_ptr;
    ball.y = *y_ball_ptr;
    ball.w = rad_ball;
    ball.h = rad_ball;
    player2_foot.x = *x_player2_foot_ptr;
    player2_foot.y = *y_player2_foot_ptr;
    player2_foot.w = width_player2_foot;
    player2_foot.h = height_player2_foot;
    SDL_bool collision = SDL_HasIntersection(&ball,&player2_foot);
    if(collision)
    {
        *x_player2_head_ptr += *vx_ball_ptr/10;
        *y_player2_head_ptr += *vy_ball_ptr/10;
        *x_player2_body_ptr += *vx_ball_ptr/10;
        *y_player2_body_ptr += *vy_ball_ptr/10;
        *x_player2_foot_ptr += *vx_ball_ptr/10;
        *y_player2_foot_ptr += *vy_ball_ptr/10;
        if(*y_ball_ptr+rad_ball<*y_player2_foot_ptr+height_player2_foot)
        {
            *vy_ball_ptr=-30;
            *vx_ball_ptr=-30;
        }
        else if(*y_ball_ptr+2*rad_ball<*y_player2_foot_ptr+height_player2_foot)
        {
            *vy_ball_ptr=11;
            if(*vx_ball_ptr>=0)
                *vx_ball_ptr=-40;
            else
                *vx_ball_ptr=40;
        }
        else if(*y_ball_ptr<*y_player2_foot_ptr+height_player2_foot)
        {
            *vy_ball_ptr=30;
            *vx_ball_ptr=-30;
        }
    }
}
void player1_jump(int*vy_player1,int*y_player1_head,int height_player1_head,int*y_player1_body,int height_player1_body
    ,int*y_player1_foot,int height_player1_foot,int y_ground,int gravity)
{
    int total_height = height_player1_head+height_player1_body+height_player1_foot;
    if(*y_player1_head+total_height>=y_ground)
    {
        *y_player1_head = y_ground-total_height;
        *y_player1_body = y_ground-height_player1_foot-height_player1_body;
        *y_player1_foot = y_ground-height_player1_foot;
        *vy_player1 = 0;
    }
    else if(*y_player1_head+total_height<y_ground)
    {
        *vy_player1 += gravity;
        *y_player1_head += *vy_player1;
        *y_player1_body += *vy_player1;
        *y_player1_foot += *vy_player1;
    }
}
void player2_jump(int*vy_player2,int*y_player2_head,int height_player2_head,int*y_player2_body,int height_player2_body
    ,int*y_player2_foot,int height_player2_foot,int y_ground,int gravity)
{
    int total_height = height_player2_head+height_player2_body+height_player2_foot;
    if(*y_player2_head+total_height>=y_ground)
    {
        *y_player2_head = y_ground-total_height;
        *y_player2_body = y_ground-height_player2_foot-height_player2_body;
        *y_player2_foot = y_ground-height_player2_foot;
        *vy_player2 = 0;
    }
    else if(*y_player2_head+total_height<y_ground)
    {
        *vy_player2 += gravity;
        *y_player2_head += *vy_player2;
        *y_player2_body += *vy_player2;
        *y_player2_foot += *vy_player2;
    }
}
void ball_hit_ground(int *vy_ball_ptr ,int *y_ball_ptr , int y_ground)
{
    // if ball wasn't above ground we change velocity direction
    if(*y_ball_ptr>=y_ground)
        *vy_ball_ptr *= -1;
    if(*y_ball_ptr>=y_ground && *vy_ball_ptr>-1)
    {
        *vy_ball_ptr = 0;
        *y_ball_ptr = y_ground;
    }
}
void ball_hit_sides(int*vx_ball_ptr,int*x_ball_ptr,int win_w,int rad_ball)
{
    // if ball was going out of window we don't let it happen
    if(*x_ball_ptr-*vx_ball_ptr-2*rad_ball<=0 && *x_ball_ptr<0)
        *vx_ball_ptr *= -1;
    else if(*x_ball_ptr+rad_ball>=win_w && *x_ball_ptr>0)
        *vx_ball_ptr *= -1;
}
bool Goal_checker(SDL_Renderer *m_renderer,int*x_ball_ptr,int*y_ball_ptr,int x_left_goal,int y_both_goal,int x_right_goal,int width,int height,int*player1_goal_number
    ,int*player2_goal_number,time_t*player1_passed_time,time_t*player2_passed_time,time_t*start_time1,time_t*start_time2,int*vx_ball,int rand_pow1,int rand_pow2)
{
    // check if ball is in the left goal
    if(*x_ball_ptr<x_left_goal+width && *x_ball_ptr>x_left_goal && *y_ball_ptr>y_both_goal && *y_ball_ptr<y_both_goal+height && *vx_ball<0)
    {
        // hell yeah make a celebration
        *player2_goal_number+=1;
        texture(m_renderer,400,150,"pictures\\images.png",400,100);
        SDL_RenderPresent(m_renderer);
        SDL_Delay(4000);
        play_page(m_renderer,player1_goal_number,player2_goal_number,player1_passed_time,player2_passed_time,start_time1,start_time2,rand_pow1,rand_pow2);
    }
    // check if ball is in the right goal
    else if(*x_ball_ptr<x_right_goal+width && *x_ball_ptr>x_right_goal && *y_ball_ptr>y_both_goal && *y_ball_ptr<y_both_goal+height && *vx_ball>0)
    {
        // wow nice mate

        *player1_goal_number+=1;
        texture(m_renderer,400,150,"pictures\\images.png",400,100);
        SDL_RenderPresent(m_renderer);
        SDL_Delay(4000);
        play_page(m_renderer,player1_goal_number,player2_goal_number,player1_passed_time,player2_passed_time,start_time1,start_time2,rand_pow1,rand_pow2);
    }
    if(*player1_goal_number == 4 && *player2_goal_number == 4)
    {
        const char*tie_str = "I'm afraid the game had no winner :(";
        textRGBA(m_renderer,400,350,tie_str,2,50,255,0,255,255);
        SDL_Delay(3000);
        return false;
    }
    if(*player1_goal_number == 5 || *player2_goal_number == 5)
    {
        if(*player1_goal_number == 5)
        {
            const char*pl1_win = "Congratulations Dog handler. You won the game !!";
            textRGBA(m_renderer, 200, 350, pl1_win, 2, 30, 255, 0, 0, 255);
            SDL_Delay(3000);
        }
        else
        {
            const char*pl2_win = "Congratulations Cat handler. You won the game !!";
            textRGBA(m_renderer, 200, 350, pl2_win, 2, 30, 0, 0, 255, 255);
            SDL_Delay(3000);
        }
        return false;
    }
    return true;
}
void left_barfiller(time_t*player1_passed_time,int win_w,SDL_Renderer*m_renderer)
{
    if(*player1_passed_time<30)
        boxRGBA(m_renderer,win_w/4-5,0,win_w/4+(*player1_passed_time*win_w)/120-5,40,255,0,0,255);
    else
        boxRGBA(m_renderer,win_w/4-5,0,win_w/4+(int(30)*win_w)/120-5,40,255,0,0,255);
}
void right_barfiller(time_t*player2_passed_time,int win_w,SDL_Renderer*m_renderer)
{
    if(*player2_passed_time<30)
        boxRGBA(m_renderer,3*win_w/4+5,0,3*win_w/4-(*player2_passed_time)*win_w/120+5,40,0,0,255,255);
    else
        boxRGBA(m_renderer,3*win_w/4+5,0,3*win_w/4-(int(30)*win_w)/120+5,40,0,0,255,255);
}
int settings_page(SDL_Renderer *m_renderer, int &songNumber)
{
  int win_w = 1280, win_h = 800;
    int cursor_x , cursor_y;
    SDL_Event *eve = new SDL_Event();

    while(1){
        SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 125 );
        SDL_RenderClear(m_renderer);

        filledCircleRGBA(m_renderer, win_w / 2, win_h/2, 100, 120, 120, 2, 245);
        SDL_PollEvent(eve);
        if(eve -> key.keysym.sym == SDLK_ESCAPE){
            eve->type = NULL;
            break;
        }
        if(eve->button.button == SDL_BUTTON_LEFT){
            SDL_GetMouseState(&cursor_x , &cursor_y);
            if( (cursor_x - win_w/2)*(cursor_x - win_w/2) +(cursor_y - win_h/2)*(cursor_y - win_h/2) <= 10000){
                if(songNumber == 1){
                    songNumber = 2;
                    eve -> type = 0;
                    SDL_Delay(1000);
                    return 0;
                }
                else if(songNumber == 2){
                    songNumber = 1;
                    eve -> type = 0;
                    SDL_Delay(1000);
                    return 0;
                }
            }
        }
         SDL_RenderPresent(m_renderer);
    }
    return 0;
}
int scoreboard_page(SDL_Renderer *m_renderer)
{
    int win_w = 1280, win_h = 800;
    while(1)
    {
        SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
        SDL_RenderClear(m_renderer);


        thickLineRGBA( m_renderer, 200, 0, 200, win_h, 10, 100, 100, 100, 255);
        for(int i = 0; i < win_h; i += 100)
            thickLineRGBA( m_renderer, 0, i, win_w, i, 20, 2, 120, 255, 255);



        for(int i = 0; i < player_str.size(); i++){
            textRGBA( m_renderer, 10, i*100+50, player_str[i].c_str(), 2, 25, 122, 200, 80, 255);
            textRGBA( m_renderer, 310, i*100+50, to_string(player_score[i]).c_str(), 2, 25, 122, 200, 80, 255);

        }


        SDL_Event * ev = new SDL_Event;

        SDL_PollEvent(ev);
        if(ev->key.keysym.sym == SDLK_ESCAPE)
        {
            break;
        }
        SDL_RenderPresent(m_renderer);
    }
return 0;

}
void texture(SDL_Renderer *m_renderer,int xp,int yp,string addressOfImage,int width,int height)
{
    int n = addressOfImage.length();
    char char_array[n+1];

    strcpy(char_array, addressOfImage.c_str());
    SDL_Texture *myTexture;
    myTexture = IMG_LoadTexture( m_renderer, char_array);
    int w1, h1;
    SDL_QueryTexture(myTexture, NULL, NULL, &w1, &h1);
    SDL_Rect texr1;
    texr1.x = xp;
    texr1.y = yp;
    texr1.w = width;
    texr1.h = height;
    SDL_RenderCopy( m_renderer, myTexture, NULL, &texr1);
        SDL_DestroyTexture(myTexture);
}
