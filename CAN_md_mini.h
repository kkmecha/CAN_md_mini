#ifndef __INCLUDE_CAN_MD_MINI_H__
#define __INCLUDE_CAN_MD_MINI_H__

#include "mbed.h"
#include <cstdint>
#include <cmath>

class CAN_md_mini{
    public:
    CAN_md_mini(CAN &can, int motor_num);
    int send(int *speed);

    private:
    enum Brake_mask{
        Rotate,
        Brake,
    };
    enum Direction_mask{
        CW,
        CCW,
    };
    CAN &_can;
    CANMessage _msg;
    int _i, _motor_num;   
};

#endif // __INCLUDE_CAN_MD_MINI_H__
