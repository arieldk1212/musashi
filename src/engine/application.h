#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <memory>
#include <string>

#include "platform/window.h"

namespace musashi {

struct ApplicationSpecification {
  std::string application_name = "Application";
  WindowSpecification window_specs;
};

class Application {
 public:
  Application();
  explicit Application(
      const ApplicationSpecification& specs = ApplicationSpecification());
  ~Application() noexcept;

  void Run();
  void Stop() { running_ = false; }

 private:
  bool running_{false};
  std::shared_ptr<Window> window_;
  ApplicationSpecification specifications_;
};

}  // namespace musashi

// namespace extras {
//
// inline float last_x{static_cast<float>(kGameWidth) / 2};
// inline float last_y{static_cast<float>(kGameHeight) / 2};
// inline bool first_mouse{true};
// inline float delta_time{0.0f};
// inline float last_frame{0.0f};
// inline bool show_imgui{false};
// inline glm::vec3 light_pos(1.2f, 1.0f, 2.0f);
// inline glm::vec3 light_direction(-0.2f, -1.0f, -0.3f);
// inline glm::vec3 object_color(1.0f, 0.5f, 0.31f);
// inline glm::vec3 light_color(1.0f, 1.0f, 1.0f);
// }  // namespace extras

//   static int GetMaxVertexAttributes();
//   static void FramebufferSizeCallback(GLFWwindow* window, int width,
//                                       int height);
//   static void MouseCallbackWrapper(GLFWwindow* window, double xpos,
//                                    double ypos);
//   static void ScrollCallbackWrapper(GLFWwindow* window, double xoffset,
//                                     double yoffset);

//   void Run();
//   void Shaders();

//  private:
//   void MouseCallback(GLFWwindow* window, double xpos, double ypos);
//   void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

//   GLuint VAO_{0};
//   GLuint VBO_{0};
//   GLuint LightVAO_{0};
//   std::string game_title_;
//   std::unique_ptr<Camera> camera_;
//   std::unique_ptr<Shader> shader_;
//   // std::unique_ptr<Texture> texture_;
//   std::unique_ptr<Shader> light_shader_;
// };

#endif
