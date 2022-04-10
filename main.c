#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "SCI.h"
#include "Sounds.h"
#include "menu.h"
#ifdef __cplusplus
extern "C"
#endif
void MCU_init(void); /* Device initialization function declaration */

char dato;
unsigned char FLAG_saludo = 1;

void main(void) {
  MCU_init();	/* call Device Initialization */
  /* include your code here */
  SCI_init();
  PTBDD_PTBDD2 = 0; // Si no hay un dispositivo conectado, es 0. Si lo hay, es 1.
  sounds_stop();

  

  for(;;) {
    SCI_update();
    if (PTBD_PTBD2)
    {
      if(FLAG_saludo)
      {
        menu_showMenu();
      }
      else
      {
        if (SCI_getCommand(&dato))
        {
          switch(dato)
          {
            case 'A':
                SCI_writeStringToBuffer("Se ingresó A\n");
                //sounds_frecuency (100);
                break;

            case 'B':
                SCI_writeStringToBuffer("Se ingresó B\n");
                //sounds_frecuency (300);
                break;

            case 'C':
                SCI_writeStringToBuffer("Se ingresó C\n");
                //sounds_frecuency (500);
                break;
            
            case 'D':
                SCI_writeStringToBuffer("Se ingresó D\n");
                //sounds_frecuency (1000);
                break;
            case 'E':
                SCI_writeStringToBuffer("Se ingresó E\n");
                //sounds_frecuency (2000);
                break;
            case 'F':
                SCI_writeStringToBuffer("Se ingresó F\n");
                //sounds_frecuency (5000);
                break;
            case 'G':
                SCI_writeStringToBuffer("Se ingresó G\n");
                //sounds_frecuency (10000);
                break;
            case 'H':
                SCI_writeStringToBuffer("Se ingresó H\n");
                //sounds_frecuency (12000);
                break;
            case 'I':
                SCI_writeStringToBuffer("Se ingresó I... reproduciendo\n");
                //sounds_play();
                break;
            case 'J':
                SCI_writeStringToBuffer("Se ingresó J... APAGADO\n");
                //sounds_stop();
                break;
            case 'K':
              SCI_writeStringToBuffer("Se ingresó K... REINICIANDO\n");
              //sounds_frecuency (0);
              //sounds_stop();
              break;
            default:
            	break;
          
               
          }
        }
        
      }
      
    }
    

   // RESET_WATCHDOG(); //By default COP is disabled with device init. When enabling, also reset the watchdog. */
  } /* loop forever */
  /* please make sure that you never leave main */
}
