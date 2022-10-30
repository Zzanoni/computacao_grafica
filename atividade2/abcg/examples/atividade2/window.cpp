#include "window.hpp"

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

void Window::onCreate() {
  auto const assetsPath{abcg::Application::getAssetsPath()};

  auto const filename{assetsPath + "Inconsolata-Medium.ttf"};
  m_font = ImGui::GetIO().Fonts->AddFontFromFileTTF(filename.c_str(), 60.0f);
  if (m_font == nullptr) {
    throw abcg::RuntimeError("Cannot load font file");
  }

  // Renderização dos objetos
  m_objectsProgram =
      abcg::createOpenGLProgram({{.source = assetsPath + "objects.vert",
                                  .stage = abcg::ShaderStage::Vertex},
                                 {.source = assetsPath + "objects.frag",
                                  .stage = abcg::ShaderStage::Fragment}});
  
  abcg::glClearColor(0, 0, 0, 1);

#if !defined(__EMSCRIPTEN__)
  abcg::glEnable(GL_PROGRAM_POINT_SIZE);
#endif

  m_randomEngine.seed(
      std::chrono::steady_clock::now().time_since_epoch().count());
  restart();
}

void Window::restart() {
  m_gameData.m_state = State::Playing;

  m_platform.create(m_objectsProgram);
  m_balls.create(m_objectsProgram);
}

void Window::onUpdate() {
  auto const deltaTime{gsl::narrow_cast<float>(getDeltaTime())};

  // Delay do início
  if (m_gameData.m_state != State::Playing &&
      m_restartWaitTimer.elapsed() > 5) {
    restart();
    return;
  }

  m_platform.update(m_gameData, deltaTime);
  m_balls.update(m_platform, deltaTime);

  if (m_gameData.m_state == State::Playing) {
    checkCollisions();
  }
}

void Window::onPaint() {
  abcg::glClear(GL_COLOR_BUFFER_BIT);
  abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);

  m_balls.paint();
  m_platform.paint(m_gameData);
}

void Window::onPaintUI() {
  abcg::OpenGLWindow::onPaintUI();

  {
    auto const size{ImVec2(300, 85)};
    auto const position{ImVec2((m_viewportSize.x - size.x) / 2.0f,
                               (m_viewportSize.y - size.y) / 2.0f)};
    ImGui::SetNextWindowPos(position);
    ImGui::SetNextWindowSize(size);
    ImGuiWindowFlags const flags{ImGuiWindowFlags_NoBackground |
                                 ImGuiWindowFlags_NoTitleBar |
                                 ImGuiWindowFlags_NoInputs};
    ImGui::Begin(" ", nullptr, flags);
    ImGui::PushFont(m_font);

    if (m_gameData.m_state == State::Win) {
      ImGui::Text("Vitória!");
    }

    ImGui::PopFont();
    ImGui::End();
  }
}

void Window::onResize(glm::ivec2 const &size) {
  m_viewportSize = size;

  abcg::glClear(GL_COLOR_BUFFER_BIT);
}

void Window::onDestroy() {
  abcg::glDeleteProgram(m_objectsProgram);

  m_balls.destroy();
  m_platform.destroy();
}

void Window::checkCollisions() {
  // Verifica de a plataforma se colidiu com a bola
  for (auto const &asteroid : m_balls.m_balls) {
    auto const asteroidTranslation{asteroid.m_translation};
    auto const distance{
        glm::distance(m_platform.m_translation, asteroidTranslation)};

  // Açao quando colide a bola e a plataforma
    if (distance < m_platform.m_scale * 0.6f + asteroid.m_scale * 0.1f) {
      m_gameData.m_state = State::Win;
      m_restartWaitTimer.restart();

    }
  }
}
