#include "AD9833.h"
#include "delay.h"

void AD9833_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	HAL_GPIO_WritePin(AD9833_FSYNC_PORT, AD9833_FSYNC_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(AD9833_SDATA_PORT, AD9833_SDATA_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(AD9833_SCLK_PORT, AD9833_SCLK_PIN, GPIO_PIN_SET);

	GPIO_InitStruct.Pin = AD9833_FSYNC_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(AD9833_FSYNC_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = AD9833_SDATA_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(AD9833_SDATA_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = AD9833_SCLK_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(AD9833_SCLK_PORT, &GPIO_InitStruct);
	AD9833_Write(0x0100);
}

void AD9833_Write(uint16_t DATA)
{
	AD9833_SCLK_ON;
	AD9833_FSYNC_ON; 
	AD9833_FSYNC_OFF;
	
	for(int j=0,i = 0;i < 16;i++)
	{
		if(DATA&0x8000)
			AD9833_SDATA_ON;
		else
			AD9833_SDATA_OFF;
		AD9833_SCLK_OFF;
		DATA = DATA <<1;
		AD9833_SCLK_ON;
	}
	
	AD9833_FSYNC_ON;
	AD9833_SCLK_OFF;
	AD9833_SCLK_ON;
}

void AD9833_Phase(float phase)
{
	uint16_t phase_new;
	
	phase_new = 5.6888889*phase;
	
	AD9833_Write((phase_new&0x3fff)|0xc000);
	
}

void AD9833_Frequnce_SIN(float data)
{
	uint16_t data_h,data_l;
	uint32_t data_new;
	
	data_new = 10.73741824 * data;
	
	data_h = ((data_new>>14)&0x3fff)|0x4000;
	data_l = (data_new&0x3fff)|0x4000;
	
	AD9833_Write(0x0100);
	AD9833_Write(0x2100);
	AD9833_Write(data_l);
	AD9833_Write(data_h);
	AD9833_Write(0x2000);
}

void AD9833_Frequnce_TRI(float data)
{
	uint16_t data_h,data_l;
	uint32_t data_new;
	
	data_new = 10.73741824 * data;	
	
	data_h = ((data_new>>14)&0x3fff)|0x4000;
	data_l = (data_new&0x3fff)|0x4000;
	
	AD9833_Write(0x0100);
	AD9833_Write(0x2100);
	AD9833_Write(data_l);
	AD9833_Write(data_h);
	AD9833_Write(0x2002);
}

void AD9833_Frequnce_SQU(float data)
{
	uint16_t data_h,data_l;
	uint32_t data_new;
	
	data_new = 10.73741824 * data;	
	
	data_h = ((data_new>>14)&0x3fff)|0x4000;
	data_l = (data_new&0x3fff)|0x4000;
	
	AD9833_Write(0x0100);
	AD9833_Write(0x2100);
	AD9833_Write(data_l);
	AD9833_Write(data_h);
	AD9833_Write(0x2028);
}

