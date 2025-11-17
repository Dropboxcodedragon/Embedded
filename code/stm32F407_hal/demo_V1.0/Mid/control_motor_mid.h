#ifndef __CONTROL_MOTOR_MID_H__
#define __CONTROL_MOTOR_MID_H__

#include "stdint.h"
#include "H_Motor_Mid.h"

// 新增函数指针类型定义
typedef void (*MotorPWM_Handler)(__RunDir direction, float duty);
 
// PWM规划器结构体
typedef struct {
    float current;
    float target;
    float accel_rate;
    float decel_rate;
    float step;
} PWM_Planner;
// 新增PID结构体
typedef struct {
    float Kp;
    float Ki; 
    float Kd;
    float integral;
    float prev_error;
    float integral_limit;
    float output_limit;
} PID_Controller;

// 新增结构体
typedef struct {
    // 双环控制参数
    PWM_Planner* pwm_planner;    // PWM规划器指针
    PID_Controller* pid_ctrl;    // PID控制器指针
    
    // 电流环参数
    float current_feedback;      // 反馈电流
    float current_target;        // 目标电流
    float current_error;         // 电流误差
    
    // 电压环参数 
    float voltage_feedback;      // 反馈电压
    float voltage_target;        // 目标电压
    float voltage_error;         // 电压误差
    
    // 保护参数
    float current_limit;         // 电流限制
    float voltage_limit;         // 电压限制
    
   MotorPWM_Handler motor_control_cb;  // 新增函数指针成员
   

} ControlLoop_Struct;

void control_motor_Mid(uint16_t accel, uint16_t decel, uint8_t target);
void control_PWM_Mode(ControlLoop_Struct *planner);
float get_current_pwm(void);
// 新增函数声明
void PID_Init(PID_Controller *pid);
float PID_Compute(PID_Controller *pid, float setpoint, float measurement);
void Set_PID_Params(float kp, float ki, float kd);


// 新增初始化函数声明
void ControlLoop_Init(ControlLoop_Struct* loop, 
                     PWM_Planner* pwm_ptr, 
                     PID_Controller* pid_ptr);
#endif

