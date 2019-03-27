/*=======================================================================================*
 * @file    ampmeas.c
 * @author  Marcin Badzioch
 * @version 1.0
 * @date    02-09-2017
 * @brief   Source file for Amplitude measurement module
 *======================================================================================*/

/**
 * @addtogroup Ampmeas Description
 * @{
 * @brief  Amplitude measurement module
 */

/*======================================================================================*/
/*                       ####### PREPROCESSOR DIRECTIVES #######                        */
/*======================================================================================*/
/*-------------------------------- INCLUDE DIRECTIVES ----------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "stm32f4xx_conf.h"
#include "template.h"
#include "delay.h"
/*----------------------------- LOCAL OBJECT-LIKE MACROS -------------------------------*/
#define TEMP_CALLIB 80
/*---------------------------- LOCAL FUNCTION-LIKE MACROS ------------------------------*/

/*======================================================================================*/
/*                      ####### LOCAL TYPE DECLARATIONS #######                         */
/*======================================================================================*/
/*---------------------------- ALL TYPE DECLARATIONS -----------------------------------*/

/*-------------------------------- OTHER TYPEDEFS --------------------------------------*/

/*------------------------------------- ENUMS ------------------------------------------*/

/*------------------------------- STRUCT AND UNIONS ------------------------------------*/

/*======================================================================================*/
/*                    ####### LOCAL FUNCTIONS PROTOTYPES #######                        */
/*======================================================================================*/
static void ADC_Port_Config(void);

/*======================================================================================*/
/*                         ####### OBJECT DEFINITIONS #######                           */
/*======================================================================================*/
/*--------------------------------- EXPORTED OBJECTS -----------------------------------*/


/*---------------------------------- LOCAL OBJECTS -------------------------------------*/


/*======================================================================================*/
/*                  ####### EXPORTED FUNCTIONS DEFINITIONS #######                      */
/*======================================================================================*/
template_E AmpMeas_Init(void)
{
	ADC_Port_Config();
	ADC_Config();
	ADC_BatteryVoltageMeasure();
	return AMP_OK;
}
/*======================================================================================*/
/*                   ####### LOCAL FUNCTIONS DEFINITIONS #######                        */
/*======================================================================================*/
/*
 * Port config:
 * 		PB14 - Amplitude C
 * 		PB15 - Amplitude R
 * 		PA0  - Thermistor
 */
static void ADC_Port_Config(void)
{
//	GPIO_InitTypeDef			GPIO_InitStructure;
//
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
//
//	GPIO_StructInit(&GPIO_InitStructure);
//	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14 | GPIO_Pin_15;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//
//	GPIO_StructInit(&GPIO_InitStructure);
//	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * @} end of group Ampmeas
 */
