/*
 * vrs_cv5.c
 *
 *  Created on: 18. 10. 2016
 *      Author: Juraj B
 */
#include <stddef.h>
#include "stm32l1xx.h"
#include <vrs_cv5.h>
#include <stdlib.h>
#include <string.h>

void ADC_init()
	{
			GPIO_InitTypeDef GPIO_InitStructure;
			ADC_InitTypeDef ADC_InitStructure;
			/* Enable GPIO clock */
			 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
			 /* Configure ADCx Channel 2 as analog input */
			 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
			 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
			 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
			 GPIO_Init(GPIOA, &GPIO_InitStructure);
			/* Enable the HSI oscillator */
			 RCC_HSICmd(ENABLE);
			/* Check that HSI oscillator is ready */
			 while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
			 /* Enable ADC clock */
			 RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
			 /* Initialize ADC structure */
			 ADC_StructInit(&ADC_InitStructure);
			 /* ADC1 configuration */
			 ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
			 ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
			 ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
			 ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
			 ADC_InitStructure.ADC_NbrOfConversion = 1;
			 ADC_Init(ADC1, &ADC_InitStructure);
			/* ADCx regular channel8 configuration */
			 ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_384Cycles);

			 ADC_ITConfig(ADC1,ADC_IT_EOC,ENABLE);


			 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
			 	NVIC_InitTypeDef NVIC_InitStructure;
			 	NVIC_InitStructure.NVIC_IRQChannel = ADC1_IRQn ; //zoznam preru�en� n�jdete v s�bore stm32l1xx.h
			 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
			 	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
			 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			 	NVIC_Init(&NVIC_InitStructure);

			 	/* Enable the ADC */
			 	ADC_Cmd(ADC1, ENABLE);
			 	/* Wait until the ADC1 is ready */
			 	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
			 	{
			 	}
			 	/* Start ADC Software Conversion */
			 	ADC_SoftwareStartConv(ADC1);
	}

void ADC1_IRQHandler(void)
{
	value = ADC_GetConversionValue(ADC1);

	return;
}

void Dio_init()
	{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
		/*nastavenie diody */
		GPIO_InitTypeDef gpioInitStruc;

		gpioInitStruc.GPIO_Mode = GPIO_Mode_OUT;
		gpioInitStruc.GPIO_OType = GPIO_OType_PP;
		gpioInitStruc.GPIO_Pin = GPIO_Pin_5;
		gpioInitStruc.GPIO_PuPd= GPIO_PuPd_UP;
		gpioInitStruc.GPIO_Speed = GPIO_Speed_40MHz;

		GPIO_Init(GPIOA, &gpioInitStruc);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
	}

void blikanie(uint32_t cas)
{
	uint32_t i=0;
	for (i = 0; i <= cas; i++)
		  	  	  	  {
		  	  	  	  }
		  GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
}

void usart_init()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

		GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

		GPIO_InitTypeDef GPIO_usrt;

		GPIO_usrt.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
		GPIO_usrt.GPIO_Mode = GPIO_Mode_AF;
		GPIO_usrt.GPIO_OType = GPIO_OType_PP;
		GPIO_usrt.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_usrt.GPIO_Speed = GPIO_Speed_40MHz;

		GPIO_Init(GPIOA,&GPIO_usrt);

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

		USART_InitTypeDef USART_InitStructure;
		USART_InitStructure.USART_BaudRate = 9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART2, &USART_InitStructure);

		  /* Enable the USARTx Interrupt */
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		//interrupt
		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

		USART_Cmd(USART2, ENABLE);

}

void Send_data(char send[])
{
	int j =0;
	while(send[j] != 0)
	{
		USART_SendData(USART2, send[j]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		j++;
	}
	USART_SendData(USART2,'\r');
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
}

void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		Rec = USART_ReceiveData(USART2);
    }
}
