#include "CAbstractParticleEmitter.h"

CAbstractParticleEmitter::~CAbstractParticleEmitter()
{
    delete particleShape;
}

void CAbstractParticleEmitter::BeginScript()
{
    CAbstractActor::BeginScript();

    ProgramFixedVar(iHeight, 0);
    ProgramLongVar(iCount, 1);
    ProgramLongVar(iShape, DEFAULT_PARTICLE_SHAPE);
    ProgramLongVar(iIsAmbient, false);
    ProgramMessage(iStartMsg, iStartMsg);
    ProgramLongVar(iStopMsg, 0);
    ProgramLongVar(iStatus, false);
}

CAbstractActor *CAbstractParticleEmitter::EndScript()
{
    if (CAbstractActor::EndScript()) {
        RegisterReceiver(&startMsg, ReadLongVar(iStartMsg));
        RegisterReceiver(&stopMsg, ReadLongVar(iStopMsg));
        status = ReadLongVar(iStatus);
        
        particleCount = ReadLongVar(iCount);
        
        uint16_t resId = ReadLongVar(iShape);
        auto bsp = AssetManager::GetBsp(resId);
        if (bsp) {
            // Load part without applying materials, and keep out of standard
            // partList.
            LoadPartWithMaterials(0, resId);
            particleShape = (CBSPPart *)partList[0];
            if (ReadLongVar(iIsAmbient) > 0)
                particleShape->userFlags |= CBSPUserFlags::kIsAmbient;
            particleShape->Reset();
            partList[0] = nullptr;
        }

        return this;
    } else {
        return nullptr;
    }
}

void CAbstractParticleEmitter::FrameAction()
{
    CAbstractActor::FrameAction();

    if (stopMsg.triggerCount > startMsg.triggerCount) {
        status = false;
    } else if (stopMsg.triggerCount < startMsg.triggerCount) {
        status = true;
    }

    stopMsg.triggerCount = 0;
    startMsg.triggerCount = 0;

    isActive &= ~kHasMessage;
}
