# Computação Gráfica - Atividade 3

Nome: Lucas Zanoni de Oliveira
RA: 11056816

![CONFISSÃO](https://user-images.githubusercontent.com/27233049/202924594-3094b435-55ce-4d2c-a574-b7a95241a669.png)


## Funcionamento

O programa construído, denominado de Confissão, consiste em uma sala em 3D inspirada em um confessionário, onde o usuário pode andar por ela.

## Implementação

Para a terceira atividade da matéria de Computação Gráfica da UFABC, foi utilizada a interface gráfica da biblioteca Dear ImGui, além da ABCg e do SDK Emscripten, conforme apresentado no decorrer das aulas ministradas.

Para construção do programa, foram utilizadas configurações de janela e fonte similares aos exemplos vistos e testados em sala de aula, visto que o núcleo do programa proposto permitia a manutenção do padrão. Adicionalmente, o código-fonte do programa está dividido em sete arquivos: main.cpp, window.cpp, window.hpp, ground.hpp, ground.cpp, camera.hpp e camera.cpp.

Inicialmente, temos no arquivo main.cpp informações básicas como o tamanho da janela e seu título.

```c++
   window.setWindowSettings({
        .width = 750,
        .height = 750,
        .title = "Confissão",
```

Agora olhemos para o arquivo window.cpp, onde estão presentes algumas das funções mais importantes para o devido funcionamento do programa. Uma vez executado, pode receber seis ações do usuário: ir para a direira. ir para a esquerda, ir para frente, ir para trás, rodar no sentido horário e rodar no sentido antihorário.

```c++
void Window::onEvent(SDL_Event const &event) {
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_w)
      m_dollySpeed = 1.0f;
    if (event.key.keysym.sym == SDLK_s)
      m_dollySpeed = -1.0f;
    if (event.key.keysym.sym == SDLK_q)
      m_panSpeed = -1.0f;
    if (event.key.keysym.sym == SDLK_e)
      m_panSpeed = 1.0f;
    if (event.key.keysym.sym == SDLK_a)
      m_truckSpeed = -1.0f;
    if (event.key.keysym.sym == SDLK_d)
      m_truckSpeed = 1.0f;
  }
```
Além disso, é neste arquivo onde encontramos a inserção do modelo 3D da sala em que podemos caminhar.

```c++
// Carregar modelo
  loadModelFromFile(assetsPath + "room.obj");
```

```c++
 glm::mat4 model{2.0f};
  model = glm::translate(model, glm::vec3(-.8f, 0.0f, 0.0f));
  model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0, 1, 0));
  model = glm::scale(model, glm::vec3(0.65f));
```

Os arquivos balls.cpp e platform.cpp são importantes por serem responsáveis por possuírem a composição da pltaforma e das bolhas, principais elementos do jogo. No primeiro arquivo, encontramos a configuração da quantidade de bolhas e sua velocidade/direção.

```c++
  m_balls.resize(3);
```

```c++
  glm::vec2 const direction{0.0f, -0.1f};
  ball.m_velocity = glm::normalize(direction) / 4.0f;
```

Por outro lado, no segundo arquivos teremos as dimensões da plataforma e uma série de outras configurações envolvendo o EBO, VBO e VAO.


```c++
std::array positions{
      glm::vec2{+14.f, -2.f}, glm::vec2{+14.f, +2.f},
      glm::vec2{-14.f, +2.f}, glm::vec2{-14.f, -2.f},
      glm::vec2{+0.f, +2.f}
      };
  for (auto &position : positions) {
    position /= glm::vec2{14.f, 14.f};
  }
  std::array const indices{0, 1, 2, 3, 4, 0, 3, 2, 1};
```

Os demais arquivos (main.cpp, window.hpp, balls.hpp e plarform.hpp), por sua vez, serão bem mais enxutos e serão responsáveis pela configuração do tamanho da janela, por exemplo.

```c++
window.setWindowSettings({
        .width = 500,
        .height = 500,
        .showFPS = false,
        .showFullscreenButton = false,
        .title = "Atividade 2",
    });
```

[Clique aqui](https://zzanoni.github.io/computacao_grafica/atividade2/abcg/public/index.html) para jogar. 
