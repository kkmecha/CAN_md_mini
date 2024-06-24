#include "CAN_md_mini.h"
#include <cstdint>
#include <cmath>

CAN_md_mini::CAN_md_mini(CAN &can, int motor_num) 
        : _can(can), _motor_num(motor_num) {
        _can.frequency(1000000);
        _can.mode(CAN::Normal);
}

int CAN_md_mini::send(int* speed){
    int _abs_speed[_motor_num];

    for(int i = 0; i < _motor_num; i++){
        _msg.id = 0x301 + i;
        _msg.len = 8;

        _abs_speed[i] = abs(speed[i]);
        if(_abs_speed[i] > 10000){
            _msg.data[0]=1;
        }else{
            _msg.data[0]=0;
        }
        if(0 < speed[i]){
            _msg.data[1] = Rotate;
            _msg.data[2] = CW;
        }else if(speed[i] < 0){
            _msg.data[1] = Rotate;
            _msg.data[2] = CCW;
        }else{
            _msg.data[1] = Free;
            _msg.data[2] = CW;
            _abs_speed[i] = 0;
        }

        _msg.data[3] = (char)(_abs_speed[i] >> 8);
        _msg.data[4] = (char)(_abs_speed[i] & 0xff);

        
        if(!_can.write(_msg)){
            return -1;
        }      
    }
    return 1;
}
