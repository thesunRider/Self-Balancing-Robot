//all includes available from arduino library manager
#include <Arduino.h>
#include <TinyMPU6050.h>
#include <AutoPID.h>
#include <Kalman.h> 
#include <L293D.h>



// CODE BY SURYASARADHI

double motorsetcontrols(double control);
#define READ_DELAY 1



//pid settings and gains  ,values from pidtuner website
#define KP 0.18
#define KI 1.85
#define KD 6400


//for eualising the power of both the motors
double inc_del = 0.025;

uint32_t timer;
double outputVal,controls;
double x_ang,y_ang,z_ang;
double kalAngleX, kalAngleY,kalAngleZ;


//Enable 3,5 
//control 11,10 - 9,8
L293D motorL(3,11,10);
L293D motorR(5,9,8);
double setPoint = 1.1,inputval = 1.5;
AutoPID selfPID(&inputval, &setPoint, &outputVal, -0.9, 0.9, KP, KI, KD);
Kalman kalmanX, kalmanY,kalmanZ;
MPU6050 mpu (Wire);

void switch_m(){
   motorL.set(0);
  motorR.set(0);
  Serial.println("switch set inpoint");
  mpu.Execute();
  x_ang = mpu.GetAngX();
  setPoint = x_ang;
  delay(1500);
}


/*
 *  Setup
 */
void setup() {

  Serial.begin(9600);
  pinMode(2,INPUT);
  mpu.Initialize();
  mpu.SetGyroOffsets(-675.29,57.50,-93.66);
  //mpu.Calibrate();
  
  mpu.Execute();
  
  kalmanX.setAngle(mpu.GetAngX()); 
  kalmanY.setAngle(mpu.GetAngY());
  kalmanZ.setAngle(mpu.GetAngY());

  selfPID.setBangBang(3); //when crossing 30 degrees set to full throttle to stabilize
  selfPID.setTimeStep(READ_DELAY); //set PID update interval to 10ms

  Serial.println("new==========");
}

/*
 *  Loop
 */
void loop() {
  mpu.Execute();
  x_ang = mpu.GetAngX();
  y_ang = mpu.GetAngY();
  z_ang = mpu.GetAngZ();
  if (digitalRead(2) == HIGH)
    switch_m();
  
  double dt = (double)(micros() - timer) / 1000000; // Calculate delta time
  timer = micros();

  kalAngleX = kalmanX.getAngle(x_ang, mpu.GetGyroX(), dt);
  kalAngleY = kalmanY.getAngle(y_ang, mpu.GetGyroY(), dt);
  kalAngleZ = kalmanZ.getAngle(z_ang, mpu.GetGyroZ(), dt);

  inputval = kalAngleX;
  
  
  selfPID.run();
  controls = motorsetcontrols(outputVal);
  motorL.set(controls);
  motorR.set(controls+inc_del);

  if (abs(inputval) > 15.0){
    Serial.println("ENDCONFIG");}
  else{
  Serial.print(inputval);
  Serial.print(",");
  Serial.print(controls);
  Serial.print(",");
  Serial.println(micros());
  }
  delay(READ_DELAY);
}


double motorsetcontrols(double control){
  control = control *10;
  if (control < 0){
    control = map(control,0,-10,-10,0);
    return control /10;
  }
  if (control > 0){
    return control/10;
  }
  
}
