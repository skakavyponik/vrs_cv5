/*
 * vrs_cv5.h
 *
 *  Created on: 18. 10. 2016
 *      Author: Juraj B
 */

#ifndef VRS_CV5_H_
#define VRS_CV5_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "stm32l1xx.h"


int value;
char Rec;
char send[8];
int j;


void ADC_init();
void Dio_init();
void usart_init();
void blikanie(uint32_t cas);
void Send_data(char send[]);
void USARTp_start(char send[]);


#endif /* VRS_CV5_H_ */
