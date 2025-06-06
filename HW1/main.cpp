#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>


int main() {
    
    glm::vec3 x(3.0f, 5.0f, 7.0f);
    std::cout << "1) x = " << glm::to_string(x) << std::endl;

    glm::vec3 y = x;
    std::cout << "2) y = " << glm::to_string(y) << std::endl;

    y = x + y;
    std::cout << "3) y = " << glm::to_string(y) << std::endl;
    
    float dot = glm::dot(x, y);
    std::cout << "4) dot(x, y) = " << dot << std::endl;

    x = glm::vec3(1.0f, 0.0f, 0.0f);
    y = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 z = glm::cross(x, y);
    std::cout << "5) cross(x, y) = " << glm::to_string(z) << std::endl;

    glm::mat4 A(1.0f);
    std::cout << "6) identity matrix A = \n" << glm::to_string(A) << "\n\n";

    A[0][0] = 1;  A[1][0] = 2;  A[2][0] = 3;  A[3][0] = 0;
    A[0][1] = 2;  A[1][1] = 1;  A[2][1] = -2; A[3][1] = 0;
    A[0][2] = -1; A[1][2] = 0;  A[2][2] = 1;  A[3][2] = 0;
    A[0][3] = -1; A[1][3] = 2;  A[2][3] = 4;  A[3][3] = 1;

    std::cout << "7) modified matrix A = \n" << glm::to_string(A) << "\n\n";

    glm::mat4 B = glm::transpose(A);
    std::cout << "8) transposed matrix B = \n" << glm::to_string(B) << "\n\n";

    glm::mat4 I(1.0f);

    glm::mat4 translation = glm::translate(I, glm::vec3(1.0f, -1.0f, 2.0f));
    std::cout << "9-1) Translation Matrix:\n" << glm::to_string(translation) << "\n\n";

    glm::mat4 rotation = glm::rotate(I, glm::radians(90.0f), glm::normalize(glm::vec3(1.0f, 2.0f, -1.0f)));
    std::cout << "9-2) Rotation Matrix:\n" << glm::to_string(rotation) << "\n\n";

    glm::mat4 scaling = glm::scale(I, glm::vec3(2.0f, 1.0f, 1.5f));
    std::cout << "9-3) Scaling Matrix:\n" << glm::to_string(scaling) << "\n\n";

    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, -5.0f), // eye
        glm::vec3(0.0f, 0.0f, 0.0f),  // center
        glm::vec3(0.0f, 1.0f, 0.0f)   // up
    );
    std::cout << "9-4) View Transform Matrix:\n" << glm::to_string(view) << "\n\n";

    glm::mat4 ortho = glm::ortho(1.0f, -1.f, 1.f, -1.f, 1.f, -1.f);
    std::cout << "9-5) Ortho Projection Matrix:\n" << glm::to_string(ortho) << "\n\n";

    glm::mat4 frustum = glm::frustum(-0.1f, 0.1f, -0.1f, 0.1f, 0.1f, 1000.0f);
    std::cout << "9-6) Frustum Projection Matrix:\n" << glm::to_string(frustum) << "\n\n";

    glm::mat4 perspective = glm::perspective(glm::radians(60.0f), 1.0f, 0.001f, 10000.0f);
    std::cout << "9-7) Perspective Projection Matrix:\n" << glm::to_string(perspective) << "\n\n";



    return 0;
}

