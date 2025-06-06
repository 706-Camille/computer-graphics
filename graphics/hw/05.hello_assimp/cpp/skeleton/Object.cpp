#include "Object.h"

void Object::init_buffer_objects() 
{
    // 1. 정점 위치 VBO
    glGenBuffers(1, &position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * pmesh_->mNumVertices, pmesh_->mVertices, GL_STATIC_DRAW);

    // 2. 정점 색상 VBO (있는 경우만)
    if (pmesh_->HasVertexColors(0)) {
        is_color = true;

        glGenBuffers(1, &color_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(aiColor4D) * pmesh_->mNumVertices, pmesh_->mColors[0], GL_STATIC_DRAW);
    }

    // 3. Face마다 인덱스 버퍼 생성 (EBO)
    for (unsigned int i = 0; i < pmesh_->mNumFaces; ++i)
    {
        const aiFace& face = pmesh_->mFaces[i];

        GLuint index_buf = 0;
        glGenBuffers(1, &index_buf);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buf);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * face.mNumIndices, face.mIndices, GL_STATIC_DRAW);

        Face f;
        f.index_buffer = index_buf;
        f.num_indices = face.mNumIndices;
        faces.push_back(f);
    }
}

glm::mat4 Object::get_model_matrix() const
{
    glm::mat4 mat_model = glm::mat4(1.0f);

    // T * R * S 순서
    mat_model = glm::translate(mat_model, vec_translate_);
    mat_model *= glm::mat4_cast(quat_rotate_);
    mat_model = glm::scale(mat_model, vec_scale_);

    return mat_model;
}

void Object::draw(int loc_a_position, int loc_a_color)
{
    // 위치 버퍼 바인딩 + vertex attrib pointer 설정
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glEnableVertexAttribArray(loc_a_position);
    glVertexAttribPointer(loc_a_position, 3, GL_FLOAT, GL_FALSE, sizeof(aiVector3D), (void*)0);

    // 색상 버퍼 있는 경우만 바인딩
    if (is_color) {
        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        glEnableVertexAttribArray(loc_a_color);
        glVertexAttribPointer(loc_a_color, 4, GL_FLOAT, GL_FALSE, sizeof(aiColor4D), (void*)0);
    }

    // Face마다 인덱스 버퍼 바인딩 후 draw
    for (const Face& f : faces) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, f.index_buffer);
        glDrawElements(GL_TRIANGLES, f.num_indices, GL_UNSIGNED_INT, 0);
    }
}
    
void Object::print_info()
{
    std::cout << "print mesh info" << std::endl;

    std::cout << "num vertices " << pmesh_->mNumVertices << std::endl;
    for (unsigned int i = 0; i < pmesh_->mNumVertices; ++i)
    {
        aiVector3D vertex = pmesh_->mVertices[i];
        std::cout << "  vertex  (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")" << std::endl;

        if (pmesh_->mColors[0] != NULL)
        {
            aiColor4D color = pmesh_->mColors[0][i];
            std::cout << "  color  (" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")" << std::endl;
        }
    }
}