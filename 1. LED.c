//模式0、模式1内部切换标志
bool  mode0_next;  
bool  mode1_next; 

//模式时间和种类
#define MODE0_TIME    500
#define MODE1_TIME    1000
#define MODE_0 0
#define MODE_1 1
#define MODE_2 2
#define MODE_3 3

//LED控制
#define ON     1
#define OFF    0
#define LED_PORT  P0
#define LED0_Pin GPIO_Pin_0
#define LED1_Pin GPIO_Pin_1
#define LED2_Pin GPIO_Pin_2
#define LED3_Pin GPIO_Pin_3
#define LED4_Pin GPIO_Pin_4
#define LED5_Pin GPIO_Pin_5
#define LED6_Pin GPIO_Pin_6
#define LEDs_NUM               sizeof (LED)/ sizeof(u8)

u8 LED[] = {LED0_Pin,LED1_Pin,LED2_Pin,.....};

u8 GPIO_WritePin(u8 GPIO , u8 Pinx , bit Level)
 { 
	 if(GPIO > GPIO_P5)				return 1;	//¿Õ²Ù×÷
	 if(Pinx > GPIO_Pin_All)	return 2;	//´íÎó
	 if(GPIO == GPIO_P0)
	  {
	   if(Level)
		  P0 &= (~Pinx);
	   else
	    P0 |= Pinx;
    }
 }

 u8 GPIO_ReadPin(u8 GPIO , u8 Pinx )
 { 
	 if(GPIO > GPIO_P5)				return 3;	//¿Õ²Ù×÷
	 if(Pinx > GPIO_Pin_All)	return 2;	//´íÎó
	 if(GPIO == GPIO_P0)
	  {
      if ( P0 & Pinx != 0)
		  return 1;
	   else
	    return 0;
    }
 }

u8 GPIO_TogglePin(u8 GPIO , u8 Pinx )
 { 
	 if(GPIO > GPIO_P5)				return 1;	//¿Õ²Ù×÷
	 if(Pinx > GPIO_Pin_All)	return 2;	//´íÎó
	 if(GPIO == GPIO_P0)      P0 ^= Pinx;
 }

 //LED_On(LED_PORT , LED0_Pin , ON);
//LED_On(LED_PORT , LED1_Pin , ON);
//上述两条语句执行完，LED0亮。
void LED_On(u8 led_port,u8 led_pin )
{
  GPIO_Write_Pin(led_port ,led_pin , on);
}

void LED_Off(u8 led_port,u8 led_pin)
{
  GPIO_Write_Pin(led_port ,led_pin , off);
}

void LED_Toggle(u8 led_port,u8 led_pin)
{
  GPIO_TogglePin(led_port , led_pin );
}

void LED_LeftToRight(u8 Pinx)
{
  
  if (Pinx == 0) //仅点亮Left的LED
  {
    LED_Toggle（LED_PORT, LED[0]）;  
  }
  else if (Pinx >= LEDs_NUM) //仅熄灭Right的LED
  {
    LED_Toggle（LED_PORT, LED[LEDs_NUM-1]）;
  }
  else //先点亮右边的LED，再熄灭左边的
  {   
    LED_Toggle（LED_PORT, LED[Pinx]）;
    Pinx--;
    LED_Toggle（LED_PORT, LED[Pinx]）;    
  }
}

void timer0_int (void) interrupt TIMER0_VECTOR
{  
	  static unsigned int cnt=0; 
    if (cnt++ % MODE0_TIME == 0)  mode0_next = TRUE ;
    if (cnt++ % MODE1_TIME == 0)  mode1_next = TRUE ;
    if (cnt % 60000 == 0) cnt = 0;
  
}

void main()
{
  while(1)
  {
    unsigned char i = 0;
    switch (mode) 
    {
      case MODE_0:
      {
        //做模式0要做的事  
         if (mode0_next) == TRUE)
         {
            mode0_next = FALSE;
            LED_ShiftToRight(i);
            if( i == LEDs_NUM） 
            {
              mode = MODE_1;
              break;
            } 
            i++;
            
         }
       }
      break;
      case MODE_1:
      {
      }
    }

  }
}

