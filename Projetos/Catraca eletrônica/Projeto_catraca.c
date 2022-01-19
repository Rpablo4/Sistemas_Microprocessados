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
}
return(tcl);
}
void main(){
int x,op,car1,car2,car3;
int16 car, clida;
x=1;
while(true){
   lcd_init();
   lcd_putc("\fselec. uma opção\n1Cad.S 2Ins.S"); //Menu inicial
   delay_ms(1000);
   op=ler();
   delay_ms(500);
   switch(op){
      case 1:
         //Permite que o usuario cadastre uma senha
         lcd_putc("\fDig. Senha\n");
         delay_ms(300);
         car1=ler();
         lcd_putc("\n*");
         delay_ms(300);
         car2=ler();
         lcd_putc("*");
         delay_ms(300);
         car3=ler();
         lcd_putc("*");
         delay_ms(1000);
         car=car1*100+car2*10+car3;//Processa e salva a senha inserida
         clida=read_eeprom(1);
            if(car==clida){
               lcd_putc("\fERRO!\nsenha já cad");
               output_high(pin_e0);
               delay_ms(1000);
               output_low(pin_e0);
            }
            else
            {
               write_eeprom(1,car);//Salvando a senha na EEPROM
               x++;
               output_high(pin_e2);
               lcd_putc("\fsenha cadastrada");
               delay_ms(1000);
               output_low(pin_e2);
            }
            break;
      case 2: 
         //Permite que o usuario insira uma senha
         lcd_putc("\fDig. Senha\n");
         delay_ms(300);
         car1=ler();
         lcd_putc("\n*");
         delay_ms(300);
         car2=ler();
         lcd_putc("*");
         delay_ms(300);
         car3=ler();
         lcd_putc("*");
         delay_ms(1000);
         car=car1*100+car2*10+car3;//Processa e salva a senha inserida
         
         clida=read_eeprom(1);
            if(car==clida){
               lcd_putc("\fLIBERADO!!!");
               output_high(pin_e2);//Acende led verde
               output_high(pin_c0);//libera a catraca
               delay_ms(8000);//Aguarda 8 segundos para bloquear a catraca
               output_low(pin_e2);//apaga led verde
               output_low(pin_c0);//bloqueia a catraca
               }
            else
            {
               lcd_putc("\fSenha não cad!");
               output_high(pin_e0);//Acende led vermelho
               delay_ms(2000);//Aguarda 2 segundos e volta para o menu
               output_low(pin_e0);//apaga led vermelho
            }
            break;
            default:
               lcd_putc("\fOp invalida");
               output_high(pin_e0);//Acende led vermelho
               delay_ms(2000);//Aguarda 2 segundos e volta para o menu
               output_low(pin_e0);//Acende led vermelho
               break;     
                    }
}                   
}

