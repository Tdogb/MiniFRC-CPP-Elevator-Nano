#include <stdint.h>

class Brushed
{
private:
    int FWDPin;
    int RVSPin;
    int ENPin;
    int rampTime;
public:
    Brushed(int _FWDPin, int _RVSPin, int _ENPin);
    ~Brushed();
    void rotate(int speed);
};
