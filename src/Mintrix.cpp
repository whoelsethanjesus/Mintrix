/* * * * * * * * * * * * * * * * * * * *
 *                                     *
 *            M I N T R I X            *
 *           by Janik Heiler           *
 *                                     *
 * * * * * * * * * * * * * * * * * * * */

#include "Mintrix.h"

// create mintrix instance
CMintrix Mintrix;

// initiate webserver and fastled
CMintrix::CMintrix() : server(80)
{
	// initiate fastled things
	FastLED.addLeds<WS2812B, 2, GRB>(leds, 81);
	FastLED.setBrightness(100);
	FastLED.setCorrection(UncorrectedColor);
	FastLED.setTemperature(UncorrectedTemperature);
	FastLED.clear();
	FastLED.show();
}

void CMintrix::staticWiFi(String wifi_ssid, String wifi_pswd)
{
	WiFi.mode(WIFI_AP);
	WiFi.softAPConfig(IPAddress(10, 10, 10, 1), IPAddress(10, 10, 10, 1), IPAddress(255, 255, 255, 0));

	wifi_pswd = (wifi_pswd.length() >= 8) ? wifi_pswd : "";
	_wifi_ssid_ = wifi_ssid;
	_wifi_pswd_ = wifi_pswd;
	if(_wifi_pswd_ == "")  WiFi.softAP(_wifi_ssid_);
	else                   WiFi.softAP(_wifi_ssid_, _wifi_pswd_);
}

void CMintrix::dynamicWiFi_start(String wifi_pswd)
{
	_wifi_pswd_ = (wifi_pswd.length() >= 8) ? wifi_pswd : "";
	WiFi.scanNetworks(true); // true makes it an async scan
}

int CMintrix::dynamicWiFi_state()
{
	if(_mintrix_id_ > -1)
		return _mintrix_id_;
	
	int wifi_scanComplete = WiFi.scanComplete();
	if(wifi_scanComplete < 0)
		return wifi_scanComplete; // -1: still searching, -2: hasnt started yet

	bool _has_id_ = false;
	while(!_has_id_) {
		_has_id_ = true;
		_mintrix_id_ ++;

		for(int i = 0; i < wifi_scanComplete; i++)
			if(WiFi.SSID(i) == (String)"Mintrix Nr. " + ((_mintrix_id_ < 10) ? "0" : "") + (String)_mintrix_id_)
				_has_id_ = false;
	}

	_wifi_ssid_ = (String)"Mintrix Nr. " + ((_mintrix_id_ < 10) ? "0" : "") + (String)_mintrix_id_;
	if(_wifi_pswd_ == "") WiFi.softAP(_wifi_ssid_);
	else                  WiFi.softAP(_wifi_ssid_, _wifi_pswd_);
	
	return _mintrix_id_;
}

void CMintrix::webStart()
{
	_dns_server_.start(53, "home.mintrix", IPAddress(10, 10, 10, 1));
	
	server.onNotFound([](){Mintrix.server.send(404);});
	server.begin();
}

void CMintrix::webPage(MintrixWeb::WebPage web_page)
{
	page_html = (char*)(web_page.page_html);
	style_css = (char*)(web_page.style_css);
	script_js = (char*)(web_page.script_js);

	server.on("/",          [](){Mintrix.server.send(200, "text/html",       Mintrix.page_html);});
	server.on("/style.css", [](){Mintrix.server.send(200, "text/css",        Mintrix.style_css);});
	server.on("/script.js", [](){Mintrix.server.send(200, "text/javascript", Mintrix.script_js);});
}
