# Computação Gráfica - Atividade 4

Nome: Lucas Zanoni de Oliveira
RA: 11056816

![storm cube](https://user-images.githubusercontent.com/27233049/206914958-d92987e2-8ac7-40bc-9f60-700cb7c725ad.png)

## Funcionamento

A aplicação construída, denominado de Storm Cube, consiste-se de um artefato cúbico presente no espaço que, em seu interior, possui uma tempestade de raios.

Sabendo disso, a ideia de interação com o artefato é de girar o espaço em que se encontra, além de se movimentar no mesmo.

## Implementação

Para a quarta atividade da matéria de Computação Gráfica da UFABC, foi utilizada a interface gráfica da biblioteca Dear ImGui, além da ABCg, do SDK Emscripten e OpenGL conforme apresentado no decorrer das aulas ministradas.

Para construção do programa, foram utilizadas configurações de janela e fonte similares aos exemplos vistos e testados em sala de aula, visto que o núcleo do programa proposto permitia a manutenção do padrão. Adicionalmente, o código-fonte do jogo está dividido em nove arquivos: main.cpp, window.cpp, window.hpp, trackball.hpp, trackball.cpp, camera.hpp, camera.cpp, model.cpp e model.hpp.

Inicialmente, temos no arquivo main.cpp informações básicas da janela da aplicação e alguns de seus recursos, como FPS e título:

```c++
  window.setWindowSettings({
        .width = 1920,
        .height = 1080,
        .showFPS = false,
        .showFullscreenButton=false,
        .title = "Atividade 4", 
    });
```

Agora olhemos para o arquivo window.cpp, onde estão presentes algumas das funções mais importantes para o devido funcionamento do programa. O jogo, uma vez executado, pode receber ações do usuário: rodar o espaço através do botão direito do mouse ou se movimentar pelo teclado (WASD):

```c++
// Movimentação via mouse
  if (event.type == SDL_MOUSEMOTION) {
    m_trackBallModel.mouseMove(mousePosition);
    m_trackBallLight.mouseMove(mousePosition);
  }
  if (event.type == SDL_MOUSEBUTTONDOWN) {    
    if (event.button.button == SDL_BUTTON_RIGHT) {
      m_trackBallLight.mousePress(mousePosition);
    }
  }
  if (event.type == SDL_MOUSEBUTTONUP) {
    if (event.button.button == SDL_BUTTON_RIGHT) {
      m_trackBallLight.mouseRelease(mousePosition);
    }
  }
```

```c++
  // Movimentação via teclado
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
:warning: **Apesar de estar presente no código do window.cpp (além dos arquivos camera.cpp e camera.hpp), o funcionamento da movimentação lateral e frontal não funcionou como esperado**.

Além disso, é neste arquivo onde encontramos o carregamento do objeto que, apesar de ser um arquivo .obj, foi construído manualmente tomando como base a [documentação](https://www.cs.cmu.edu/~mbz/personal/graphics/obj.html) relacionada.


```c++
  // Carregamento do modelo 3d construido
  loadModel(assetsPath + "planet.obj");
```

Por fim, no mesmo arquivo também está presente o carregamento do shader utilizado, denominado como thunder. Construído a partir dos modelos de shaders vistos no decorrer das aulas, o ideia deste shader é emular os efeitos luminosos de uma tempestade de raio, através do uso de refração e movimentação contínua o objeto.

```c++
  // Carregamento dos shaders utilizados
  for (auto const &name : m_shaderNames) {
    auto const path{assetsPath + "shaders/" + name};
    auto const program{abcg::createOpenGLProgram(
        {{.source = path + ".vert", .stage = abcg::ShaderStage::Vertex},
         {.source = path + ".frag", .stage = abcg::ShaderStage::Fragment}})};
    m_programs.push_back(program);
  }
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
