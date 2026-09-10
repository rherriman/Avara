#include "AbstractRenderer.h"
#include "CParticleBox.h"

extern Rect gLastBoxRect;
extern Fixed gLastBoxRounding;

CAbstractActor *CParticleBox::EndScript()
{
    if (CAbstractParticleEmitter::EndScript()) {
        minBounds[0] = ToFloat(gLastBoxRect.left);
        minBounds[1] = ToFloat(ReadFixedVar(iHeight) + ReadFixedVar(iBaseHeight));
        minBounds[2] = ToFloat(gLastBoxRect.top);

        maxBounds[0] = ToFloat(gLastBoxRect.right);
        maxBounds[1] = ToFloat(minBounds[1] + gLastBoxRounding);
        maxBounds[2] = ToFloat(gLastBoxRect.bottom);
        
        // Random generator for numbers [0.0f, 1.0f] inclusive.
        std::random_device seed;
        randGenerator = std::mt19937(seed());
        randDistribution = std::uniform_real_distribution<float>(
            0.0f,
            std::nextafter(1.0f, std::numeric_limits<float>::max())
        );
        
        gRenderer->RegisterEmitter(this);

        return this;
    } else {
        return nullptr;
    }
}

std::array<float, 3> CParticleBox::GetNewParticlePosition()
{
    return {
        minBounds[0] + (randDistribution(randGenerator) * (maxBounds[0] - minBounds[0])),
        minBounds[1] + (randDistribution(randGenerator) * (maxBounds[1] - minBounds[1])),
        minBounds[2] + (randDistribution(randGenerator) * (maxBounds[2] - minBounds[2])),
    };
}

std::array<float, 3> CParticleBox::GetNewParticleRotation()
{
    const float maxDegrees = std::nextafter(360.0f, std::numeric_limits<float>::min());
    return {
        randDistribution(randGenerator) * maxDegrees,
        randDistribution(randGenerator) * maxDegrees,
        randDistribution(randGenerator) * maxDegrees,
    };
}

float CParticleBox::GetNewParticleScale()
{
    return randDistribution(randGenerator);
}
