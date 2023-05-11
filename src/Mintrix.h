/* * * * * * * * * * * * * * * *
 * Mintrix              v1.0.2 *
 *                             *
 *                Janik Heiler *
 * GitHub:   @whoelsethanjesus *
 * * * * * * * * * * * * * * * */

// prevents multiple inclusion
#ifndef MINTRIX_H
#define MINTRIX_H

#define MINTRIX_LIBRARY_VERSION "v1.0.2"

#if !defined(ESP8266)
  #error Please install the ESP8266 board!
// http://arduino.esp8266.com/stable/package_esp8266com_index.json
#endif

// include all necessary libraries
#include "Arduino.h"           // standard arduino/esp things
#include "DNSServer.h"         // dns server -> "mintrix.home"
#include "ESP8266WebServer.h"  // web server
#include "ESP8266WiFi.h"       // wifi module
#include "FastLED.h"           // led controller
#include "WiFiClient.h"        // other wifi stuff

// definition of web page type
namespace MintrixWeb {
	typedef struct {
		const char * page_html;
		const char * style_css;
		const char * script_js;
	} WebPage;
}


// mintrix class
class CMintrix
{
	private:
		DNSServer _dns_server_;

		int _mintrix_id_ = -1;
		String _wifi_ssid_ = "";
		String _wifi_pswd_ = "";

	public:
		// pysical properties
	    const int num_leds = 81;
		const int width = 9;
		const int height = 9;

		// access leds via .leds[] or []
		CRGB  leds[81];
		CRGB& operator[](unsigned int i){return leds[i];}

		// some led operations
		void show()  {FastLED.show();}
		void clear() {FastLED.clear();}

		// web server and web page
		ESP8266WebServer server;
		char * page_html = "";
		char * style_css = "";
		char * script_js = "";

		CMintrix();

		// things that ought to be looped
		void loop() {_dns_server_.processNextRequest(); server.handleClient();};

		// methods for opening wifi
		void staticWiFi(String wifi_ssid, String wifi_pswd = "");
		void dynamicWiFi_start(String wifi_pswd = "");
		int  dynamicWiFi_state();

		// start web handling and (opt.) set website
		void webStart();
		void webPage(MintrixWeb::WebPage web_page);

		// handle incoming data from web
		void onData(void (*data_handler)());

		// access incoming data from web
		String uri()                    {return server.uri();       };
		String arg(const char *name)    {return server.arg(name);   };
		String arg(int i)               {return server.arg(i);      };
		String argName(int i)           {return server.argName(i);  };
		int    args()                   {return server.args();      };
		bool   hasArg(const char *name) {return server.hasArg(name);};

		// send response to incoming data from web
		void send(int code, const char*    content_type = NULL, const String & content = String("")) {server.send(code, content_type, content);};
		void send(int code, char*          content_type,        const String & content)              {server.send(code, content_type, content);};
		void send(int code, const String & content_type,        const String & content)              {server.send(code, content_type, content);};
};

// makes the program aware of an externally declared class instance
extern CMintrix Mintrix;

#endif
