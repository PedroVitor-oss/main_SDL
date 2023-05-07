#ifndef CONTROLEANIMATION_H
#define CONTROLEANIMATION_H
#include <Engine.h>
#include <Animation.h>
struct mainControler {
	Animation ani;
	SDL_Texture* textu;
};
class ControleAnimation
{
	public:
		SDL_Texture* GetTexture();
		SpriteGame GetSpriteGame();
		int  GetNubAnimation();
		void SetNubAnimation(int nubAnimation_);
		void AddAnimation(mainControler cont);
	private:
		int nubAnimation = 0;
		mainControler animations[100];
		int lengthAnimations = 0;


};

#endif // CONTROLEANIMATION_H
