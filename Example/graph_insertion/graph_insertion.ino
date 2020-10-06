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
int graphId=2;
IoTLand iotland(apikey); //Initializing Library with api key




//************************************************************************

//Veriables for reading data from nodeMcu pins
float pin2;
float pin3;

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

  //Pin mode for reading value
  pinMode(A0,INPUT);
  pinMode(D3,INPUT);

}

void loop() {

  /**
   * Before Start make sure You are connecting to a Working Wifi Network
   * 
   * ***********************************************************************
   * Graph function need there parameter
   * 
   * First parameter is Graph Id. It is a Integer Type parameter. You can get Graph Id from your IoTLand control Panel
   * Pass GraphId as a Integer.
   * 
   * Second Parameter is Graph Variable Name array. It is a String Array.You can get Variables name from your IoT Control Panel
   * Pass it as a String Array
   * 
   * Third parameter is Graph Variable's value array. It is a Float Array. So when you read data from sensors/pins please type cast into float.
   * Pass it as a Float Array
   * 
   * *************************** Funtion Return ***************************
   * This function is a boolean function.So if data successfully post to the server then you will get 1.If any thing goes wrong you will get 0.
   * If you get 0 then please open serial monitor and check the error message.
   */

   
  pin2=(float)analogRead(2);
  pin3=(float)digitalRead(D3);
  
  String variable[]={"RPM", "Voltage"}; //String type Array of Variables names
  float value[]={pin2, pin3}; //Float type Array of Values
  Serial.println(iotland.graph(graphId,variable, value)); // posting and Checking the retun value via serial monitor. You can also save this value in a bool variable
  delay(60000);

}