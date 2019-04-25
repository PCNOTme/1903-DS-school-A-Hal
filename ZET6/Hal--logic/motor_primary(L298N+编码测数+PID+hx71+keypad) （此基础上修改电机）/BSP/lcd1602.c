#include "lcd1602.h"
#include "systick.h"


#define LCD_DATA_PORT GPIOA
#define HX711_I2C_SCK GPIO_PIN_0
#define HX711_I2C_DAT GPIO_PIN_1

int32_t data;



void LCD1602_Wait_Ready(void)
{
	int8_t sta;

	DATAOUT(0xff);    //
	LCD_RS_Clr();     //RS 0
	LCD_RW_Set();     //RW 1
	do
	{
		LCD_EN_Set();   //EN 1
		SysTick_Delay_Ms(5);	//??5MS
 		sta = HAL_GPIO_ReadPin(GPIOA, LCD_DATA4_Pin);//
		LCD_EN_Clr();  //EN  0
		
	}while(sta & 0x80);//

}

 


void LCD1602_Write_Cmd(uint8_t cmd)
{
	LCD1602_Wait_Ready();  //?????
	LCD_RS_Clr();   
	LCD_RW_Clr();
	DATAOUT(cmd);  //?????

	LCD_EN_Set();
	LCD_EN_Clr();
	DATAOUT(cmd<<4); //?????????

	LCD_EN_Set();

	LCD_EN_Clr();

}

void LCD1602_Write_Dat(uint8_t dat)
{
	LCD1602_Wait_Ready(); //?????
	LCD_RS_Set();   //1
	LCD_RW_Clr();   //0
	DATAOUT(dat);   //?????
	LCD_EN_Set();  
	LCD_EN_Clr();
	
	DATAOUT(dat<<4); //?????????
	LCD_EN_Set(); 
	LCD_EN_Clr();


}


void LCD1602_ClearScreen(void)
{

	LCD1602_Write_Cmd(0x01);
}


void LCD1602_Set_Cursor(uint8_t x, uint8_t y)
{
	uint8_t addr;
	if (y == 0)
		addr = 0x00 + x;
	else
		addr = 0x40 + x;

	LCD1602_Write_Cmd(addr | 0x80);

}


void LCD1602_Show_Str(uint8_t x, uint8_t y, uint8_t *str)
{

	LCD1602_Set_Cursor(x, y);

	while(*str != '\0')

	{

		LCD1602_Write_Dat(*str++);

	}

}


void LCD1602_Init(void)
{
	LCD1602_Write_Cmd(0x28);	//16*2??,5*7??,4????

	LCD1602_Write_Cmd(0x0C);	//???,????

	LCD1602_Write_Cmd(0x06);	//????,????+1

	LCD1602_Write_Cmd(0x01);	//??

}

