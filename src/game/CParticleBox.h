#pragma once
#include "CAbstractParticleEmitter.h"

class CParticleBox : public CAbstractParticleEmitter {
public:
    float minBounds[3];
    float maxBounds[3];

    virtual CAbstractActor *EndScript() override;

    virtual std::array<float, 3> GetNewParticlePosition() override;
    virtual std::array<float, 3> GetNewParticleRotation() override;
    virtual float GetNewParticleScale() override;
};
