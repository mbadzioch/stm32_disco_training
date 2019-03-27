
#include <stdio.h>
#include <stdlib.h>
#include "stm32f4xx_conf.h"
#include "delay.h"
#include "timer.h"
#include "kom.h"


int main()
{
	Delay_Init();
	Timer_Init();
	Kom_Init();

	while (1)
	{
		Kom_Main();
	}
}

