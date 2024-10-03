const byte SEGMENT_PIN[7] = { D0, D1, D2, D3, D4, D5, D6 };

const int pb = D8;

int a = 0;
int buttonAwal, buttonAkhir;

bool angka[10][7] = {
  // a b c d e f g
  { 1, 1, 1, 1, 1, 1, 0 },  //0
  { 0, 1, 1, 0, 0, 0, 0 },  //1
  { 1, 1, 0, 1, 1, 0, 1 },  //2
  { 1, 1, 1, 1, 0, 0, 1 },  //3
  { 0, 1, 1, 0, 0, 1, 1 },  //4
  { 1, 0, 1, 1, 0, 1, 1 },  //5
  { 1, 0, 1, 1, 1, 1, 1 },  //6
  { 1, 1, 1, 0, 0, 0, 0 },  //7
  { 1, 1, 1, 1, 1, 1, 1 },  //8
  { 1, 1, 1, 1, 0, 1, 1 }   //9
};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i <= 7; i++) {
    pinMode(SEGMENT_PIN[i], OUTPUT);
  }
  pinMode(pb, INPUT);
}

void display_angka(int number) {
  for (int i = 0; i <= 7; i++) {
    digitalWrite(SEGMENT_PIN[i], angka[number][i]);
  }
}

void loop() {

  buttonAwal = buttonAkhir;
  buttonAkhir = digitalRead(pb);
  Serial.println(buttonAkhir);
  delay(500);

  if (buttonAwal != buttonAkhir) {
    a++;
  }
  display_angka(a);

  // if(digitalRead(9) == 1 && a < 9){
  //   while(digitalRead(9) == 1){}
  //   a++;
  // }

  // display_angka(a);


  // display_angka(0);
  // delay(500);
  // display_angka(1);
  // delay(500);
  // display_angka(2);
  // delay(500);
  // display_angka(3);
  // delay(500);
  // display_angka(4);
  // delay(500);
  // display_angka(5);
  // delay(500);
  // display_angka(6);
  // delay(500);
  // display_angka(7);
  // delay(500);
  // display_angka(8);
  // delay(500);
  // display_angka(9);
  // delay(500);
}
