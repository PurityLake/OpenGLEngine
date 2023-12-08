#include "oglengine/app.hpp"

#include <iostream>

BaseApp::BaseApp()
    : m_Running(false), m_LastTime(0.0f), m_Width(800), m_Height(600) {}

BaseApp::~BaseApp() { glfwTerminate(); }

void BaseApp::OnResize(int width, int height) {}

int BaseApp::Run() {
  m_LastTime = glfwGetTime();
  int ret = Init();
  if (ret == 0) {
    while (!glfwWindowShouldClose(m_Window)) {
      Update();
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      Render();
      glfwSwapBuffers(m_Window);
      glfwPollEvents();
    }
  }
  return ret;
}

void BaseApp::Close() {
  m_Running = false;
  glfwSetWindowShouldClose(m_Window, true);
}

int BaseApp::Init() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if __APPLE___
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE___

  m_Window = glfwCreateWindow(m_Width, m_Height, "OpenGL Engine", NULL, NULL);
  if (m_Window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(m_Window);
  glfwSetWindowUserPointer(m_Window, this);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(
      m_Window, [](GLFWwindow *w, int width, int height) {
        BaseApp *app = static_cast<BaseApp *>(glfwGetWindowUserPointer(w));
        app->Resize(w, width, height);
      });

  OnStart();

  return 0;
}

void BaseApp::Update() {
  float time = glfwGetTime();
  OnUpdate(time - m_LastTime);
  m_LastTime = time;
}

void BaseApp::Render() { OnRender(); }

void BaseApp::Resize(GLFWwindow *window, int width, int height) {
  m_Width = width;
  m_Height = height;
  OnResize(width, height);
}
