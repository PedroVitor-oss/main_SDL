#include <Engine.h>
#include <ControleAnimation.h>
#include <Rigidbody2D.h>

Engine Game;
void DrawInArea(SDL_Rect box, SDL_Texture* texture, SpriteGame sprite, Engine engi);
int main( int argc, char * argv[] )
{

    setlocale(LC_ALL,"portuguese");
    Game.Init("my game",1200,700);
    Game.SetColorScreen(Game.hexToRGB("#05f"));
    //ground
    SDL_Texture* groundsTextures = Game.CreateTexture("img/grounds.png");
    SpriteGame grounds[3];
    for(int i=0;i<3;i++)
    {
        grounds[i] = {32*i,0,32,32};
    }
    //frog
    SDL_Texture* frogIdleTexture  = Game.CreateTexture("img/frogIndle.png");
    Animation frogIdleAni;
    frogIdleAni.SetTimeUpdate(5);
    for(int i =0;i<7;i++){
        SpriteGame newSpriteGame  = {64* i + 20,28, 40 ,25};
        frogIdleAni.AddSprite(newSpriteGame);
    }
    Rigidbody2D frog({200,200,111,81},1);
    float forceJump = 0;
    float isGrounded = false;
    float direction = 1;
    Rigidbody2D ground({0,636,1200,64},10);
    Rigidbody2D plataform1({400,400,700,64},10);
    Rigidbody2D plataforms[] = {ground,plataform1};
    while(1){
        Game.Clean();
        //Entrada do usuario
        if((Game.Input.KeyUp(SDLK_SPACE) || Game.Input.KeyUp(SDLK_UP)) && isGrounded)
        {
            frog.applyForce({0,-forceJump});
            forceJump = 0;
            isGrounded = false;
        }
        if((Game.Input.KeyIsPressed(SDLK_SPACE) || Game.Input.KeyIsPressed(SDLK_UP)) && isGrounded == true)
        {
            if(forceJump<150){
                forceJump+=10;
            }
            //std::cout<<"addicionar";
        }
        if(Game.Input.KeyDown(SDLK_LEFT))
        {
            if(direction == -1){
                if(isGrounded){
                    frog.applyForce({-30,-70});
                    isGrounded = false;
                }
            }else{
            direction = -1;
            }
        }
        if(Game.Input.KeyDown(SDLK_RIGHT))
        {
            if(direction == 1){
                if(isGrounded){
                    frog.applyForce({30,-70});
                    isGrounded = false;
                }
            }else{
                direction = 1;
            }
        }

        if(!isGrounded)
        {
            if(Game.Input.KeyIsPressed(SDLK_LEFT))
            {
                frog.SetVelocity({-30,frog.GetVelocity().y});
            }
            if(Game.Input.KeyIsPressed(SDLK_RIGHT))
            {
                frog.SetVelocity({30,frog.GetVelocity().y});
            }
        }

        frog.update(0.5);

        //colisões
        if(frog.checkCollision(plataforms,2) && !isGrounded)
        {
            isGrounded = true;
        }


        //desenha na tela
        Game.DrawTexture(frogIdleTexture,frogIdleAni.GetSprite(),frog.GetBox(),direction!=1,false);
        for(int i =0;i<2;i++){
            Rigidbody2D rg = plataforms[i];
            DrawInArea(rg.GetBox(),groundsTextures,grounds[1],Game);
        }
        if(forceJump>0) //show bar force jump
        {
            Game.DrawRect({frog.GetBox().x-15,frog.GetBox().y-50,forceJump,20},Game.hexToRGB("#fa0"));
        }

        Game.Update(41);
    }
    return 0;
}
void DrawInArea(SDL_Rect box, SDL_Texture* texture, SpriteGame sprite, Engine engi)
{
    for(int i=0;i<box.w;i+=box.h)
    {
        engi.DrawTexture(texture,sprite, {box.x+ i,box.y,box.h,box.h});
    }
}
