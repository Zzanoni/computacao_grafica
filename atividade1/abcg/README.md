# Computação Gráfica - Atividade 1

Nome: Lucas Zanoni de Oliveira
RA: 11056816

![alt text](https://www.nattrip.com.br/wp-content/uploads/2017/07/team-building-caca-ao-tesouro-01-1500x430.jpg)

## Funcionamento

O jogo construído de Caça do Tesouro consiste na ideia de encontrar o tesouro, demarcado por um X, em um terreno desconhecido. 

Sabendo disso, é apresentado ao jogador um tabuleiro 4x4 representando a área em que o tesouro pode estar enterrado, onde possuirá apenas uma chance de descobrir onde ele está.

## Implementação

Para a primeira atividade da matéria de Computação Gráfica da UFABC, foi utilizada a interface gráfica da biblioteca Dear ImGui, além da ABCg e do SDK Emscripten, conforme apresentado no decorrer das aulas ministradas.

Para construção do programa, foram utilizadas configurações de janela e fonte similares aos exemplos vistos e testados em sala de aula, visto que o núcleo do jogo proposto permitia a manutenção do padrão. Adicionalmente, o código-fonte do jogo está dividido em três arquivos: main.cpp, window.cpp e window.hpp.

Agora olhemos para o arquivo window.cpp, onde estão presentes as funções mais importantes para o devido funcionamento do programa. O jogo, uma vez executado, pode possuir 3 estados, sendo o play (quando o jogo ainda não tem um resultado), win (quando o jogador vence encontrando o tesouro) e lose (quando o jogador não encontra o tesouro).

```c++
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
```

No início do jogo, é utilizada a função rand() para determinar, de forma aleatório, onde o tesouro ficará localizado na matriz 4 x 4.

```c++
int col = rand() % 4;
int row = rand() % 4;
```

Feito isso, o tabuleiro está pronto para interação do jogador, onde o mesmo terá que escolher uma casa da tabuleiro (matriz) 4x4. Se ele acertar, aparece um X na casa em questão e o jogo recebe o estado de win, caso contrário aparece um O na casa escolhida, a localização do tesouro é revelada em seguida e o jogo recebe o estado de lose.

```c++
if (offset == (row * m_N + col)){
  m_board.at(offset) = 'X';
  m_gameState = GameState::Win;
}
else {
  m_board.at(offset)='O';
  m_board.at(col * m_N + row)='X';
  m_gameState = GameState::Lose;
}
```

Por fim, independente do resultado, o jogador poderá recomeçar o jogo e tentar acertar novamente a localização do tesouro.

Os demais arquivos (main.cpp e window.hpp), por sua vez, serão bem mais enxutos e serão responsáveis pela configuração do tamanho da janela e do tabuleiro, por exemplo, além de chamarem as funções presentes no window.cpp.

[Clique aqui](https://zzanoni.github.io/computacao_grafica/atividade1/abcg/public/index.html) para jogar. 
