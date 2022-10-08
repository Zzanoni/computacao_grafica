#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "abcgOpenGL.hpp"

class Window : public abcg::OpenGLWindow {
protected:
  void onCreate() override;
  void onPaintUI() override;

private:
// Define o tamanho do tabuleiro
  static int const m_N{4}; 

  enum class GameState { Play, Win, Lose};
  GameState m_gameState;

  std::array<char, m_N * m_N> m_board{}; 

  ImFont *m_font{};

  void checkEndCondition();
  void restartGame();
};

#endif
    