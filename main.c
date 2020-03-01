#include "main.h"

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