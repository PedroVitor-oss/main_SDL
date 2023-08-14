#include "Engine.h"

#include <SDL.h>
#include <SDL_Image.h>
#include "SDL_Mixer.h"
#include <iostream>
#include <windows.h>
#include <fstream>

void Engine::Init(std::string title, int widthWindow, int heightWindow ){


	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	int imgInit = IMG_Init(imgFlags);
	if ((imgInit & imgFlags) == imgFlags && SDL_Init(SDL_INIT_VIDEO)== 0) {
		//sucessed
		std::cout<< "crie uma nova janela chamdade de :"<<title<<" com tamanho de "<<widthWindow<<"x"<<heightWindow;
		window = SDL_CreateWindow( title.c_str(),SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,widthWindow,heightWindow,SDL_WINDOW_SHOWN);
		screen = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	}else{
		//erro
		std::cout<<"erro na iniciação";
	}

};
void Engine::Update(int FPS){
	SDL_RenderPresent(screen);
	Input.KeyEvent();
	if (Input.GetExit()){
		Quit();
	}
	Sleep(FPS);
}
void Engine::Clean(){
	SDL_SetRenderDrawColor(screen,ColorScreen.r,ColorScreen.g,ColorScreen.b,SDL_ALPHA_OPAQUE);
	SDL_RenderClear(screen);
	SDL_RenderPresent(screen);
};
void Engine::SetColorScreen(RGBColor color){
	ColorScreen = color;
};

void Engine::DrawRect(SDL_Rect box, RGBColor cor){

	SDL_SetRenderDrawColor(screen,cor.r,cor.g,cor.b,SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(screen,&box);
};
//render basico
void Engine::DrawTexture(SDL_Texture* texture, SpriteGame sprite, SDL_Rect boxArea){
SDL_Rect boxFrameImg;
	boxFrameImg.h = sprite.h;
	boxFrameImg.w = sprite.w;
	boxFrameImg.x = sprite.x;
	boxFrameImg.y = sprite.y;

	if (sprite.w != 0 && boxArea.w != 0) {
		SDL_RenderCopy(screen, texture, &boxFrameImg, &boxArea);
	} else if (boxArea.w != 0) {
		SDL_RenderCopy(screen, texture, nullptr, &boxArea);
	} else if (sprite.w != 0) {
		SDL_RenderCopy(screen, texture, &boxFrameImg, nullptr);
	} else {
		SDL_RenderCopy(screen, texture, nullptr, nullptr);
	}
};

//render com flips
void Engine::DrawTexture(SDL_Texture* texture, SpriteGame sprite, SDL_Rect boxArea, bool flipX, bool flipY) {
    SDL_Rect boxFrameImg;
    boxFrameImg.h = sprite.h;
    boxFrameImg.w = sprite.w;
    boxFrameImg.x = sprite.x;
    boxFrameImg.y = sprite.y;

     SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (flipX && flipY) {
        flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    } else if (flipX) {
        flip = SDL_FLIP_HORIZONTAL;
    } else if (flipY) {
        flip = SDL_FLIP_VERTICAL;
    }

    SDL_RenderCopyEx(screen, texture, &boxFrameImg, &boxArea, 0, nullptr, flip);
}
SDL_Texture* Engine::CreateTexture(std::string Path){
	SDL_Texture* newTexture =NULL;
	SDL_Surface* newImage = IMG_Load(Path.c_str());
	newTexture = SDL_CreateTextureFromSurface(screen, newImage);
	return newTexture;
};

void Engine::Quit(){
		SDL_Quit();
		IMG_Quit();
};
void Engine::DrawLine(Line l, RGBColor cor){
	SDL_SetRenderDrawColor(screen,cor.r,cor.g,cor.b,SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(screen, l.startX, l.startY, l.endX, l.endY);
}
bool Engine::ColisionRect(SDL_Rect box1, SDL_Rect box2)
{
	if(box1.x+box1.w>box2.x&&box1.x<box2.x+box2.w&&
	   box1.y+box1.h>box2.y&&box1.y<box2.y+box2.h){
			return true;
	   }else{
			return false;
	   }
}
void Engine::AddSave(std::string name, std::string value)
{
	std::fstream arquivo;
	arquivo.open(nameSave,std::ios::app);
	arquivo<<name<<'-'<<value<<"\n";
	arquivo.close();
}
void Engine::SetSave(std::string name, std::string value)
{
	std::string arquivoAlterado;
	std::ifstream arquivo;
	arquivo.open(nameSave);
	std::string line;
	while(getline(arquivo,line)){
		std::string nameArquive;
		for(int i =0;i<name.length();i++){
			nameArquive+=line[i];
		}
		if(nameArquive == name){
			arquivoAlterado+=name+'-'+value+"\n";
		}else{
			arquivoAlterado+=line+"\n";
		}
	}
	arquivo.close();
	std::fstream arquivo2;
	arquivo2.open(nameSave);
	arquivo2<<arquivoAlterado;
	arquivo2.close();
}
std::string Engine::GetSave(std::string name)
{


	std::ifstream arquivo;
	arquivo.open(nameSave);
	std::string line;
	std::string strReturn;
	while(getline(arquivo,line)){
		std::string nameArquive;
		for(int i =0;i<name.length();i++){
			nameArquive+=line[i];
		}
		if(nameArquive == name){

			for(int i=nameArquive.length()+1;i<line.length();i++){
				strReturn+=line[i];
			}

			arquivo.close();

		}
	}
	return strReturn;
}

int Engine::hexCharToInt(char c){
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    return 0;
}

RGBColor Engine::hexToRGB(const std::string& hexColor){
    RGBColor color;

    std::string hexValue = hexColor;

    // Remove o caractere '#' se estiver presente
    if (hexValue[0] == '#') {
        hexValue.erase(0, 1);
    }

    // Verifica se a string tem o formato correto
    if (hexValue.length() == 3 || hexValue.length() == 6) {
        // Se a string tem 3 caracteres, duplica cada caractere
        if (hexValue.length() == 3) {
            hexValue = hexValue.substr(0, 1) + hexValue.substr(0, 1) +
                       hexValue.substr(1, 1) + hexValue.substr(1, 1) +
                       hexValue.substr(2, 1) + hexValue.substr(2, 1);
        }

        // Converte a string hexadecimal para inteiros
        color.r = hexCharToInt(hexValue[0]) * 16 + hexCharToInt(hexValue[1]);
        color.g = hexCharToInt(hexValue[2]) * 16 + hexCharToInt(hexValue[3]);
        color.b = hexCharToInt(hexValue[4]) * 16 + hexCharToInt(hexValue[5]);
    }
    else {
        // Valores padrão se a string não tem o formato correto
        color.r = 0;
        color.g = 0;
        color.b = 0;
    }

    return color;
}
