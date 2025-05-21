#include "stm32f10x.h"                  // Device header
#include "Motor.h"

void Car_Init(void){
	Motor_Init();
}

void Go_Ahead(int8_t Speed){
	Motor_SetLeftSpeed(-Speed);
	Motor_SetRightSpeed(-Speed);
}
void Go_Back(int8_t Speed){
	Motor_SetLeftSpeed(Speed);
	Motor_SetRightSpeed(Speed);
}
void Turn_Left(int8_t Speed){
	Motor_SetLeftSpeed(-Speed/2);
	Motor_SetRightSpeed(-Speed);
}
void Turn_Right(int8_t Speed){
	Motor_SetRightSpeed(-Speed/2);
	Motor_SetLeftSpeed(-Speed);
}
void Self_Left(int8_t Speed){
	Motor_SetLeftSpeed(Speed);
	Motor_SetRightSpeed(-Speed);
}
void Self_Right(int8_t Speed){
	Motor_SetLeftSpeed(-Speed);
	Motor_SetRightSpeed(Speed);
}
void Car_Stop(void){
	Motor_SetLeftSpeed(0);
	Motor_SetRightSpeed(0);
}

