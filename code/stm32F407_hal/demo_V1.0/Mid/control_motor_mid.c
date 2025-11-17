#include "control_motor_Mid.h"
#include "math.h"
#include "H_Motor_Mid.h"

void control_PWM_Mode(ControlLoop_Struct *planner) 
{
    // 通过指针访问PWM规划器成员
    PWM_Planner* pwm = planner->pwm_planner;
    
    // 计算剩余距离
    float remaining = pwm->target - pwm->current;
    
    // 结构体指针访问修正
    if (fabsf(remaining) < 0.001f) 
		{
        pwm->step = 0;
    } 
		else if (remaining> 0) 
		{ 
        pwm->step = pwm->accel_rate;
    }
		else
		{
			pwm->step = -pwm->accel_rate;
		}
    
    // 应用步长（假设在定时器中断中调用，时间基数为1ms）
    pwm->current += pwm->step;
    

    // 钳制输出
    pwm->current = fmaxf(-1.0f, fminf(1.0f, pwm->current));
    
    // 更新PWM输出
    if(planner->motor_control_cb) {
        float duty = fabsf(pwm->current);
        __RunDir dir = (pwm->current >= 0) ? Forward : Backward;
        planner->motor_control_cb(dir, duty);
    }
    else {
        // 错误处理或默认行为
    }
}

// PID初始化
void PID_Init(PID_Controller *pid) {
    pid->Kp = 0.5f;
    pid->Ki = 0.2f;
    pid->Kd = 0.05f;
    pid->integral = 0.0f;
    pid->prev_error = 0.0f;
    pid->integral_limit = 1.0f;  // 积分限幅
    pid->output_limit = 1.0f;    // 输出限幅
}

// PID计算（带限幅）
float PID_Compute(PID_Controller *pid, float setpoint, float measurement) {
    float error = setpoint - measurement;
    
    // 积分项（带抗饱和）
    pid->integral += error;
    pid->integral = fmaxf(-pid->integral_limit, fminf(pid->integral, pid->integral_limit));
    
    // 微分项
    float derivative = error - pid->prev_error;
    
    // PID输出
    float output = (pid->Kp * error) + (pid->Ki * pid->integral) + (pid->Kd * derivative);
    
    // 输出限幅
    output = fmaxf(-pid->output_limit, fminf(output, pid->output_limit));
    pid->prev_error = error;
    
    return output;
}



//不用，在应用层初始化时针对每个电机设置
void ControlLoop_Init(ControlLoop_Struct* loop,
                     PWM_Planner* pwm_ptr,
                     PID_Controller* pid_ptr)
{
    loop->pwm_planner = pwm_ptr;
    loop->pid_ctrl = pid_ptr;
    
    // 初始化默认参数
    loop->current_limit = 10.0f;  // 10A限流
    loop->voltage_limit = 24.0f;  // 24V限压
    loop->current_target = 0.0f;
    loop->voltage_target = 0.0f;
}


