/**
 * @~Chinese
 * @file run_speed.ino
 * @brief 示例：以指定的速度（单位RPM）驱动电机。
 * @example run_speed.ino
 * 以指定的速度（单位RPM）驱动电机。
 */
/**
 * @~English
 * @file run_speed.ino
 * @brief Example: Rotate the motor at the specified speed (RPM).
 * @example run_speed.ino
 * Rotate the motor at the specified speed (RPM).
 */

#include "encoder_motor.h"
#include "encoder_motor_lib.h"

namespace {
constexpr uint32_t kPPR = 12;              // Pulses per revolution.
constexpr uint32_t kReductionRation = 90;  // Reduction ratio.

#if defined(CONFIG_IDF_TARGET_ESP32S3)

constexpr gpio_num_t kMotor0PinPos = GPIO_NUM_42;
constexpr gpio_num_t kMotor0PinNeg = GPIO_NUM_41;
constexpr gpio_num_t kEncoder0PinA = GPIO_NUM_38;
constexpr gpio_num_t kEncoder0PinB = GPIO_NUM_37;

constexpr gpio_num_t kMotor1PinPos = GPIO_NUM_1;
constexpr gpio_num_t kMotor1PinNeg = GPIO_NUM_2;
constexpr gpio_num_t kEncoder1PinA = GPIO_NUM_40;
constexpr gpio_num_t kEncoder1PinB = GPIO_NUM_39;

constexpr gpio_num_t kMotor2PinPos = GPIO_NUM_45;
constexpr gpio_num_t kMotor2PinNeg = GPIO_NUM_48;
constexpr gpio_num_t kEncoder2PinA = GPIO_NUM_21;
constexpr gpio_num_t kEncoder2PinB = GPIO_NUM_47;

constexpr gpio_num_t kMotor3PinPos = GPIO_NUM_35;
constexpr gpio_num_t kMotor3PinNeg = GPIO_NUM_36;
constexpr gpio_num_t kEncoder3PinA = GPIO_NUM_13;
constexpr gpio_num_t kEncoder3PinB = GPIO_NUM_14;
#elif defined(CONFIG_IDF_TARGET_ESP32)

constexpr gpio_num_t kMotor0PinPos = GPIO_NUM_27;
constexpr gpio_num_t kMotor0PinNeg = GPIO_NUM_13;
constexpr gpio_num_t kEncoder0PinA = GPIO_NUM_18;
constexpr gpio_num_t kEncoder0PinB = GPIO_NUM_19;

constexpr gpio_num_t kMotor1PinPos = GPIO_NUM_4;
constexpr gpio_num_t kMotor1PinNeg = GPIO_NUM_2;
constexpr gpio_num_t kEncoder1PinA = GPIO_NUM_5;
constexpr gpio_num_t kEncoder1PinB = GPIO_NUM_23;

constexpr gpio_num_t kMotor2PinPos = GPIO_NUM_17;
constexpr gpio_num_t kMotor2PinNeg = GPIO_NUM_12;
constexpr gpio_num_t kEncoder2PinA = GPIO_NUM_35;
constexpr gpio_num_t kEncoder2PinB = GPIO_NUM_36;

constexpr gpio_num_t kMotor3PinPos = GPIO_NUM_15;
constexpr gpio_num_t kMotor3PinNeg = GPIO_NUM_14;
constexpr gpio_num_t kEncoder3PinA = GPIO_NUM_34;
constexpr gpio_num_t kEncoder3PinB = GPIO_NUM_39;
#else
#error "Only ESP32 and ESP32S3 are support"
#endif

#if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
em::EncoderMotor g_encoder_motor_0(  // E0
  kMotor0PinPos,                     // The pin number of the motor's positive pole.
  kMotor0PinNeg,                     // The pin number of the motor's negative pole.
  kEncoder0PinA,                     // The pin number of the encoder's A phase.
  kEncoder0PinB,                     // The pin number of the encoder's B phase.
  kPPR,                              // Pulses per revolution.
  kReductionRation,                  // Reduction ratio.
  em::EncoderMotor::kAPhaseLeads     // Phase relationship (A phase leads or B phase leads, referring to the situation when
                                     // the motor is rotating forward)
);

em::EncoderMotor g_encoder_motor_1(  // E1
  kMotor1PinPos,                     // The pin number of the motor's positive pole.
  kMotor1PinNeg,                     // The pin number of the motor's negative pole.
  kEncoder1PinA,                     // The pin number of the encoder's A phase.
  kEncoder1PinB,                     // The pin number of the encoder's B phase.
  kPPR,                              // Pulses per revolution.
  kReductionRation,                  // Reduction ratio.
  em::EncoderMotor::kAPhaseLeads     // Phase relationship (A phase leads or B phase leads, referring to the situation when
                                     // the motor is rotating forward)
);

em::EncoderMotor g_encoder_motor_2(  // E2
  kMotor2PinPos,                     // The pin number of the motor's positive pole.
  kMotor2PinNeg,                     // The pin number of the motor's negative pole.
  kEncoder2PinA,                     // The pin number of the encoder's A phase.
  kEncoder2PinB,                     // The pin number of the encoder's B phase.
  kPPR,                              // Pulses per revolution.
  kReductionRation,                  // Reduction ratio.
  em::EncoderMotor::kAPhaseLeads     // Phase relationship (A phase leads or B phase leads, referring to the situation when
                                     // the motor is rotating forward)
);

em::EncoderMotor g_encoder_motor_3(  // E3
  kMotor3PinPos,                     // The pin number of the motor's positive pole.
  kMotor3PinNeg,                     // The pin number of the motor's negative pole.
  kEncoder3PinA,                     // The pin number of the encoder's A phase.
  kEncoder3PinB,                     // The pin number of the encoder's B phase.
  kPPR,                              // Pulses per revolution.
  kReductionRation,                  // Reduction ratio.
  em::EncoderMotor::kAPhaseLeads     // Phase relationship (A phase leads or B phase leads, referring to the situation when
                                     // the motor is rotating forward)
);

#else  // The ESP32 Arduino Core Version is less than 3.0.0

em::EncoderMotor g_encoder_motor_0(  // E0
  kMotor0PinPos,                     // The pin number of the motor's positive pole.
  0,                                 // The positive pole of the motor is attached to LED Control (LEDC) Channel 0.
  kMotor0PinNeg,                     // The pin number of the motor's negative pole.
  1,                                 // The negative pole of the motor is attached to LED Control (LEDC) Channel 1.
  kEncoder0PinA,                     // The pin number of the encoder's A phase.
  kEncoder0PinB,                     // The pin number of the encoder's B phase.
  kPPR,                              // Pulses per revolution.
  kReductionRation,                  // Reduction ratio.
  em::EncoderMotor::kAPhaseLeads     // Phase relationship (A phase leads or B phase leads, referring to the situation when
                                     // the motor is rotating forward)
);

em::EncoderMotor g_encoder_motor_1(  // E1
  kMotor1PinPos,                     // The pin number of the motor's positive pole.
  2,                                 // The positive pole of the motor is attached to LED Control (LEDC) Channel 2.
  kMotor1PinNeg,                     // The pin number of the motor's negative pole.
  3,                                 // The negative pole of the motor is attached to LED Control (LEDC) Channel 3.
  kEncoder1PinA,                     // The pin number of the encoder's A phase.
  kEncoder1PinB,                     // The pin number of the encoder's B phase.
  kPPR,                              // Pulses per revolution.
  kReductionRation,                  // Reduction ratio.
  em::EncoderMotor::kAPhaseLeads     // Phase relationship (A phase leads or B phase leads, referring to the situation when
                                     // the motor is rotating forward)
);

em::EncoderMotor g_encoder_motor_2(  // E2
  kMotor2PinPos,                     // The pin number of the motor's positive pole.
  4,                                 // The positive pole of the motor is attached to LED Control (LEDC) Channel 4.
  kMotor2PinNeg,                     // The pin number of the motor's negative pole.
  5,                                 // The negative pole of the motor is attached to LED Control (LEDC) Channel 5.
  kEncoder2PinA,                     // The pin number of the encoder's A phase.
  kEncoder2PinB,                     // The pin number of the encoder's B phase.
  kPPR,                              // Pulses per revolution.
  kReductionRation,                  // Reduction ratio.
  em::EncoderMotor::kAPhaseLeads     // Phase relationship (A phase leads or B phase leads, referring to the situation when
                                     // the motor is rotating forward)
);

em::EncoderMotor g_encoder_motor_3(  // E3
  kMotor3PinPos,                     // The pin number of the motor's positive pole.
  6,                                 // The positive pole of the motor is attached to LED Control (LEDC) Channel 6.
  kMotor3PinNeg,                     // The pin number of the motor's negative pole.
  7,                                 // The negative pole of the motor is attached to LED Control (LEDC) Channel 7.
  kEncoder3PinA,                     // The pin number of the encoder's A phase.
  kEncoder3PinB,                     // The pin number of the encoder's B phase.
  kPPR,                              // Pulses per revolution.
  kReductionRation,                  // Reduction ratio.
  em::EncoderMotor::kAPhaseLeads     // Phase relationship (A phase leads or B phase leads, referring to the situation when
                                     // the motor is rotating forward)
);
#endif
}  // namespace

void setup() {
  Serial.begin(115200);
  printf("setting up\n");
  printf("Emakefun Encoder Motor Library Version: %s\n", em::esp_encoder_motor_lib::Version().c_str());
  g_encoder_motor_0.Init();
  g_encoder_motor_1.Init();
  g_encoder_motor_2.Init();
  g_encoder_motor_3.Init();
  printf("setup completed\n");
}

void loop() {
  const int16_t speed_rpm = 100;

  g_encoder_motor_0.RunSpeed(speed_rpm);
  g_encoder_motor_1.RunSpeed(speed_rpm);
  g_encoder_motor_2.RunSpeed(speed_rpm);
  g_encoder_motor_3.RunSpeed(speed_rpm);

  printf("target speed rpm: %" PRIi16 ", current speed rpm: [%4" PRId32 ", %4" PRId32 ", %4" PRId32 ", %4" PRId32
         "], pwm duties: [%5 " PRIi16 ", %5" PRIi16 ", %5" PRIi16 ", %5" PRIi16 "], pulse counts: [%" PRId64 ", %" PRId64
         ", %" PRId64 ", %" PRId64 "]\n",
         speed_rpm,
         g_encoder_motor_0.SpeedRpm(),
         g_encoder_motor_1.SpeedRpm(),
         g_encoder_motor_2.SpeedRpm(),
         g_encoder_motor_3.SpeedRpm(),
         g_encoder_motor_0.PwmDuty(),
         g_encoder_motor_1.PwmDuty(),
         g_encoder_motor_2.PwmDuty(),
         g_encoder_motor_3.PwmDuty(),
         g_encoder_motor_0.EncoderPulseCount(),
         g_encoder_motor_1.EncoderPulseCount(),
         g_encoder_motor_2.EncoderPulseCount(),
         g_encoder_motor_3.EncoderPulseCount());

  delay(100);
}