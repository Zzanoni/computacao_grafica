#include "ground.hpp"

void Ground::create(GLuint program) {
  // Desenho dos blocos do piso
  std::array<glm::vec3, 4> vertices{{{-0.5f, 0.0f, +0.5f},
                                     {-0.5f, 0.0f, -0.5f},
                                     {+0.5f, 0.0f, +0.5f}}};

  // VBO
  abcg::glGenBuffers(1, &m_VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // VAO
  abcg::glGenVertexArrays(1, &m_VAO);
  abcg::glBindVertexArray(m_VAO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  auto const positionAttribute{
      abcg::glGetAttribLocation(program, "inPosition")};
  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);
  abcg::glBindVertexArray(0);
  m_modelMatrixLoc = abcg::glGetUniformLocation(program, "modelMatrix");
  m_colorLoc = abcg::glGetUniformLocation(program, "color");
}

void Ground::paint() {
  abcg::glBindVertexArray(m_VAO);

  // Definições do piso
  auto const N{1};
  for (auto const z : iter::range(-N, N + 1)) {
    for (auto const x : iter::range(-N, N + 1)) {
      glm::mat4 model{1.0f};
      model = glm::translate(model, glm::vec3(x, 0.0f, z));
      abcg::glUniformMatrix4fv(m_modelMatrixLoc, 1, GL_FALSE, &model[0][0]);
      auto const gray{(z + x) % 2 == 0 ? 1.0f : 0.5f};
      abcg::glUniform4f(m_colorLoc, gray, gray, gray, 1.0f);

      abcg::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
  }

  abcg::glBindVertexArray(0);
}

void Ground::destroy() {
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}