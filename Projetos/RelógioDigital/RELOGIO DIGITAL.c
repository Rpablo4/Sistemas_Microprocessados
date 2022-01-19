/*
Funções necessarias:
Mostrar o horário - ok
Mostrar data - ok
Função de Alarme - ok
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
output_high(pin_b0); //Nível ALTO na linha A
if (input(pin_a0)==0b1)
tcl=1;
if (input(pin_a1)==0b1)
tcl=2;
if (input(pin_a2)==0b1)
tcl=3;
output_low(pin_b0); //Nível baixo na linha A
output_high(pin_b1); //Nível ALTO na linha B
if (input(pin_a0)==0b1)
tcl=4;
if (input(pin_a1)==0b1)
tcl=5;
if (input(pin_a2)==0b1)
tcl=6;
output_low(pin_b1); //Nível baixo na linha B
output_high(pin_b2); //Nível ALTO na linha C
if (input(pin_a0)==0b1)
tcl=7;
if (input(pin_a1)==0b1)
tcl=8;
if (input(pin_a2)==0b1)
tcl=9;
output_low(pin_b2); //Nível baixo na linha C
output_high(pin_b3);
if (input(pin_a1)==0b1)
tcl=0;
}
return(tcl);
}

int hora, min, seg, dig1, dig2,dia, mes,horaAlarme,minAlarme, but1, but, but2;

void define_alarme(){
DefineHoraAlarme:
   lcd_putc("\fDefina a h Alrm:\nH=");
   delay_ms(300);
   dig1=ler();
   printf(lcd_putc,"\nH=%u",dig1);
   delay_ms(300);
   dig2=ler();
   printf(lcd_putc,"\nH=%u%u",dig1,dig2);
   delay_ms(300);
   horaAlarme=(dig2+dig1*10);
   if ( hora > 23 ) {
     lcd_putc("\fvalor invalido!\ntente nov");
     delay_ms(1000);
     goto DefineHoraAlarme;
     }
     else{
     printf(lcd_putc,"\nH=%u",hora);
     }

DefineMinAlarme:
   lcd_putc("\fDefina o M Alrm:\nM=");
   delay_ms(300);
   dig1=ler();
   printf(lcd_putc,"\nM=%u",dig1);
   delay_ms(400);
   dig2=ler();
   printf(lcd_putc,"\nM=%u%u",dig1,dig2);
   delay_ms(300);
   minAlarme=(dig2+dig1*10);
     if ( min > 59 ) {
     lcd_putc("\fvalor invalido!\ntente nov");
     delay_ms(1000);
     goto DefineMinAlarme;
     }
     else{
     printf(lcd_putc,"\nM=%u%u",dig1,dig2);
     delay_ms(1000);
     }
}
void define_data(){
DefineMes:
   lcd_putc("\fDefina o Mes:\nMes=");
   delay_ms(300);
   dig1=ler();
   delay_ms(300);
   printf(lcd_putc,"\nMes=%u",dig1);
   delay_ms(300);
   dig2=ler();
   delay_ms(300);
   printf(lcd_putc,"\nMes=%u%u",dig1,dig2);
   mes=(dig2+dig1*10);
   if ( mes > 12 ) {
     lcd_putc("\fvalor invalido!\ntente nov");
     delay_ms(1000);
     goto DefineMes;
     }
DefineDia:
   lcd_putc("\fDefina o Dia:\nDia=");
   delay_ms(300);
   dig1=ler();
   printf(lcd_putc,"\nDia=%u",dig1);
   delay_ms(300);
   dig2=ler();
   printf(lcd_putc,"\nDia=%u%u",dig1,dig2);
   delay_ms(300);
   dia=(dig2+dig1*10);
   if ( dia > 31 || dia == 0 ) {
     lcd_putc("\fvalor invalido!\ntente nov");
     delay_ms(1000);
     goto DefineDia;
     }

}
void define_hora(){
DefineHora:
   lcd_putc("\fDefina a hora:\nH=");
   delay_ms(300);
   dig1=ler();
   printf(lcd_putc,"\nH=%u",dig1);
   delay_ms(500);
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
   delay_ms(300);
   dig1=ler();
   printf(lcd_putc,"\nM=%u",dig1);
   delay_ms(300);
   dig2=ler();
   printf(lcd_putc,"\nM=%u%u",dig1,dig2);
   delay_ms(300);
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
   delay_ms(300);
   dig1=ler();
   printf(lcd_putc,"\nS=%u",dig1);
   delay_ms(300);
   dig2=ler();
   printf(lcd_putc,"\nS=%u%u",dig1,dig2);
   delay_ms(300);
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
void defineTudo(){
define_hora();
define_min();
define_seg();
define_data();}

void main(){

lcd_init();
defineTudo();

/*
      Este laço repetidor funciona como contador
      Vai incrementando até que atinge o número máximo
      em cada operação.
*/       while ( true ) {
         but1=input(pin_e2);
         but2=input(pin_c0);
         Start:
         printf(lcd_putc,"\fH-M-S     %u|%u\n%u - %u - %u",dia,mes,hora, min, seg);
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
              dia++;
         }
         if ( dia > 31 ) {
              dia = 1;
              mes++;
         }
         if ( mes > 12 ) {
            mes=1;
            dia++;
         }
         
         if (hora==horaAlarme && min==minAlarme){
            while(true){
            delay_ms(1000);
            seg++
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
              dia++;
            }
               output_high(pin_e0);//dispara buzzer
               but=input(pin_e1);
               
            if(but==0b1){
               horaAlarme=99;
               minAlarme=99;
               output_low(pin_e0);
            goto Start;}
            }
         }
         if (but1==0b1){
            define_alarme();
         }   
     }
}
     
