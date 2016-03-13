//--------------------------------- Functions ---------------------------------//
/////////////////////////////////От Брокера//////////////////////////////////////////////
char* ToChar (String intstr){
    intstr.toCharArray(b, 2);
    return b;
  }
String InvertOut(int pin){
    delay(pause);
    digitalWrite(pin, !digitalRead(pin)); //инвертируем состояние пина
    out = String(digitalRead(pin), DEC);
    return out;
}
 
void callback_iobroker(String strTopic, String strPayload) {
  
  if (strTopic == "myhome/Lighting/BathRoom_Main") {
      if (strPayload == "0") {
        posetitel = 0;
        bathswitch = 0;
      }
      digitalWrite(33, strPayload.toInt());
      delay(pause);
      client.publish("myhome/Lighting/BathRoom_Main", ToChar(strPayload));
  }
  //////////////////////////
  else if (strTopic == "myhome/Lighting/BedRoom_Main") {
      digitalWrite(23, strPayload.toInt());
      delay(pause);
      client.publish("myhome/Lighting/BedRoom_Main", ToChar(strPayload));
    }
  ////////////////////////
  else if (strTopic == "myhome/Lighting/BedRoom_Additional") {
      digitalWrite(25, strPayload.toInt());
      delay(pause);
      client.publish("myhome/Lighting/BedRoom_Additional", ToChar(strPayload));
    }
  ///////////////////////
  else if (strTopic == "myhome/Lighting/Kitchen_Main") {
      digitalWrite(31, strPayload.toInt());
      delay(pause);
      client.publish("myhome/Lighting/Kitchen_Main", ToChar(strPayload));
    }
  ///////////////////////
  else if (strTopic == "myhome/Lighting/Kitchen_Additional") {
      digitalWrite(35, strPayload.toInt());
      delay(pause);
      client.publish("myhome/Lighting/Kitchen_Additional", ToChar(strPayload));
    }
  //////////////////////
  else if (strTopic == "myhome/Lighting/Hall_Main") {
      digitalWrite(43, strPayload.toInt());
      delay(pause);
      client.publish("myhome/Lighting/Hall_Main", ToChar(strPayload));
    }
  ///////////////////////
  else if (strTopic == "myhome/Lighting/GuestRoom_Main") {
      digitalWrite(27, strPayload.toInt());
      delay(pause);
      client.publish("myhome/Lighting/GuestRoom_Main", ToChar(strPayload));
    }
    ///////////////////////
  else if (strTopic == "myhome/Lighting/GuestRoom_Main2") {
      digitalWrite(29, strPayload.toInt());
      delay(pause);
      client.publish("myhome/Lighting/GuestRoom_Main2", ToChar(strPayload));
    }
  /////////////////////
  else if (strTopic == "myhome/Lighting/GuestRoom_Additional") {
      digitalWrite(41, strPayload.toInt());
      delay(pause);
      client.publish("myhome/Lighting/GuestRoom_Additional", ToChar(strPayload));
    }
  //////////////////////
   else if (strTopic == "myhome/Lighting/Lock") {
      if (strPayload == "1") {
          Lock = true;
      } else {
         posetitel = 1;
         Lock = false;
        }
      delay(pause);
      client.publish("myhome/Lighting/Lock", ToChar(strPayload));
    }
  /////////////////////
  else if (strTopic == "myhome/Lighting/Cupboard") {
    if (strPayload == "0") {
      analogWrite(6, strPayload.toInt());
     // flag2_Cupboard = 0;
      client.publish("myhome/Lighting/Cupboard", ToChar(strPayload));
    }
    else if (strPayload == "1") {
      analogWrite(6, 255);
    //  flag2_Cupboard = 1;
      client.publish("myhome/Lighting/Cupboard", "1");
    }
  }
  /////////////////////
  else if (strTopic == "myhome/Bathroom/Ventilator") {
      digitalWrite(49, strPayload.toInt());
      delay(pause);
      client.publish("myhome/Bathroom/Ventilator", ToChar(strPayload));
    }
  ///////////////////
  else if (strTopic == "myhome/Lighting/All_OFF") {
    if (strPayload == "1") {
      for (int i = 0 ; i <= n_DO_pin; i++) {
        digitalWrite (start_DO_pin [i], LOW);
      }
      PubTopic();
      client.publish("myhome/Lighting/All_OFF", "OK");
      posetitel = 0;
      bathswitch = 0;
    }
  }
}
////////////////////////////////////Брокеру/////////////////////////////////////
void Button() {
  /////////////////////////////////////// Шкаф ////////////////////////////
 /* if ((digitalRead(4) == 0 || digitalRead(5) == 0) && flag_Cupboard == 0) { //если произошло событие
    for (int i = 0; i <= 255; i++) {
      analogWrite(6, i);
      delay(10);
    }
    client.publish("myhome/Lighting/Cupboard", "1");
    flag_Cupboard == 1;
  }
  if (digitalRead(3) == 1 && digitalRead(4) == 1 && flag_Cupboard == 1) {
    flag_Cupboard == 0;
    analogWrite(6, 0);
    client.publish("myhome/Lighting/Cupboard", "0");
  }*/
  /////////////////////////////////////// Ванная ////////////////////////////
  if (digitalRead(22) != pre1) {    //если произошло событие
    InvertOut(33);
    client.publish("myhome/Lighting/BathRoom_Main", ToChar(out));
    posetitel = digitalRead(33);
    pre1 = digitalRead(22);
    bathswitch = posetitel;
  }
  
    if (digitalRead(2) == 1 && (millis() - previousMillis > 3000)) { //Если кто то зашел в ванную то
      previousMillis = millis();
      if (bathswitch == 1) {
        posetitel = 0;
        bathswitch = 0;
      }
      posetitel++;
      if (posetitel > 0) {
        delay(50);
        digitalWrite(33, 1);//Включаем свет
        if (posetitel > 5) {
          posetitel = 5;
        }
        delay(5);
        client.publish("myhome/Lighting/BathRoom_Main", "1");
      }
    }
    if (digitalRead(3) == 1 && (millis() - previousMillis > 3000) && Lock == false) { //Если кто то вышел из ванной то
      previousMillis = millis();
      posetitel--;
      if (posetitel <= 0) {
        posetitel = 0;
        delay(50);
        digitalWrite(33, 0);//Выключаем свет
        delay(5);
        client.publish("myhome/Lighting/BathRoom_Main", "0");
      }
    }
  /////////////////////////////////////// Спальня 1 ////////////////////////
  if (digitalRead(24) != pre2) {    //если произошло событие
    InvertOut(23);
    client.publish("myhome/Lighting/BedRoom_Main", ToChar(out));
    pre2 = digitalRead(24);
  }
  ////////////////////////////////////// Спальня 2 ////////////////////////////////////
  if (digitalRead(26) != pre3) {    //если произошло событие
    InvertOut(25);
    client.publish("myhome/Lighting/BedRoom_Additional", ToChar(out));
    pre3 = digitalRead(26);
  }
  ///////////////////////////////////////// Кухня 1 //////////////////////////////////////
  if (digitalRead(28) != pre4) {    //если произошло событие
    InvertOut(31);
    client.publish("myhome/Lighting/Kitchen_Main", ToChar(out));
    pre4 = digitalRead(28);
  }
  ///////////////////////////////////////// Кухня 2 //////////////////////////////////////
  if (digitalRead(30) != pre5) {    //если произошло событие
    InvertOut(35);
    client.publish("myhome/Lighting/Kitchen_Additional", ToChar(out));
    pre5 = digitalRead(30);
  }
  ///////////////////////////////////////// Коридор /////////////////////////////////////
  if (digitalRead(32) != pre6) {    //если произошло событие
    InvertOut(43);
    client.publish("myhome/Lighting/Hall_Main", ToChar(out));
    pre6 = digitalRead(32);
  }
  ///////////////////////////////////////// Зал лев 1/////////////////////////////////////
  if (digitalRead(34) != pre7) {    //если произошло событие
    InvertOut(27);
    client.publish("myhome/Lighting/GuestRoom_Main", ToChar(out));
    pre7 = digitalRead(34);
  }
  ///////////////////////////////////////// Зал лев 2 //////////////////////////////////
  if (digitalRead(36) != pre8) {    //если произошло событие
    InvertOut(29);
    client.publish("myhome/Lighting/GuestRoom_Main2", ToChar(out));
    pre8 = digitalRead(36);
  }
 ///////////////////////////////////////// Зал лев 3 //////////////////////////////////
  if (digitalRead(44) != pre12) {    //если произошло событие
    InvertOut(41);
    client.publish("myhome/Lighting/GuestRoom_Additional", ToChar(out));
    pre8 = digitalRead(44);
  }
  ////////////////////////////////////////// Зал пр 1 /////////////////////////////
  if (digitalRead(38) != pre9) {    //если произошло событие
    InvertOut(27);
    client.publish("myhome/Lighting/GuestRoom_Main", ToChar(out));
    pre9 = digitalRead(38);
  }
  ////////////////////////////////////////// Зал пр 2 ///////////////////////////
  if (digitalRead(40) != pre10) {    //если произошло событие
    InvertOut(29);
    client.publish("myhome/Lighting/GuestRoom_Main2", ToChar(out));
    pre10 = digitalRead(40);
  }
  /* ///////////////////////////// Зал лев 3 ///////////////////////////////
     if (digitalRead(43)!= pre12) {     //если произошло событие
        digitalWrite(37,!digitalRead(37));//инвертируем состояние пина
        client.publish("myhome/Lighting/BedRoom_Main", "1");
        pre12 = digitalRead(43);
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

