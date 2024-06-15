#include "CAN_md_mini.h"
#include <cstdint>
#include <cmath>

CAN_md_mini::CAN_md_mini(CAN &can, char motor_num) 
        : _can(can), _motor_num(motor_num) {
            _can.frequency(1000000);
            _can.mode(CAN::Normal);
            _motor_max = 10000;
}

int CAN_md_mini::send(int speed){ // とりあえずモーター1個分だけ
    _msg.id = 0x300 + *((uint32_t *)_id_ptr);
    _msg.len = 8;

    int _abs_speed = abs(speed);
    if(_abs_speed >= 10000){
        _abs_speed = 9999;
    }
    if(0 < speed){
        _msg.data[0] = Rotate;
        _msg.data[1] = CW;
    }else if(speed < 0){
        _msg.data[0] = Rotate;
        _msg.data[1] = CCW;
    }else{
        _msg.data[0] = Brake;
        _msg.data[1] = CW;
        _abs_speed = 0;
    }

    _msg.data[2] = (_abs_speed >> 8);
    _msg.data[3] = (_abs_speed & 0xff);

    for(_i = 4 ; _i < 8; _i++)
        _msg.data[_i] = 0; // Nullを残さない
    
    if(_can.write(_msg)){
        return 1;
    }
    else{
        return -1;
    } 
}
