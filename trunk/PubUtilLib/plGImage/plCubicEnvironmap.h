#ifndef _PLCUBICENVIRONMAP_H
#define _PLCUBICENVIRONMAP_H

#include "plMipmap.h"

class plCubicEnvironmap : public plBitmap {
public:
    enum Faces { kLeftFace, kRightFace, kFrontFace, kBackFace,
                 kTopFace, kBottomFace };

protected:
    plMipmap faces[6];

public:
    plCubicEnvironmap();
    virtual ~plCubicEnvironmap();
    
    virtual short ClassIndex();
    virtual short ClassIndex(PlasmaVer ver);

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);

    virtual void readData(hsStream* S);
    virtual void writeData(hsStream* S);
};

#endif
