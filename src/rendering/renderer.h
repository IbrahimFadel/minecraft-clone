#ifndef RENDERER_H
#define RENDERER_H

#include "../shader.h"

namespace mc
{
    class Renderer;
}; // namespace mc

#include "../terrain/chunk.h"
#include "../entity.h"
#include <map>

namespace mc
{
    enum ShaderType
    {
        Skybox,
        RegularBlock,
        WaterBlock
    };

    class Renderer
    {
    private:
        std::map<ShaderType, Shader *> shaders;

        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;

        void renderEntityWithRegularBlockShader(Entity *entity);
        void renderEntityWithWaterBlockShader(Entity *entity);

    public:
        Renderer();
        void render(Entity *entity, ShaderType shaderType);

        void setProjectionMatrix(glm::mat4 proj) { projectionMatrix = proj; }
        void setViewMatrix(glm::mat4 view) { viewMatrix = view; }
    };
}; // namespace mc

#endif