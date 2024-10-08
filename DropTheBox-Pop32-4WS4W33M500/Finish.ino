void Finish() {
  long int RunningTime;
  RunningTime = ReadTimer2(); 
  OffMotor();
  beep(0);oled.textSize(1);
  oled.clear();
  oled.text(0,0,"   Finish.   ");
  oled.text(2,0,"Running Time.");
  oled.text(4,0,"%l.%l seconds", RunningTime/1000, RunningTime%1000);
  oled.show();                  //แสดงบนหน้าจอ
  while(1){};
}
