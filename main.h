#include <windows.h>
#include <gdiplus.h>

void process(HDC hdc);

class Neuron
{
public:
    void setSize(int inSize)
    {
        size = inSize;
    }
    void setPtr(BYTE *ptr)
    {
        inPtr = ptr;
    }

protected:
    int size;
    BYTE *inPtr;
};

class Convolver : public Neuron
{
public:
    BYTE *convolve(int *kernel, int channels, int stride);
};