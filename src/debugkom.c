/*
 * komunikacja.c
 *
 *  Created on: 12 wrz 2016
 *      Author: Marcin
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f4xx_conf.h"
#include "debugkom.h"
#include "timer.h"
#include "memory.h"

#define UART_FTDI 1
#define UART_DEBUG 1

char *err[]={" OK "," Blad 1 "," Blad 2 "," Blad 3 "," Timeout "};
char *state[]={" A "," B "," C "," D "," E "};

static enum {DTIME,DATA,DAKC,DKAL,DST,DPOW,DREG}msgFormat=DATA;

volatile uint8_t debugBuf[DEBUG_BUF_LENGTH],debugOVF=0,debugBufRDY=0;
volatile uint16_t debugBufCnt=0;
uint8_t debugTimer;

char cbuf[64];

static void Debug_InputHandler(void);
static void Debug_Raport(void);
static void Uart_Init();
static void Uart_BufClr();
/*
 * 	Inicjalizacja modułu
 */
void Debug_Init(void)
{

	Uart_Init();
	Uart_BufClr();
	if(Timer_Register(&debugTimer,1000,timerOpt_AUTORESET) != 1)PC_Debug("Blad rejestracji timera!\n\r");
	PC_Debug("WilgotechMeasure  v3.0\n\r");
}


void Debug_Main(void)
{
	Debug_InputHandler();
	if(Timer_Check(&debugTimer)==1){
		//Debug_Raport();
	}
}

static void Debug_Raport(void)
{


	switch(msgFormat){
	case DTIME:
		//sprintf(cbuf,"%.2d-%.2d-%2d %.2d:%.2d:%.2d \n\r",sTime.date,sTime.month,sTime.year,sTime.hours,sTime.minutes,sTime.seconds);
		PC_Debug(cbuf);
		break;

	case DATA:
		//sprintf(cbuf,"%.2d:%.2d:%.2d AmpR: %d AmpC: %d Bat: %d Faza: %d\n\r",ampmeas_filtered_data_S.amplitudeResistor,
		//		ampmeas_filtered_data_S.amplitudeResistor,ampmeas_filtered_data_S.batteryVoltage,phasemeas_filtered_S.phase);
		//PC_Debug(cbuf);
		break;
	default:
		break;
	}

	PC_Debug("\r\n\r\n");
}
static void Debug_InputHandler(void)
{
	uint8_t p;
	uint16_t temp=0;
	uint16_t cnt=0;

	if(debugBufRDY==1){
		debugBufRDY=0;

		for(uint8_t i=0;i<debugBufCnt;i++){
			if((debugBuf[i] <= 'z') && (debugBuf[i]>='a')){
				debugBuf[i] = debugBuf[i]-('a'-'A');
			}
		}

		switch(debugBuf[0]){
		case 'S':
//			while(Memory_ReadRecHistory() == MEM_RECNEXT){
//
//				sprintf(cbuf,"HIST %u: %u %u %u %i %i %i %d %d \n\r",cnt,debug_record.timestamp,
//						debug_record.moist,debug_record.flow,debug_record.temp_z,debug_record.temp_in,
//						debug_record.temp_out,debug_record.hum_in,
//						debug_record.hum_out
//						);
//				PC_Debug(cbuf);
//				cnt++;
//			}
			break;
		case 'P':
			if(debugBuf[1] == 'S'){
				PC_Debug("BRAKE\n\r");
			}
			else if(debugBuf[1]=='G'){
				PC_Debug("UP\n\r");
			}
			else if(debugBuf[1]=='D'){
				PC_Debug("DOWN\n\r");
			}
			else if(debugBuf[1]=='A'){
				if(debugBuf[2]==' '){
					p = 3;
					while(p<50){
						if((debugBuf[p]=='\r') || (debugBuf[p]=='\n'))break;
						if(temp!=0)temp*=10;
						temp=temp+(debugBuf[p]-48);
						p++;
					}
					//Pod_SetAngle(temp);
					//sprintf(cbuf,"Podnosnik Kat: %d\n\r",podnosnikMain.setAngle);
					PC_Debug(cbuf);
				}
			}
			else{
				PC_Debug("BRAKE\n\r");
				PC_Debug("Blad!\n\r");
			}
			break;
		case 'D':
			if(debugBuf[1] == 'P'){
				msgFormat=DTIME;
			}
			else if(debugBuf[1] == 'S'){
				msgFormat=DATA;
			}
			else if(debugBuf[1] == 'L'){
				msgFormat=DAKC;
			}
			else if(debugBuf[1] == 'K'){
				msgFormat=DKAL;
			}
			else if(debugBuf[1] == 'T'){
				switch(debugBuf[2]){
				case 'F':
					Timer_Register(&debugTimer,500,timerOpt_AUTORESET);
					PC_Debug("Raport FAST\n\r");
					break;
				case 'M':
					Timer_Register(&debugTimer,1000,timerOpt_AUTORESET);
					PC_Debug("Raport MED\n\r");
					break;
				case 'S':
					Timer_Register(&debugTimer,5000,timerOpt_AUTORESET);
					PC_Debug("Raport SLOW\n\r");
					break;
				case 'X':
					Timer_Register(&debugTimer,10000,timerOpt_AUTORESET);
					PC_Debug("Raport XSLOW\n\r");
					break;
				case 'O':
					Timer_Stop(&debugTimer);
					PC_Debug("Raport OFF\n\r");
					break;
				default:
					PC_Debug("Blad!\n\r");
					break;
				}
			}
			else{
				PC_Debug("Blad!\n\r");
			}
			break;
		case 'W':
			if(debugBuf[1] == '0'){
				GPIO_ResetBits(GPIOB,GPIO_Pin_15);
				PC_Debug("W 0\n\r");
			}
			else if(debugBuf[1]=='1'){
				GPIO_SetBits(GPIOB,GPIO_Pin_15);
				PC_Debug("W 1\n\r");
			}

			break;
		case 'R':
			switch(debugBuf[1]){
			case 'P':
				sprintf(cbuf,"%d\n\r");
				PC_Debug(cbuf);
				break;
			case 'M':
				sprintf(cbuf,"%d\n\r");
				PC_Debug(cbuf);
				break;
			case 'O':
				sprintf(cbuf,"%d\n\r");
				PC_Debug(cbuf);
				break;
			case 'T':
				sprintf(cbuf,"%d\n\r");
				PC_Debug(cbuf);
				break;
			default:
				PC_Debug("Blad!\n\r");
				break;
			}
			break;
		case 'T':
			PC_Debug("TEST\n\r");
			break;
		default:
			PC_Debug("Blad!\n\r");
			break;
		}
		Uart_BufClr();

	}
	else if(debugOVF==1){
		Uart_BufClr();
	}
}

/*
 * 	Nadawanie przez UART
 */
void PC_Debug(volatile char *s)
{
	while(*s){
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		USART_SendData(USART1, *s++);
	}
}
/*
 * Legacy
 */
void PC_Send(volatile char *s)
{
	PC_Debug(s);
}
/*
 * Odbiór
 */
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET){
		if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE)){
			if(debugBufCnt < DEBUG_BUF_LENGTH){
				debugBuf[debugBufCnt] = USART_ReceiveData(USART1);
				if(debugBuf[debugBufCnt] == '\r'){
					debugBufRDY=1;
					USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
				}
				else{
					debugBufCnt++;
				}
			}
			else{
				USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
				debugOVF=1;
			}
		}
	}
}
/*
 * Przygotowanie bufora
 */
static void Uart_BufClr()
{
	for(uint16_t i=0;i<DEBUG_BUF_LENGTH;i++){
		debugBuf[i]=0;
	}
	debugBufCnt=0;
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}
/*
 * Konfiguracja UART:
 *
 * 	USART1: Komunikacja debug
 *
 * 	PB: 6,7
 *
 * 	115200,8,1,0,0
 *
 */
static void Uart_Init()
{
	USART_InitTypeDef UART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	// GPIO Config
	// TX - PB3 RX - PB4
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

	// UART Config

	UART_InitStructure.USART_BaudRate = 115200;
	UART_InitStructure.USART_WordLength = USART_WordLength_8b;
	UART_InitStructure.USART_StopBits = USART_StopBits_1;
	UART_InitStructure.USART_Parity = USART_Parity_No;
	UART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	UART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1,&UART_InitStructure);
	USART_Cmd(USART1, ENABLE);


	// NVIC Config
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

 	NVIC_Init(&NVIC_InitStructure);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}




