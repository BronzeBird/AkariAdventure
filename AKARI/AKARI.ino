/*
   Based on the following library:
   GitHub | riyas-org/max7219  https://github.com/riyas-org/max7219
*/

#include <MaxMatrix.h>

int DIN = 7;  // DIN pin of MAX7219 module
int CLK = 6;  // CLK pin of MAX7219 module
int CS = 5;   // CS pin of MAX7219 module
int maxInUse = 1;

MaxMatrix m(DIN, CS, CLK, maxInUse);

struct Point {
  int x, y;
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

int i;

void setup() {
  m.init(); // MAX7219 initialization
  m.setIntensity(8);  // initial led maxrix intensity, 0-15

  // Initialize positions
  akari_pos.x = 0;
  akari_pos.y = 0;

  vampire_pos.x = 0;
  vampire_pos.y = 0;

  for(i = 0; i < 4; i++) {
    village_people_pos[i].x = 0;
    village_people_pos[i].y = 0;
  }

  for(i = 0; i < 2; i++) {
    trap_pos[i].x = 0;
    trap_pos[i].y = 0;
  }

  akari_pos.x = random(1, 8);
  akari_pos.y = random(1, 8);

  vampire_pos.x = random(1, 8);
  vampire_pos.y = random(1, 8);

  for(i = 0; i < 4; i++) {
    village_people_pos[i].x = random(1, 8);
    village_people_pos[i].y = random(1, 8);
  }

  for(i = 0; i < 2; i++) {
    trap_pos[i].x = random(1, 8);
    trap_pos[i].y = random(1, 8);
  }
}

void loop() {
  m.clear();
}
