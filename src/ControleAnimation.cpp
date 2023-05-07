#include "ControleAnimation.h"
#include <SDL.h>
SDL_Texture* ControleAnimation::GetTexture()
{
	SDL_Texture* textureReturn = animations[nubAnimation].textu;
	return textureReturn;
}
SpriteGame ControleAnimation::GetSpriteGame()
{
	return animations[nubAnimation].ani.GetSprite();
}
int  ControleAnimation::GetNubAnimation()
{
	return nubAnimation;
}
void ControleAnimation::SetNubAnimation(int nubAnimation_)
{
	nubAnimation = nubAnimation_;
}
void ControleAnimation::AddAnimation(mainControler cont)
{
	animations[lengthAnimations] = cont;
	lengthAnimations++;
}
