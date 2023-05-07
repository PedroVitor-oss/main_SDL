#include "Input.h"
#include <SDL.h>
void InputControle::AddKey(int newKey)
{
	if(QuantKey<maxQuantKey){
		bool contem = false;
		for(int i =0; i<QuantKey;i++){
			if(newKey == keyInPressed[i]){
				contem = true;
				newKeyDown  =0;
				break;
			}
		}
		if(!contem){
			keyInPressed[QuantKey] = newKey;
			QuantKey++;
		}
	}
}

void InputControle::KeyEvent()
{
	btn_mouse[0] = false;
	btn_mouse[1] = false;
	btn_mouse[2] = false;
	newKeyDown =0;
	newKeyUp = 0;
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				SDL_Quit();
				IMG_Quit();
			break;
			case SDL_KEYDOWN:
				newKeyDown = event.key.keysym.sym;
				AddKey(newKeyDown);
			break;
			case SDL_KEYUP:
				newKeyUp = event.key.keysym.sym;
				RemoveKey(newKeyUp);
			break;
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    if (event.button.state == SDL_PRESSED) {
                       btn_mouse[0] = true;
                    }
                    break;

                case SDL_BUTTON_RIGHT:
                    if (event.button.state == SDL_PRESSED) {
                       btn_mouse[1] = true;
                    }
                    break;

                case SDL_BUTTON_MIDDLE:
                    if (event.button.state == SDL_PRESSED) {
                        btn_mouse[2] = true;
                    }
                    break;
            }

			break;
				case SDL_MOUSEMOTION:
					MousePosition = Vec2({event.motion.x,event.motion.y});
				break;
		}
	}
}
Vec2 InputControle::GetPositionMouse(){
	return MousePosition;
}
bool InputControle::MousePressed(int m)
{
	return btn_mouse[m];
}
bool InputControle::KeyUp(int CodeKey)
{
	if(newKeyUp!=0){
		return (CodeKey == newKeyUp);
	}else{
		return false;
	}
}

bool InputControle::KeyDown(int CodeKey)
{

	if(newKeyDown!=0){
		return (CodeKey ==  newKeyDown);
	}else{
		return false;
	}
}
bool InputControle::KeyIsPressed(int CodeKey)
{

	for(int i =0; i< QuantKey;i++){
		if(keyInPressed[i] == CodeKey){
			return  true;
		}
	}
	return false;
}


void InputControle::RemoveKey(int Key)
{
	for(int i =0; i< QuantKey;i++){
		if(keyInPressed[i] == Key){
			keyInPressed[i] = 0;
			QuantKey--;
			break;
		}
	}
}


