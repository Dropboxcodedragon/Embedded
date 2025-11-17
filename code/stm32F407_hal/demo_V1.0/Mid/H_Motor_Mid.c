#include "H_Motor_Mid.h"
#include "tim.h"
#include "math.h"
#include "gpio.h"

void M3_PWM_EN_Disable(void)
{
	M3B_EN_Low();
	M3A_EN_Low();
}
void M3_PWM_EN_Enable(void)
{
	M3B_EN_High();
	M3A_EN_High();
}

void M3_PWM_Disable(void)
{
	M3_PWM_EN_Disable();
	set_TIM8_Duty(PWM_CH2,0.0f);
	set_TIM8_Duty(PWM_CH1,0.0f);
}

//M3电机运行
void M3_Motor_PWM(__RunDir direction,float duty)
{
	//ch2是A相，ch1是B相
	if(No_Dir == direction)
	{
			set_TIM8_Duty(PWM_CH2,0.0f);
			set_TIM8_Duty(PWM_CH1,0.0f);
	}
	else
	{
		if(fabs(duty)>0.01f)
		{
			if(direction == Forward)	
			{
				set_TIM8_Duty(PWM_CH2,duty);
				set_TIM8_Duty(PWM_CH1,0.0f);
		}
			else
			{
				set_TIM8_Duty(PWM_CH2,0.0f);
				set_TIM8_Duty(PWM_CH1,duty);
			}
		}
		else
		{
			set_TIM8_Duty(PWM_CH2,0.0f);
			set_TIM8_Duty(PWM_CH1,0.0f);
		}
	}
	M3_PWM_EN_Enable();
}

// ============== M2 电机控制函数 ==============
void M2_PWM_EN_Disable(void)
{
    M2B_EN_Low();
    M2A_EN_Low();
}

void M2_PWM_EN_Enable(void)
{
    M2B_EN_High();
    M2A_EN_High();
}

void M2_PWM_Disable(void)
{
    M2_PWM_EN_Disable();
    set_TIM1_Duty(PWM_CH2, 0.0f);
    set_TIM1_Duty(PWM_CH1, 0.0f);
}

void M2_Motor_PWM(__RunDir direction, float duty)
{
    // ch2是A相，ch1是B相
    if(No_Dir == direction)
    {
        set_TIM1_Duty(PWM_CH2, 0.0f);
        set_TIM1_Duty(PWM_CH1, 0.0f);
    }
    else
    {
        if(fabs(duty) > 0.01f)
        {
            if(direction == Forward)
            {
                set_TIM1_Duty(PWM_CH2, duty);
                set_TIM1_Duty(PWM_CH1, 0.0f);
            }
            else
            {
                set_TIM1_Duty(PWM_CH2, 0.0f);
                set_TIM1_Duty(PWM_CH1, duty);
            }
        }
        else
        {
            set_TIM1_Duty(PWM_CH2, 0.0f);
            set_TIM1_Duty(PWM_CH1, 0.0f);
        }
    }
    M2_PWM_EN_Enable();
}

// ============== M1 电机控制函数 ==============
void M1_PWM_EN_Disable(void)
{
    M1B_EN_Low();
    M1A_EN_Low();
}

void M1_PWM_EN_Enable(void)
{
    M1B_EN_High();
    M1A_EN_High();
}

void M1_PWM_Disable(void)
{
    M1_PWM_EN_Disable();
    set_TIM1_Duty(PWM_CH4, 0.0f);  // 改为CH4
    set_TIM1_Duty(PWM_CH3, 0.0f);  // 改为CH3
}

void M1_Motor_PWM(__RunDir direction, float duty)
{
    // ch4是A相，ch3是B相
    if(No_Dir == direction)
    {
        set_TIM1_Duty(PWM_CH4, 0.0f);
        set_TIM1_Duty(PWM_CH3, 0.0f);
    }
    else
    {
        if(fabs(duty) > 0.01f)
        {
            if(direction == Forward)
            {
                set_TIM1_Duty(PWM_CH4, duty);  // 正转使用CH4
                set_TIM1_Duty(PWM_CH3, 0.0f);
            }
            else
            {
                set_TIM1_Duty(PWM_CH4, 0.0f);
                set_TIM1_Duty(PWM_CH3, duty);  // 反转使用CH3
            }
        }
        else
        {
            set_TIM1_Duty(PWM_CH4, 0.0f);
            set_TIM1_Duty(PWM_CH3, 0.0f);
        }
    }
    M1_PWM_EN_Enable();
}

