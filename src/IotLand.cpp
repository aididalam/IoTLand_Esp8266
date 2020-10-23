#include "IoTLand.h"
#include "Arduino_JSON.h"
#include "SimpleMap.h"
#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"
const String site="https://iotland.net/";
String api;


IoTLand::IoTLand(String apikey) {
  api = apikey;
}

int IoTLand::button(int id,String key){
  SimpleMap<String, String>* myMap;
  myMap = new SimpleMap<String, String>([](String& a, String& b) -> int {
        if (a == b) return 0;

        if (a > b) return 1;

        if (a < b) return -1;
    });
    
  if (WiFi.status() == WL_CONNECTED) {

      String ServerUrl=site+"btn/"+(String)id+"/"+api;
      String ButtonReadings;
      ButtonReadings = httpGETRequest(ServerUrl);
      JSONVar myObject = JSON.parse(ButtonReadings);
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        Serial.println("Please check Api key,Componant Id,wifi connectivity.\nIf everything is ok then contact with IotLand Administer or email to: support@iotland.net.");
      }else{
          JSONVar keys = myObject.keys();
          for (int i = 0; i < keys.length(); i++) {
            JSONVar val = myObject[keys[i]];
            String jsonKey=(const char*)keys[i];
            String jsonValue=(const char*)val;
            myMap->put(jsonKey, jsonValue);
          }
      }
    
      if(myMap->size()>0){
		  
        return (int)myMap->get(key).toInt();
      }else{
        return -1;
      }
  }
}

bool IoTLand::meter(int id, String value){
     
  if (WiFi.status() == WL_CONNECTED) {

      String ServerUrl=site+"imeter/"+(String)id+"/"+api+"?data="+(String)value;
      String MeterData;
      MeterData = httpGETRequest(ServerUrl);
      JSONVar myObject = JSON.parse(MeterData);
	  String jsonKey;
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
		Serial.println("Please check Api key,Componant Id,wifi connectivity.\nIf everything is ok then contact with IotLand Administer or email to: support@iotland.net.");
      }else{
			JSONVar keys = myObject.keys();
			jsonKey=(const char*)keys[0];
			return (String)jsonKey.equals("success");
      }
  }
}

bool IoTLand::card(int id, String value){
     
  if (WiFi.status() == WL_CONNECTED) {

      String ServerUrl=site+"icard/"+(String)id+"/"+api+"?value="+(String)value;
      String MeterData;
      MeterData = httpGETRequest(ServerUrl);
      JSONVar myObject = JSON.parse(MeterData);
	  String jsonKey;
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
		Serial.println("Please check Api key,Componant Id,wifi connectivity.\nIf everything is ok then contact with IotLand Administer or email to: support@iotland.net.");
      }else{
			JSONVar keys = myObject.keys();
			jsonKey=(const char*)keys[0];
			return (String)jsonKey.equals("success");
      }
  }
}

bool IoTLand::tracker(int id, String lat,String lng){
     
  if (WiFi.status() == WL_CONNECTED) {
	  

      String ServerUrl=site+"itracker/"+(String)id+"/"+api+"?lat="+(String)lat+"&long="+lng;

	  
      String TrackerData;
      TrackerData = httpGETRequest(ServerUrl);
      JSONVar myObject = JSON.parse(TrackerData);
	  String jsonKey;
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
		Serial.println("Please check Api key,Componant Id,wifi connectivity.\nIf everything is ok then contact with IotLand Administer or email to: support@iotland.net.");
      }else{
			JSONVar keys = myObject.keys();
			jsonKey=(const char*)keys[0];
			return (String)jsonKey.equals("success");
      }
  }
}

bool IoTLand::graph(int id, String variable[],float value[]){
     
  if (WiFi.status() == WL_CONNECTED) {
	  

      String ServerUrl=site+"igraph/"+(String)id+"/"+api+"?";
		
		for(int i=0; i<2; i++){
			if(variable[i].equals("") || value[i]==NULL){
				break;
			}
			ServerUrl=ServerUrl+variable[i]+"="+(String)value[i]+"&";
		}
		
		
      String GraphData;
      GraphData = httpGETRequest(ServerUrl);
      JSONVar myObject = JSON.parse(GraphData);
	  String jsonKey;
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
		Serial.println("Please check Api key,Componant Id,wifi connectivity.\nIf everything is ok then contact with IotLand Administer or email to: support@iotland.net.");
      }else{
			JSONVar keys = myObject.keys();
			jsonKey=(const char*)keys[0];
			return (String)jsonKey.equals("success");
      }
  }
}


bool IoTLand::email(int id, String msg){
     
  if (WiFi.status() == WL_CONNECTED) {

      String ServerUrl=site+"iemail/"+(String)id+"/"+api;
      String EmailData;
	  String msgdata=(String)"msg="+(String)msg;
      EmailData = httpPOSTRequest(ServerUrl,msgdata);
      JSONVar myObject = JSON.parse(EmailData);
	  String jsonKey;
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
		Serial.println("Please check Api key,Componant Id,wifi connectivity.\nIf everything is ok then contact with IotLand Administer or email to: support@iotland.net.");
      }else{
			JSONVar keys = myObject.keys();
			jsonKey=(const char*)keys[0];
			return (String)jsonKey.equals("success");
      }
  }
}

bool IoTLand::alert(int id){
     
  if (WiFi.status() == WL_CONNECTED) {

      String ServerUrl=site+"ialert/"+(String)id+"/"+api;
      String AlertData;
      AlertData = httpGETRequest(ServerUrl);
      JSONVar myObject = JSON.parse(AlertData);
	  String jsonKey;
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
		Serial.println("Please check Api key,Componant Id,wifi connectivity.\nIf everything is ok then contact with IotLand Administer or email to: support@iotland.net.");
      }else{
			JSONVar keys = myObject.keys();
			jsonKey=(const char*)keys[0];
			return (String)jsonKey.equals("success");
      }
  }
}



String IoTLand::httpGETRequest(String serverName) {
  HTTPClient http;
  WiFiClientSecure client;
  client.setInsecure();
  http.begin(client,serverName);
  http.addHeader("X-Requested-With", "XMLHttpRequest");
  int httpResponseCode = http.GET();
  String payload = "{}"; 
  String error;
  if (httpResponseCode==200) {
    payload = http.getString();
  }else if (httpResponseCode==401) {
    Serial.print("Error Api or Componant Id.\nApi key: ");
    Serial.println(api);
    Serial.println(" Please enter a valid api key and check componant id. ");
  }else if (httpResponseCode==404 || httpResponseCode==406) {
	error = http.getString();
    Serial.println(error);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
	error = http.getString();
    Serial.println(error);
    Serial.println("Please contact with IotLand Administer or email to: support@iotland.net.");
  }
  // Free resources
  http.end();

  return payload;
}



String IoTLand::httpPOSTRequest(String serverName,String data) {
  HTTPClient http;
  WiFiClientSecure client;
  client.setInsecure();
  http.begin(client,serverName);
  // Specify content-type header
	http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  int httpResponseCode = http.POST(data);
  String payload = "{}"; 
  String error;
  if (httpResponseCode==200) {
    payload = http.getString();
  }else if (httpResponseCode==401) {
    Serial.print("Error Api or Componant Id.\nApi key: ");
    Serial.println(api);
    Serial.println(" Please enter a valid api key and check componant id. ");
  }else if (httpResponseCode==404 || httpResponseCode==406) {
	error = http.getString();
    Serial.println(error);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
	error = http.getString();
    Serial.println(error);
    Serial.println("Please contact with IotLand Administer or email to: support@iotland.net.");
  }
  // Free resources
  http.end();

  return payload;
}





