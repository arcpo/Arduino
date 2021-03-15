// -------------- Librería para el Display -----------------
#include "U8glib.h"

// --------------- Librerías para el reloj -----------------
#include "RTClib.h"
#include <Time.h>
#include <Wire.h>

// --------------- No se para que es esta librería? --------
#include <Streaming.h>

// -------------- Definiendo cables para el display --------
U8GLIB_ST7920_128X64_1X u8g(13, 11, 10, 12 ); //Enable, RW, RS, Reset. Para arduino UNO, para Mega cambia

// -------------- Definiendo variables globales ------------
int posicao = 0;
int posicaoh = 0;

RTC_DS1307 rtc;
char* dia_da_semana[]={
  "Dom", "Lun", "Mar", "Mie", "Jue", "Vie", "Sab"};
int segundo,minuto,hora,dia,mes,numdiadesemana;
long anio; //variable año
DateTime HoraFecha;


//--------------------------- Funciones -----------------------------//

void mostra_relogio_digital();
void tela_2();

//============================================================================//
//                            Funcion SETUP                                   //
//============================================================================//
void setup() {
  //uint8_t u8g_Begin(u8g_t *u8g); // Reset display and put it into default state.
  //void u8g_DisableCursor(u8g_t *u8g); //The cursor will not be visible.
  
  // getMode() devuelve info del display (display mode)
  // Detecta el display y configura a la mejor vista posible
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }

  //Para el reloj
  rtc.begin(); //Inicializamos el RTC
}

//==========================================================================//
//                               Funcion Loop                               //
//==========================================================================//
void loop() {
  HoraFecha = rtc.now(); //obtenemos la hora y fecha actual
    
  segundo=HoraFecha.second();
  minuto=HoraFecha.minute();
  hora=HoraFecha.hour();
  dia=HoraFecha.day();
  mes=HoraFecha.month();
  anio=HoraFecha.year();
  numdiadesemana=HoraFecha.dayOfTheWeek();

  //picture loop
  u8g.firstPage(); 
  do{
    tela_2(); 
  } while( u8g.nextPage() );

  delay(10);
}

//==========================================================================//
//                              Funcion 1                                   //
//==========================================================================//
void tela_2(){
  u8g.drawRFrame(0, 0, 128, 64, 3);
  u8g.drawRFrame(68, 4, 55, 56, 2);
  
  mostra_relogio_digital();
  
  u8g.setFont(u8g_font_5x8); 
  u8g.drawStr( 78, 35, "MIN");
  u8g.drawStr( 78, 53, "MAX");
  u8g.setFont(u8g_font_6x13);
  u8g.setPrintPos(25, 41);
  u8g.print(dia_da_semana[(numdiadesemana)]);

  //Mostra temperatura atual
  u8g.setPrintPos(83, 19);
  u8g.print("Te"); 
  u8g.drawStr( 105, 19, "C");
  u8g.drawCircle(100, 12, 2);
  
  //Mostra temperatura minima
  u8g.setPrintPos(98, 36);
  u8g.print("Tm"); 
  u8g.drawCircle(113, 29, 2);
  
  //Mostra temperatura maxima
  u8g.setPrintPos(98, 54);
  u8g.print("TM"); 
  u8g.drawCircle(113, 47, 2);
}

//==========================================================================//
//                              Funcion 2                                   //
//==========================================================================//

void mostra_relogio_digital(){
  //Mostra a data 
  u8g.setFont(u8g_font_5x8); 
  u8g.setPrintPos(8, 55);
  u8g.print(dia);
  u8g.drawStr( 19, 55, "/");
  u8g.setPrintPos(24, 55);
  u8g.print(mes);
  u8g.drawStr( 35, 55, "/");
  u8g.setPrintPos(41, 55);
  u8g.print(anio);
  
  //Mostra hora e minutos
  u8g.drawRBox(3, 4, 62, 21,2);
  u8g.setColorIndex(0);
  u8g.setFont(u8g_font_fub17);
  u8g.drawStr(29,21,":");

  //Acerta a posicao do digito caso a hora
  //seja menor do que 10
  if (hora < 10){
    u8g.drawStr(3,23,"0");
    posicaoh = 16;
  } else posicaoh = 3;

  u8g.setPrintPos(posicaoh, 23);
  u8g.print(hora);
  
  //Acerta a posicao do digito caso o minuto
  //seja menor do que 10
  if (minuto < 10){
    u8g.drawStr(38,23,"0");
    posicao = 51;
  } else posicao = 38;
  
  u8g.setPrintPos(posicao ,23);
  u8g.print(minuto);
  u8g.setColorIndex(1);
}
