#include "window.hpp" 


void Window::onCreate() {
  auto const filename{abcg::Application::getAssetsPath() +
                      "Inconsolata-Medium.ttf"};
  m_font = ImGui::GetIO().Fonts->AddFontFromFileTTF(filename.c_str(), 65.0f);
  if (m_font == nullptr) {
    throw abcg::RuntimeError{"O arquivo não pode ser carregado"};
  }

  restartGame();
}

void Window::onPaintUI() {
  // Captura do tamanho da janela
  auto const appWindowWidth{gsl::narrow<float>(getWindowSettings().width)};
  auto const appWindowHeight{gsl::narrow<float>(getWindowSettings().height)};
  
  {
    // Configurações da janela
    ImGui::SetNextWindowSize(ImVec2(appWindowWidth, appWindowHeight));
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    auto const flags{ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoCollapse};
    ImGui::Begin("Caça ao Tesouro", nullptr, flags);

    {
      bool restartSelected{};
      if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Jogo")) {
          ImGui::MenuItem("Recomeçar", nullptr, &restartSelected);
          ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
      }
      if (restartSelected) {
        restartGame();
      }
    }

    // Retorno recebido pelo usuário dependendo do resultado do jogo
    {
      std::string text;
      switch (m_gameState) {
      case GameState::Play:
        text = fmt::format("Encontre o X do tesouro");
        break;
      case GameState::Win:
        text = "Muito bem!";
        break;
      case GameState::Lose:
        text = "Errou! Tente outra vez.";
        break;
      }
      ImGui::SetCursorPosX(
          (appWindowWidth - ImGui::CalcTextSize(text.c_str()).x) / 2);
      ImGui::Text("%s", text.c_str());
      ImGui::Spacing();
    }

    ImGui::Spacing();
    

    // Tabuleiro
    {
      auto const gridHeight{appWindowHeight - 22 - 60 - (m_N * 10) - 60};
      auto const buttonHeight{gridHeight / m_N};

    // Uso da funcao random pra definir aleatoriamente onde o X ficará escondido no tabuleiro
     int col = rand() % 4;
     int row = rand() % 4;

      ImGui::PushFont(m_font);
      if (ImGui::BeginTable("Tabuleiro", m_N)) {
        for (auto i : iter::range(m_N)) {
          ImGui::TableNextRow();
          for (auto j : iter::range(m_N)) {
            ImGui::TableSetColumnIndex(j);
            auto const offset{i * m_N + j};
            auto ch{m_board.at(offset)};
            // Troca das casas com valor 0 para espaco
            if (ch == 0) {
              ch = ' ';
            }



            // Captura da casa escolhida pelo usuário e verificação do acerto
            auto buttonText{fmt::format("{}##{}{}", ch, i, j)};
            if (ImGui::Button(buttonText.c_str(), ImVec2(-1, buttonHeight))) {
              if (m_gameState == GameState::Play && ch == ' ') {
                if (offset == (row * m_N + col)){
                    m_board.at(offset) = 'X';
                    m_gameState = GameState::Win;
                }
                else {
                    m_board.at(offset)='O';
                    m_board.at(col * m_N + row)='X';
                    m_gameState = GameState::Lose;
                }
              }
            }
          }
          ImGui::Spacing();
        }
        ImGui::EndTable();
      }
      ImGui::PopFont();
    }

    ImGui::Spacing();

    // Chama a função de recomeçar o jogo
    {
      if (ImGui::Button("Recomeçar", ImVec2(-1, 50))) {
        restartGame();
      }
    }

    ImGui::End();
  }
}

void Window::restartGame() {
  m_board.fill('\0');
  m_gameState = GameState::Play;
}