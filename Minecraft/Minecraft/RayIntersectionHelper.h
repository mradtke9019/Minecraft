#pragma once
#include "glm/glm.hpp"

struct RayIntersectionResult {
    bool IsIntersecting;
    float Distance;
};

class RayIntersectionHelper
{
public:

    /// <summary>
    /// Determine if a point is in a cube given its center coordinate and the size of the cube.
    /// </summary>
    /// <param name="point"></param>
    /// <param name="center"></param>
    /// <param name="size"></param>
    /// <returns></returns>
    static bool IsPointInCube(glm::vec3 point, glm::vec3 center, float size) {
        glm::vec3 min = center - glm::vec3(size / 2);
        glm::vec3 max = center + glm::vec3(size / 2);

        return point.x >= min.x && point.x <= max.x && point.y >= min.y && point.y <= max.y && point.z >= min.z && point.z <= max.z;
    }

    // Check if a ray intersects with a cube
    static RayIntersectionResult IsRayIntersectingCube(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3 cubeCenter, float cubeSize) {
        glm::vec3 cubeMin = cubeCenter - glm::vec3(cubeSize / 2);
        glm::vec3 cubeMax = cubeCenter + glm::vec3(cubeSize / 2);

        RayIntersectionResult r = RayIntersectionResult();
        r.Distance = -1.0f;
        r.IsIntersecting = false;


        // Calculate the inverse direction of the ray
        glm::vec3 invRayDirection = 1.0f / rayDirection;

        // Calculate the minimum and maximum t-values for each axis
        glm::vec3 tMin = (cubeMin - rayOrigin) * invRayDirection;
        glm::vec3 tMax = (cubeMax - rayOrigin) * invRayDirection;

        // Calculate the minimum and maximum t-values overall
        float tNear = glm::max(glm::max(glm::min(tMin.x, tMax.x), glm::min(tMin.y, tMax.y)), glm::min(tMin.z, tMax.z));
        float tFar = glm::min(glm::min(glm::max(tMin.x, tMax.x), glm::max(tMin.y, tMax.y)), glm::max(tMin.z, tMax.z));

        // Check if the ray intersects with the cube
        if (tNear <= tFar && tFar >= 0) {
            // Check if the intersection point is within the cube
            glm::vec3 intersectionPoint = rayOrigin + tNear * rayDirection;
            bool intersecting = IsPointInCube(intersectionPoint, cubeCenter, cubeSize);

            if (intersecting)
            {
                r.IsIntersecting = true;
                r.Distance = glm::distance(intersectionPoint, rayOrigin);
            }

            return r;

        }
        return r;
    }

};