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


    //create conponets of fisic
    Rigidbody2D myBox({100,100,100,100},1);
    //
    Rigidbody2D ground({0,600,1200,100},30);
    while(1){
        Game.Clean();
        myBox.update(0.5);
        if(myBox.checkCollision(ground)){
            std::cout<<"colision";
            myBox.SetGravity(-10);
        }
        if(Game.Input.KeyDown(SDLK_SPACE)){
            //controleMoney.SetNubAnimation(controleMoney.GetNubAnimation()==0?1:0);
            myBox.applyForce({20,-100});
        }
        Game.DrawTexture(controleMoney.GetTexture(),controleMoney.GetSpriteGame(),myBox.GetBox());
        Game.DrawRect(ground.GetBox(),{100,100,100});
        Game.Update(41);
    }
    return 0;
}
