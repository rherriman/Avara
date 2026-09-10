#pragma once
#include "CAbstractActor.h"

#include <array>
#include <random>

#define DEFAULT_PARTICLE_SHAPE 500

class CAbstractParticleEmitter : public CAbstractActor {
public:
    CBSPPart *particleShape;
    uint16_t particleCount;
    
    MessageRecord startMsg;
    MessageRecord stopMsg;
    short status;

    virtual ~CAbstractParticleEmitter();
    virtual void BeginScript() override;
    virtual CAbstractActor *EndScript() override;
    virtual void FrameAction() override;

    virtual std::array<float, 3> GetNewParticlePosition() = 0;
    virtual std::array<float, 3> GetNewParticleRotation() = 0;
    virtual float GetNewParticleScale() = 0;

protected:
    std::mt19937 randGenerator;
    std::uniform_real_distribution<float> randDistribution;
};
