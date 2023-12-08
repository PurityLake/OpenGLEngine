#ifndef __H_APP__
#define __H_APP__

#include <glad/glad.h>

#include <GLFW/glfw3.h>

class BaseApp {
public:
  BaseApp();
  virtual ~BaseApp();

  int Run();
  void Close();
  virtual void OnStart();
  virtual void OnUpdate(float dt);
  virtual void OnRender();
  virtual void OnResize(int width, int height);

private:
  int Init();
  void Update();
  void Render();
  void Resize(GLFWwindow *window, int width, int height);

  GLFWwindow *m_Window;
  bool m_Running;
  double m_LastTime;
  int m_Width, m_Height;
};

#endif // __H_APP__
