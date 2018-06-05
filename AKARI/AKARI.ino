/*
   Based on the following library:
   GitHub | riyas-org/max7219  https://github.com/riyas-org/max7219
*/

#include <MaxMatrix.h>

// Dimension values
#define WEST 1
#define NORTH 2
#define SOUTH 3
#define EAST 4
#define STAY 0
#define OTHER -1

int DIN = 7;  // DIN pin of MAX7219 module
int CLK = 6;  // CLK pin of MAX7219 module
int CS = 5;   // CS pin of MAX7219 module
int maxInUse = 1;

MaxMatrix m(DIN, CS, CLK, maxInUse);

struct Point {
  long x, y;
};

// Akari
int akari_hp = 9;
Point akari_pos;
int attack_chances = 5;
int turn = 0;

// Vampire
int vampire_hp = 9;
Point vampire_pos;

// Village People
int village_people_hp[] = { 3, 3, 3, 3 };
Point village_people_pos[4];
int village_people_num = 4;

// Servants of Vampire
int servants_hp[] = { 0, 0, 0, 0 };
Point servants_pos[4];
int servants_num = 0;

// Trap
Point trap_pos[2];

// Key values
int move_key = 0;
int attack_key = 0;

// Past key values
int past_move_key = 0;
int past_attack_key = 0;

int i;

// Convert current value to dimension value
int current_to_dimension(int current) {
  if(current >= 1011 && current <= 1029) {
    return WEST;
  }
  if(current >= 990 && current <= 1010) {
    return NORTH;
  }
  if(current >= 505 && current <= 515) {
    return SOUTH;
  }
  if(current >= 13 && current <= 17) {
    return EAST;
  }
  if(current < 13) {
    return STAY;
  }

  return OTHER;
}

void setup() {
  // For Test
  Serial.begin(9600);
  randomSeed(analogRead(2));
  
  m.init(); // MAX7219 initialization
  m.setIntensity(8);  // initial led maxrix intensity, 0-15

  akari_pos.x = random(7);
  akari_pos.y = random(7);

  vampire_pos.x = random(7);
  vampire_pos.y = random(7);

  for(i = 0; i < 4; i++) {
    village_people_pos[i].x = random(7);
    village_people_pos[i].y = random(7);
  }

  for(i = 0; i < 2; i++) {
    trap_pos[i].x = random(7);
    trap_pos[i].y = random(7);
  }

  
}

void loop() {
  m.clear();

  // Show current position of Akari
  m.setDot(akari_pos.x, akari_pos.y, true);
  
  past_move_key = move_key;
  past_attack_key = attack_key;
  move_key = analogRead(A0);
  attack_key = analogRead(A1);

  // Test Code : show key status
  Serial.println(move_key);
  Serial.println(attack_key);

  // When a move button has been pressed, turn.
  if(current_to_dimension(past_move_key) == STAY) {
    switch(current_to_dimension(move_key)) {
    case WEST:
      Serial.println("Go west!");
      if(akari_pos.x > 0)
        akari_pos.x--;
      break;
    case NORTH:
      Serial.println("Go north!");
      if(akari_pos.y > 0)
        akari_pos.y--;
      break;
    case SOUTH:
      Serial.println("Go south!");
      if(akari_pos.y < 7)
        akari_pos.y++;
      break;
    case EAST:
      Serial.println("Go east!");
      if(akari_pos.x < 7)
        akari_pos.x++;
      break;
    default:
      break;
    }
  }
}
