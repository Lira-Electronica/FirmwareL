///COMUNICACION SERIAL PARA DEMOQE128 FUNCIONA
int wer; //Esto es para probar git
//Paso 1: Incluir librería 
import processing.serial.*;
//String listaPuertos[];
Serial P; //Para guardar el Puerto del demoQE
boolean cabecera;
IntList  valores;
int estado = 1, lastx = 0, lasty = 620, posx = 0, posy, increm = 4; 
byte con1, con2;
void setup{

    size(840,620); //Tamaño de la pantalla 
    println(Serial.list()); //Mostrar en consola el pueerto en uso
    P = new Serial(this, Serial.list()[0], 115200); // Guardo en la variable P lo que recibo por puerto serial
    P.buffer(3); //Cantidad de bytes que envia el DEMOQE128
    valores = new IntList(); //Se comienza a enlistar los valores  que llegan por puerto serial 
    background(255); //Se pinta el fondo de negro
/*******************
//Paso 2: Identificar el puerto
//println(Serial.list()); // Sirve para saber donde esta ubicado el puerto de comunicacion/
*********************/
//paso 3: Seleccionar el puerto  
}

void draw(){
    if(valores.size()>=20){
      if(posx < 840){
        posy = valores.remove(0);
        line(lastx, lasty, posx, posy);
        lastx = posx;
        lasty = posy;
        posx += increm;
      } else {
        posx = 0;
        lastx = 0;
        lasty= 620;
        background(255);
        valores.clear();
      }
    }
}

void serialEvent(Serial P){ //Ciclo del programa
  byte[] trama = new byte[3]; // En un arreglo del tipo byte, se guardaran las tramas (paquetes de bytes)
  P.readBytes(trama); //Lee los bytes de entrada y los guarda en trama
  
  for(int i=0;i<3;i++){
    if(trama[i] == -15){ // Posicion en que se lee la cabecera F1  
      cabecera = true; // si se encuentra una cabecera
    } 
    if(cabecera){
      switch (estado){
        case 1: // No hago nada
          estado = 2; 
          break;
        
        case 2: 
          con1 = trama[i]; // se guarda el primar byte despues de la cabecera
          // decodificar digitales
          estado = 3;
          //println(hex(con1));
          break;
        
        case 3:
          con2 = trama[i]; //Se guarda el segundo Byte despues de la cabecera
          //println(hex(con2));
          valores.append(decode(con1,con2)); // Valores en la lista.
          
          estado = 1;
          break;
      
      }    
    }

   }
}

int decode(byte con1, byte con2){
  int aux1, aux2, aux3, aux4, code;
  
  aux1 = con1 & 0x1F; // Mascara para el segundo byte de 0001 1111
  aux2 = con2 << 1;  // Originalmente se tiene un byte 0AAA AAAA. se corre a AAAA AAA0
  aux3 = aux1 << 8; // Lo corre al primer byte, se crea una trama de 16 bits 
  aux4 = aux2 & 0x00FF; // Se guardan en una trama de 16 bits como los bits menos sginificativos (00000000 AAAAAAA0)
  aux4 = aux3 | aux4;  //Se suma las dos tramas 
  code = aux4 >> 1; //Quedan los 12 bits  del ADC juntos como los bits menos significativos
  
  code = (int)map(code,0,4096,620,0);
  //println(code);
  return code;

}
void keyPressed() {
  if (key == '+') {
    if(increm < 100){
      increm += 2;
    }
  }
  if (key == '-') {
    if(increm > 0){
      increm -= 2;
    }
  }
}