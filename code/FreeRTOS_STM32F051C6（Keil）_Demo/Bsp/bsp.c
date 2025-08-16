
#include "bsp.h"


/************************************************
函数名称 ： RCC_Configuration
功    能 ： 时钟配置
参    数 ： 无
返 回 值 ： 无
*************************************************/
void RCC_Configuration(void)
{
  /* 使能AHB时钟 */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | 
                        RCC_AHBPeriph_GPIOC | RCC_AHBPeriph_GPIOF, ENABLE);

#if 0
  /* 使能APB2时钟 */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

  /* 使能APB1时钟 */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
#endif
}

/************************************************
函数名称 ： LED_Initializes
功    能 ： LED初始化
参    数 ： 无
返 回 值 ： 无
*************************************************/
void LED_Initializes(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* 使能RCC */
  RCC_AHBPeriphClockCmd(LED1_GPIO_CLK | LED2_GPIO_CLK | 
                        LED3_GPIO_CLK | LED4_GPIO_CLK, ENABLE);

  GPIO_InitStructure.GPIO_Pin =  LED1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin =  LED2_PIN;
  GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin =  LED3_PIN;
  GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin =  LED4_PIN;
  GPIO_Init(LED4_GPIO_PORT, &GPIO_InitStructure);

  LED1_OFF;
  LED2_OFF;
  LED3_OFF;
  LED4_OFF;

#if 0
  /* MCO时钟配置 */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_0);

  RCC_MCOConfig(RCC_MCOSource_SYSCLK);
#endif
}

/************************************************
函数名称 ： BSP_Initializes
功    能 ： 底层初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void BSP_Initializes(void)
{
  LED_Initializes();                             //LED初始化
}


