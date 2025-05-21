#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Motor.h"
#include "Car.h"
#include "Delay.h"
#include "Serial.h"
#include "Servo.h"
#include "Ultrasound.h"
#include "Track.h"

#define speed 80
int8_t Speed;
uint16_t Data1;

int main(void)
{ 
	Car_Init();
	Serial_Init();
	Servo_Init();
	Ultrasound_Init();
	Infrared_Init();
	
	while (1)
	{
		if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==SET)
		{	
			Data1=USART_ReceiveData(USART1);
			USART_SendData(USART1, Data1);
			if(Data1==0x01)Car_Stop();
		    if(Data1==0x02)Go_Ahead(speed);
		    if(Data1==0x03)Go_Back(speed);
		    if(Data1==0x04)Turn_Left(speed);
		    if(Data1==0x05)Turn_Right(speed);
		    if(Data1==0x06)Self_Left(speed);
		    if(Data1==0x07)Self_Right(speed);
			if(Data1==0x08)Servo_SetAngle(0);
			if(Data1==0x09)Servo_SetAngle(90);
			if(Data1==0x10)Servo_SetAngle(180);
			if(Data1==0x11)
			{while (1)
	{
		Go_Ahead(60);
		uint16_t a = Test_Distance();
		Serial_SendNumber(a,3);
		if(a<15){
			Car_Stop();
			Servo_SetAngle(0);	Delay_ms(1000);
			uint16_t b= Test_Distance();
		
			Serial_SendNumber(b,3);
			if(b>15){
				Servo_SetAngle(90);
				Delay_ms(1000);
				Self_Right(speed);
				Delay_ms(1000);
				Go_Ahead(60);
			
			}
			else {
				Servo_SetAngle(180);
				Delay_ms(1000);
				uint16_t c= Test_Distance();
				Serial_SendNumber(c,3);
				if(c>15){	
					Servo_SetAngle(90);
					Delay_ms(1000);
					Self_Left(speed);
					Delay_ms(1000);
					Go_Ahead(60);
				}else{
					Servo_SetAngle(90);
					while (1);
				}
			}
		}
		Delay_ms(100);
	}
}
			if(Data1==0x12){
				while (1)
	{
		
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==0&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==0&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==0&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==0)
		{
			Go_Ahead(35);
		}else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==1&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==1&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==1&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==1){
			Car_Stop();
		}else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==0&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==0&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==1&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==1){
				Self_Right(speed);
		}else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==0&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==0&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==1&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==0){
				Self_Right(speed);
		}else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==0&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==0&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==0&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==1){
				Self_Right(speed);
			}
			else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==0&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==1&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==0&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==0){
				Self_Left(speed);
			}else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==1&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==1&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==0&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==0){
				Self_Left(speed);
			}else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==1&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==0&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==0&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==0){
				Self_Left(speed);
			}
			}
		}
	}
  }
}
