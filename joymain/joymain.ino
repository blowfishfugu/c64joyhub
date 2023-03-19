#include <Arduino.h>
#include <HID.h>
#include <Joystick.h>

const int debounceDelay = 5;  // debounce delay
const int pinCount = 5;
class MyJoy : Joystick_ {
public:
  const int pins[pinCount];
  int lastMoves[pinCount]{};
  MyJoy() = delete;
  MyJoy(MyJoy const&) = delete;
  MyJoy(const uint8_t id /*JOYSTICK_DEFAULT_REPORT_ID*/,
        const int u, const int d, const int l, const int r,
        const int f)
    : Joystick_(id,
                JOYSTICK_TYPE_GAMEPAD,
                1, 0,
                true, true, false,
                false, false, false,
                false, false,
                false, false, false),
      pins{ u, r, d, l, f } 
      {}
  ~MyJoy() = default;

  void init() {
    for (int i = 0; i < pinCount; ++i) {
      pinMode(pins[i], INPUT_PULLUP);
    }
    this->begin(false);
    this->setXAxisRange(-1, 1);
    this->setYAxisRange(-1, 1);
  }

  void update() {
    bool changed = false;
    for (int index = 0; index < pinCount; ++index) {
      // Read pin values
      int currentButtonState = !digitalRead(pins[index]);
      if (currentButtonState != lastMoves[index]) {
        switch (index) {
          case 0:  // UP
            setYAxis(-1 * currentButtonState);
            break;
          case 1:  // RIGHT
            setXAxis(1 * currentButtonState);
            break;
          case 2:  // DOWN
            setYAxis(1 * currentButtonState);
            break;
          case 3:  // LEFT
            setXAxis(-1 * currentButtonState);
            break;
          case 4:  // Black Button 1
            setButton(0, currentButtonState);
            break;
        }
        lastMoves[index] = currentButtonState;
        changed = true;
      }
    }
    if (changed) {
      sendState();
    }
  }
};

//frontplug
//DB9: UP 1, DOWN 2, LEFT 3, RIGHT 4, VOID 5
//:       FIRE 6, VCC 7, GND 8, VOID 9

static MyJoy Joy1(JOYSTICK_DEFAULT_REPORT_ID, 2, 3, 4, 5, 6);
static MyJoy Joy2(JOYSTICK_DEFAULT_REPORT_ID + 1, 10, 16, 14, 15, 9);

void setup() {
  Joy1.init();
  Joy2.init();
}

void loop() {
  Joy1.update();
  Joy2.update();
  delay(debounceDelay);
}
