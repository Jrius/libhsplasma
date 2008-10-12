#ifndef _PLCUBICENVIRONMAP_H
#define _PLCUBICENVIRONMAP_H

#include "plMipmap.h"

DllClass plCubicEnvironmap : public plBitmap {
public:
    enum Faces { kLeftFace, kRightFace, kFrontFace, kBackFace,
                 kTopFace, kBottomFace, kNumFaces };

protected:
    plMipmap fFaces[kNumFaces];

public:
    plCubicEnvironmap();
    virtual ~plCubicEnvironmap();
    
    DECLARE_CREATABLE(plCubicEnvironmap)

protected:
    virtual void readData(hsStream* S);
    virtual void writeData(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plMipmap* getFace(size_t idx);
};

#endif