#ifndef WINDOW_CAMERA_H
#define WINDOW_CAMERA_H
#include <glm/glm.hpp>

class Camera {
  void updateVectors();
public:
  glm::vec3 front;
  glm::vec3 up;
  glm::vec3 right;
  glm::mat4 rotation;

  float fov;
  glm::vec3 position;
  Camera(glm::vec3 position, float fov);

  void rotate(float x, float y, float z);

  glm::mat4 getProjection();
  glm::mat4 getView();
};
#endif // WINDOW_CAMERA_H
