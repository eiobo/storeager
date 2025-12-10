#include "led.h"
#include "delay.h"
#include "sys.h"

#include "pwm.h"
#include "motor.h"
#include "timer.h"
#include "track.h"
//STM32F103核心板例程
//库函数版本例程
/************** 嵌入式开发网  **************/
/********** mcudev.taobao.com 出品  ********/


//STM32开发板实验1
//LED灯实验  
//mcudev.taobao.com


	int main(void)
 {	
	delay_init();	    			//延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();		  				//初始化与LED连接的硬件接口
	TIM2_Int_Init(499,7199);		// 定时器中断50ms进入一次 
	TIM3_PWM_Init(999,0);			// PA7
	TIM4_PWM_Init(999,0);			// PB9
	Motor_Init();  
	Track_Init();
	while(1)
	{
		
//		Motor_Go(700,700); 
//		TIM_SetCompare4(TIM4,900);
//        GPIO_SetBits(GPIOA,GPIO_Pin_2); 
//        GPIO_ResetBits(GPIOA,GPIO_Pin_3);  
//		delay_ms(3000);
		
		
		
//		Motor_Right_In1 = 1;
//		Motor_Right_In2 = 0;
//		TIM_SetCompare2(TIM3,900);
//        GPIO_SetBits(GPIOA,GPIO_Pin_4); 
//        GPIO_ResetBits(GPIOA,GPIO_Pin_5);  
//		delay_ms(3000);
	    
//	    //以60%的速度反转
//	    TIM_SetCompare2(TIM3,600);
//        GPIO_SetBits(GPIOA,GPIO_Pin_5); 
//        GPIO_ResetBits(GPIOA,GPIO_Pin_4);
//		delay_ms(3000);
	}
 }

