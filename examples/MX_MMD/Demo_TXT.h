#ifndef DEMO_TXT_H
#define DEMO_TXT_H
namespace DEMO_TXT {

bool canvas[7][1500];
int csize, pos;
String str;
unsigned long t0;

String filter(String s, String mask)
{
  String f = "";
  
  for(int i = 0; i < s.length(); i++)
    if('a' <= s[i] && s[i] <= 'z') s[i] += 'A' - 'a';
  
  for(int i = 0; i < s.length(); i++)
    if(mask.indexOf(s[i]) >= 0) f += s[i];

  if(f.length() > 250) f = f.substring(0, 250);
  return f;
}

void paintCanvas()
{
  int x, y;
  int ptr = 0;
  
  str = filter(str, "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ");

  for(char c : str)
  {
    if(c == ' ')
    {
      for(y = 0; y < 7; y++)
        for(x = 0; x < 2; x++)
          canvas[y][x + ptr] = 0;
      ptr += 2;
    }
    else
    {
      for(y = 0; y < 7; y++)
        for(x = 0; x < 5; x++)
               if('A' <= c && c <= 'Z') canvas[y][x + ptr] = MintrixChar_Alphabet[c - 'A'][y][x];
          else if('0' <= c && c <= '9') canvas[y][x + ptr] = MintrixChar_Digit   [c - '0'][y][x];
      ptr += 5;
    }
    
    for(y = 0; y < 7; y++)
      canvas[y][ptr] = 0;
    ptr ++;
  }
  
  ptr --;

  for(y = 0; y < 7; y++)
    for(x = 0; x < 6; x++)
      canvas[y][x + ptr] = 0;
  ptr += 6;

  csize = ptr;
}

void setup()
{
  str = "MINTRIX VOM KKG";
  paintCanvas();
  pos = 0;
  t0 = 0;
}

void loop()
{
  if(millis() - t0 < 160) return;
  t0 = millis();

  Mintrix.clear();
  for(int y = 0; y < 7; y++)
    for(int x = 0; x < 9; x++)
      Mintrix[xy2i(x,y+1)] = canvas[y][(x+pos) % csize] * CRGB::White;

  Mintrix.show();
  pos = (pos + 1) % csize;
}

}
#endif
