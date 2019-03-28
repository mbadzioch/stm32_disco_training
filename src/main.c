
#include <stdio.h>
#include <stdlib.h>
#include "stm32f4xx_conf.h"
#include "delay.h"
#include "timer.h"
#include "kom.h"
#include "debugkom.h"


int main()
{
	Delay_Init();
	Timer_Init();
	Debug_Init();
	//Kom_Init();


	while (1)
	{
		///Kom_Main();
		Debug_Main();
	}
}

