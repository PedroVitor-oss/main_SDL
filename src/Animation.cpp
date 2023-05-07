#include "Animation.h"

SpriteGame Animation::GetSprite(){
	Update();
	return sprites[frame];
}
void Animation::AddSprite(SpriteGame sprite){
	sprites[quantSprites] = sprite;
	quantSprites++;
}
void Animation::SetTimeUpdate(int time){
	timeUpdate = time;
}
void Animation::Update(){
	temp++;
	if(temp%timeUpdate == 0){
		frame++;
		temp=0;
		if(frame==quantSprites){
			frame = 0;
		}
	}
}
int Animation::GetLength(){
	return quantSprites;
}
