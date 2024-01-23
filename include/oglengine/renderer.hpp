// Copyright © 2024 Robert O'Shea

#ifndef __HPP_RENDER__
#define __HPP_RENDER__

#include <oglengine/camera.hpp>
#include <oglengine/light.hpp>
#include <oglengine/model.hpp>

#include <vector>

class Renderer {
public:
  Renderer() = default;
  ~Renderer() = default;

  void Draw(const Camera &camera, const std::vector<Model> &models,
            glm::mat4 &view, glm::mat4 &projection, const Light &light) const;
};

#endif // __HPP_RENDER__
