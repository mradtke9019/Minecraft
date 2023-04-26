#pragma once
#include "Plane.h"
#include <glm/glm.hpp>
#include "Volume.h"
#include "ICamera.h"
class Frustum
{
private:
    float aspect;
    float fovY;
    float zNear;
    float zFar;

    Plane topFace;
    Plane bottomFace;

    Plane rightFace;
    Plane leftFace;

    Plane farFace;
    Plane nearFace;

public:

    Frustum();

    Frustum(ICamera* cam);

    void UpdateFrustum(ICamera* cam);

    bool IsVolumeInFrustum(Volume& v);
};