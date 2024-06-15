#include "CAN_md_mini.h"
#include <cstdint>
#include <cmath>

CAN_md_mini::CAN_md_mini(CAN &can, char motor_num) 
        : _can(can), _motor_num(motor_num) {
            _can.frequency(1000000);
            _can.mode(CAN::Normal);
            _motor_max = 10000;
}

int CAN_md_mini::send(int *speed){ // とりあえずモーター1個分だけ

    for(int _id = 0; _id < _motor_num; _id++){
        _msg.id = 0x300 + _id;
        _msg.len = 8;

        int _abs_speed = abs(speed[_id]);
        if(_abs_speed >= 10000){
            _abs_speed = 9999;
        }
        if(0 < speed[_id]){
            _msg.data[0] = Rotate;
            _msg.data[1] = CW;
        }else if(speed[_id] < 0){
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
        
        if(!_can.write(_msg)){
            return -1;
        } 
    }
    return 1;
}
