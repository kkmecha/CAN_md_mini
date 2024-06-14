#include "Motor_md_mini.h"
#include <cstdint>
#include <cmath>

Motor_md_mini::Motor_md_mini(CAN &can, char motor_num) 
        : _can(can), _motor_num(motor_num) {
    _can.frequency(1000000);
    _can.mode(CAN::Normal);
    _motor_max = 10000;
    // その他処理など
}

int Motor_md_mini::send(int speed){ // とりあえずモーター1個分だけ
    _msg.id = 0x300 + *((uint32_t *)_id_ptr);
    _msg.len = 8;

    if(abs(speed) >= 10000){
        _msg.data[0] = Brake;
        _msg.data[1] = CW;
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
    }

    _msg.data[2] = (speed >> 8);
    _msg.data[3] = (speed & 0xff);

    if(_over) _i = 2; else _i = 4;
    for( ; _i < 8; _i++)
        _msg.data[_i] = 0; // Nullを残さない
    
    if(_can.write(_msg)){
        return 1;
    }
    else{
        return -1;
    } 

    // if(0 < *speed_arr){ // 制御信号以外のビットのセット
    //     _data |= Rotate;
    //     _data |= CW;
    // }else if(*speed_arr < 0){
    //     _data |= Rotate;
    //     _data |= CCW;
    // }else{
    //     _data |= Brake;
    //     _data |= CW; // セットしているが関係ない
    // }

    // char _byte_top[_motor_num * 2], _byte_sub[_motor_num * 2];
    // int _a = 0;

    // for(int i=0;i<_motor_num;i++){
    //     if(speed_arr[i]>=_motor_max)return 0;
    //     _byte_top[_a++] = (char)(speed_arr[i] >> 8);
    //     _byte_sub[_a++] = (char)(speed_arr[i] & 0xFF);
    // }
}
