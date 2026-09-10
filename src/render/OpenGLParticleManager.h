#pragma once
#include "AbstractParticleManager.h"

#include <glm/gtc/matrix_transform.hpp>

class OpenGLParticleManager final : public AbstractParticleManager<glm::mat4> {
public:
    std::map<uint16_t, GLuint> vbos = {};
    
    ~OpenGLParticleManager();
    virtual glm::mat4 MakeNewTransform() override;
    virtual void RegisterEmitter(CAbstractParticleEmitter *emitter) override;
    virtual void Reset() override;
    virtual void Rotate(glm::mat4 &transform, const std::array<float, 3> &rotationDegrees) override;
    virtual void Scale(glm::mat4 &transform, float scale) override;
    virtual void Translate(glm::mat4 &transform, const std::array<float, 3> &worldCoords) override;
};
