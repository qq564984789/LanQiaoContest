
/*------------------------------------------------------------------*/
/* --- STC MCU International Limited -------------------------------*/
/* --- STC 1T Series MCU RC Demo -----------------------------------*/
/* --- Mobile: (86)13922805190 -------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ---------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ---------------------*/
/* --- Web: www.GXWMCU.com -----------------------------------------*/
/* --- QQ:  800003751 ----------------------------------------------*/
/* If you want to use the program or the program referenced in the  */
/* article, please specify in which data and procedures from STC    */
/*------------------------------------------------------------------*/


#ifndef		__CONFIG_H
#define		__CONFIG_H


/*********************************************************/

//#define MAIN_Fosc		 5529600L	//定义主时钟	 110 ~ 4800
//#define MAIN_Fosc		11059200L	//定义主时钟	 110 ~ 9600
//#define MAIN_Fosc		12000000L	//定义主时钟	 110 ~ 9600
#define MAIN_Fosc		22118400L	//定义主时钟	 220 ~ 19200
//#define MAIN_Fosc		24000000L	//定义主时钟	 220 ~ 19200
//#define MAIN_Fosc		33177600L	//定义主时钟	 220 ~ 38400

#define BaudRate		9600		//模拟串口波特率

/*********************************************************/

#include	"STC15Fxxxx.H"



#endif
