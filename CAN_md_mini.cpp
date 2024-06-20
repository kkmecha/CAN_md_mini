#include "CAN_md_mini.h"
#include <cstdint>
#include <cmath>

CAN_md_mini::CAN_md_mini(CAN &can, int motor_num) 
        : _can(can), _motor_num(motor_num) {
        _can.frequency(1000000);
        _can.mode(CAN::Normal);
}

int CAN_md_mini::send(int *speed){
    for(int i = 0; i < motor_num; i++){
        _abs_speed[i] = abs(speed[i]);

        if(_abs_speed[i] >= 10000) return -1;
        _byte_top[i] = (_abs_speed[i] >> 8);
        _byte_lower[i] = (_abs_speed[i] & 0xff);

        
    }

    _msg.id = 0x300;
    _msg.len = 8;

}
