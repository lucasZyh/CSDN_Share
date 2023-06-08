#include "stm32f10x.h"                  // Device header

void AD_Init(void){
	//开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//选择规则组的输入通道
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	//初始化ADC
	ADC_InitTypeDef ADC_InitTypeDefstructure;
	ADC_InitTypeDefstructure.ADC_DataAlign = ADC_DataAlign_Right;//对齐方式
	ADC_InitTypeDefstructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//触发源选择
	ADC_InitTypeDefstructure.ADC_Mode = ADC_Mode_Independent;//配置ADC工作模式
	ADC_InitTypeDefstructure.ADC_ContinuousConvMode = DISABLE;//连续转换
	ADC_InitTypeDefstructure.ADC_ScanConvMode = DISABLE;//扫描转换
	ADC_InitTypeDefstructure.ADC_NbrOfChannel = 1;//通道数目
	
	ADC_Init(ADC1,&ADC_InitTypeDefstructure);
	
	//开启ADC
	ADC_Cmd(ADC1,ENABLE);
	//校准ADC
	ADC_ResetCalibration(ADC1);//复位校准
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);//等待校准完成
	ADC_StartCalibration(ADC1);//复位校准
	while(ADC_GetCalibrationStatus(ADC1) == SET);
	
}

uint16_t AD_GetValue(void){
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//软件触发转换
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);//获取标志位状态
	return ADC_GetConversionValue(ADC1);//获取转换值
}
