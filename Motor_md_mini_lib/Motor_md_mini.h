// brake_flag, rotate_direction_flag, control_signal(top 8bit, subordinate 8bit)
//    0, 1              0, 1        

#ifndef __INCLUDE_MOTOR_MD_MINI_H__
#define __INCLUDE_MOTOR_MD_MINI_H__

#include "mbed.h"
#include <cstdint>
#include <cmath>

class Motor_md_mini{
    public:
        Motor_md_mini(CAN &can, char motor_num);
        int send(int speed);
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
        bool _over;
        uint32_t _id_ptr = 0x0800F800;
        int _motor_max, _i;
        char _motor_id, _motor_num;
        
};


#endif // __INCLUDE_MOTOR_MD_MINI_H__