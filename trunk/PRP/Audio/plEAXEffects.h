#ifndef _PLEAXEFFECTS_H
#define _PLEAXEFFECTS_H

#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

DllClass plEAXSourceSoftSettings {
protected:
    short fOcclusion;
    float fOcclusionLFRatio, fOcclusionRoomRatio, fOcclusionDirectRatio;

public:
    void Reset();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};

DllClass plEAXSourceSettings {
public:
    enum ParamSets {
        kOcclusion = 0x1,
        kRoom = 0x2,
        kOutsideVolHF = 0x4,
        kFactors = 0x8,
        kAll = 0xFF
    };

protected:
    short fRoom, fRoomHF;
    bool fEnabled, fRoomAuto, fRoomHFAuto;
    short fOutsideVolHF;
    float fAirAbsorptionFactor, fRoomRolloffFactor;
    float fDopplerFactor, fRolloffFactor;
    plEAXSourceSoftSettings fSoftStarts, fSoftEnds;
    float fOcclusionSoftValue;
    unsigned long fDirtyParams;

public:
    plEAXSourceSettings();

    void Enable(bool en);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

protected:
    void IRecalcSofts(unsigned char which);
};

#endif