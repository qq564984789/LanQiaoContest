/*---------------------------------------------------------------------*/
/* --- STC MCU International Limited ----------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.GXWMCU.com --------------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了宏晶科技的资料及程序   */
/*---------------------------------------------------------------------*/

/*************	功能说明	**************

本文件为STC15xxx系列的定时器初始化和中断程序,用户可以在这个文件中修改自己需要的中断程序.


******************************************/



#include	"timer.h"
#include "compare.h"

bit	B_Timer0;

#define	ADC_SCALE	37565		//ADC满量程, 根据需要设置
sbit	P_ADC	= P1^2;				//P1.2 比较器输出端
u16		adc;			//ADC中间值, 用户层不可见
u16		adc_duty;		//ADC计数周期, 用户层不可见
u16		adc_value;		//ADC值, 用户层使用
bit		adc_ok;			//ADC结束标志, 为1则adc_value的值可用. 此标志给用户层查询,并且清0

/********************* Timer0中断函数************************/
void timer0_int (void) interrupt TIMER0_VECTOR
{
	B_Timer0 = 1;

	if((CMPCR1 & CMPRES) == 0)		//比较器输出高电平
	{
		P_ADC = 1;			//P_ADC输出高电平, 给负输入端做反馈. 
		adc ++;	//ADC计数+1
	}
	else	P_ADC = 0;			//P_ADC输出低电平, 给负输入端做反馈. 
	if(--adc_duty == 0)			//ADC周期-1, 到0则ADC结束
	{
		adc_duty = ADC_SCALE;	//周期计数赋初值
		adc_value = adc;		//保存ADC值
		adc = 0;				//清除ADC值
		adc_ok = 1;				//标志ADC已结束
	}
}

/********************* Timer1中断函数************************/
void timer1_int (void) interrupt TIMER1_VECTOR
{

}

/********************* Timer2中断函数************************/
void timer2_int (void) interrupt TIMER2_VECTOR
{
	P10 = ~P10;
}


//========================================================================
// 函数: u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
// 描述: 定时器初始化程序.
// 参数: TIMx: 结构参数,请参考timer.h里的定义.
// 返回: 成功返回0, 空操作返回1,错误返回2.
// 版本: V1.0, 2012-10-22
//========================================================================
u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
{
	if(TIM > Timer2)	return 1;	//空操作

	if(TIM == Timer0)
	{
		TR0 = 0;		//停止计数
		if(TIMx->TIM_Interrupt == ENABLE)		ET0 = 1;	//允许中断
		else									ET0 = 0;	//禁止中断
		if(TIMx->TIM_Polity == PolityHigh)		PT0 = 1;	//高优先级中断
		else									PT0 = 0;	//低优先级中断
		if(TIMx->TIM_Mode >  TIM_16BitAutoReloadNoMask)	return 2;	//错误
		TMOD = (TMOD & ~0x03) | TIMx->TIM_Mode;	//工作模式,0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装, 3: 16位自动重装, 不可屏蔽中断
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~0x80;	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x80;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x04;	//对外计数或分频
		else										TMOD &= ~0x04;	//定时
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x01;	//输出时钟
		else							INT_CLKO &= ~0x01;	//不输出时钟
		
		TH0 = (u8)(TIMx->TIM_Value >> 8);
		TL0 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR0 = 1;	//开始运行
		return	0;		//成功
	}

	if(TIM == Timer1)
	{
		TR1 = 0;		//停止计数
		if(TIMx->TIM_Interrupt == ENABLE)		ET1 = 1;	//允许中断
		else									ET1 = 0;	//禁止中断
		if(TIMx->TIM_Polity == PolityHigh)		PT1 = 1;	//高优先级中断
		else									PT1 = 0;	//低优先级中断
		if(TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return 2;	//错误
		TMOD = (TMOD & ~0x30) | TIMx->TIM_Mode;	//工作模式,0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~0x40;	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x40;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x40;	//对外计数或分频
		else										TMOD &= ~0x40;	//定时
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x02;	//输出时钟
		else							INT_CLKO &= ~0x02;	//不输出时钟
		
		TH1 = (u8)(TIMx->TIM_Value >> 8);
		TL1 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR1 = 1;	//开始运行
		return	0;		//成功
	}

	if(TIM == Timer2)		//Timer2,固定为16位自动重装, 中断无优先级
	{
		AUXR &= ~(1<<4);	//停止计数
		if(TIMx->TIM_Interrupt == ENABLE)			IE2  |=  (1<<2);	//允许中断
		else										IE2  &= ~(1<<2);	//禁止中断
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~(1<<2);	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  (1<<2);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	AUXR |=  (1<<3);	//对外计数或分频
		else										AUXR &= ~(1<<3);	//定时
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x04;	//输出时钟
		else							INT_CLKO &= ~0x04;	//不输出时钟

		TH2 = (u8)(TIMx->TIM_Value >> 8);
		TL2 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	AUXR |=  (1<<4);	//开始运行
		return	0;		//成功
	}
	return 2;	//错误
}
