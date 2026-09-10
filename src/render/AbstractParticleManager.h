#pragma once
#include "CAbstractParticleEmitter.h"

#include <map>
#include <memory>
#include <vector>

template <typename T>
struct ParticleCollection {
    CBSPPart *particleShape = nullptr;
    std::vector<T> transforms = std::vector<T>();
    std::vector<CAbstractParticleEmitter*> emitters = std::vector<CAbstractParticleEmitter*>();
};

template <typename T>
class AbstractParticleManager {
public:
    virtual T MakeNewTransform() = 0;
    virtual void RegisterEmitter(CAbstractParticleEmitter *emitter) = 0;
    virtual void Reset() = 0;
    virtual void Rotate(T &transform, const std::array<float, 3> &rotationDegrees) = 0;
    virtual void Scale(T &transform, float scale) = 0;
    virtual void Translate(T &transform, const std::array<float, 3> &worldCoords) = 0;
    
    typename std::map<uint16_t, ParticleCollection<T>>::iterator begin() { return collections.begin(); }
    typename std::map<uint16_t, ParticleCollection<T>>::iterator end() { return collections.end(); }
    typename std::map<uint16_t, ParticleCollection<T>>::const_iterator begin()  const { return collections.begin(); }
    typename std::map<uint16_t, ParticleCollection<T>>::const_iterator end()    const { return collections.end(); }
    typename std::map<uint16_t, ParticleCollection<T>>::const_iterator cbegin() const { return collections.cbegin(); }
    typename std::map<uint16_t, ParticleCollection<T>>::const_iterator cend()   const { return collections.cend(); }
    
protected:
    std::map<uint16_t, ParticleCollection<T>> collections = {};
};
