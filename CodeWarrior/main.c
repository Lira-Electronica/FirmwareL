/* ###################################################################
**     Filename    : main.c
**     Project     : Semana_3_Lunes
**     Processor   : MC9S08QE128CLK
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2018-01-22, 23:12, # CodeGen: 0
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
#include "Cap1.h"
#include "Bit1.h"
#include "Bit2.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

//unsigned char estado = esperar;
//unsigned char CodError;
//unsigned int Enviados = 2;
//unsigned int error;
//bool primero = FALSE;
//unsigned int periodo;
unsigned int puntero = 2;
typedef union{
	unsigned char u8[2];
	unsigned int u16;
}ANCHO;
volatile ANCHO iADC;
int A,B,C,D1,D2,b;
bool H1,H2;
unsigned char Array[3];
//unsigned char cTrama[5]={0x00,0x00,0x00,0x00,0xFF};
//unsigned char dTrama[2]={0x00,0x00};

/* User includes (#include below this line is not maintained by Processor Expert) */
void main(void)
{
	//Enviar Bloque
	estado = esperar;
  /* Write your local variable definition here 
	
	bloque.u8[0]=0x5A;
	bloque.u8[1]=0x61;
	bloque.u8[2]=0x64;
	bloque.u8[3]=0x6B;
	bloque.u8[4]=0x69;
	bloque.u8[5]=0x65;  
	bloque.u8[6]=0x6C;
	bloque.u8[7]=0x20; */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  for(;;) { 
	  
	   switch (estado){
  		
  		case esperar:
  			break;
  			
  		case medir:
  			AD1_Measure(TRUE);
  			AD1_GetValue16(&iADC.u16);
  			//H1 = Bit1_GetVal();
  			//H2 = Bit2_GetVal();
  			//if(H1 == TRUE){
  				//D1 = 0x40;
  				//Bit3_PutVal(TRUE);
  			//}else{
  				//D1 = 0x00;
  				//Bit3_PutVal(FALSE);
  			//}
			//if(H2 == 0x02){ //true
				//D2 = 0x20;
				//Bit4_PutVal(TRUE);
			//}else{
			  //	D2 = 0x00;
			  	///Bit4_PutVal(FALSE);
			//}
  			//Puerto digital
  		  // PROTOCOLO DE COMUNICACION PARA LOS SENSORES//
  			iADC.u16=iADC.u16>>4;
  			A = iADC.u16;
  			C = A & 0x7F; //Tomo los 8 bits menos significativos 
  			B = A>>7;	//Desplazamos 7 bits a la derecha para obtener los 8 bits restantes
  			B = B & 0x1F; //Tomamos los 8 bits menos significativos de B y lo guardamos en B
  			//b = B | D1;
  			//B = b | D2;
  			//B = B | d1;
  			//Concatenamos el arreglo
  			Array[0] = 0xF1;
  			Array[1] = B;
  			Array[2] = C;
  			//Array[3] = 0xFF;
  			//Array[4] = 0xFF;     
  		   //A Partir de aca se debe enviar el bloque de datos[Literal: SenBlock(&Array,otras vainas)] 
  		   //
  		  ///FALTA ENCABEZADO 0xFN donde N indica el numero del canal mixto de adquisición. 
  			estado = mandar;
  			break;
  	
  		case mandar:
  			
  			AS1_SendBlock(&Array,3,&puntero);//PROTOCOLO
  			//AS1_SendBlock(&iADC.u8,2,&puntero);
  			estado = esperar;
  			
  			/*if(bloque.u8[0] != 0xFF){
  				cTrama[1] = bloque.u8[0];
  				cTrama[3] = 0x00;	
  			}else{
  				cTrama[1] = 0xFE;
  				cTrama[3] = 0x00;
  			}
  			
  			if(bloque.u8[1] != 0xFF){
  				cTrama[2] = bloque.u8[1];				
  			}else{
  				cTrama[2] = 0xFE;
  				cTrama[3] = cTrama[3] | 0x0A;
  			}
  	
  			dTrama[0]=(periodo >> 8) & (0xFF);
  			dTrama[1]=(periodo) & (0xFF);*/
  			
  			//CodError = AS1_SendBlock(dTrama,2,&puntero);
  			//estado = esperar;
  			
  			break;
  			
  		default:
  			break;
  	
  	}

	  
	  
	  
	  
	  //Mandar bloque
	  /*if(estado==esperar){
		  
	  }
	  if(estado == mandar){
		  AS1_SendBlock(&bloque.u8,8,&puntero);
		  estado = esperar;
	  }*/
	   
	  
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
