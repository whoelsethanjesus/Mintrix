/* * * * * * * * * * * * * * * * * * * *
 *                                     *
 *            M I N T R I X            *
 *           by Janik Heiler           *
 *                                     *
 * * * * * * * * * * * * * * * * * * * */

#include <Mintrix.h>
#define BAUD 19200

void http_request_handler()
{
  Serial.println("NEW HTTP-REQUEST");
  Serial.println("HTTPMethod:\t" + (String)Mintrix.server.method());
  Serial.println("URL:\t" + Mintrix.server.uri());
  Serial.println("\nHeaders - - - - - >");
  Serial.println("HostHeader:\t" + Mintrix.server.hostHeader());
  for(int i = 0; i < Mintrix.server.headers(); i++)
    Serial.println("[" + (String)i + "]\t" + Mintrix.server.headerName(i) + "\t" + Mintrix.server.header(i));
  Serial.println("\nArgs - - - - - >");
  for(int i = 0; i < Mintrix.server.args(); i++)
    Serial.println("[" + (String)i + "]\t" + Mintrix.server.argName(i) + "\t" + Mintrix.server.arg(i));
  Serial.println("> - - - - - - CONTENT END\n\n\n");

  Mintrix.server.send(200, "text/plain", "Your request has been received and processed.");
}

void setup()
{
  Mintrix.staticWiFi("My Mintrix");
  Mintrix.webStart();

  Mintrix.server.onNotFound(http_request_handler);
  delay(1000);
  Serial.begin(BAUD);
  delay(1000);
}

void loop()
{
  Mintrix.loop();
}
