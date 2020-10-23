#ifndef IoTLand_h
#define IoTLand_h

#include <Arduino.h>

int button(String key);

class IoTLand {
		String api;
	public:
		IoTLand(String apikey);
		int button(int id,String key);
		bool meter(int id,String value);
		bool card(int id,String value);
		bool tracker(int id,String lat,String lng);
		bool graph(int id,String variable[],float value[]);
		bool email(int id,String msg);
		bool alert(int id);
	private:
		String httpGETRequest(String serverName);
		String httpPOSTRequest(String serverName,String data);
		
};

#endif
