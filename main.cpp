#include <Engine.h>
#include <Rigidbody2D.h>
#include <Animation.h>
#include <ControleAnimation.h>
Engine Game;
int main( int argc, char * argv[] )
{
    Game.Init("my game",1200,700);
    Game.SetColorScreen({248,248,248});
    //create Texture
    SDL_Texture* money = Game.CreateTexture("img/money.jpg");
    //create Animations
    Animation AnimationMoneyRotation;
    AnimationMoneyRotation.SetTimeUpdate(5);
    SpriteGame spritesMoney[6] = {{16,20,70,92},{86,20,70,92},{156,20,70,92},{236,20,70,92},{86,20,70,92},{156,20,70,92}};
    for(int i =0;i<6;i++){
        AnimationMoneyRotation.AddSprite(spritesMoney[i]);
    }
    Animation AnimationMoneyIdle;
    AnimationMoneyIdle.AddSprite({16,20,70,92});
    //controle de animação
    ControleAnimation controleMoney;
    controleMoney.AddAnimation({AnimationMoneyRotation,money});
    controleMoney.AddAnimation({AnimationMoneyIdle,money});

    //constantes
    float speed = 10.0;
    float forceJump = 150.0;

    //create conponets of fisic
    Rigidbody2D myBox({100,100,100,100},1);
    myBox.SetGravity(1);
    Rigidbody2D ground({0,600,1200,100},30);
    Rigidbody2D otherBox({400,300,100,300},1);
    Rigidbody2D teto({0,0,1200,100},1);
    while(Game.Input.GetExit()==false){
        Game.Clean();
        myBox.update(-0.5);
        Rigidbody2D coliders[3] = {ground,otherBox,teto};
        if(Game.Input.KeyDown(SDLK_SPACE) && myBox.checkCollision(ground)){
            myBox.applyForce({0,-forceJump});
        }
        myBox.checkCollision(coliders,3);
        if(Game.Input.KeyIsPressed(SDLK_LEFT)){
            SDL_Rect movement = myBox.GetBox();
            movement.x-=speed;
            myBox.SetRect(movement);
        }
        if(Game.Input.KeyIsPressed(SDLK_RIGHT)){
            SDL_Rect movement = myBox.GetBox();
            movement.x+=speed;
            myBox.SetRect(movement);
        }
        Game.DrawRect(otherBox.GetBox(),{100,100,100});
        Game.DrawTexture(controleMoney.GetTexture(),controleMoney.GetSpriteGame(),myBox.GetBox());
        Game.DrawRect(ground.GetBox(),{100,100,100});
        Game.DrawRect(teto.GetBox(),{100,100,100});
        Game.Update(41);
    }
    return 0;
}
