#include "AbstractRenderer.h"
#include "CParticleSphere.h"

#include <cmath>

CAbstractActor *CParticleSphere::EndScript()
{
    if (CAbstractParticleEmitter::EndScript()) {
        Vector vSphere;
        Fixed ignore1, ignore2; // We don't care about "arc" angle/span.
        vSphere[3] = GetDome(vSphere, &ignore1, &ignore2);
        vSphere[1] = ReadFixedVar(iHeight) + ReadFixedVar(iBaseHeight);
        
        sphere[0] = ToFloat(vSphere[0]);
        sphere[1] = ToFloat(vSphere[1]);
        sphere[2] = ToFloat(vSphere[2]);
        sphere[3] = ToFloat(vSphere[3]);
        
        float radius = sphere[3];
        radiusSquared = radius * radius;
        
        // Random generator for numbers [-radius, radius] inclusive.
        std::random_device seed;
        randGenerator = std::mt19937(seed());
        randDistribution = std::uniform_real_distribution<float>(
            -1.0f,
            std::nextafter(1.0f, std::numeric_limits<float>::max())
        );
        
        gRenderer->RegisterEmitter(this);

        return this;
    } else {
        return nullptr;
    }
}

std::array<float, 3> CParticleSphere::GetNewParticlePosition()
{
    float rx, ry, rz;
    do {
        rx = randDistribution(randGenerator) * sphere[3];
        ry = randDistribution(randGenerator) * sphere[3];
        rz = randDistribution(randGenerator) * sphere[3];
    } while (((rx * rx) + (ry * ry) + (rz * rz)) > radiusSquared);
    
    return {sphere[0] + rx, sphere[1] + ry, sphere[2] + rz};
}

std::array<float, 3> CParticleSphere::GetNewParticleRotation()
{
    const float maxDegrees = std::nextafter(360.0f, std::numeric_limits<float>::min());
    return {
        randDistribution(randGenerator) * maxDegrees,
        randDistribution(randGenerator) * maxDegrees,
        randDistribution(randGenerator) * maxDegrees,
    };
}

float CParticleSphere::GetNewParticleScale()
{
    return std::abs(randDistribution(randGenerator));
}
