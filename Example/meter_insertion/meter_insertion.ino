/*
 * This Libary is from IotLand.
 * Documentations: https://iotland.net/doc/nodemcu
 * Author: Aidid Alam
 * Email: aididalam@gmail.com
 *        support@iotland.net
 */


#include <ESP8266WiFi.h>   //Include the wifi libary
#include <IoTLand.h>  //Include IotLand Libary

//Wifi Cardinals
const char* ssid = "wifi_name"; 
const char* password = "wifi_password";



/**************************************************************************
 * Library needs Api key and Componant Id.
 * So login to your IotLand controll panel and get apikey and componant id.
 */


 
String apikey = "75ae1d3ce1ed43043bc23535cf341e45";
int meterID=2;
IoTLand iotland(apikey); //Initializing Library with api key




//************************************************************************

//Variables for reading data from NodeMcu
float data;

void setup() {
  // Serial and Wifi is begining
  Serial.begin(115200);
  WiFi.begin(ssid, password);

 //Wait until nodemcu connected to wifi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.println(WiFi.localIP());// Print the IP addres


  pinMode(A0,INPUT);


}

void loop() {

  /**
   * Before Start make sure You are connecting to a Working Wifi Network
   * 
   * ***********************************************************************
   * Meter function need Two parameter
   * 
   * First parameter is Meter Id. It is a Integer Type parameter. You can get Meter Id from your IoTLand control Panel
   * Pass meterID as a Integer.
   * 
   * Second Parameter is Value of Sensor/Nodemcu Pin. It is a String data.As there are limitations for passing float data to function so you have to cast float data into String.
   * Pass it as a String data type
   * 
   * *************************** Funtion Return ***************************
   * This function is a boolean function.So if data successfully post to the server then you will get 1.If any thing goes wrong you will get 0.
   * If you get 0 then please open serial monitor and check the error message.
   * 
   * ******************** Casting flaot data type into String Data type **************************
   * 
   *      You can use it like this String(56.094325) and you will get 56.09
   *      if you need more decimal number then cast it like this String(56.094325,6) and you will get 56.094325
   *      
   *      In this example we are going with first one
   * 
   */
  
  data=analogRead(A0);

  
 
  Serial.println(iotland.meter( meterID,String(data) )); // posting and Checking the retun value via serial monitor. You can also save this value in a bool variable
  delay(60000);

}
