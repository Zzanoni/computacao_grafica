#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "abcgOpenGL.hpp"
#include "model.hpp"
#include "trackball.hpp"
#include "camera.hpp"

class Window : public abcg::OpenGLWindow {
protected:
  void onEvent(SDL_Event const &event) override;
  void onCreate() override;
  void onUpdate() override;
  void onPaint() override;
  void onPaintUI() override;
  void onResize(glm::ivec2 const &size) override;
  void onDestroy() override;

private:
  glm::ivec2 m_viewportSize{};

  Model m_model;
  int m_trianglesToDraw{};

  TrackBall m_trackBallModel;
  TrackBall m_trackBallLight;

  glm::mat4 m_modelMatrix{1.0f};
  glm::mat4 m_viewMatrix{1.0f};
  glm::mat4 m_projMatrix{1.0f};

  GLint m_viewMatrixLocation{};
  GLint m_projMatrixLocation{};

  Camera m_camera;
  float m_dollySpeed{};
  float m_truckSpeed{};
  float m_panSpeed{};

  // Shaders
  std::vector<char const *> m_shaderNames{
      "thunder"};
  std::vector<GLuint> m_programs;
  int m_currentProgramIndex{};

  int m_mappingMode{};

  // propriedades de iluminacao e material
  glm::vec4 m_lightDir{-1.0f, -1.0f, -1.0f, 0.0f};
  glm::vec4 m_Ia{1.0f};
  glm::vec4 m_Id{1.0f};
  glm::vec4 m_Is{1.0f};
  glm::vec4 m_Ka{};
  glm::vec4 m_Kd{};
  glm::vec4 m_Ks{};
  float m_shininess{};

  // Cubo de fundo
  std::string const m_skyShaderName{"skybox"};
  GLuint m_skyVAO{};
  GLuint m_skyVBO{};
  GLuint m_skyProgram{};

  // Dimensoes do cubo de fundo
  std::array<glm::vec3, 36> const m_skyPositions{{
      {-5, -5, +5}, {+5, -5, +5}, {+5, +5, +5},
      {-5, -5, +5}, {+5, +5, +5}, {-5, +5, +5},
      {+5, -5, -5}, {-5, -5, -5}, {-5, +5, -5},
      {+5, -5, -5}, {-5, +5, -5}, {+5, +5, -5},
      {+5, -5, -5}, {+5, +5, -5}, {+5, +5, +5},
      {+5, -5, -5}, {+5, +5, +5}, {+5, -5, +5},
      {-5, -5, +5}, {-5, +5, +5}, {-5, +5, -5},
      {-5, -5, +5}, {-5, +5, -5}, {-5, -5, -5},
      {-5, +5, +5}, {+5, +5, +5}, {+5, +5, -5},
      {-5, +5, +5}, {+5, +5, -5}, {-5, +5, -5},
      {-5, -5, -5}, {+5, -5, -5}, {+5, -5, +5},
      {-5, -5, -5}, {+5, -5, +5}, {-5, -5, +5}}};

  void createSkybox();
  void renderSkybox();
  void destroySkybox() const;
  void loadModel(std::string_view path);
};

#endif