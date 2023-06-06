#ifndef DEMO_COL_H
#define DEMO_COL_H
namespace DEMO_COL {

byte pos, hue;
unsigned long t0, t1;

int mirror_at_diagonal(int i)
{
  int y = floor(i / 9.0);
  int x = (y % 2) ? 8 - (i - 9 * y) : i - 9 * y;
  
  return (x % 2) ? x * 9 + 8 - y : x * 9 + y;
}

void setup()
{
  hue = 0;
  pos = 0;
  t0 = 0;
  t1 = 0;
}

void loop()
{
  if(millis() - t0 >= 5)
  {
    t0 = millis();
    fadeToBlackBy(Mintrix.leds, Mintrix.num_leds, 2);
    Mintrix.show();
  }
  
  if(millis() - t1 < 20) return;
  t1 = millis();
  
  Mintrix[pos] += CHSV(hue, 255, 160);
  Mintrix[mirror_at_diagonal((pos + 0) % 81)] += CHSV((hue + 127) % 256, 255, 160);
  pos = (pos + 1) % 81;
  hue += 3;

  for(int i = 0; i < 6; i++)
  {
    if(!random(40)) Mintrix[random(81)] = CHSV(random(256), random(256), random(200, 256));
  }
  Mintrix.show();
}

}
#endif
