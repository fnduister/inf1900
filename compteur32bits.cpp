/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme 
 * Version: 1.1
 */


#include <avr/io.h> 
#include <util/delay.h>
//#define F_CPU 14.7456E6;

void antirebond(unsigned int& decompte, bool& pressed){
  if( PIND & 0x04 ){
    if(decompte < 2){decompte++;}
    
    if(decompte == 2){
      pressed = false;
    }
  }else{
    decompte = 0;
    pressed = true;
  }
}

int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode lecture
  unsigned int decompte = 0;
  bool pressed = false;
  unsigned long compteur=0; // le compteur est initialise a 0.
                            // c'est un compteur de 32 bits

  for(;;)  // boucle sans fin
  {
    compteur++;  // incremente le compteur
                 // si le compteur est 0xffff ffff il revient a 0
    PORTD = compteur;       // PORTD = 8 bits de large,
                            // il prend les bits de 0 a 7 du compteur
    PORTC = compteur >> 8;  // PORTC = 8 bits de large,
    
    antirebond(decompte,pressed);

    if(pressed){
      PORTB = 0x02; // PORTB = 8 bits de large,
      _delay_ms(100);
      PORTB = 0x01;
      _delay_ms(10);
    }else{
      PORTB = 0x00;
    }
    
                            // il prend les bits de 16 a 23 du compteur
                            // en faisant un decallage de 16 bits.
                            //01010101 - 10100101= rouge
                            //10101010 - 01011010= vert
    PORTA = compteur >> 24; // PORTA = 8 bits de large,
                            // il prend les bits de 24 a 31 du compteur
                            // en faisant un decallage de 24 bits.
  }
  return 0; 
}

