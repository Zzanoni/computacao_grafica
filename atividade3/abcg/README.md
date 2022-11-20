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

Agora olhemos para o arquivo window.cpp e window.hpp, onde estão presentes algumas das funções mais importantes para o devido funcionamento do programa. Uma vez executado, pode receber seis ações do usuário: ir para a direira. ir para a esquerda, ir para frente, ir para trás, rodar no sentido horário e rodar no sentido antihorário.

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

Os arquivos ground.cpp e ground.hpp são importantes por serem responsáveis pela construção do piso em que o modelo é inserido. No primeiro arquivo, encontramos a configuração dos pisos e sua disposição.

```c++
// Desenho dos blocos do piso
  std::array<glm::vec3, 4> vertices{{{-0.5f, 0.0f, +0.5f},
                                     {-0.5f, 0.0f, -0.5f},
                                     {+0.5f, 0.0f, +0.5f}}};
```

Por outro lado, no segundo arquivos temos a composição da classe relacionado.


```c++
class Ground {
public:
  void create(GLuint program);
  void paint();
  void destroy();

private:
  GLuint m_VAO{};
  GLuint m_VBO{};

  GLint m_modelMatrixLoc{};
  GLint m_colorLoc{};
};
```


Por fim, os arquivos camera.hpp e camera.cpp possuem as configrações da movimentação dentro do modelo 3D.
```c++
 transform = glm::translate(transform, m_eye);
  transform = glm::rotate(transform, -speed, m_up);
  transform = glm::translate(transform, -m_eye);
```

[Clique aqui]([https://zzanoni.github.io/computacao_grafica/atividade3/abcg/public/index.html]) para jogar. 
