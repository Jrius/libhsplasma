#ifndef _PFGUIRADIOGROUPCTRL_H
#define _PFGUIRADIOGROUPCTRL_H

#include "pfGUIControlMod.h"

DllClass pfGUIRadioGroupCtrl : public pfGUIControlMod {
public:
    enum RadioGroupFlags { kAllowNoSelection = kDerivedFlagsStart };

protected:
    hsTArray<plKey> fControls;
    int fDefaultValue;

public:
    pfGUIRadioGroupCtrl();
    virtual ~pfGUIRadioGroupCtrl();

    DECLARE_CREATABLE(pfGUIRadioGroupCtrl)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif