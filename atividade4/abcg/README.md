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

Agora olhemos para os arquivos window.cpp e window.hpp, onde estão presentes algumas das funções mais importantes para o devido funcionamento do programa. O jogo, uma vez executado, pode receber ações do usuário: rodar o espaço através do botão direito do mouse ou se movimentar pelo teclado (WASD):

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

No mesmo arquivo também está presente o carregamento do shader utilizado, denominado como thunder. Construído a partir dos modelos de shaders vistos no decorrer das aulas, o ideia deste shader é emular os efeitos luminosos de uma tempestade de raio, através do uso de refração e movimentação contínua do objeto.

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
```c++
  // Shaders
  std::vector<char const *> m_shaderNames{
      "thunder"};
```

Por fim, temos o carregamento do shader utilizado no espaço cúbico que simula um espaço.  

```c++
 // Criação do cubo de fundo
void Window::createSkybox() {
  auto const assetsPath{abcg::Application::getAssetsPath()};
  auto const path{assetsPath + "shaders/" + m_skyShaderName};
  m_skyProgram = abcg::createOpenGLProgram(
      {{.source = path + ".vert", .stage = abcg::ShaderStage::Vertex},
       {.source = path + ".frag", .stage = abcg::ShaderStage::Fragment}});
```

Os arquivos trackball.hpp e trackball.cpp, são responsáveis, principalmente, por possibilitar a rotação do ambiente em que o objeto se encontra, ou seja, o cubo que emula o espaço, contendo variáveis como a velocidade de rotação.

```c++
    //velocidade de rotacao
  if (m_lastPosition == currentPosition) {
    m_velocity *= m_lastTime.elapsed() > 0.01 ? 0.0 : 1.0;
    return;
  }
```
Em seguida temos os arquivos model.cpp e model.hpp, reponsáveis por calcular as normais e vértices do modelo, por exemplo, além do VBO, buffers e EBO.

```c++
  for (auto const offset : iter::range<int>(0, m_indices.size(), 3)) {
    auto &a{m_vertices.at(m_indices.at(offset + 0))};
    auto &b{m_vertices.at(m_indices.at(offset + 1))};
    auto &c{m_vertices.at(m_indices.at(offset + 2))};
    auto const edge1{b.position - a.position};
    auto const edge2{c.position - b.position};
    auto const normal{glm::cross(edge1, edge2)};
    a.normal += normal;
    b.normal += normal;
    c.normal += normal;
  }
  }
```
Por fim, temos os arquivos camera.cpp e camera.hpp que seriam responsáveis pelo funcionamento do efeito de câmera utilizada como base para a interação com o modelo e espaço a partir do teclado, podendo se movimentar horizontalmente (A e D) e verticalmente (W e S), possuindo configurações como a velocidade de movimentação, entretanto não está funcionando corretamente.

```c++
 // Movimentação
  m_eye += forward * speed;
  m_at += forward * speed;
```

[Clique aqui](https://zzanoni.github.io/computacao_grafica/atividade4/abcg/public/index.html) para acesssar a aplicação. 
