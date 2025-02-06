
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <tangram/engine/scene/transform.hpp>

namespace tangram::engine
{

    glm::mat4 Transform::matrix() const
    {
        glm::mat4 matrix{1.0f};
        matrix = glm::translate(matrix, position);
        matrix = matrix * glm::mat4_cast(rotation);
        matrix = glm::scale(matrix, scale);
        return matrix;
    }
} // namespace tangram::engine
