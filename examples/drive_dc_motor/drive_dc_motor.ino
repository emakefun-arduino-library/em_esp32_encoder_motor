/**
 * @~Chinese
 * @file drive_dc_motor.ino
 * @brief 示例：PWM驱动直流电机正反转
 * @example drive_dc_motor.ino
 * PWM驱动直流电机正反转
 */
/**
 * @~English
 * @file drive_dc_motor.ino
 * @brief Example: Use PWM to drive the DC motor to rotate forward and backward.
 * @example drive_dc_motor.ino
 * Use PWM to drive the DC motor to rotate forward and backward.
 */

#include "encoder_motor_lib.h"
#include "motor.h"

#if defined(CONFIG_IDF_TARGET_ESP32S3)
constexpr gpio_num_t kMotor0PinPos = GPIO_NUM_42;
constexpr gpio_num_t kMotor0PinNeg = GPIO_NUM_41;

constexpr gpio_num_t kMotor1PinPos = GPIO_NUM_1;
constexpr gpio_num_t kMotor1PinNeg = GPIO_NUM_2;

constexpr gpio_num_t kMotor2PinPos = GPIO_NUM_45;
constexpr gpio_num_t kMotor2PinNeg = GPIO_NUM_48;

constexpr gpio_num_t kMotor3PinPos = GPIO_NUM_35;
constexpr gpio_num_t kMotor3PinNeg = GPIO_NUM_36;

#elif defined(CONFIG_IDF_TARGET_ESP32)
constexpr gpio_num_t kMotor0PinPos = GPIO_NUM_27;
constexpr gpio_num_t kMotor0PinNeg = GPIO_NUM_13;

constexpr gpio_num_t kMotor1PinPos = GPIO_NUM_4;
constexpr gpio_num_t kMotor1PinNeg = GPIO_NUM_2;

constexpr gpio_num_t kMotor2PinPos = GPIO_NUM_17;
constexpr gpio_num_t kMotor2PinNeg = GPIO_NUM_12;

constexpr gpio_num_t kMotor3PinPos = GPIO_NUM_15;
constexpr gpio_num_t kMotor3PinNeg = GPIO_NUM_14;

#else
#error "Only ESP32 and ESP32S3 are supported"
#endif

namespace {
#if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
em::Motor g_motor_0(  // M0
  kMotor0PinPos,      // The pin number of the motor's positive pole.
  kMotor0PinNeg       // The pin number of the motor's negative pole.
);

em::Motor g_motor_1(  // M1
  kMotor1PinPos,      // The pin number of the motor's positive pole.
  kMotor1PinNeg       // The pin number of the motor's negative pole.
);

em::Motor g_motor_2(  // M2
  kMotor2PinPos,      // The pin number of the motor's positive pole.
  kMotor2PinNeg       // The pin number of the motor's negative pole.
);

em::Motor g_motor_3(  // M3
  kMotor3PinPos,      // The pin number of the motor's positive pole.
  kMotor3PinNeg       // The pin number of the motor's negative pole.
);

#else  // The ESP32 Arduino Core Version is less than 3.0.0

em::Motor g_motor_0(  // M0
  kMotor0PinPos,      // The pin number of the motor's positive pole.
  0,                  // The positive pole of the motor is attached to LED Control (LEDC) Channel 0.
  kMotor0PinNeg,      // The pin number of the motor's negative pole.
  1                   // The negative pole of the motor is attached to LED Control (LEDC) Channel 1.
);

em::Motor g_motor_1(  // M1
  kMotor1PinPos,      // The pin number of the motor's positive pole.
  2,                  // The positive pole of the motor is attached to LED Control (LEDC) Channel 2.
  kMotor1PinNeg,      // The pin number of the motor's negative pole.
  3                   // The negative pole of the motor is attached to LED Control (LEDC) Channel 3.
);

em::Motor g_motor_2(  // M2
  kMotor2PinPos,      // The pin number of the motor's positive pole.
  4,                  // The positive pole of the motor is attached to LED Control (LEDC) Channel 4.
  kMotor2PinNeg,      // The pin number of the motor's negative pole.
  5                   // The negative pole of the motor is attached to LED Control (LEDC) Channel 5.
);

em::Motor g_motor_3(  // M3
  kMotor3PinPos,      // The pin number of the motor's positive pole.
  6,                  // The positive pole of the motor is attached to LED Control (LEDC) Channel 6.
  kMotor3PinNeg,      // The pin number of the motor's negative pole.
  7                   // The negative pole of the motor is attached to LED Control (LEDC) Channel 7.
);
#endif
}  // namespace

void setup() {
  Serial.begin(115200);
  printf("setting up\n");
  printf("Emakefun Encoder Motor Library Version: %s\n", em::esp_encoder_motor_lib::Version().c_str());
  g_motor_0.Init();
  g_motor_1.Init();
  g_motor_2.Init();
  g_motor_3.Init();
  printf("setup completed\n");
}

void loop() {
  g_motor_0.RunPwmDuty(1023);
  g_motor_1.RunPwmDuty(1023);
  g_motor_2.RunPwmDuty(1023);
  g_motor_3.RunPwmDuty(1023);
  printf("forward\n");
  delay(1000);

  g_motor_0.RunPwmDuty(-1023);
  g_motor_1.RunPwmDuty(-1023);
  g_motor_2.RunPwmDuty(-1023);
  g_motor_3.RunPwmDuty(-1023);
  printf("backward\n");
  delay(1000);
}