#ifndef ENTITY_H
#define ENTITY_H

#include "terrain/chunk.h"
#include "texture.h"
#include <glm/glm.hpp>

namespace mc
{
    class Entity
    {
    private:
        Mesh *mesh;
        Texture *texture;
        glm::mat4 *modelMatrix;

        GLuint vao;
        std::vector<VBO> vbos;

    public:
        Entity(Mesh *mesh, Texture *texture, glm::mat4 *modelMatrix) : mesh(mesh), texture(texture), modelMatrix(modelMatrix){};

        void setVAO(GLuint _vao) { vao = _vao; }
        void setVBOs(std::vector<VBO> _vbos) { vbos = _vbos; }

        Mesh *getMesh() { return mesh; }
        glm::mat4 *getModelMatrix() { return modelMatrix; }
        Texture *getTexture() { return texture; }
        GLuint getVAO() { return vao; }
        std::vector<VBO> getVBOs() { return vbos; }
    };
}; // namespace mc

#endif