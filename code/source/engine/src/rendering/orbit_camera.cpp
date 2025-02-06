#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <tangram/engine/rendering/orbit_camera.hpp>

namespace tangram::engine
{
    void OrbitCamera::move(const glm::vec2& movement)
    {
        glm::vec3 dir = eye - center;
        glm::vec3 right = glm::normalize(glm::cross(up, dir));

        glm::quat hQuat = glm::angleAxis(glm::radians(-movement.x), up);
        glm::quat vQuat = glm::angleAxis(glm::radians(-movement.y), right);

        glm::mat4 matrix = glm::mat4_cast(hQuat * vQuat);
        dir = matrix * glm::vec4{dir, 0.0f};

        eye = center + dir;

        up = glm::mat4_cast(vQuat) * glm::vec4{up, 0.0f};
    }

    void OrbitCamera::zoom(float zoom)
    {
        glm::vec3 dir = eye - center;
        glm::vec3 normDir = glm::normalize(dir);
        dir -= normDir * zoom;
        if (glm::length(dir) < 1.0f)
        {
            dir = normDir;
        }
        eye = center + dir;
    }
} // namespace tangram::engine
