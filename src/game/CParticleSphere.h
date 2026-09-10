#pragma once
#include "CAbstractParticleEmitter.h"

class CParticleSphere : public CAbstractParticleEmitter {
public:
    float sphere[4];

    virtual CAbstractActor *EndScript() override;

    virtual std::array<float, 3> GetNewParticlePosition() override;
    virtual std::array<float, 3> GetNewParticleRotation() override;
    virtual float GetNewParticleScale() override;

protected:
    float radiusSquared = 0.0f;
};
