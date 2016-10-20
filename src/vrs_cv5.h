/*
 * vrs_cv5.h
 *
 *  Created on: 18. 10. 2016
 *      Author: Juraj B
 */

#ifndef VRS_CV5_H_
#define VRS_CV5_H_
uint32_t value;
char Rec;
char send[5];


void ADC_init();
void Dio_init();
void usart_init();
void blikanie(uint32_t cas);
void Send_data(char send[]);


#endif /* VRS_CV5_H_ */
