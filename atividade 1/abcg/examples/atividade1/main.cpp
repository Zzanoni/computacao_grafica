#include "window.hpp"

int main(int argc, char **argv) {
  try {
    abcg::Application app(argc, argv);

    Window window;
    window.setWindowSettings(
        // Dimensoes da janela e nome da aplicacao
        {.width = 600, .height = 600, .title = "Atividade 1"});

    app.run(window);
  } catch (std::exception const &exception) {
    fmt::print(stderr, "{}\n", exception.what());
    return -1;
  }
  return 0;
}
