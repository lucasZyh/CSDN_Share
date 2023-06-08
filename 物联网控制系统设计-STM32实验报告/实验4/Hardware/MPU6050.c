#include "stm32f10x.h"                  // Device header
#include "MyI2C.h"
#include "MPU6050_Reg.h"
#include "Delay.h"

#define MPU6050_ADDRESS			0xD0

/**
  * @brief  指定地址写
  * @param  
  * @retval 
  */
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress);//指定寄存器地址
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Data);//指定写入数据
	MyI2C_ReceiveAck();
	MyI2C_Stop();
}

/**
  * @brief  指定地址读
  * @param  
  * @retval 
  */
uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	uint8_t Data;
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS | 0x01);//发送 读 指令
	MyI2C_ReceiveAck();
	Data = MyI2C_ReceiveByte();//接受数据
	MyI2C_SendAck(1);//发送应答
	MyI2C_Stop();
	
	return Data;
}

/**
  * @brief  初始化
  * @param  
  * @retval 
  */
void MPU6050_Init(void)
{
	MyI2C_Init();
	//解除睡眠,选择陀螺仪时钟,6个轴不待机,采样分频为10,滤波参数最大,陀螺仪和加速度计选最大量程
	
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);//电源管理寄存器1,选择陀螺仪时钟
	//Delay_ms(100);
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);//电源管理寄存器2
	//Delay_ms(100);
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);//采样率分频,10分频
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);//配置寄存器,0000 0110
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);//陀螺仪配置寄存器, 0001 1000 
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);//加速度计配置寄存器
}

/**
  * @brief  
  * @param  
  * @retval 
  */
uint8_t MPU6050_ReadID(void)
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

/**
  * @brief  获取数据寄存器数据
  * @param  
  * @retval 
  */
void MPU6050_ReadData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
					  int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
	//加速度
	*AccX = (MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H) << 8)| MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	
	*AccY = (MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H) << 8)
			| MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	
	*AccZ = (MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H) << 8)
			| MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	
	*GyroX = (MPU6050_ReadReg(MPU6050_GYRO_XOUT_H) << 8)
			| MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	
	*GyroY = (MPU6050_ReadReg(MPU6050_GYRO_YOUT_H) << 8)
			| MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	
	*GyroZ = (MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H) << 8)
			| MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
}



