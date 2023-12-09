#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <oglengine/shader.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <oglengine/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //
    0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, //
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, //
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //

    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
    0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, //
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, //
    -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, //
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //

    -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, //
    -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, //
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
    -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, //

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
    0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, //
    0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, //
    0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, //
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
    0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, //
    0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
    0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //

    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, //
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
    -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, //
    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f  //
};

static bool wire = false;
static bool pressed = false;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

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

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;
  unsigned char *data;
  data = stbi_load("assets/container.jpg", &width, &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture" << std::endl;
    return -1;
  }
  stbi_image_free(data);

  glEnable(GL_DEPTH_TEST);

  glm::vec3 cubePositions[] = {
      glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

  shader.Use();
  shader.SetInt("texture1", 0);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    projection =
        glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    shader.Use();
    shader.SetMat4("view", view);
    shader.SetMat4("projection", projection);
    shader.SetInt("texture1", 0);

    glBindVertexArray(VAO);
    for (unsigned int i = 0; i < 10; i++) {
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * i;
      model =
          glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      shader.SetMat4("model", model);

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteBuffers(1, &VAO);
  glDeleteBuffers(1, &VBO);

  if (window) {
    glfwDestroyWindow(window);
  }
  glfwTerminate();

  return 0;

image_fail:
  stbi_image_free(data);

  glDeleteBuffers(1, &VAO);
  glDeleteBuffers(1, &VBO);
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
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !pressed) {
    pressed = true;
    wire = !wire;
    if (wire) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
    pressed = false;
  }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
