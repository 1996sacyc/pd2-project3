#ifndef LISA_H
#define LISA_H
#include "des.h"

class Lisa:public des
{
public:
    Lisa();
    virtual~Lisa();
    virtual void COUNT(blank*arr[10][10]);
};

#endif // LISA_H
