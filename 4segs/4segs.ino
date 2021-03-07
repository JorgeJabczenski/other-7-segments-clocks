#include "RTClib.h"
/* Declara o RTC DS3132 */
RTC_DS3231 rtc;

#define CTL_0 10
#define CTL_1 11
#define CTL_2 12
#define CTL_3 13

#define DELAY 2

/* Codificação dos números em 7 segmentos (ativo em 0) */
/* ABCD EFG. */
int nums[16]{
    B00000011, /*0*/
    B10011111, /*1*/
    B00100101, /*2*/
    B00001101, /*3*/
    B10011001, /*4*/
    B01001001, /*5*/
    B01000001, /*6*/
    B00011111, /*7*/
    B00000001, /*8*/
    B00011001, /*9*/
    B00010001, /*a*/
    B11000001, /*b*/
    B01100011, /*c*/
    B10000101, /*d*/
    B01100001, /*e*/
    B01110001, /*f*/
};

int segs[8] = {2, 3, 4, 5, 6, 7, 8, 9}; /*a b c d e f g .*/
int ctls[4] = {10, 11, 12, 13};         /* MS . . . . LS */

void printNum(int num, int disp) {
  for (int i = 0; i < 4; i++)
    digitalWrite(ctls[i], LOW);
  for (int i = 0; i < 8; i++) {
    //digitalWrite(segs[7 - i], !(nums[num] & (1 << i))); /* Modo Negado */
    digitalWrite(segs[7 - i], nums[num] & (1 << i)); /* Modo Normal */
  }
  digitalWrite(disp, HIGH);
  delay(DELAY);
}

void setup() {

  rtc.begin();
  Serial.begin(9600);

  /* Arruma o horário baseado na hora de compilação do sketch */
  /* Descomente na primeira vez que for rodar o programa e depois comente
   * novamente */
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  /* Define todos os pinos como saída */
  for (int i = 2; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
}

void writeHour(DateTime now) {
  int horario[4];
  horario[0] = now.hour() / 10;
  horario[1] = now.hour() % 10;
  horario[2] = now.minute() / 10;
  horario[3] = now.minute() % 10;

  for (int i = 0; i < 4; i++) {
    printNum(horario, 1);
    delay(DELAY);
  }
}

void loop() {

  DateTime now = rtc.now();
  int horario[4];
  horario[0] = now.hour() / 10;
  horario[1] = now.hour() % 10;
  horario[2] = now.minute() / 10;
  horario[3] = now.minute() % 10;

  int i = 0;
  printNum(horario[0], ctls[i % 4 + 0]);
  printNum(horario[1], ctls[i % 4 + 1]);
  printNum(horario[2], ctls[i % 4 + 2]);
  printNum(horario[3], ctls[i % 4 + 3]);
}
