#pragma once
#include <glm/glm.hpp>
class Plane {
private:
public:
    // unit vector
    glm::vec3 normal = { 0.f, 1.f, 0.f };

    // distance from origin to the nearest point in the plane
    float distance = 0.f;
    Plane() {};

    Plane(const glm::vec3& p1, const glm::vec3& norm)
    {
        normal = (glm::normalize(norm));
        distance = glm::dot(normal, p1);
    }
};
