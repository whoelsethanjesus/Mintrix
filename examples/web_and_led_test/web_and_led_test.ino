/* * * * * * * * * * * * * *
 * Mintrix by Janik Heiler *
 * * * * * * * * * * * * * */

#include <Mintrix.h>
#include <MintrixWeb.h>

int i = Mintrix.num_leds - 1;
unsigned long t0;

void setup() {
	delay(1000);
	
	while(Mintrix.dynamicWiFi_state() < 0) {
		Mintrix.dynamicWiFi_start();
		delay(50);
	}
	
	Mintrix.webStart();
	Mintrix.webPage(MintrixWeb::HelloWorld);
}

void loop() {
	Mintrix.loop();
	
	// only execute every 200 ms
 	if(millis() - t0 <= 200)
		return;
    
	t0 = millis();
	Mintrix[i] = CRGB(0);
	i = (i + 1) % Mintrix.num_leds;
	Mintrix[i] = CRGB(0xffffff);
	Mintrix.show();
}
