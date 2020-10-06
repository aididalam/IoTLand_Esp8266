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
int buttonGroupID=2;
IoTLand iotland(apikey); //Initializing Library with api key




//************************************************************************

//Veriables for reading data from Server
int light; //Light will store the value 
String key="light"; //key will feach the value from buttonGroup

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
   * Button function need Two parameter
   * 
   * First parameter is Button Id. It is a Integer Type parameter. You can get Button Group Id from your IoTLand control Panel
   * Pass buttonGroupID as a Integer.
   * 
   * Second Parameter is Button key. It is a String data.You can get Button key name from your IoT Control Panel
   * Pass it as a String data type
   * 
   * *************************** Funtion Return ***************************
   * This function is a Integer function.So if data successfully featched from the server then you will get Button's value from the function.If any thing goes wrong you will get -1.
   * If you get -1 then please open serial monitor and check the error message.
   */
  
  int light=iotland.button(buttonGroupID,key) ; //Storing function's retun value in Light variable
 
  Serial.println(light); // Checking the retun value via serial monitor
  delay(60000);

}
