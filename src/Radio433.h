#include <stdint.h>

class Radio433
{
private:
public:
    Radio433();
    void update();
    typedef struct packet_s {
        int8_t ballTheta; //from -128 to 128
        int8_t hatchTheta;
        bool intakeBall;
        bool intakeHatch;
        bool outtakeBall;
        bool outtakeHatch;
    } packet_t;
    packet_t packet;
};
