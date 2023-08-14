#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include "SDL_Image.h"
#include "SDL_Mixer.h"
#include <iostream>
#include <fstream>
#include <Input.h>
#include <cmath>



struct RGBColor{

    int r = 0;
    int g = 0;
    int b = 0;
};
struct SpriteGame{

    int x ;
    int y ;
    int w ;
    int h ;
};
struct Line{
    int startX,startY;
    int endX,endY;

};
class Engine{
public:
    InputControle Input;
    KeyControle KeyCode;
    MouseButtonControle MouseButton;
    void Init(std::string title = "new window",int widthWindow = 1200,int heightWindow = 700);
    void Update(int FPS);
    void SetColorScreen(RGBColor color = {0,0,0});
    void Quit();
    SDL_Texture * CreateTexture(std::string Path);
    void DrawTexture(SDL_Texture* texture,SpriteGame sprite ,SDL_Rect boxArea);
    void DrawTexture(SDL_Texture* texture, SpriteGame sprite, SDL_Rect boxArea, bool flipX, bool flipY);
    void DrawRect(SDL_Rect box,RGBColor cor);
    void DrawLine(Line l,RGBColor cor);

    bool ColisionRect(SDL_Rect box1,SDL_Rect box2);
    void AddSave(std::string name,std::string value);
    void SetSave(std::string name,std::string value);
    std::string GetSave(std::string name);
    void Clean();
    RGBColor hexToRGB(const std::string& hexColor);
private:
    SDL_Window* window = NULL;
    SDL_Renderer* screen = NULL;
    RGBColor ColorScreen = {0,0,0};
    int hexCharToInt(char c);


    std::string nameSave = "save/save.txt";

};





#endif // ENGINE_H
