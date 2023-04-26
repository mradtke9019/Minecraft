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
    glm::vec3 center;
};