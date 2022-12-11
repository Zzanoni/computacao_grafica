# Computação Gráfica - Atividade 4

Nome: Lucas Zanoni de Oliveira
RA: 11056816

![storm cube](https://user-images.githubusercontent.com/27233049/206914958-d92987e2-8ac7-40bc-9f60-700cb7c725ad.png)

## Funcionamento

A aplicação construída, denominado de Storm Cube, consiste-se de um artefato cúbico presente no espaço que, em seu interior, possui uma tempestade de raios.

Sabendo disso, a ideia de interação com o artefato é de girar o espaço em que se encontra, além de se movimentar no mesmo.

## Implementação

Para a segunda atividade da matéria de Computação Gráfica da UFABC, foi utilizada a interface gráfica da biblioteca Dear ImGui, além da ABCg e do SDK Emscripten, conforme apresentado no decorrer das aulas ministradas.

Para construção do programa, foram utilizadas configurações de janela e fonte similares aos exemplos vistos e testados em sala de aula, visto que o núcleo do jogo proposto permitia a manutenção do padrão. Adicionalmente, o código-fonte do jogo está dividido em oito arquivos: main.cpp, window.cpp, window.hpp, balls.hpp, balls.cpp, platform.hpp, platform.cpp e gamedata.hpp.

Inicialmente, temos no arquivo gamedata.hpp informações básicas como os possíveis estados do jogo (vitória e jogando) e as ações permitidas (direita e esquerda).

```c++
  enum class Input { Right, Left};
  enum class State { Playing, Win };
```

Agora olhemos para o arquivo window.cpp, onde estão presentes algumas das funções mais importantes para o devido funcionamento do programa. O jogo, uma vez executado, pode receber duas ações do usuário: ir para a direira e ir para a esquerda.

```c++
void Window::onEvent(SDL_Event const &event) {
  // Ações do teclado
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
      m_gameData.m_input.set(gsl::narrow<size_t>(Input::Left));
    if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
      m_gameData.m_input.set(gsl::narrow<size_t>(Input::Right));
  }
  if (event.type == SDL_KEYUP) {
    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
      m_gameData.m_input.reset(gsl::narrow<size_t>(Input::Left));
    if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
      m_gameData.m_input.reset(gsl::narrow<size_t>(Input::Right));
  }
}
```
Além disso, é neste arquivo onde encontramos a condição de vitória, ocorrida quando a bolha repousa sobre a plataforma.

```c++
// Açao quando colide a bola e a plataforma
    if (distance < m_platform.m_scale * 0.6f + asteroid.m_scale * 0.1f) {
      m_gameData.m_state = State::Win;
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
