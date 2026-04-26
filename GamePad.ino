#include <BleGamepad.h>

const int buttonPins[8] = {27, 5, 13, 14, 18, 19, 22, 23};
const int JOY1_X = 34, JOY1_Y = 35, JOY1_SW = 32;
const int JOY2_X = 25, JOY2_Y = 26, JOY2_SW = 33;

uint16_t prevButtons = 9999;
int8_t prevLX = -128, prevLY = -128, prevRX = -128, prevRY = -128;
signed char prevHat = -1;

BleGamepad gamepad("ESP32 Gamepad", "DIY", 100);

int8_t applyDeadzone(int value, int deadzone) {
  if (abs(value) < deadzone) return 0;
  return value;
}

void setup() {
  Serial.begin(115200);
  Serial.println("Booting...");

  for (int i = 0; i < 8; i++) pinMode(buttonPins[i], INPUT_PULLUP);
  pinMode(JOY1_SW, INPUT_PULLUP);
  pinMode(JOY2_SW, INPUT_PULLUP);

  BleGamepadConfiguration config;
  config.setAutoReport(false);
  config.setButtonCount(6);
  config.setHatSwitchCount(1);
  config.setAxesMin(-127);
  config.setAxesMax(127);
  config.setVid(0x045e);
  config.setPid(0x02fd);
  gamepad.begin(&config);

  Serial.println("ESP32 Gamepad Ready!");
  Serial.println("Waiting for connection...");
}

void loop() {
  if (gamepad.isConnected()) {

    // D-pad
    bool up    = !digitalRead(buttonPins[0]);
    bool down  = !digitalRead(buttonPins[1]);
    bool left  = !digitalRead(buttonPins[2]);
    bool right = !digitalRead(buttonPins[3]);

    signed char hat = HAT_CENTERED;
    if      (up && right)   hat = HAT_UP_RIGHT;
    else if (up && left)    hat = HAT_UP_LEFT;
    else if (down && right) hat = HAT_DOWN_RIGHT;
    else if (down && left)  hat = HAT_DOWN_LEFT;
    else if (up)            hat = HAT_UP;
    else if (down)          hat = HAT_DOWN;
    else if (left)          hat = HAT_LEFT;
    else if (right)         hat = HAT_RIGHT;

    // Face buttons
    bool triangle = !digitalRead(buttonPins[4]);
    bool circle   = !digitalRead(buttonPins[5]);
    bool square   = !digitalRead(buttonPins[6]);
    bool cross    = !digitalRead(buttonPins[7]);

    // Joystick clicks
    bool l3 = !digitalRead(JOY1_SW);
    bool r3 = !digitalRead(JOY2_SW);

    // Axes
    int8_t lx = applyDeadzone(map(analogRead(JOY1_X), 0, 4095, -127, 127), 15);
    int8_t ly = applyDeadzone(map(analogRead(JOY1_Y), 0, 4095, -127, 127), 15);
    int8_t rx = applyDeadzone(map(analogRead(JOY2_X), 0, 4095, -127, 127), 15);
    int8_t ry = applyDeadzone(map(analogRead(JOY2_Y), 0, 4095, -127, 127), 15);

    uint16_t buttons = 0;
    if (triangle) buttons |= (1 << 0);
    if (circle)   buttons |= (1 << 1);
    if (square)   buttons |= (1 << 2);
    if (cross)    buttons |= (1 << 3);
    if (l3)       buttons |= (1 << 4);
    if (r3)       buttons |= (1 << 5);

    // Print only on change
    if (buttons != prevButtons ||
        hat != prevHat ||
        lx != prevLX || ly != prevLY ||
        rx != prevRX || ry != prevRY) {

      Serial.printf("DPAD:%d | △:%d ○:%d □:%d ✕:%d L3:%d R3:%d | LX:%d LY:%d RX:%d RY:%d\n",
        hat, triangle, circle, square, cross,
        l3, r3, lx, ly, rx, ry);

      prevButtons = buttons;
      prevHat = hat;
      prevLX = lx; prevLY = ly;
      prevRX = rx; prevRY = ry;
    }

    gamepad.setHat(hat);

    if (triangle) gamepad.press(BUTTON_1); else gamepad.release(BUTTON_1);
    if (circle)   gamepad.press(BUTTON_2); else gamepad.release(BUTTON_2);
    if (square)   gamepad.press(BUTTON_3); else gamepad.release(BUTTON_3);
    if (cross)    gamepad.press(BUTTON_4); else gamepad.release(BUTTON_4);
    if (l3)       gamepad.press(BUTTON_5); else gamepad.release(BUTTON_5);
    if (r3)       gamepad.press(BUTTON_6); else gamepad.release(BUTTON_6);

    gamepad.setLeftThumb(lx, ly);
    gamepad.setRightThumb(rx, ry);

    gamepad.sendReport();

  } else {
    Serial.println("Waiting for connection...");
    delay(1000);
  }

  delay(20);
}
