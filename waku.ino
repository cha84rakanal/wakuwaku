#include "AccelStepper.h" 
//Library created by Mike McCauley at http://www.airspayce.com/mikem/arduino/AccelStepper/

#include "util.h"
//ピンアサインとタイマークラスを記述

//ラベルを上につけてください
//同じ方向につけているので、巻き上げる時は、片方は逆回転

//右のステッピングモーター
AccelStepper stepperR(1, 2, 3);   // 1 = Easy Driver interface
                                  // UNO Pin 2 to Driver STEP 
                                  // UNO Pin 3 to Driver DIR
     
//左のステッピングモーター                             
AccelStepper stepperL(1, 5, 6);   // 1 = Easy Driver interface
                                  // UNO Pin 2 to Driver STEP 
                                  // UNO Pin 3 to Driver DIR

int move_finished=1;  // Used to check if move is completed

//ステッピングモータのスピード調整
float spd = 1000.0;

void setup() {
  
  Serial.begin(9600);  //Start the Serial monitor with speed of 9600 Bauds
  
  stepperR.setMaxSpeed(spd);      //Set Max Speed
  stepperR.setAcceleration(spd);  //Acceleration

  stepperL.setMaxSpeed(spd);      // Set Max Speed of X axis
  stepperL.setAcceleration(spd);  // Acceleration of X axis
}

//調整で動く幅
long control_step = 150;

//通常で動く幅
long general_step = 400;

//逆回転flag
int reverse_motor = 0;

void loop() {

  /*******デバッグ用のプログラム********/
  //タクトスイッチを入れる使えます
  //http://daisuki-arduino.com/arduino_program_sw/

  if(digitalRead(control_pin) == HIGH){
    
    if(digitalRead(r_back_pin) == HIGH){
      stepperR.moveTo(-control_step);
      move_finished=0;
    }else if(digitalRead(r_forward_pin) == HIGH){
      stepperR.moveTo(control_step);
      move_finished=0;
    }

    if(digitalRead(l_back_pin) == HIGH){
      stepperL.moveTo(-control_step);
      move_finished=0;
    }else if(digitalRead(l_forward_pin) == HIGH){
      stepperL.moveTo(control_step);
      move_finished=0;
    }
    
  }

  /*******通常のプログラム********/

  //モータの回転ステップを指定する
  //第一引数:回転ステップ
  //moveTo(step);
  
  //指定したステップ回転させる
  //
  //run();
  
  //回転中かどうか
  //
  //distanceToGo()

  //ステッピングモータの回転
  if(stepperR.distanceToGo() != 0)
    stepperR.run();
  else{
    move_finished=1;

    //20秒ごとにTUKTUKさせる
    if(reverse_motor == 1){
      reverse_motor = 0;
      stepperR.moveTo(general_step);
      move_finished=0;
    }
  }
    
  if(stepperL.distanceToGo() != 0)
    stepperL.run();
  else{
    move_finished=1;

    //20秒ごとにTUKTUKさせる
    if(reverse_motor == 1){
      reverse_motor = 0;
      stepperL.moveTo(general_step);
      move_finished=0;
    }
  }

  //20秒ごとにTUKTUKさせる
  interval<20000>::run([]{
    stepperL.moveTo(-general_step);
    stepperR.moveTo(general_step);
    move_finished=0;
    reverse_motor = 1;
  });
  
}
