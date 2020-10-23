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
int alertID=2;
IoTLand iotland(apikey); //Initializing Library with api key


//************************************************************************


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



}

void loop() {

  /**
   * Before Start make sure You are connecting to a Working Wifi Network
   * 
   * ***********************************************************************
   * Alert function need One parameter
   * 
   * The parameter is Alert Id. It is a Integer Type parameter. You can get Alert Id from your IoTLand control Panel.Pass alertID as a Integer.
   
   * 
   * *************************** Funtion Return ***************************
   * This function is a boolean function.So if data successfully send to the server then you will get 1.If any thing goes wrong you will get 0.
   * If you get 0 then please open serial monitor and check the error message.
   * 
   
   * 
   */


  
 
  Serial.println(iotland.alert( alertID)); // posting and Checking the retun value via serial monitor. You can also save this value in a bool variable
  delay(60000);

}
