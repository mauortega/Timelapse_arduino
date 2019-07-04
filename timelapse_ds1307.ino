// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
#include <Time.h> // Needed for time_t variables and tmElements

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sabado"};

void setup () {
  while (!Serial); // for Leonardo/Micro/Zero

  Serial.begin(57600);
  if (! rtc.begin()) {
    Serial.println("Não foi possivel encontrar o RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("O RTC não está rodando!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }


}



void loop () {
  DateTime now = rtc.now();

  static DateTime startTime = now.unixtime();

  Serial.print("***************\n\n");
  Serial.print("Estou ligado a ");
  Serial.print(zero(((now.unixtime() - startTime.unixtime())) / 86400L));
  Serial.print (" Dias, ");
  Serial.print(zero((((now.unixtime() - startTime.unixtime())) / 3600) % 24));
  Serial.print(" Horas, ");
  Serial.print(zero((((now.unixtime() - startTime.unixtime())) / 60) % 60));
  Serial.print(" Minutos, ");
  Serial.print(zero((now.unixtime() - startTime.unixtime()) % 60));
  Serial.print(" Segundos \n\n");
  Serial.print("***************\n\n");


  Serial.print(zero(now.day()));
  Serial.print('/');
  Serial.print(zero(now.month()));
  Serial.print('/');
  Serial.print(zero(now.year()));
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(zero(now.hour()));
  Serial.print(':');
  Serial.print(zero(now.minute()));
  Serial.print(':');
  Serial.print(zero(now.second()));
  Serial.println();

  Serial.println();
  delay(1000);
}

String zero(int digito) {
  String strDigito;
  if (digito < 10) {
    strDigito = "0" + String(digito);
  }
  else {
    strDigito = String(digito);
  }
  return strDigito;
}
