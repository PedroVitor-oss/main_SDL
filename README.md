# main_SDL
Este projeto é um molde para criar jogos em c++ com o editor codeblocks. Ele utiliza o sdl2, sdl2_image e sdl2_mixer, mesmo que algumas funções dessas bibliotecas não sejam usadas. Esse projeto é de código aberto permitindo a edição e adição de códigos nas bibliotecas principais, isso ajuda a entender mais sobre o sdl2. Por padrão o projeto vai vim com no mínimo um sprite sheet ( imagem com vários sprite) para demonstrar as bibliotecas de animação, entrada do teclado como por exemplo keydown, e um corpo com física para de mostrar funções físicas..

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
Alem desse exemplo podemos adicionar um flip na imagem tanto para horizontal tanto para vertical. Veja o codigo abaixo.

    Game.DrawTexture(SDL_Texture*,SpriteGame,SDL_Rect,bool,bool);

O quarto parametro é o um boleano que verifica se ele deve flipar no eixo horizontal e o quito é referente ao vertical.



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
Essa class como a engine deve ser declarada e adicionada no cabeçalho  ele controla a entrada do teclado e mouse.
```
//declaração
#include <InputControle.h>
InputControle Input;
```
## KeyDown
Essa função retorna verdadeiro quando a tecla é precionada ( apenas uma vez ).
```
  Input.KeyDown(KeyValue);
```
No local de KeyValue temos que colocar um SDLK, voce pode verificar como chamar eles nessa planilha [keycode SDL](https://docs.google.com/spreadsheets/d/1auOFSs5HZ7iZ710WjbPp9iQCZkYOlmUi2TawAkOjYX4/edit?usp=sharing).
## KeyUp
Essa função retorna verdadeiro quando a tecla deeixa de ser precionada ( apenas uma vez ).
```
  Input.KeyUp(keyvalue);
```
## KeyIsPressed
Essa função retorna verdadeiro, emquando a tecla esta precionada.
```
  Input.KeyIsPressed(keyvalue);
```
## MousePressed
Essa função retorna ( **true** ou **false** ) se  um botão do mouse foi precionada.
```
  Input.MousePressed(controleMouse);
```
No local do controleMouse temos que colocar um Game.MouseButton com as seguintes variaveis:
- Center
- Left
- Right
```
  Input.MousePressed(Game.MouseButton.Left)
```
## GetPositionMouse
Essa função retorna em forma  de  vetor a posição do mouse na janela. ( terá uma esplicação melhor da biblioteca Vec2 embreve)<br>
```
  Vec2 positionMouse = Input.GetPositionMouse();
  positionMouse.x;//posição x
  positionMouse.y;//posição y
```

## GetExit
Essa é uma função que permite verificar quando é precionado o botão de fechar a janela.<br>
Costumo colocar como parametro do loop.
```
int main( int argc, char * argv[] )
{
  while(!Input.GetExit())
  {
  //code game
  }
  //apos fechar a janela
  return 0;
}
```
# Vec2.h
Essa biblioteca possui uma class bem simples ela posui apenas doias variaveis float , **x** e **y**.<br>
Ela futuramente utilizara de opradores como **+**,**-**,***** e **/**.

# Rigidbody2D.h
Essa função é responsavel por aplicar fisica aos SDL_Rect, como graficade, lançamento e colisão.<br>
## Iniciação 
Para iniciat uma corpo fisico usamos a seguinte codigo.
```
 Rigidbody2D myBox(SDL_Rect, massa);
```
O SDL_Rect pode ser colocado um ja definido que utilizamos para anterior mente para desenhar na tela ou um novo com ```{100,100,100,100}```. A massa é um intero que serve para funções futuras.
## Update
Essa função faz os calculos da de fisica, ele recebe apenas uma parametro float o deltaTime, o deltaTime controla o tempo de atualização, quanto maior o valor mais rapido ( lembrando que o valor não pode ser  0 pois isso faz com que não aja valvulo nem um).
```
  myBox.update(0.5);
```
## SetGravity
Essa função ser para dizer qual gravidade deve ser aplicado no corpo, por padrão ela esta como dez mas ela pode ser alterada. O parametro que ela recebe é um float.
```
myBox.SetGravity(9.8);
```
## applyForce
Essa função serve como um "empurão", ele adiciona uma aceleração inicial que vaz com que o corpo se locaomova ate que a velocidade chegue a zero. Ele recebe como parametro um Vec2 onde o parametro x seria a força x e y a força y,  que pode ser substituido por ```{fx,fy}```.( No momento não há desaceleração por atrito e elasticidade ).
```
  myBox.applyForce({0,-100});
```
Por nossa gravidade ser positiva para que nosso corpo suba para sima com efeito de pulo temos que colocar gravidade negativa.
## checkCollision 
Essa função tem duas possibilidade de usar ela apenas com um outro corpo fisico e com uma lista. Quando é apenas uma corpo fisica ela retorna se ouve uma colisão com o objeto do parametro. Exemplo:
```
   Rigidbody2D ground({0,600,1200,100},30);
   myBox.checkCollision(ground);
```
Nesse caso a função retornara quano myBox colidir com o ground ( o chão ).<br>
No caso da lista podemos fazer da seguinte forma:
```
Rigidbody2D ground({0,600,1200,100},30);
Rigidbody2D wall({400,300,100,300},1);

Rigidbody2D listColiders[2] = {ground, wall};

myBox.checkCollision(listColiders, 2);
```
Nesse caso ela ira retornar **true** mesmo que não esteja colidindo com nada, pois ela esta calculando o comportamento fisico que o my.box teria com esse corpos.

## GetBox
Essa função retorna um SDL_Rect, ou seja, caso quereia desenhar um retangulo com as posições  fisicas do corpo essa função é apição mais adequada.
```
  myBox.GetBox();
```
## GetVelocity
Essa função retorna um Vec2 sendo x a velçocidade x e y a velocidade y.
```
  myBox.GetVelocity();
```
# Animation.h
Essa classe possui funções referente a SpriteGame uma estrutura da biblioteca Engine.h, comentada na função DrawTexture.
## AddSprite
Essa função adiciona um sprite a um array de sprites que sera acessado, lembrando que a ordem que o addSprite é colocado é aordem que ira aparecer na animação.
```
  Animation run;
  run.AddSprite({0,0,30,40});
  run.AddSprite({30,0,30,40});
  run.AddSprite({60,0,30,40});
  run.AddSprite({90,0,30,40});
```
## SetTimeUpdate
Essa função define quando a atualização ira acontecer, no updade da engine, caso tenha colocado o valor 41 para a atualização isso equivale a 1000ms/41 equivale a aprocimadamente 24 frames por segundo(fps) quando definimos que a atualização deve ocorer em 5 em 5 frames de animação (24fps/5) temos aproximadamente 4 sprites por segundo  passando na tela. Por padrão o tempo de atualização é  10 .
```
run.SetTimeUpdate(5);
```
## GetSprite
Essa função retorna o sprite game que dever ser mostrado na tela, seguindo as regras das outras funções.
```
   Game.DrawTexture(CharaterTexture,run.GetSprite(),myBox);
```
# ControleAnimation.h
Essa classe permite que tenhamos varias animaçãoes 
