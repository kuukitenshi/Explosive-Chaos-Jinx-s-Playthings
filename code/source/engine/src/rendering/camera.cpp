#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <tangram/engine/rendering/camera.hpp>

namespace tangram::engine
{
    glm::mat4 Camera::viewMatrix() const
    {
        return glm::lookAt(eye, center, up);
    }
} // namespace tangram::engine
