#include "CAN_md_mini.h"
#include <cstdint>
#include <cmath>

CAN_md_mini::CAN_md_mini(CAN &can, int motor_num) 
        : _can(can), _motor_num(motor_num) {
        _can.frequency(1000000);
        _can.mode(CAN::Normal);
}

int CAN_md_mini::send(int *speed){
    int _abs_speed[_motor_num];

    for(int i = 0; i < _motor_num; i++){
        _msg.id = 0x301 + i;
        _msg.len = 8;

        _abs_speed[i] = abs(speed[i]);
        if(_abs_speed[i] >= 10000){
            return -1;
        }
        if(0 < speed[i]){
            _msg.data[0] = Rotate;
            _msg.data[1] = CW;
        }else if(speed[i] < 0){
            _msg.data[0] = Rotate;
            _msg.data[1] = CCW;
        }else{
            _msg.data[0] = Brake;
            _msg.data[1] = CW;
            _abs_speed[i] = 0;
        }

        _msg.data[2] = ((_abs_speed[i] >> 8) & 0xff);
        _msg.data[3] = (_abs_speed[i] & 0xff);

        for(i = 4 ; i < 8; i++){
            _msg.data[i] = 0;
        }   
        
        if(!_can.write(_msg)){
            return -1;
        }      
    }
    return 1;
}
