#ifndef _PLUOID_H
#define _PLUOID_H

#include "plLoadMask.h"
#include "plLocation.h"

DllClass plUoid {
private:
    enum ContentsFlags {
        kHasCloneIDs = 0x1,
        kHasLoadMask = 0x2
    };

private:
    plLocation location;
    plLoadMask loadMask;
    short classType;
    plString objName;
    unsigned int objID, clonePlayerID, cloneID;
    unsigned char eoaExtra;

public:
    plUoid();
    ~plUoid();

    plUoid& operator=(const plUoid& other);
    bool operator==(const plUoid& other) const;
    bool operator<(const plUoid& other) const;

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    plString toString() const;

    short getType() const;
    const plString& getName() const;
    const plLocation& getLocation() const;
    const plLoadMask& getLoadMask() const;
    unsigned int getID() const;
    unsigned int getCloneID() const;
    unsigned int getClonePlayerID() const;

    void setType(short type);
    void setName(const plString& name);
    void setLocation(const plLocation& loc);
    void setLoadMask(const plLoadMask& mask);
    void setID(unsigned int id);
    void setCloneIDs(unsigned int cloneID, unsigned int clonePlayerID);
};

#endif
