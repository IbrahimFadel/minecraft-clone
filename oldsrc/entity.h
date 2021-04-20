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
        GLuint testTexture;

        GLuint vao;
        std::vector<VBO> vbos;

    public:
        Entity(Mesh *mesh, Texture *texture, glm::mat4 *modelMatrix) : mesh(mesh), texture(texture), modelMatrix(modelMatrix){};

        glm::vec3 cameraPos;

        void setVAO(GLuint _vao) { vao = _vao; }
        void setVBOs(std::vector<VBO> _vbos) { vbos = _vbos; }
        void setTestTexture(GLuint tex) { testTexture = tex; }

        Mesh *getMesh() { return mesh; }
        glm::mat4 *getModelMatrix() { return modelMatrix; }
        Texture *getTexture() { return texture; }
        GLuint getVAO() { return vao; }
        std::vector<VBO> getVBOs() { return vbos; }
        GLuint getTestTexture() { return testTexture; }
    };
}; // namespace mc

#endif