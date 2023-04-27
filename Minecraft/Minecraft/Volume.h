#pragma once

#include "Frustum.h"
struct Volume
{
};

struct BoxVolume : Volume
{
    glm::vec3 center;
};

struct AABB : Volume
{
    glm::vec3 min; // Minimum extent of the AABB
    glm::vec3 max; // Maximum extent of the AABB

    AABB()
    {
        min = glm::vec3(-1.0f, -1.0f, -1.0f); // Minimum extent
        max = glm::vec3(1.0f, 1.0f, 1.0f);   // Maximum extent
    }

    AABB(glm::vec3 min, glm::vec3 max)
    {
        this->min = min;
        this->max = max;
    }


    //bool IsInsideFrustum(Frustum frustum) 
    //{
    //    // Extract the frustum planes from the viewProjectionMatrix
    //    Plane planes[6];
    //    planes[0] = frustum.leftFace;  // Left
    //    planes[1] = frustum.rightFace;  // Right
    //    planes[2] = frustum.bottomFace;  // Bottom
    //    planes[3] = frustum.topFace;  // Top
    //    //planes[4] = frustum.nearFace;  // Near
    //    //planes[5] = frustum.farFace;  // Far
    //    
    //    // Check if the AABB intersects any of the frustum planes
    //    for (int i = 0; i < 6; i++) 
    //    {
    //        // Calculate the signed distance from the AABB center to the plane
    //        glm::vec3 planeNormal = planes[i].normal;
    //        float planeDistance = planes[i].distance;
    //        float signedDistance = glm::dot(planeNormal, (min + max) * 0.5f) + planeDistance;

    //        // Check if the AABB is completely outside the frustum plane
    //        if (signedDistance < -glm::dot(glm::abs(planeNormal), (max - min) * 0.5f))
    //            return false;
    //    }

    //    // The AABB is visible in the frustum
    //    return true;
    //}
};