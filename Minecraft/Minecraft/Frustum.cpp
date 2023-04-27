#include "Frustum.h"
#include "FirstPersonCamera.h"
#include "Projection.h"

Frustum::Frustum()
{
    this->aspect = Projection::Width / Projection::Height;
    this->fovY = Projection::fovy;
    this->zNear = Projection::zNear;
    this->zFar = Projection::zFar;
}

Frustum::Frustum(ICamera* cam)
    :Frustum()
{
    UpdateFrustum(cam);
}


void Frustum::UpdateFrustum(ICamera* cam)
{
    ITransformable* transform = static_cast <ITransformable*> (cam);
    glm::vec3 pos = transform->GetPosition();
    glm::vec3 front = cam->GetCameraDirection();
    glm::vec3 right = cam->GetCameraRight();
    glm::vec3 up = cam->GetCameraUp();

    const float halfVSide = zFar * tanf(fovY * .5f);
    const float halfHSide = halfVSide * aspect;
    const glm::vec3 frontMultFar = zFar * front;

    nearFace = Plane(pos + zNear * front, front);
    farFace = Plane(pos + frontMultFar, -front);
    rightFace = Plane(pos, glm::cross(frontMultFar - right * halfHSide, up));
    leftFace = Plane(pos, glm::cross(up,frontMultFar + right * halfHSide));
    topFace = Plane(pos, glm::cross(right, frontMultFar - up * halfVSide));
    bottomFace = Plane(pos, glm::cross(frontMultFar + up * halfVSide, right));
}

//bool Frustum::IsVolumeInFrustum(Volume& v)
//{
//    return true;
//}