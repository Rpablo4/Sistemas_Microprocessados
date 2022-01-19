/*
Fun��es necessarias:
Mostrar o hor�rio
Mostrar data
Fun��o de Alarme
*/

#include <16F874A.h>
#use delay(clock=4000000)
#include <lcd.c>
#FUSES XT

int ler()
{
int tcl=13;
while(tcl==13)
{
output_high(pin_b0); //N�vel ALTO na linha A
if (input(pin_a0)==0b1)
tcl=1;
if (input(pin_a1)==0b1)
tcl=2;
if (input(pin_a2)==0b1)
tcl=3;
output_low(pin_b0); //N�vel baixo na linha A
output_high(pin_b1); //N�vel ALTO na linha B
if (input(pin_a0)==0b1)
tcl=4;
if (input(pin_a1)==0b1)
tcl=5;
if (input(pin_a2)==0b1)
tcl=6;
output_low(pin_b1); //N�vel baixo na linha B
output_high(pin_b2); //N�vel ALTO na linha C
if (input(pin_a0)==0b1)
tcl=7;
if (input(pin_a1)==0b1)
tcl=8;
if (input(pin_a2)==0b1)
tcl=9;
output_low(pin_b2); //N�vel baixo na linha C
output_high(pin_b3);
if (input(pin_a1)==0b1)
tcl=0;
}
return(tcl);
}

int hora, min, seg, dig1, dig2;


void define_hora(){
DefineHora:
   lcd_putc("\fDefina a hora:\nH=");
   dig1=ler();
   delay_ms(300);
   printf(lcd_putc,"\nH=%u",dig1);
   dig2=ler();
   delay_ms(300);
   printf(lcd_putc,"\nH=%u%u",dig1,dig2);
   hora=(dig2+dig1*10);
   if ( hora > 23 ) {
     lcd_putc("\fvalor invalido!\ntente nov");
     delay_ms(1000);
     goto DefineHora;
     }
     else{
     printf(lcd_putc,"\nH=%u",hora);
     }
}
void define_min(){
DefineMin:
   lcd_putc("\fDefina o min:\nM=");
   dig1=ler();
   delay_ms(300);
   printf(lcd_putc,"\nM=%u",dig1);
   dig2=ler();
   delay_ms(300);
   printf(lcd_putc,"\nM=%u%u",dig1,dig2);
   min=(dig2+dig1*10);
     if ( min > 59 ) {
     lcd_putc("\fvalor invalido!\ntente nov");
     delay_ms(1000);
     goto DefineMin;
     }
     else{
     printf(lcd_putc,"\nM=%u",min);
     }
}
void define_seg(){
DefineSeg:
   lcd_putc("\fDefina o seg:\nS=");
   dig1=ler();
   delay_ms(300);
   printf(lcd_putc,"\nS=%u",dig1);
   dig2=ler();
   delay_ms(300);
   printf(lcd_putc,"\nS=%u%u",dig1,dig2);
   seg=(dig2+dig1*10);
   if ( seg > 59 ) {
     lcd_putc("\fvalor invalido!\ntente nov");
    delay_ms(1000);
    goto DefineSeg;
     }
     else{
     printf(lcd_putc,"\nS=%u",seg);
     }
}

void main(){

lcd_init();
define_hora();
define_min();
define_seg();

/*
      Este la�o repetidor funciona como contador
      Vai incrementando at� que atinge o n�mero m�ximo
      em cada opera��o.
*/    
     while ( true ) {
     printf(lcd_putc,"\fH - M - S\n%u - %u - %u",hora, min, seg);
         delay_ms( 1000 );
         seg++;
         if ( seg > 59 ) {
              seg = 0;
              min++;
         }
         if ( min > 59 ) {
              min = 0;
              hora++;
         }
         if ( hora > 23 ) {
              hora = 0;
         }
     }
     }
