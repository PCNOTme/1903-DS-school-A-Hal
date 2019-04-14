#ifndef _HX711_H_
#define _HX711_H_
#include "stm32f1xx_hal.h"

unsigned long HX711_Read(void);
long Get_Weight(void);
void Get_Maopi(void);

#endif
