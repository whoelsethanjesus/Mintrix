#ifndef ANIMATION_H
#define ANIMATION_H
namespace Animation {

const byte index[] = {70, 69, 55, 56, 52, 51, 37, 38, 34, 33, 19, 20, 16, 15,
                      21, 32, 31, 39, 40, 49, 41, 30, 23,
                      11, 10, 24, 25, 29, 28, 42, 43, 47, 46, 60, 61, 65, 64};

void logo()
{
  int i, k;
  
  Mintrix.clear();
  Mintrix.show();
  delay(1000);

  for(i = 0; i < 37; i++)
  {
    for(k = 0; k < Mintrix.num_leds; k++)
      Mintrix[k] *= 2;

    Mintrix[index[i]] = CRGB(1, 1, 1);
    Mintrix.show();
    delay(20);
  }

  for(i = 0; i < 8; i++)
  {
    for(k = 0; k < Mintrix.num_leds; k++)
      Mintrix[k] *= 2;
      
    Mintrix.show();
    delay(20);
  }

  delay(700);
  
  Mintrix[48] = CRGB(0xfbfb00);
  Mintrix[46] = CRGB(0xfbfb00);
  Mintrix[60] = CRGB(0xfbfb00);
  Mintrix[66] = CRGB(0xfbfb00);
  Mintrix[64] = CRGB(0xfbfb00);
  Mintrix.show();
  
  delay(1300);
  Mintrix.clear();
  Mintrix.show();
}

}
#endif
