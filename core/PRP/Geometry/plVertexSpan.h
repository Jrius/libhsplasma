#ifndef _PLVERTEXSPAN_H
#define _PLVERTEXSPAN_H

#include "plSpan.h"

DllClass plVertexSpan : public plSpan {
public:
    unsigned int fGroupIdx, fVBufferIdx, fCellIdx,
                 fCellOffset, fVStartIdx, fVLength;

public:
    plVertexSpan();
    plVertexSpan(const plVertexSpan& init);
    virtual ~plVertexSpan();

    virtual const char* ClassName();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);

public:
    unsigned int getGroupIdx() const;
    unsigned int getVBufferIdx() const;
    unsigned int getCellIdx() const;
    unsigned int getCellOffset() const;
    unsigned int getVStartIdx() const;
    unsigned int getVLength() const;

    void setGroupIdx(unsigned int idx);
    void setVBufferIdx(unsigned int idx);
    void setCellIdx(unsigned int idx);
    void setCellOffset(unsigned int off);
    void setVStartIdx(unsigned int idx);
    void setVLength(unsigned int len);
};

#endif