#ifndef __H_MOTOR_MID_H__
#define __H_MOTOR_MID_H__

typedef enum
{
	No_Dir = 0,
	Forward = 1,
	Backward = 2
}__RunDir;

// M3电机函数声明
void M3_PWM_Disable(void);
void M3_Motor_PWM(__RunDir direction, float duty);

// M2电机函数声明
void M2_PWM_Disable(void);
void M2_Motor_PWM(__RunDir direction, float duty);

// M1电机函数声明
void M1_PWM_Disable(void);
void M1_Motor_PWM(__RunDir direction, float duty);

#endif

