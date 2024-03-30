void storememory() {

  switch (CO)
  {
    default: {
        CO = 8;
      }
      break;
    case 0:
      break;
    // Memoria bollean ISFAN
    case 8: {
        if (ISFAN) (EepromRTC.write(65, 1));
        else {
          EepromRTC.write(65, 0);
        }
        Serial.print("_ISFAN ");
        Serial.println(ISFAN);
        Serial.print("_ISFAN ");
        Serial.println(_ISFAN);

        CO = CO + 9;
      }
      break;
    // memoria valor Ciclo solar
    case 7: {
        _Ciclo = EepromRTC.read(70); //Ciclo
        if (_Ciclo != Ciclo) {
          EepromRTC.write(70, Ciclo);  //Ciclo
        }
        CO = CO + 9;
      }
      break;
    //Memoria rampa2
    case 6: {
        float Mramp2 = (EepromRTC.readFloat(160), DEC);
        if (Mramp2 != ramp2) (EepromRTC.writeFloat(160, ramp2));
        CO = CO + 9;
      }
      break;
    //Memoria rampa4
    case 5: {
        float Mramp4 = (EepromRTC.readFloat(150), DEC);
        if (Mramp4 != ramp4) (EepromRTC.writeFloat(150, ramp4));
        CO = CO + 9;
      }
      break;

    //memoria  Humedad Maxima
    case 4: {
        _Humedadmaxima = Humedadmaxima;

        EepromRTC.write(30, _Humedadmaxima);
        //  _Humedadmaxima = (EepromRTC.read(140));
        Serial.print("Humedamaxima ");
        Serial.println(Humedadmaxima);

        Serial.print("_Humedamaxima ");
        Serial.println(_Humedadmaxima);
        CO = CO + 9;
      }
      break;
    //Memoria switch control por temperatura
    case 3: {
        //
        //      void write(unsigned int address, byte data);
        //byte read(unsigned int address);
        _modetemp = (EepromRTC.read(130));
        if (modetemp) (MDtemp = 1);
        if (!modetemp) (MDtemp = 0);

        if (MDtemp == 1) (EepromRTC.write(130, 1));
        if (MDtemp == 0) (EepromRTC.write(130, 0));
        //if ((_modetemp,DEC) > 1) (EepromRTC.writeFloat(130, 1));
        CO = CO + 9;
      }
      break;
    //memoria ciclo nocturno
    case 2: {


        _invert = (EepromRTC.read(25));

        if (!invert) (EepromRTC.write(25, 0));
        if (invert) (EepromRTC.write(25, 1));
        // if (_invert > 1) (EepromRTC.write(55, 1));
        CO = CO + 9;
        Serial.print("_invert ");
        Serial.println(_invert);
        Serial.print("invert ");
        Serial.println(invert);
      }
      break;
    //memoria offset de ciclo
    case 1: {
        _offset =  (EepromRTC.readFloat(110), DEC);
        int MEMoffset = _offset - 20;
        if (MEMoffset != offset) {
          _offset = offset + 20;
          (EepromRTC.writeFloat(110, (_offset)));
        }
        CO = CO + 9;
      }
      break;
    case 17: {
        CO = CO - 10;
      }
      break;
    case 16: {
        CO = CO - 10;
      }
      break;
    case 15: {
        CO = CO - 10;
      }
      break;
    case 14: {
        CO = CO - 10;
      }
      break;
    case 13: {
        CO = CO - 10;
      }
      break;
    case 12: {
        CO = CO - 10;
      }
      break;
    case 11: {
        CO = CO - 10;
      }
      break;
    case 10: {
        CO = CO - 10;
      }
      break;
  }
}
void LeerMemoria() {
  switch (leeMemoria)
  {
    default: {
        leeMemoria = 0;
      }
      break;
    case 0:
      break;
    // Memoria bollean ISFAN
    case 8: {
        Serial.print("_ISFAN ");
        Serial.println(_ISFAN);
        Serial.print("ISFAN ");
        Serial.println(ISFAN);
        _ISFAN = EepromRTC.read(65);

        if (_ISFAN == 1) (ISFAN = true);
        if (_ISFAN == 0) (ISFAN = false);

        leeMemoria = leeMemoria + 9 ;
      }
      break;
    // memoria valor Ciclo solar
    case 7: {

        _Ciclo = EepromRTC.read(70);  //Ciclo
        Ciclo = _Ciclo;  //Ciclo
        //if (Ciclo > 24) (Ciclo = 16);
        leeMemoria = leeMemoria + 9;
      }
      break;
    //Memoria rampa2
    case 6: {
        ramp2 = EepromRTC.readFloat(160), DEC;

        leeMemoria = leeMemoria + 9;
      }
      break;
    //Memoria rampa4
    case 5: {
        ramp4 = EepromRTC.readFloat(150), DEC;
        leeMemoria = leeMemoria + 9;
      }
      break;
    //memoria  Humedad Maxima
    case 4: {
        // Humedadmaxima = 0;

        _Humedadmaxima = EepromRTC.read(30); //Humedad Maxima
        Humedadmaxima = _Humedadmaxima;

        Serial.print("Humedamaxima ");
        Serial.println(Humedadmaxima);

        Serial.print("_Humedamaxima ");
        Serial.println(_Humedadmaxima);
        if (Humedadmaxima > 100) (Humedadmaxima = 25);
        leeMemoria = leeMemoria + 9;
      }
      break;

    //Memoria switch control por temperatura
    case 3: {
        _modetemp = EepromRTC.read(130);
        if (_modetemp == 1) (modetemp = true);
        if (_modetemp == 0) (modetemp = false);
        leeMemoria = leeMemoria + 9;
      }
      break;
    //memoria ciclo nocturno
    case 2: {

        _invert = EepromRTC.read(25);

        if (_invert == 1) (invert = true);
        if (_invert == 0) (invert = false);

        leeMemoria = leeMemoria + 9;
        Serial.print("_invert ");
        Serial.println(_invert);
        Serial.print("invert ");
        Serial.println(invert);
      }
      break;
    //memoria offset de ciclo
    case 1: {
        _offset = EepromRTC.readFloat(110), DEC;
        offset = _offset - 20;
        if (offset == 6) {
        _offset = EepromRTC.readFloat(110), DEC;
        offset = _offset - 20; 
        }
        leeMemoria = leeMemoria + 9;

        if (offset > 20) (offset = 0);
      }
      break;


    case 17: {
        leeMemoria = leeMemoria - 10;
      }
      break;
    case 16: {
        leeMemoria = leeMemoria - 10;
      }
      break;
    case 15: {
        leeMemoria = leeMemoria - 10;
      }
      break;
    case 14: {
        leeMemoria = leeMemoria - 10;
      }
      break;
    case 13: {
        leeMemoria = leeMemoria - 10;
      }
      break;
    case 12: {
        leeMemoria = leeMemoria - 10;
      }
      break;
    case 11: {
        leeMemoria = leeMemoria - 10;
      }
      break;
    case 10: {
        leeMemoria = leeMemoria - 10;
      }
      break;

  }
}


///// Extractor dimmerizable para Triacs con libreria ///// 
//void extractor1() {
//  //T a PWR
//  if (modetemp) {
//    if (t >= ramp2) {
//      isExt = 1;
//      if (t <= ramp4) {
//        extPWM = map((t * 10), (ramp2 * 10), (ramp4 * 10), (ramp1 * 10), (ramp3 * 10));
//        extPWM = pwrtmp / 10;
//        if (extPWM < minimoextractor) (extPWM = minimoextractor);
//        pwr = map(pwrtmp, 0, 100, 0, 100);
//
//      }
//
//      if (t >= ramp4) {
//        pwr = ramp3;
//        extPWM = ramp3;
//      }
//    }
//    else {
//      isExt = 0;
//      pwr = 0;
//      extPWM = 0;
//    pwrtmp = "Off";
//    }
//  }
//  else
//  {
//    pwr = 0;
//    extPWM = 0;
//    pwrtmp = "Off";
//    isExt = 0;
//  }
//
///  if (h >= Humedadmaxima) {
///    isExt = 1;
//    pwr = 100;
//    extPWM = 100;
//    pwrtmp = String(extPWM);
////  }
////
////  if (isExt) {
////    if (pwr == 100) {
////      digitalWrite(_ext, HIGH);                             ////////////////REESCRIBIR
////      extPWM = 100;
////     pwrtmp = String(extPWM);
////    }
////    if (pwr != 100) {
////      digitalWrite(_ext, LOW);
////      extPWM = 0;
 //// pwrtmp = "Off";
////    }
////  }
////  else {
////    digitalWrite(_ext, LOW) ;
////    pwrtmp = "Off";
////  }
////
//}

///////////////// Extractor ON/OFF para Triac/Reles ///// 

void extractor2() {

if (extON) {
  
  if (t >= ramp4) {
    isExt = 1;
    ext_timer = millis();
  }
  if ((t <= ramp2) && ((ext_timer + interval + interval) < millis())) (isExt = 0);
  
  if (modetemp == false) {
    isExt = 0;
  }
  
  if (h >= Humedadmaxima) (isExt = 1);

}

else {
  isExt = 0;
  }

  if (isExt) {

    digitalWrite(_ext, HIGH);
     pwrtmp = "On";
  }
  else {
     digitalWrite(_ext, LOW);
     pwrtmp = "Off";
  }

if (t > 30) (pwrtmp = String(pwrtmp+" ALERTA"));

}



void RTCaCiclo() {
  hora = horaSis + offset;
  if (invert) (hora = hora + 12);
  if (hora < 0)  (hora += 24);
  if (hora > 24) (hora -= 24);

  //////////////////rtc a ciclo////////////////
  if (Ciclo > 24 ) (Ciclo = 16);
  if (Ciclo % 2 == 0) {

    if (Ciclo == 24) {
      luzprendida = true;
      ventiladorprendido = true;
 
    }
    if (Ciclo <= 0) {
      luzprendida = false;
      ventiladorprendido = false;
    }

    if (hora >= (13 - (Ciclo / 2))) {
      if    (hora < (13 + (Ciclo / 2))) {
        luzprendida = true;
        ventiladorprendido = true;
      }
      else
      {
        luzprendida = false;
        ventiladorprendido = false;
      }
    }
    else
    {
      luzprendida = false;
      ventiladorprendido = false;
    }
  }

  else {
    if (hora >= (13 - ((Ciclo + 1) / 2))) {
      if    (hora < (13 + ((Ciclo - 1) / 2))) {
        luzprendida = true;
        ventiladorprendido = true;
      }
      else
      {
        luzprendida = false;
        ventiladorprendido = false;
      }
    }
    else
    {
      luzprendida = false;
      ventiladorprendido = false;
    }

  }

  if (hora == (13 + (Ciclo / 2))) {
    if (minuto < fan) (ventiladorprendido = true);
    else {
      ventiladorprendido = false;
    }

  }

  if (ISFAN) {
    if (ventiladorprendido) {
      digitalWrite(_ven, HIGH);
    }
    else {
      digitalWrite(_ven, LOW);
    }
  }
  else {
    digitalWrite(_ven, LOW);
  }

  if (luzprendida) {
    digitalWrite(_luz, HIGH);
    Icono =  "cccc00";
  }
  else {
    digitalWrite(_luz, LOW);
    Icono =  "0000cc";
  }


}
void DataLogger() {
  int ahoramilis = millis();

  if ((ahoramilis > DLA + DLTA)) {
    DLA = millis();
    for (int i = 0; i <= 18; i++) {
      DLCval[i] = DLCval[i + 1];
    }
    DLCval[19] = t;

  }
  if (minuto == 58) (DLB = 1);
  if ((minuto == 0) && (DLB == 1)) {
    DLB = 0;
    for (int i = 0; i <= 10; i++) {
      DLBval[i] = DLBval[i + 1];
    }
    DLBval[11] = DLMax;
    DLMax = t;

    for (int i = 0; i <= 10; i++) {
      DLAval[i] = DLAval[i + 1] ;
    }
    DLAval[11] = DLMin;
    DLMin = t;
  }

}

/* void httpRequest(float field1Data, float field2Data, bool field3Data, bool field4Data) {
  ThingSpeak.setField(1, field1Data);
  ThingSpeak.setField(2, field2Data);
  ThingSpeak.setField(3, field3Data);
  ThingSpeak.setField(4, field4Data);
  int response = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(response == 200){
    estadoserver = String (" OK, 200");
  }
  else{
   estadoserver = String (" Problem updating channel. HTTP error code " + String(response));
  }
  

} */
