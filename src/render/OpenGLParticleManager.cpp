#include "OpenGLParticleManager.h"
#include "AbstractRenderer.h"

#include <glad/glad.h>

OpenGLParticleManager::~OpenGLParticleManager()
{
    Reset();
}

glm::mat4 OpenGLParticleManager::MakeNewTransform()
{
    return glm::mat4(1.0f);
}

void OpenGLParticleManager::RegisterEmitter(CAbstractParticleEmitter *emitter)
{
    uint16_t emitterShapeId = emitter->particleShape->resId;
    if (collections.count(emitterShapeId) == 0) {
        collections.insert_or_assign(emitterShapeId, ParticleCollection<glm::mat4>());
        collections.at(emitterShapeId).particleShape = emitter->particleShape;
        if (emitter->particleShape->vData == nullptr) {
            emitter->particleShape->vData = gRenderer->NewVertexDataInstance();
            emitter->particleShape->vData->Replace(*emitter->particleShape);
        }
        
        GLuint newVbo;
        glGenBuffers(1, &newVbo);
        vbos.insert_or_assign(emitterShapeId, newVbo);
    }
    
    ParticleCollection<glm::mat4> &collection = collections.at(emitterShapeId);
    uint16_t desiredSize = collection.transforms.size() + emitter->particleCount;
    collection.transforms.reserve(desiredSize);
    collection.emitters.reserve(desiredSize);
    for (int i = 0; i < emitter->particleCount; i++) {
        glm::mat4 transform = MakeNewTransform();
        std::array<float, 3> worldCoords = emitter->GetNewParticlePosition();
        std::array<float, 3> rotation = emitter->GetNewParticleRotation();
        float scale = emitter->GetNewParticleScale();
        Translate(transform, worldCoords);
        Rotate(transform, rotation);
        Scale(transform, scale);
        collection.transforms.push_back(transform);
        collection.emitters.push_back(emitter);
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, vbos.at(emitterShapeId));
    glBufferData(GL_ARRAY_BUFFER, collection.transforms.size() * sizeof(glm::mat4), &collection.transforms[0], GL_STATIC_DRAW);
}

void OpenGLParticleManager::Reset()
{
    collections.clear();
    for (auto const &[resId, vboId] : vbos) {
        glDeleteBuffers(1, &vboId);
    }
}

void OpenGLParticleManager::Rotate(glm::mat4 &transform, const std::array<float, 3> &rotationDegrees)
{
    glm::quat q(glm::vec3(
        glm::radians(rotationDegrees[0]),
        glm::radians(rotationDegrees[1]),
        glm::radians(rotationDegrees[2])
    ));

    transform = transform * glm::mat4_cast(q);
}

void OpenGLParticleManager::Scale(glm::mat4 &transform, float scale)
{
    transform = glm::scale(transform, glm::vec3(scale, scale, scale));
}

void OpenGLParticleManager::Translate(glm::mat4 &transform, const std::array<float, 3> &worldCoords)
{
    transform = glm::translate(transform, glm::vec3(worldCoords[0], worldCoords[1], worldCoords[2]));
}
