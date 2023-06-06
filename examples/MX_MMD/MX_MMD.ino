#include <Mintrix.h>
#include "Chars.h"

int xy2i(int x, int y)
{
  return (y % 2) ? y * 9 + 8 - x : y * 9 + x;
}

#include "Animation.h"

#include "Demo_COL.h"
#include "Demo_ACC.h"
#include "Demo_SNK.h"
#include "Demo_TXT.h"

byte demo_app = 0;
void start_demo()
{
  Animation::logo();

       if(demo_app == 0) { DEMO_COL::setup(); }
  else if(demo_app == 1) { DEMO_ACC::setup(); }
  else if(demo_app == 2) { DEMO_SNK::setup(); }
  else if(demo_app == 3) { DEMO_TXT::setup(); }
}

void data()
{
  if(Mintrix.hasArg("app"))
  {
    byte h = Mintrix.arg("app")[0] - '0';
    if(h > 3)
    {
      Mintrix.send(400);
      return;
    }

    demo_app = h;
    start_demo();
    Mintrix.send(200);
    return;
  }

  if(demo_app == 0) // COL
  {
    /* nothing here :) */
    Mintrix.send(200);
    return;
  }
  
  else if(demo_app == 1) // ACC
  {
    if(!Mintrix.hasArg("x") || !Mintrix.hasArg("y"))
    {
      Mintrix.send(400);
      return;
    }

    int x = constrain(round(-Mintrix.arg("x").toInt() * 4.0 / 8.0) + 4, 0, 8);
    int y = constrain(round( Mintrix.arg("y").toInt() * 4.0 / 8.0) + 4, 0, 8);

    Mintrix.clear();
    Mintrix[40] = CRGB::White;
    Mintrix[xy2i(x, y)] = CRGB::Red;
    Mintrix.show();
  
    Mintrix.send(200);
    return;
  }
  
  else if(demo_app == 2) // SNK
  {
    if(!Mintrix.hasArg("dir"))
    {
      Mintrix.send(400);
      return;
    }
    
    DEMO_SNK::play = true;
    if(abs(Mintrix.arg("dir")[0] - '0' - DEMO_SNK::dir) != 2) DEMO_SNK::dir = Mintrix.arg("dir")[0] - '0';
  
    Mintrix.send(200);
    return;
  }
  
  else if(demo_app == 3) // TXT
  {
    if(!Mintrix.hasArg("txt") || Mintrix.arg("txt") == "")
    {
      Mintrix.send(400);
      return;
    }

    DEMO_TXT::str = Mintrix.arg("txt");
    DEMO_TXT::paintCanvas();
    DEMO_TXT::pos = 0;
    
    Mintrix.send(200);
    return;
  }

  Mintrix.send(400);
}

void setup()
{
  delay(1000);
  Serial.begin(19200);
  delay(1000);
  Mintrix.staticWiFi("KKG Mintrix");
  Mintrix.onData(data);
  Mintrix.webStart();
  start_demo();
}

void loop()
{
  Mintrix.loop();
  
       if(demo_app == 0) { DEMO_COL::loop(); }
  else if(demo_app == 1) { DEMO_ACC::loop(); }
  else if(demo_app == 2) { DEMO_SNK::loop(); }
  else if(demo_app == 3) { DEMO_TXT::loop(); }
  
  delay(2);
}
