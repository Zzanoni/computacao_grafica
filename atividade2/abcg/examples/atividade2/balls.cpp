#include "balls.hpp"

#include <glm/gtx/fast_trigonometry.hpp>

void Balls::create(GLuint program) {
  destroy();

  m_randomEngine.seed(
      std::chrono::steady_clock::now().time_since_epoch().count());

  m_program = program;

  m_colorLoc = abcg::glGetUniformLocation(m_program, "color");
  m_rotationLoc = abcg::glGetUniformLocation(m_program, "rotation");
  m_scaleLoc = abcg::glGetUniformLocation(m_program, "scale");
  m_translationLoc = abcg::glGetUniformLocation(m_program, "translation");

  // Criação das bolas
  m_balls.clear();

  //Quantidade de bolas
  m_balls.resize(3);

  for (auto &ball : m_balls) {
    ball = makeBall();

    do {
      ball.m_translation = {m_randomDist(m_randomEngine),
                                m_randomDist(m_randomEngine)};
    } while (glm::length(ball.m_translation) < 0.5f);
  }
}

void Balls::paint() {
  abcg::glUseProgram(m_program);

  for (auto const &ball : m_balls) {
    abcg::glBindVertexArray(ball.m_VAO);

    abcg::glUniform4fv(m_colorLoc, 1, &ball.m_color.r);
    abcg::glUniform1f(m_scaleLoc, ball.m_scale);
    abcg::glUniform1f(m_rotationLoc, ball.m_rotation);

    for (auto i : {-2, 0, 2}) {
      for (auto j : {-2, 0, 2}) {
        abcg::glUniform2f(m_translationLoc, ball.m_translation.x + j,
                          ball.m_translation.y + i);

        abcg::glDrawArrays(GL_TRIANGLE_FAN, 0, ball.m_polygonSides + 2);
      }
    }

    abcg::glBindVertexArray(0);
  }

  abcg::glUseProgram(0);
}

void Balls::destroy() {
  for (auto &ball : m_balls) {
    abcg::glDeleteBuffers(1, &ball.m_VBO);
    abcg::glDeleteVertexArrays(1, &ball.m_VAO);
  }
}

void Balls::update(const Platform &platform, float deltaTime) {
  for (auto &ball : m_balls) {
    ball.m_translation -= platform.m_velocity * deltaTime;
    ball.m_rotation = glm::wrapAngle(
        ball.m_rotation + ball.m_angularVelocity * deltaTime);
    ball.m_translation += ball.m_velocity * deltaTime;

    if (ball.m_translation.x < -1.0f)
      ball.m_translation.x += 2.0f;
    if (ball.m_translation.x > +1.0f)
      ball.m_translation.x -= 2.0f;
    if (ball.m_translation.y < -1.0f)
      ball.m_translation.y += 2.0f;
    if (ball.m_translation.y > +1.0f)
      ball.m_translation.y -= 2.0f;
  }
}

Balls::Ball Balls::makeBall(glm::vec2 translation,
                                            float scale) {
  Ball ball;

  auto &re{m_randomEngine}; 

  ball.m_polygonSides = 20;

  // Coloração dos objetos
  std::uniform_real_distribution randomIntensity(5.0f, 5.0f);
  ball.m_color = glm::vec4(randomIntensity(re));

  ball.m_color.a = 5.0f;
  ball.m_rotation = 0.0f;
  ball.m_scale = scale;
  ball.m_translation = translation;

  // velocidade das bolas
  ball.m_angularVelocity = m_randomDist(re);
  glm::vec2 const direction{0.0f, -0.1f};
  ball.m_velocity = glm::normalize(direction) / 4.0f;

  std::vector<glm::vec2> positions{{0, 0}};
  auto const step{M_PI * 2 / ball.m_polygonSides};
  std::uniform_real_distribution randomRadius(0.15f, 0.15f);
  for (auto const angle : iter::range(0.0, M_PI * 2, step)) {
    auto const radius{randomRadius(re)};
    positions.emplace_back(radius * std::cos(angle), radius * std::sin(angle));
  }
  positions.push_back(positions.at(1));

  // Geração do VBO
  abcg::glGenBuffers(1, &ball.m_VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, ball.m_VBO);
  abcg::glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec2),
                     positions.data(), GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Localização dos atributos
  auto const positionAttribute{
      abcg::glGetAttribLocation(m_program, "inPosition")};

  // Criação do VAO
  abcg::glGenVertexArrays(1, &ball.m_VAO);
  abcg::glBindVertexArray(ball.m_VAO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, ball.m_VBO);
  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);
  abcg::glBindVertexArray(0);

  return ball;
}