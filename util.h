//タクトスイッチのDigitalReadPin
#define control_pin   18
//モーターをまわすスイッチ
#define r_back_pin    14
#define r_forward_pin 15
#define l_back_pin    16
#define l_forward_pin 17

//http://arms22.blog91.fc2.com/blog-entry-501.html

//タイマー用クラス
//https://lowreal.net/2016/02/24/3
template <uint16_t time>
class interval {
  uint32_t next_run = 0;

  template <class T>
  void _run(T func) {
    uint32_t now = millis();
    if (next_run < now) {
      func();
      next_run = now + time;
    }
  }

  interval() {}
public:

  template <class T>
  static void run(T func) {
    static interval<time> instance;
    instance._run(func);
  }
};
