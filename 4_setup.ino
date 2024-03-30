void setup() {
  engagestorememory = false;
  started = true;
  dostore = false;
  Humedadmaxima = 60;
  extON = true;

  Serial.begin(115200);
  ArduinoOTA.setHostname("Control");

  pinMode(_luz, OUTPUT);              //  Luz
  pinMode(_ext, OUTPUT);              //  Extractor
  pinMode(_SDA, INPUT_PULLUP);        //  SDA
  pinMode(_SCL, INPUT_PULLUP);        //  SCL


  pinMode(_ven, OUTPUT);              //  Ventilador
 //pinMode(_zcro, INPUT);              //  ZCross
  pinMode(_hig, INPUT);               //  Higrometro

  //dimmer.begin(NORMAL_MODE, ON);

 
  ////////////////  Wire i2C////////////////
   Wire.begin(22,21); // Start the I2C
  ////////////////////////////////////MeMORIA
  minuto = (RTC.getMinute());
  hora = (RTC.getHour(h12Flag, pmFlag));

  RTCaCiclo();



  ///////////////////////////////// Recuperamos config de memoria ////////////////////////////

  leeMemoria = 8;

  if (Humedadmaxima > 101) (Humedadmaxima = 50);

  ///////
  //  Configurador de RTC, si es necesario correr una vez
  //
  // RTC.setClockMode(false);
  //////
  //////
 //        RTC.setMonth(4);
 //        RTC.setDate(4);
 //        RTC.setHour(21);
 //        RTC.setMinute(17);
 //        RTC.setSecond(0);
  // #define DS3231_I2C_ADDRESS 0x68             // 0x68 is the RTC address
  //  Wire.begin();
  //  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  //  Wire.write(0xE);                            // Address the Control Register
  //  Wire.write(0x00100100);                           // Write 0x0 to control Register
  //  Wire.endTransmission();
  //  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  //  Wire.write(0xF);                            // Address the Status register
  //  Wire.write(0x00);                           // Write 0x0 to Status Register
  //  Wire.endTransmission();
  //
  //
  //
 dht.begin();
  ///////////////////WEBSERVER////////////////
 
  WiFi.mode(WIFI_STA);
  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(STASSID, STAPSK);
  WiFi.softAP("Control", STAPSK);
  Serial.println("");
  // Connect to Wi-Fi
  Serial.println("Connecting to WiFi");
  for (wifitimeout = 0; wifitimeout <= 300; wifitimeout++) {
    //Serial.println(WiFi.status());
    delay(50);
    if (WiFi.status() == WL_CONNECTED) (wifitimeout = 400);
  }
  wifitimeout = 0;


  Serial.println(WiFi.getAutoConnect());
  Serial.println(WiFi.localIP());

  // Change OTA port.
  // Default: 8266
  // ArduinoOTA.setPort(8266);

  // Re-programming passowrd.
  // No password by default.
  // ArduinoOTA.setPassword("123");

  ArduinoOTA.begin();


  // Route for root / web page
  server.on("/config.html", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", config_html, processor);
  });
  server.on("/configh.html", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", config2_html, processor);
  });
  server.on("/about.html", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", about_html, processor);
  });
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/charts.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/js", charts_js, processor);
  });
  server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html, processor);
  });
   server.on("/curl.html", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", curl_html, processor);
  });
     server.on("/curl", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", curl_html, processor);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", String(t).c_str());
  });
  server.on("/horario", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", String(horaSis).c_str());
  });
  server.on("/minurio", HTTP_GET, [](AsyncWebServerRequest * request) {
    String Minuto = "";
    if (minuto < 10) {
      Minuto = "0";
    }
    Minuto = Minuto + minuto;

    request->send_P(200, "text/plain", String(Minuto).c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", String(h).c_str());
  });
  server.on("/power", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", String(pwrtmp).c_str());
    if (pwr == 100) {

      request->send_P(200, "text/plain", "ON");
    }
    if (pwr == 0) {
      request->send_P(200, "text/plain", "OFF");
    }

  });
  server.on("/systemp", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", String(systemp).c_str());
  });
  server.on("/ventilador", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", String(ISFAN).c_str());

  });
  server.on("/modetemp", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", String(modetemp).c_str());

  });
  server.on("/invert", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", String(invert).c_str());

  });
  server.on("/guardar", HTTP_GET, [] (AsyncWebServerRequest * request) {
    CO = 8;
    request->send(200, "text/plain", "OK");
  });
  server.on("/cargar", HTTP_GET, [] (AsyncWebServerRequest * request) {
    leeMemoria = 8;

    request->send(200, "text/plain", "OK");
  });
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String inputMessage1;
    String inputMessage2;
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      if (inputMessage1 == "vent") {
        ISFAN = !ISFAN;

      }
      if (inputMessage1 == "invert") {
        invert = !invert;

      }
      if (inputMessage1 == "modet") {
        modetemp = !modetemp;
      }
    }
    else {
      inputMessage1 = "No message sent";
      inputMessage2 = "No message sent";
    }
    request->send(200, "text/plain", "OK");
  });

  server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String inputMessage;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      sliderValue = inputMessage;
      Ciclo = sliderValue.toInt();
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", String(Ciclo).c_str());
  });
  server.on("/slidersol", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String inputMessage;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      sliderValue = inputMessage;
      offset = sliderValue.toInt();
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", String(offset).c_str());
  });

  server.on("/slidermax", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String inputMessage;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      sliderValue = inputMessage;
      ramp4 = sliderValue.toFloat();
    }
    else {
      inputMessage = "No message sent";
    }
    request->send(200, "text/plain", String(ramp4).c_str());
  });

  server.on("/sliderhum", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String inputMessage;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      sliderValue = inputMessage;
      Humedadmaxima = sliderValue.toInt();
    }
    else {
      inputMessage = "No message sent";
    }
    request->send(200, "text/plain", String(Humedadmaxima).c_str());
  });

  server.on("/slidermin", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String inputMessage;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      sliderValue = inputMessage;
      ramp2 = sliderValue.toFloat();
    }
    else {
      inputMessage = "No message sent";
    }
    request->send(200, "text/plain", String(ramp2).c_str());
  });


  // Start server
  server.begin();
 //ThingSpeak.begin(cliente);
  /////////
  /// Datalogger init ///
  DLMin = 26;
  DLMax = 26;
 /* ThingSpeak.begin(cliente); */
  modetemp = false;
}