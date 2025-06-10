#include "Mesh.h"

void Mesh::gen_gl_buffers()
{
    glGenBuffers(1, &position_buffer_);
    glGenBuffers(1, &color_buffer_);
    glGenBuffers(1, &normal_buffer_);
}


void Mesh::update_tv_indices()
{
    // triangle-vertex indices
    tv_indices_.clear();
    for (unsigned int i = 0; i < pmesh_->mNumFaces; ++i) 
    {
        aiFace& ai_face = pmesh_->mFaces[i];
        assert(ai_face.mNumIndices >= 3);

        // convert a polygon to a triangle fan
        for (unsigned int idx = 0; idx < ai_face.mNumIndices - 2; ++idx)
        {
            tv_indices_.push_back(ai_face.mIndices[0]);
            tv_indices_.push_back(ai_face.mIndices[idx+1]);
            tv_indices_.push_back(ai_face.mIndices[idx+2]);
        }
    }
}


void Mesh::set_gl_position_buffer_()
{
    assert(pmesh_->HasPositions());

    std::vector<glm::vec3>  tv_positions;       // per triangle-vertex 3D position (size = 3 x #triangles)
    tv_positions.reserve(tv_indices_.size());

    // TODO: for each triangle, set tv_positions
    for (unsigned int idx : tv_indices_)
    {
        aiVector3D v = pmesh_->mVertices[idx];
        tv_positions.emplace_back(v.x, v.y, v.z);
    }

    glBindBuffer(GL_ARRAY_BUFFER, position_buffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*tv_positions.size(), &tv_positions[0], GL_STATIC_DRAW);
}

void Mesh::set_gl_color_buffer_(unsigned int cs_idx)
{
    assert(pmesh_->HasVertexColors(cs_idx));

    std::vector<glm::vec3>  tv_colors;       // per triangle-vertex 3D position (size = 3 x #triangles)
    tv_colors.reserve(tv_indices_.size());


    // TODO: for each triangle, set tv_colors
    for (unsigned int idx : tv_indices_)
    {
        aiColor4D c = pmesh_->mColors[cs_idx][idx];
        tv_colors.emplace_back(c.r, c.g, c.b);
    }

    glBindBuffer(GL_ARRAY_BUFFER, color_buffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*tv_colors.size(), &tv_colors[0], GL_STATIC_DRAW);

    is_color_ = true;
}


// Smooth shading은 각 정점의 법선을 그 정점이 속한 삼각형들의 평균 방향으로 정해야 한다.
// 즉, 이 정점이 소속된 모든 삼각형이 어디를 바라보는지 평균을 낸다.
// 따라서 normal 값을 누적으로 더하고 마지막에 다시 normal

void Mesh::set_gl_normal_buffer_(ShadingType shading_type)
{
    std::vector<glm::vec3>      tv_flat_normals;    // per triangle-vertex flat normal (size = 3 x #triangles)
    std::vector<glm::vec3>      tv_smooth_normals;  // per triangle-vertex smooth normal (size = 3 x #triangles)
    std::vector<glm::vec3>      v_smooth_normals;   // per-vertex 3D normal (size = #vertices)

    // init normals
    v_smooth_normals.resize(pmesh_->mNumVertices);
    for (std::size_t i = 0; i < v_smooth_normals.size(); ++i)
        v_smooth_normals[i] = glm::vec3(0.0f, 0.0f, 0.0f);

    // TODO: compute per-triangle normal & 
    //       add_up to tv_flat_normals & v_smooth_normals
    tv_flat_normals.resize(tv_indices_.size());

    for (size_t i = 0; i < tv_indices_.size(); i += 3)
    {
        unsigned idx0 = tv_indices_[i];
        unsigned idx1 = tv_indices_[i + 1];
        unsigned idx2 = tv_indices_[i + 2];

        glm::vec3 v0 = glm::vec3(pmesh_->mVertices[idx0].x, pmesh_->mVertices[idx0].y, pmesh_->mVertices[idx0].z);
        glm::vec3 v1 = glm::vec3(pmesh_->mVertices[idx1].x, pmesh_->mVertices[idx1].y, pmesh_->mVertices[idx1].z);
        glm::vec3 v2 = glm::vec3(pmesh_->mVertices[idx2].x, pmesh_->mVertices[idx2].y, pmesh_->mVertices[idx2].z);

        glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));

        tv_flat_normals[i] = normal;
        tv_flat_normals[i + 1] = normal;
        tv_flat_normals[i + 2] = normal;

        v_smooth_normals[idx0] += normal;
        v_smooth_normals[idx1] += normal;
        v_smooth_normals[idx2] += normal;
    }

    // normalize v_smooth_normals
    for (std::size_t i = 0; i < v_smooth_normals.size(); ++i) 
        v_smooth_normals[i] = glm::normalize(v_smooth_normals[i]);

    // if pmesh_ has per-vertex normals, then just use them.
    if (pmesh_->HasNormals())
        memcpy(&v_smooth_normals[0], &pmesh_->mNormals[0], sizeof(pmesh_->mNormals[0])*pmesh_->mNumVertices);

    // TODO: set tv_smooth_normals from v_smooth_normals
    tv_smooth_normals.reserve(tv_indices_.size());

    for (unsigned int idx : tv_indices_) {
        tv_smooth_normals.emplace_back(v_smooth_normals[idx]);
    }

    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_);
    if (shading_type == kSmooth)
    {
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*tv_smooth_normals.size(), &tv_smooth_normals[0], GL_STATIC_DRAW);
    }
    else //if (shading_type == kFlat)
    {
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*tv_flat_normals.size(), &tv_flat_normals[0], GL_STATIC_DRAW);
    }
}

void Mesh::set_gl_buffers(ShadingType shading_type)
{
    set_gl_position_buffer_();
    if (pmesh_->HasVertexColors(0))
        set_gl_color_buffer_(0);
    set_gl_normal_buffer_(shading_type);
}


void Mesh::draw(int loc_a_position, int loc_a_normal)
{
    // TODO : draw a triangular mesh
    //          glBindBuffer() with position_buffer_
    //          glEnableVertexAttribArray() for loc_a_position  
    //          glVertexAttribPointer() by reusing GPU data in loc_a_position
    //
    //          glBindBuffer() with normal_buffer_
    //          glEnableVertexAttribArray() for loc_a_normal  
    //          glVertexAttribPointer() by reusing GPU data in loc_a_normal
    //
    //          glDrawArrays(GL_TRIANGLES, ...)
    //
    //          glDisableVertexAttribArray() for loc_a_position & loc_a_normal

    // set position buffer
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer_);
    glEnableVertexAttribArray(loc_a_position);
    glVertexAttribPointer(loc_a_position, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // 2. set normal buffer
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_);
    glEnableVertexAttribArray(loc_a_normal);
    glVertexAttribPointer(loc_a_normal, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(tv_indices_.size()));

    glDisableVertexAttribArray(loc_a_position);
    glDisableVertexAttribArray(loc_a_normal);

}
    
void Mesh::print_info()
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