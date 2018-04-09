/* ###################################################################
**     Filename    : main.c
**     Project     : Comunicacion_Serial
**     Processor   : MC9S08QE128CLK
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2018-04-07, 14:35, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.12
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "TI1.h"
#include "AS1.h"
#include "AD1.h"
#include "Bit1.h"
#include "Bit2.h"
#include "Bit3.h"
#include "Bit4.h"
#include "Bit5.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
unsigned int puntero = 9;
typedef union{
	unsigned char u8[2];
	unsigned int u16;
}ANCHO;
volatile ANCHO iADC,iiADC,iiiADC,ivADC;
int A1,A2,A3,A4,B1,B2,B3,B4,C1,C2,C3,C4,D1,D2,D3,b,i;
bool H1=TRUE;
bool H2=TRUE;
bool H3=TRUE;
unsigned char Array[8]; 
char errror;

void main(void)
{
  /* Write your local variable definition here */
	estado = esperar;
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
	for(;;) {
		   switch (estado){
	  		
	  		case esperar:
	  			break;
	  			
	  		case medir:
	  			AD1_MeasureChan(TRUE,0);
	  			AD1_MeasureChan(TRUE,1);
	  			AD1_MeasureChan(TRUE,2);
	  			AD1_MeasureChan(TRUE,3);
	  			H1=Bit3_GetVal();
	  			H2=Bit4_GetVal();
	  			H3=Bit5_GetVal();
	  			AD1_GetChanValue(0,&iADC.u16);
	  			AD1_GetChanValue(1,&iiADC.u16);
	  			AD1_GetChanValue(2,&iiiADC.u16);
	  			AD1_GetChanValue(3,&ivADC.u16);	 
// PROTOCOLO DE COMUNICACION PARA LOS SENSORES//
	    	
	    		iADC.u16=iADC.u16>>4;
	    		A1 = iADC.u16;
	    		C1 = A1 & 0x7F; //Tomo los 8 bits menos significativos 
	    		B1 = A1>>7;	//Desplazamos 7 bits a la derecha para obtener los 8 bits restantes
	    		B1 = B1 & 0x1F; //Tomamos los 8 bits menos significativos de B y lo guardamos en B
	    		if(H1==0){B1= B1|0x40;
	    		}else{B1=B1;}
	    		if(H2==0){B1=B1|0x20;}
	    		else{B1=B1;}

	    		//CANAL 2
	    		iiADC.u16=iiADC.u16>>4;
	    		A2 = iiADC.u16;
	    		C2 = A2 & 0x7F; //Tomo los 8 bits menos significativos 
	    		B2 = A2>>7;	//Desplazamos 7 bits a la derecha para obtener los 8 bits restantes
	    		B2 = B2 & 0x1F; //Tomamos los 8 bits menos significativos de B y lo guardamos en B
	    		if(H3==0){B2=B2|0x40;}
	    		else{B2=B2;}
	    		
	    		//Canal 3
	    		iiiADC.u16=iiiADC.u16>>4;
	    		A3 = iiiADC.u16;
	    		C3 = A3 & 0x7F; //Tomo los 8 bits menos significativos 
	    		B3 = A3>>7;	//Desplazamos 7 bits a la derecha para obtener los 8 bits restantes
	    		B3 = B3 & 0x1F; //Tomamos los 8 bits menos significativos de B y lo guardamos en B
	    		
	    		//Canal 4
	    		ivADC.u16=ivADC.u16>>4;
	    		A4 = ivADC.u16;
	    		C4 = A4 & 0x7F; //Tomo los 8 bits menos significativos 
	    		B4 = A4>>7;	//Desplazamos 7 bits a la derecha para obtener los 8 bits restantes
	    		B4 = B4 & 0x1F; //Tomamos los 8 bits menos significativos de B y lo guardamos en B
	    
	    		//Concatenamos el arreglo
	    		Array[0] = 0xFF;
	    		Array[1] = B1;
	    		Array[2] = C1;
	    		Array[3] = B2;
	    		Array[4] = C2;
	    		Array[5] = B3;
	    		Array[6] = C3;
	    		Array[7] = B4;
	    		Array[8] = C4;
	    		estado = mandar;
	    		break;
	  		case mandar:
	  			for(i=0;i<9;i++){
	  				do{
	  					errror=AS1_SendChar(Array[i]);
	  				}while((errror != ERR_OK));
	  			}	
	  			estado = esperar;
	  			break;
	  			
	  		default:
	  			break;
	  	
	  	}



 } 

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
