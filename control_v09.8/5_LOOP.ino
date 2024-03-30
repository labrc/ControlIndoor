void loop() {

  // Aveces no carga bien la configuracion, a los 10seg carga otra vez.
  if (started) {
    if (millis() > 10000) {
      leeMemoria = 8;
      started = false;
      DLMin = t;
      DLMax = t;

      float DLAval[] = { 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25 };
      float DLBval[] = { 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28 };
      float DLCval[] = { 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25 };

          for (int i = 0; i <= 11; i++) {
              DLBval[i] = t;
          }
          
          for (int i = 0; i <= 11; i++) {
              DLAval[i] = t;
          }
          
      }


    }
  

  //////////Set HORA//////////
  if (millis() > milismenu + 200) {

    milismenu = millis();
    minuto = (RTC.getMinute());
    if (minuto > 61) (minuto = 0);
    horaSis = (RTC.getHour(h12Flag, pmFlag));
    //  if (horaSis > 24) (horaSis = 0);
    segundo = (RTC.getSecond());
    if (segundo > 61) (segundo = 0);

    systemp = (RTC.getTemperature());
    if (systemp > 61) (systemp = 0);
  }
  ///////////////////////////////

  /////////////////////////////////dht///////////////////////////////

  currentMillisdht = millis();
  milsto = currentMillisdht / 1000;
  milsto2 = milsto / 60;
  
  if (currentMillisdht - previousMillisdht >= interval) {
    // save the last time you updated the DHT values
    previousMillisdht = millis();
    // Read temperature as Celsius (the default)
    float newT = dht.readTemperature();

    Serial.print("Temperatura: ");
    if (isnan(newT)) {
       Serial.print("falló");
    }
    else {
      t = newT;
     
      Serial.print(t);
    }
    Serial.print("  ");
    // Read Humidity
    float newH = dht.readHumidity();
    // if humidity read failed, don't change h value
    Serial.println("Humedad: ");

    if (isnan(newH)) {
      Serial.println("falló") ;
    }
    else {

      h = newH;

      Serial.println(h);
    }
    ///////////DHT a Datalogg////////

    if (t > DLMax) (DLMax = t);
    if (t < DLMin) (DLMin = t);
  
  }

  if (segundo == 0 || segundo == 20 || segundo == 40) {
    DataLogger();

  }

  //////////////////rtc a ciclo////////////////

  RTCaCiclo();

  //// Manejo de Memoria///
  LeerMemoria();
  storememory();

  if (horaSis == 1) {
    engagestorememory = true;
  }

  if (engagestorememory) {
    if (horaSis == 2) {
      CO = 8;
    }
    engagestorememory = false;
  }

  //////////////////dimmer//////////////////////

  extractor2();


  ArduinoOTA.handle();

}
