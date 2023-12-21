#ifndef __HPP_RENDER__
#define __HPP_RENDER__

#include <oglengine/light.hpp>
#include <oglengine/model.hpp>

#include <iostream>
#include <vector>

class Renderer {
public:
  Renderer() = default;
  ~Renderer() = default;

  void Draw(const std::vector<Model> &models, glm::mat4 &view,
            glm::mat4 &projection, const Light &light) const;
};

#endif // __HPP_RENDER__
