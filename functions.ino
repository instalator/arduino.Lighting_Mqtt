//--------------------------------- Functions ---------------------------------//
/////////////////////////////////От Брокера//////////////////////////////////////////////
void callback_iobroker(String strTopic, String strPayload){
  if (strTopic == "myhome/Lighting/BathRoom_Main") {
    if (strPayload == "0"){
      digitalWrite(33, 0);
      delay(pause);
      client.publish("myhome/Lighting/BathRoom_Main", "0");
    }
    else if (strPayload == "1") {
      digitalWrite(33, 1);
      delay(pause);
      client.publish("myhome/Lighting/BathRoom_Main", "1");
    }
  } 
  //////////////////////////
  if (strTopic == "myhome/Lighting/BedRoom_Main") {
    if (strPayload == "0") {
      digitalWrite(23, 0);
      delay(pause);
      client.publish("myhome/Lighting/BedRoom_Main", "0");
    }
    else if (strPayload == "1") {
      digitalWrite(23, 1);
      delay(pause);
      client.publish("myhome/Lighting/BedRoom_Main", "1");
    }
  } 
  ////////////////////////
  if (strTopic == "myhome/Lighting/BedRoom_Additional") {
    if (strPayload == "0") {
      digitalWrite(25, 0);
      delay(pause);
      client.publish("myhome/Lighting/BedRoom_Additional", "0");
    }
    else if (strPayload == "1") {
      digitalWrite(25, 1);
      delay(pause);
      client.publish("myhome/Lighting/BedRoom_Additional", "1");
    }
  } 
  ///////////////////////
  if (strTopic == "myhome/Lighting/Kitchen_Main") {
    if (strPayload == "0") {
      digitalWrite(31, 0);
      delay(pause);
      client.publish("myhome/Lighting/Kitchen_Main", "0");
    }
    else if (strPayload == "1") {
      digitalWrite(31, 1);
      delay(pause);
      client.publish("myhome/Lighting/Kitchen_Main", "1");
    }
  } 
  ///////////////////////
  if (strTopic == "myhome/Lighting/Kitchen_Additional") {
    if (strPayload == "0") {
      digitalWrite(35, 0);
      delay(pause);
      client.publish("myhome/Lighting/Kitchen_Additional", "0");
    }
    else if (strPayload == "1") {
      digitalWrite(35, 1);
      delay(pause);
      client.publish("myhome/Lighting/Kitchen_Additional", "1");
    }
  } 
  //////////////////////
  if (strTopic == "myhome/Lighting/Hall_Main") {
    if (strPayload == "0") {
      digitalWrite(37, 0);
      delay(pause);
      client.publish("myhome/Lighting/Hall_Main", "0");
    }
    else if (strPayload == "1") {
      digitalWrite(37, 1);
      delay(pause);
      client.publish("myhome/Lighting/Hall_Main", "1");
    }
  } 
  ///////////////////////
  if (strTopic == "myhome/Lighting/GuestRoom_Main") {
    if (strPayload == "0") {
      digitalWrite(27, 0);
      delay(pause);
      client.publish("myhome/Lighting/GuestRoom_Main", "0");
    }
    else if (strPayload == "1") {
      digitalWrite(27, 1);
      delay(pause);
      client.publish("myhome/Lighting/GuestRoom_Main", "1");
    }
  } 
  /////////////////////
  if (strTopic == "myhome/Lighting/GuestRoom_Additional") {
    if (strPayload == "0") {
      digitalWrite(29, 0);
      delay(pause);
      client.publish("myhome/Lighting/GuestRoom_Additional", "0");
    }
    else if (strPayload == "1") {
      digitalWrite(29, 1);
      delay(pause);
      client.publish("myhome/Lighting/GuestRoom_Additional", "1");
    }
  } 
    /////////////////////
  if (strTopic == "myhome/Bathroom/Ventilator") {
    if (strPayload == "0") {
      digitalWrite(49, 0);
      delay(pause);
      client.publish("myhome/Bathroom/Ventilator", "0");
    }
    else if (strPayload == "1") {
      digitalWrite(49, 1);
      delay(pause);
      client.publish("myhome/Bathroom/Ventilator", "1");
    }
  } 
  ///////////////////
    if (strTopic == "myhome/Lighting/All_OFF") {
      if (strPayload == "1") {
        for(int i=0 ;i<=n_DO_pin; i++) { digitalWrite (start_DO_pin [i], LOW); }
        delay(pause);
        client.publish("myhome/Lighting/All_OFF", "OK");
        client.publish("myhome/Lighting/BedRoom_Main", "0");
        client.publish("myhome/Lighting/BedRoom_Additional", "0");
        client.publish("myhome/Lighting/GuestRoom_Main", "0");
        client.publish("myhome/Lighting/GuestRoom_Additional", "0");
        client.publish("myhome/Lighting/Kitchen_Main", "0");
        client.publish("myhome/Lighting/Kitchen_Additional", "0");
        client.publish("myhome/Lighting/BathRoom_Main", "0");
        client.publish("myhome/Lighting/BathRoom_Additional", "0");
        client.publish("myhome/Lighting/Hall_Main", "0");
      }
    }
}
////////////////////////////////////Брокеру/////////////////////////////////////
void Button(){
    char b[2]; 
/////////////////////////////////////// Ванная ////////////////////////////
   
    if (digitalRead(22)!= pre1) {     //если произошло событие
      delay(pause);
      digitalWrite(33,!digitalRead(33));//инвертируем состояние пина
      pre1 = digitalRead(22);
      int out1 = digitalRead(33);
      String char_out1 = String(out1);
      char_out1.toCharArray(b,2);
      client.publish("myhome/Lighting/BathRoom_Main", b);
          
          if (digitalRead(33) == HIGH){
             posetitel = 1;
             }
          else if (digitalRead(33) == LOW)
            {
             posetitel = 0;
             }
     }
     else if (digitalRead(53) == 1 && flag == 1){ //Если кто то зашел в ванную то
        delay(50);
        digitalWrite(33, 1);//Включаем свет
        posetitel = 0;
        client.publish("myhome/Lighting/BathRoom_Main", "1");
        flag = 0;
       /* int outq1 = digitalRead(33);
        String char_outq1 = String(outq1);
        char_outq1.toCharArray(b,2);
        
        client.publish("myhome/Lighting/BathRoom_Main", b);*/
        //delay(1000);   
     }
     else if (digitalRead(53) == 0 && posetitel == 0){
        delay(50);
        digitalWrite(33, 0);//Выключам свет
        posetitel = 1;
        flag = 1;
       /* int outw1 = digitalRead(33);
        String char_outw1 = String(outw1);
        char_outw1.toCharArray(b,2);
        delay(1000);
        client.publish("myhome/Lighting/BathRoom_Main", b);*/
        client.publish("myhome/Lighting/BathRoom_Main", "0"); 
      }
/////////////////////////////////////// Спальня 1 ////////////////////////
     if (digitalRead(24)!= pre2) {     //если произошло событие
        delay(pause);
        digitalWrite(23,!digitalRead(23));//инвертируем состояние пина
        int out2 = digitalRead(23);
        String char_out2 = String(out2);
        char_out2.toCharArray(b,2);
        client.publish("myhome/Lighting/BedRoom_Main", b);
        pre2 = digitalRead(24);
     }
////////////////////////////////////// Спальня 2 ////////////////////////////////////
    if (digitalRead(26)!= pre3) {     //если произошло событие
       delay(pause);
       digitalWrite(25,!digitalRead(25));//инвертируем состояние пина
       int out3 = digitalRead(25);
       String char_out3 = String(out3);
       char_out3.toCharArray(b,2);
       client.publish("myhome/Lighting/BedRoom_Additional", b);
       pre3 = digitalRead(26);
     }
///////////////////////////////////////// Кухня 1 //////////////////////////////////////
     if (digitalRead(28)!= pre4) {     //если произошло событие
       delay(pause);
       digitalWrite(31,!digitalRead(31));//инвертируем состояние пина
       int out4 = digitalRead(31);
       String char_out4 = String(out4);
       char_out4.toCharArray(b,2);
       client.publish("myhome/Lighting/Kitchen_Main", b);
       pre4 = digitalRead(28);
     }
///////////////////////////////////////// Кухня 2 //////////////////////////////////////
     if (digitalRead(30)!= pre5) {     //если произошло событие
       delay(pause);
       digitalWrite(35,!digitalRead(35));//инвертируем состояние пина
       int out5 = digitalRead(35);
       String char_out5 = String(out5);
       char_out5.toCharArray(b,2);
       client.publish("myhome/Lighting/Kitchen_Additional", b);
       pre5 = digitalRead(30);
     }
///////////////////////////////////////// Коридор /////////////////////////////////////
     if (digitalRead(32)!= pre6) {     //если произошло событие
       delay(pause);
       digitalWrite(37,!digitalRead(37));//инвертируем состояние пина
       int out6 = digitalRead(37);
       String char_out6 = String(out6);
       char_out6.toCharArray(b,2);
       client.publish("myhome/Lighting/Hall_Main", b);
       pre6 = digitalRead(32);
     }
///////////////////////////////////////// Зал лев 1/////////////////////////////////////
     if (digitalRead(34)!= pre7) {     //если произошло событие
       delay(pause);
       digitalWrite(27,!digitalRead(27));//инвертируем состояние пина
       int out7 = digitalRead(27);
       String char_out7 = String(out7);
       char_out7.toCharArray(b,2);
       client.publish("myhome/Lighting/GuestRoom_Main", b);
       pre7 = digitalRead(34);
     }
///////////////////////////////////////// Зал лев 2 //////////////////////////////////
     if (digitalRead(36)!= pre8) {     //если произошло событие
       delay(pause);
       digitalWrite(29,!digitalRead(29));//инвертируем состояние пина
       int out8 = digitalRead(29);
       String char_out8 = String(out8);
       char_out8.toCharArray(b,2);
       client.publish("myhome/Lighting/GuestRoom_Additional", b);
       pre8 = digitalRead(36);
     }
////////////////////////////////////////// Зал пр 1 /////////////////////////////
     if (digitalRead(38)!= pre9) {     //если произошло событие
       delay(pause);
       digitalWrite(27,!digitalRead(27));//инвертируем состояние пина
       int out9 = digitalRead(27);
       String char_out9 = String(out9);
       char_out9.toCharArray(b,2);
       client.publish("myhome/Lighting/GuestRoom_Main", b);
       pre9 = digitalRead(38);
     }
////////////////////////////////////////// Зал пр 2 ///////////////////////////
     if (digitalRead(40)!= pre10) {     //если произошло событие
       delay(pause);
       digitalWrite(29,!digitalRead(29));//инвертируем состояние пина
       int out10 = digitalRead(29);
       String char_out10 = String(out10);
       char_out10.toCharArray(b,2);
       client.publish("myhome/Lighting/GuestRoom_Additional", b);
       pre10 = digitalRead(40);
     }
  /*   ///////////////////////////// Зал пр 3 //////////////////////////////
     if (digitalRead(42)!= pre11) {     //если произошло событие
        digitalWrite(37,!digitalRead(37));//инвертируем состояние пина
        client.publish("myhome/Lighting/BedRoom_Main", "1");
        pre11 = digitalRead(42);
     }
     ///////////////////////////// Зал лев 3 ///////////////////////////////
     if (digitalRead(44)!= pre12) {     //если произошло событие
        digitalWrite(37,!digitalRead(37));//инвертируем состояние пина
        client.publish("myhome/Lighting/BedRoom_Main", "1");
        pre12 = digitalRead(44);
     }
     ///////////////////////////// Ванная 2 ////////////////////////////////////
     if (digitalRead(46)!= pre13) {     //если произошло событие
        digitalWrite(37,!digitalRead(37));//инвертируем состояние пина
        client.publish("myhome/Lighting/BedRoom_Main", "1");
        pre13 = digitalRead(46);
     }
     ///////////////////////////// Коридор 2 //////////////////////////////
     if (digitalRead(48)!= pre14) {     //если произошло событие
        digitalWrite(37,!digitalRead(37));//инвертируем состояние пина
        client.publish("myhome/Lighting/BedRoom_Main", "1");
        pre14 = digitalRead(48);
     }
     */
}
