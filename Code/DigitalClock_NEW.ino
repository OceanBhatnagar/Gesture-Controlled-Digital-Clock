#include <Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int s,m,h,a,d,state,state1,state2,dg,cnt,dt,mo;
char months[13]={' ','1','2','3','4','5','6','7','8','9','o','n','d'};
int l[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
int x,y,z;

void setup()
{
  
  state=1;   //state for decrementing value in setting mode
  state1=1;  // state for incrementing value in setting mode
  state2=1;   //state for opening settin mode
  lcd.begin(16,2);
  lcd.init();       // initialize the lcd
  lcd.backlight();

  pinMode(8,INPUT); // Setting pinmode for IR SENSOR1
  pinMode(9,INPUT); //Setting pinmode for IR SENSOR2
  pinMode(10,INPUT); //Setting pinmode for IR SENSOR3
  
  s=0;   //seconds
  m=0;   //minutes
  h=0;   //hours
  dt=1;   //date
  mo=1;   //month
}
void printNumber(int value, int col) {
  if (value == 0) {
    lcd.setCursor(col, 0); 
    lcd.print("0");  
}
  if (value == 1) {
    lcd.setCursor(col, 0); 
    lcd.print("1");  
}
  if (value == 2) {
   lcd.setCursor(col, 0); 
   lcd.print("2");  
}
   if (value == 3) {
   lcd.setCursor(col, 0); 
   lcd.print("3");  
}
   if (value == 4) {
    lcd.setCursor(col, 0); 
    lcd.print("4");  
}
   if (value == 5) {
   lcd.setCursor(col, 0); 
   lcd.print("5");  
}
   if (value == 6) {
    lcd.setCursor(col, 0); 
    lcd.print("6");  
}
   if (value == 7) {
    lcd.setCursor(col, 0); 
  lcd.print("7");  
}
   if (value == 8) {
    lcd.setCursor(col, 0); 
  lcd.print("8");  
}
   if (value == 9) {
    lcd.setCursor(col, 0); 
  lcd.print("9");  
}
}
        
 
void loop()
{
  x=digitalRead(8);
  y=digitalRead(9);
  z=digitalRead(10);
  
  if(x==1 &&state==1){        //if gesture is detected by IR sensor1 value is incremented
    cnt++;
    state=0;
    cnt=cnt%5;
    }else if(x==0&&state==0){
    state=1;
    }
  
   if (z==1&&state1==1){             //if gesture is detected by IR sensor2 value is decremented
    dg=1; 
    state1=0;
    }
    else if(z==0 &&state1==0){
    state1=1;
    }


  if(y==1&& state2==1){             //if gesture is detected by IR sensor3 Setting mode is opened
     dg=-1;
     state2=0;
    }
    else if(y==0 &state2==0){
    state2=1;
    }


    switch(cnt){
      case 1:
      h=h+dg;
      dg=0;if(h>23){
    h=h-24;}
    if(h<0){
    h=23;}
      break;
      
       case 2:
      m=m+dg;
      dg=0;  if(m>59){
    m=0;}
    if(m<0){
    m=59;}
      break;
     
     case 3:
      dt=dt+dg;
      dg=0;if(dt>l[mo]){
    dt=l[mo];}
    if(dt<1){
      dt=1;}
      break;
     
     case 4:
      mo=mo+dg;
      dg=0;if(mo>12){
    mo=1;
     }
    if(mo<1){
      mo=12;}
    if(dt>l[mo]){
    dt=1;
    mo++;
     mo=(1+(mo-1)%12);
    }
      break;
    }
  
  if(s>59){
    s=0;
    m++;
  
  if(m>59){
    m=0;
   h++;
    
  if(h>23){
    h=0;
    dt++;
  
  if(dt>l[mo]){
    dt=1;
    mo++;
    }
      if(mo>12){
    mo=1;
    }

  } 
  }
  }


  h=h;
  d=(h)%10;
  printNumber(d, 3);
  d=(h)/10;
   printNumber(d, 0);

     d=m%10;
     printNumber(d, 10);
     d=m/10;
     printNumber(d, 7);
     lcd.setCursor(14, 0);
     lcd.print(s/10);
     lcd.print(s%10);

    
     lcd.setCursor(15, 1);
      lcd.print(months[mo]);
      
    
    lcd.setCursor(12,1);
    
     lcd.print(dt/10);
     lcd.print(dt%10);
        if(cnt==0){
           s++;
        lcd.setCursor(5, 0);
      lcd.print(" ");
      lcd.setCursor(6, 1);
      lcd.print(" ");
     
      lcd.setCursor(13,0);
         lcd.print(" ");
      delay(500);
      
      lcd.setCursor(5, 0);
      lcd.print(":");
      lcd.setCursor(6, 1);
      lcd.print(" ");
      delay(500);
      
     
        lcd.setCursor(13,0);
      lcd.print(":");
      delay(500);
       }}




