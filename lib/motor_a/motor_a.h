#pragma once

#include<MA.h>
#include<angle.h>
#define motor_max 3     //移動平均で使う配列の大きさ

class motor_attack{
    public:
        motor_attack();
        void moveMotor_0(angle ang,int val,double ac_val,int flag);
        void motor_0();
        void motor_ac(float);
        int line_val = 2;
        int NoneM_flag = 0;
        float Moutput(int,float);
    private:
        int PWM_p[5][2] = {
            {7,6},{8,9},{5,4},{2,3},{0,1}
        };
        double mSin[4] = {1,1,-1,-1};  //行列式のsinの値
        double mCos[4] = {1,-1,-1,1};  //行列式のcosの値
        MA Motor[4];
};