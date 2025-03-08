#include "stm32f10x.h"                  // Device header

int16_t Encoder_Count;

void Encoder_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//开启GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//开启AFIO的时钟
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//上拉输入
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);//配置外部中断引脚为PB0
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);//配置外部中断引脚为PB1
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//指定外部中断线使能
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
	EXTI_Init(&EXTI_InitStructure);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//指定NVIC线路使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//响应优先级为1
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//指定NVIC线路使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;//响应优先级为3
	NVIC_Init(&NVIC_InitStructure);
}


int16_t Encoder_Get(void)
{
	int16_t Temp;
	Temp = Encoder_Count;
	Encoder_Count = 0;
	return Temp;
}

void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0) == SET)//判断是否是外部中断0号线触发的中断
	{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
		{
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)//判断旋转方向
			{
				Encoder_Count --;//反转自减
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line0);	//清除中断标志位
	}
}

void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1) == SET)		//判断是否是外部中断1号线触发的中断
	{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
		{
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)//判断旋转方向
			{
				Encoder_Count ++;//正转自增
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line1);//清除中断标志位
	}
}
