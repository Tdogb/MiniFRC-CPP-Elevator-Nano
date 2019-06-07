// #include <stdint.h>

// class Brushed
// {
// private:
//     int FWDPin;
//     int RVSPin;
//     int ENPin;
//     int rampTime;
// public:
//     Brushed(int _FWDPin, int _RVSPin, int _ENPin);
//     ~Brushed();
//     void rotate(int speed);
// };
#include <stdint.h>

class Brushed
{
private:
    int FWDPin;
    int RVSPin;
    int rampTime;
    bool enPinMode;
    int enPin;
public:
    Brushed(int _FWDPin, int _RVSPin, int _enPin);
    void rotate(int speed);
    void ramp();
};
