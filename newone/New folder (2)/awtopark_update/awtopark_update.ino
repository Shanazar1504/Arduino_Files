#include <SharpIR.h>
int val0;
int val1;
int val2;
int val3;
int val4;
int val5;
int val6;
int val7;
int val8;
int val9;
int val10;
int val11;
void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A12, INPUT);
  pinMode(A13, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  pinMode(A10, INPUT);
  pinMode(A11, INPUT);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(29, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(37, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(49, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
}
void loop() {
  val0 = digitalRead(A0);
  val1 = digitalRead(A1);
  val2 = digitalRead(A2);
  val3 = digitalRead(A3);
  val4 = digitalRead(A8);
  val5 = digitalRead(A9);
  val6 = digitalRead(A10);
  val7 = digitalRead(11);
  val8 = digitalRead(A12);
  val9 = digitalRead(A13);
  val10 = digitalRead(A14);
  val11 = digitalRead(A15);
  if (val0 == 1 && val1 == 1 && val2 == 1 && val3 == 1 && val4 == 1 && val5 == 1) {
    digitalWrite(14, 0);
    digitalWrite(16, 1);
  }
  else {
    digitalWrite(14, 1);
    digitalWrite(16, 0);
  }
  if (val6 == 1 && val7 == 1 && val8 == 1 && val9 == 1 && val10 == 1 && val11 == 1) {
    digitalWrite(15, 0);
    digitalWrite(17, 1);
  }
  else {
    digitalWrite(15, 1);
    digitalWrite(17, 0);
  }
  if (val0 == 1) {
    digitalWrite(22, 0);
    digitalWrite(23, 1);
  }
  else {
    digitalWrite(22, 1);
    digitalWrite(23, 0);
  }
  if (val1 == 1) {
    digitalWrite(24, 0);
    digitalWrite(25, 1);
  }
  else {
    digitalWrite(24, 1);
    digitalWrite(25, 0);
  }
  if (val2 == 1) {
    digitalWrite(26, 0);
    digitalWrite(27, 1);
  }
  else {
    digitalWrite(26, 1);
    digitalWrite(27, 0);
  }
  if (val3 == 1) {
    digitalWrite(29, 0);
    digitalWrite(30, 1);
  }
  else {
    digitalWrite(29, 1);
    digitalWrite(30, 0);
  }
  if (val4 == 1) {
    digitalWrite(31, 0);
    digitalWrite(32, 1);
  }
  else {
    digitalWrite(31, 1);
    digitalWrite(32, 0);
  }
  if (val5 == 1) {
    digitalWrite(33, 0);
    digitalWrite(34, 1);
  }
  else {
    digitalWrite(33, 1);
    digitalWrite(34, 0);
  }
  if (val6 == 1) {
    digitalWrite(36, 0);
    digitalWrite(37, 1);
  }
  else {
    digitalWrite(36, 1);
    digitalWrite(37, 0);
  }
  if (val7 == 1) {
    digitalWrite(38, 0);
    digitalWrite(39, 1);
  }
  else {
    digitalWrite(38, 1);
    digitalWrite(39, 0);
  }
  if (val8 == 1) {
    digitalWrite(40, 0);
    digitalWrite(41, 1);
  }
  else {
    digitalWrite(40, 1);
    digitalWrite(41, 0);
  }
  if (val9 == 1) {
    digitalWrite(43, 0);
    digitalWrite(44, 1);
  }
  else {
    digitalWrite(43, 1);
    digitalWrite(44, 0);
  }
  if (val10 == 1) {
    digitalWrite(45, 0);
    digitalWrite(46, 1);
  }
  else {
    digitalWrite(45, 1);
    digitalWrite(46, 0);
  }
  if (val11 == 1) {
    digitalWrite(47, 0);
    digitalWrite(48, 1);
  }
  else {
    digitalWrite(47, 1);
    digitalWrite(48, 0);
  }
}
