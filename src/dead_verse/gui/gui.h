#ifndef GUI_H_
#define GUI_H_

#include "platform/window.h"
// Do not remove
#include <memory>

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// TODO: add imgui menu, control with button the color of the cubes

namespace musashi {

class Gui {
 public:
  explicit Gui(std::shared_ptr<Window> window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window->GetHandler(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
  }
  ~Gui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  }

  static void SetFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
  }

 private:
};

}  // namespace musashi

#endif
