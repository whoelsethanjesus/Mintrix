#ifndef DEMO_SNK_H
#define DEMO_SNK_H
namespace DEMO_SNK {
  
unsigned long t0;

byte head_pos[2];
byte snake[81];
byte snake_len;
byte apple_pos;
bool play = false;
byte dir; // left, up, right, down

void render()
{
  Mintrix.clear();

  Mintrix[apple_pos] = CRGB(0xff0000);
  
  Mintrix[snake[0]] = CRGB(0x0000ff);
  
  for(int i = 1; i < snake_len; i++)
    Mintrix[snake[i]] = CRGB(0xaaaaaa);
  
  Mintrix.show();

  for(int i = 0; i < snake_len; i++)
    Serial.println("[" + (String)i + "]\t" + snake[i]);
  Serial.println();
}

void newApplePos()
{
  bool apple_fine = false;

  while(!apple_fine)
  {
    apple_fine = true;
    apple_pos = random(81);
    for(int i = 0; i < snake_len; i++)
      if(snake[i] == apple_pos)
        apple_fine = false;
  }
}

void snk_step()
{
  for(int i = snake_len - 1; i > 0; i--)
    snake[i] = snake[i-1];

  switch(dir)
  {
    case 0: if(head_pos[0] > 0) {head_pos[0] --;} else {play = false;} break;
    case 1: if(head_pos[1] > 0) {head_pos[1] --;} else {play = false;} break;
    case 2: if(head_pos[0] < 8) {head_pos[0] ++;} else {play = false;} break;
    case 3: if(head_pos[1] < 8) {head_pos[1] ++;} else {play = false;} break;
    default: break;
  }

  snake[0] = xy2i(head_pos[0], head_pos[1]);
}

void snk_check_apple()
{
  if(snake[0] != apple_pos)
    return;

  snake_len ++;
  snake[snake_len - 1] = snake[snake_len - 2];
  newApplePos();

  if(snake_len == 81) play = false;
}

void snk_check_snake()
{
  for(int i = 1; i < snake_len; i++)
    if(snake[i] == snake[0])
    {
      play = false;
      return;
    }
}
void setup()
{
  t0 = 0;
  dir = 2;
  snake_len = 4;
  head_pos[0] = 4;
  head_pos[1] = 4;
  snake[0] = xy2i(head_pos[0],head_pos[1]);
  snake[1] = xy2i(3,4);
  snake[2] = xy2i(2,4);
  snake[3] = xy2i(1,4);
  newApplePos();
  play = false;
  render();
}

void loop()
{
  if(!play)
    return;
  
  if(millis() - t0 < 500) return;
  t0 = millis();

  snk_step();
  
  snk_check_apple();
  snk_check_snake();

  render();
}

}
#endif
