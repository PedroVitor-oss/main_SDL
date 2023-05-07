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
/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Engine::Update(int FPS){
	//Clean();
	SDL_RenderPresent(screen);
	//EventQuit();
	Input.KeyEvent();
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
void Engine::EventQuit()
{

	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				Engine::Quit();

			break;

		}
	}
}

void Engine::DrawRect(SDL_Rect box, RGBColor cor){

	SDL_SetRenderDrawColor(screen,cor.r,cor.g,cor.b,SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(screen,&box);
};

void Engine::DrawTexture(SDL_Texture* texture, SpriteGame sprite, SDL_Rect boxArea){

if(sprite.w!=0&&boxArea.w == 0){
		SDL_Rect boxFrameImg;
		boxFrameImg.h = sprite.h;
		boxFrameImg.w = sprite.w;
		boxFrameImg.x = sprite.x;
		boxFrameImg.y = sprite.y;
		SDL_RenderCopy(screen, texture,&boxFrameImg,NULL);
	}else if(sprite.w!=0&&boxArea.w != 0){
		SDL_Rect boxFrameImg;
		boxFrameImg.h = sprite.h;
		boxFrameImg.w = sprite.w;
		boxFrameImg.x = sprite.x;
		boxFrameImg.y = sprite.y;
		SDL_RenderCopy(screen, texture,&boxFrameImg,&boxArea);

	}else if(sprite.w==0&&boxArea.w != 0){
		SDL_RenderCopy(screen, texture,NULL,&boxArea);
	}else{
		SDL_RenderCopy(screen, texture,NULL,NULL);

	}
};

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

