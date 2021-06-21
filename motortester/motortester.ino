#include <L293D.h>
double motorsetcontrols(double control);
L293D motorL(3,11,10);
L293D motorR(5,9,8);
double control;
double inc = 0.1;
float i;
float k;
double inc_del = 0.025;

void setup()
{
  Serial.begin(9600);
}

void  loop()
{     
      for (int i = 0;i <= 10; i++){
      control = motorsetcontrols((double) i/20);
      motorL.set(control);
      motorR.set(control+inc_del);
      Serial.println(control);
      delay(1500);
      }
      for (int i = 0;i >= -10; i--){
      control = motorsetcontrols((double) i/20);
      motorL.set(control);
      motorR.set(control+inc_del);
      Serial.println(control);
      delay(1500);
      }
    
}

double motorsetcontrols(double control){
  Serial.println("dpping");
  control = control *10;
  if (control < 0){
    control = map(control,0,-10,-10,0);
    return control /10;
  }
  if (control > 0){
    return control/10;
  }
  
}
