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

namespace {
em::Motor g_motor_0(  // M0
    GPIO_NUM_27,      // The pin number of the motor's positive pole.
    GPIO_NUM_13       // The pin number of the motor's negative pole.
);

em::Motor g_motor_1(  // M1
    GPIO_NUM_4,       // The pin number of the motor's positive pole.
    GPIO_NUM_2        // The pin number of the motor's negative pole.
);

em::Motor g_motor_2(  // M2
    GPIO_NUM_17,      // The pin number of the motor's positive pole.
    GPIO_NUM_12       // The pin number of the motor's negative pole.
);

em::Motor g_motor_3(  // M3
    GPIO_NUM_15,      // The pin number of the motor's positive pole.
    GPIO_NUM_14       // The pin number of the motor's negative pole.
);
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
  g_motor_0.PwmDuty(1023);
  g_motor_1.PwmDuty(1023);
  g_motor_2.PwmDuty(1023);
  g_motor_3.PwmDuty(1023);
  printf("forward\n");
  delay(1000);

  g_motor_0.PwmDuty(-1023);
  g_motor_1.PwmDuty(-1023);
  g_motor_2.PwmDuty(-1023);
  g_motor_3.PwmDuty(-1023);
  printf("backward\n");
  delay(1000);
}