#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <oglengine/camera.hpp>
#include <oglengine/model.hpp>
#include <oglengine/renderer.hpp>
#include <oglengine/shader.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

GLenum glCheckError_(const char *file, int line) {
  GLenum errorCode;
  while ((errorCode = glGetError()) != GL_NO_ERROR) {
    std::string error;
    switch (errorCode) {
    case GL_INVALID_ENUM:
      error = "INVALID_ENUM";
      break;
    case GL_INVALID_VALUE:
      error = "INVALID_VALUE";
      break;
    case GL_INVALID_OPERATION:
      error = "INVALID_OPERATION";
      break;
    case GL_STACK_OVERFLOW:
      error = "STACK_OVERFLOW";
      break;
    case GL_STACK_UNDERFLOW:
      error = "STACK_UNDERFLOW";
      break;
    case GL_OUT_OF_MEMORY:
      error = "OUT_OF_MEMORY";
      break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      error = "INVALID_FRAMEBUFFER_OPERATION";
      break;
    }
    std::cout << error << " | " << file << " (" << line << ")" << std::endl;
  }
  return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__)

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if __APPLE___
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE___

  GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Engine", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  ShaderBuilder builder;
  Shader shader;
  builder.AddShader(GL_VERTEX_SHADER, "assets/vert.glsl")
      .AddShader(GL_FRAGMENT_SHADER, "assets/frag.glsl");
  UNWRAP_SHADER(shader, builder.Build(), return -1);
  builder.Clear();

  std::cout << "HERE" << std::endl;
  Model model("assets/backpack.obj", shader);
  std::cout << "HERE" << std::endl;

  // view/projection transformations
  glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
                                          800.0f / 600.0f, 0.1f, 100.0f);
  glm::mat4 view = camera.GetViewMatrix();

  std::vector<Model> models{model};

  Renderer renderer;

  glEnable(GL_DEPTH_TEST);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    renderer.Draw(models, view, projection);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  if (window) {
    glfwDestroyWindow(window);
  }
  glfwTerminate();

  return 0;

error:
  if (window) {
    glfwDestroyWindow(window);
  }
  glfwTerminate();

  return -1;
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
