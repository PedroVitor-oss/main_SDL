# main_SDL
Esse projeto é uma base para criar projetos em cpp com o editor code::blocks utilizando o renderizador SDL2.<br>
O projeto por padrão esta com uma images de uma moeda ( sprite animation - imagens com varias imagende movimeto), para demonstrar a utilização de animação.
Alem de conter a entrada do teclado, mais especificamente a tecla espaço, que faz a moeda se mover.<br>
Abaixo temos as bibliotecas adicionadas por padrão do preojeto para criação da janela.

# bibliotecas
- Engine.h
- Input.h
- Vec2.h
- Rigidbody2D.h
- Animation.h
- ControleAnimation.h


# Engine.h
Essa biblioteca é a mais importante de todo o projeto, ela possui funções que cria a janela do jogo, desenha coisa na tela, criar texturas entre outras coisas.<br>
A lista abaixo são funções e variaveis que essa biblioteca oferece.<br>
## Init
Essa função inicia o projeto criando uma janela, passando como parametro o nome da janela, largura e altura.<br>
```
  Engine Game;
  Game.Init("my game",1200,700);
```
Eu costumo declarar a variavem ```Game``` fora do ```int main```, e init dentro do ```int main```.

## SetColorScreen
Essa função serve para mudar o fundo da tela.<br>
O SDL desenha as coisas, e qunado ele precisa redesenhar, ele cobre os desenhos anteriores com uma cor ( a cor da tela/screen ). Ela recebe apenas um paramentro, um RGBColor uma estrutura dessa biblioteca.
```
  Game.SetColorScreen({248,248,248});
```
ou
```
  RGBColor colorScreen  = {248,248,248};
  Game.SetColorScreen(colorScreen);
```

## CreateTexture
Essa função serve para caregar uma imagem que queremos utilizar em nossos jogo. 
Essa função é chadama apenas uma vez antes do loop do jogo.<br>
estrutura de arquivos:
``` 
|- pasta do projeto
|  |-- img
|  |   |-- imagem.png
|  | ...
|  |-- main.cpp
```
codigo:
```
  SDL_Texture* imagem = Game.CreateTexture("img/imagem.jpg");
```
É preciso utilizar o ponteiro( * ) no SDL_Texture.

## DrawRect
Essa unção adicona um retangulo da lista de renderização do SDL.
```
  Game.DrawRect(SDL_Rect,RGBColor);
```
o SDL_Rect é uma estrutura do SDL que pode ser declarada das seguintes formas:
```
  Game.DrawRect({100,100,100,100},{255,255,255});
```
ou
```
  SDL_Rect box = {100,100,100,100};
  Game.DrawRect(box,{255,255,255});
```
## DrawTexture
Essa função serve para adicionar a imagem carregada pela função CreateTexture na lista de renderização do SDL.
```
  Game.DrawTexture(SDL_Texture*,SpriteGame,SDL_Rect);
```
O primeiro paramtro é a SDL_Texture ( imagem ) que vai ser mostrada.<br>
O SpriteGame é uma struct da biblioteca Engine.h que possui sua configuração igual a do SDL_Rect. Ele define o espaço da imgem que queremos que preenche.<br>
O SDL_Rect representa o espaço e posição que a imagem deve preencher na janela criada.

## Update
Podemos adicionar reatangulos e imagens na lista de renderização mas não mostramos na tela. Para isso temos a função update que atualiza a tela mostrando os item da lista de renderizando, mas no final ele apaga todos itens da lista.<br>
Essa função deve ser colocada dentro de um loop infinito.Ela precisa de um parametro inteiro, que é a a taxa de atualisação ou fps, eu costumo colocar 41.
```
#include <Engine.h>
Engine Game;
int main( int argc, char * argv[] )
{
  Game.Init("my game",1200,700);
  Game.SetColorScreen({248,248,248});
  SDL_Texture* texturePlayer = Game.CreateTexture("img/player.png");
  SDL_Rect playerBox = {100,100,100,100};
  while(1){
     Game.DrawTexture(texturePlayer,{100,100,100,100},playerBox);
     Game.Update(41);
  }
  return 0;
}
```

## Clean
Lembra que para redesenhar temos que cobrir os desenhos anteriores. A função ```Clean``` serve para isso colocamos ela como a primeria ou ultima coisa do loop.
```
  while(1){
     Game.Clean();
     Game.DrawTexture(texturePlayer,{100,100,100,100},playerBox);
     Game.Update(41);
  }
```
## Controle de Save
O controle de save, são tres funções que server para salvar dados em arquivo de texto.<br>
 - Temos como adicionar um novo save caso ele não existe.
 - Editar o valor de um save que exista.
 - E pegar o dados ( lembrando que os dados são sempre strings ).
```
  if(Game.GetSave("NameSave")!=''){
    Game.SetSave("novo valor salvo");
  }else{
    //o save NameSave não existe então irei criar ele
    Game.AddSave("NameSave","Valor inicial");
   }
```
Estrutura de onde o arquivo deve ser salvo:
``` 
|- pasta do projeto
|  |-- img
|  |   |-- imagem.png
|  |-- save
|  |   |-- save.txt
|  | ...
|  |-- main.cpp
```
# Input.h
Essa class esta atribuida na Engine.h com o nome input ele controla a entrada do teclado e mouse.
## KeyDown
Essa função retorna verdadeiro quando a tecla é precionada ( apenas uma vez ).
```
  Game.Input.KeyDown(KeyValue);
```
No local de KeyValue temos que colocar um SDLK, voce pode verificar como chamar eles nessa planilha [keycode SDL](https://docs.google.com/spreadsheets/d/1auOFSs5HZ7iZ710WjbPp9iQCZkYOlmUi2TawAkOjYX4/edit?usp=sharing).
## KeyUp
Essa função retorna verdadeiro quando a tecla deeixa de ser precionada ( apenas uma vez ).
```
  Game.Input.KeyUp(keyvalue);
```
## KeyIsPressed
Essa função retorna verdadeiro, emquando a tecla esta precionada.
```
  Game.Input.KeyIsPressed(keyvalue);
```
## MousePressed
Essa função retorna quando um botão do mouse foi precionada.
```
  GAme.Input.MousePressed(controleMouse);
```
No local do controleMouse temos que colocar um Game.MouseButton com as seguintes variaveis:
- center
- Left
- Right

