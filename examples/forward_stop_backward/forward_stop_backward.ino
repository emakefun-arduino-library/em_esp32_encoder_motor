/**
 * @~Chinese
 * @file forward_stop_backward.ino
 * @brief 示例：电机前进后退停止
 * @example forward_stop_backward.ino
 * 电机前进后退停止
 */
/**
 * @~English
 * @file forward_stop_backward.ino
 * @brief Example: Move the motor forward, stop it, and then move it backward.
 * @example forward_stop_backward.ino
 * Move the motor forward, stop it, and then move it backward.
 */

#include "encoder_motor.h"
#include "encoder_motor_lib.h"

namespace {
constexpr uint32_t kPPR = 12;              // Pulses per revolution.
constexpr uint32_t kReductionRation = 90;  // Reduction ratio.

em::EncoderMotor g_encoder_motor_0(  // E0
    GPIO_NUM_27,                     // The pin number of the motor's positive pole.
    GPIO_NUM_13,                     // The pin number of the motor's negative pole.
    GPIO_NUM_18,                     // The pin number of the encoder's A phase.
    GPIO_NUM_19,                     // The pin number of the encoder's B phase.
    kPPR,                            // Pulses per revolution.
    kReductionRation,                // Reduction ratio.
    em::EncoderMotor::kAPhaseLeads   // Phase relationship (A phase leads or B phase leads, referring to the situation when
                                     // the motor is rotating forward)
);

em::EncoderMotor g_encoder_motor_1(  // E1
    GPIO_NUM_4,                      // The pin number of the motor's positive pole.
    GPIO_NUM_2,                      // The pin number of the motor's negative pole.
    GPIO_NUM_5,                      // The pin number of the encoder's A phase.
    GPIO_NUM_23,                     // The pin number of the encoder's B phase.
    kPPR,                            // Pulses per revolution.
    kReductionRation,                // Reduction ratio.
    em::EncoderMotor::kAPhaseLeads   // Phase relationship (A phase leads or B phase leads, referring to the situation when
                                     // the motor is rotating forward)
);

em::EncoderMotor g_encoder_motor_2(  // E2
    GPIO_NUM_17,                     // The pin number of the motor's positive pole.
    GPIO_NUM_12,                     // The pin number of the motor's negative pole.
    GPIO_NUM_35,                     // The pin number of the encoder's A phase.
    GPIO_NUM_36,                     // The pin number of the encoder's B phase.
    kPPR,                            // Pulses per revolution.
    kReductionRation,                // Reduction ratio.
    em::EncoderMotor::kAPhaseLeads   // Phase relationship (A phase leads or B phase leads, referring to the situation when
                                     // the motor is rotating forward)
);

em::EncoderMotor g_encoder_motor_3(  // E3
    GPIO_NUM_15,                     // The pin number of the motor's positive pole.
    GPIO_NUM_14,                     // The pin number of the motor's negative pole.
    GPIO_NUM_34,                     // The pin number of the encoder's A phase.
    GPIO_NUM_39,                     // The pin number of the encoder's B phase.
    kPPR,                            // Pulses per revolution.
    kReductionRation,                // Reduction ratio.
    em::EncoderMotor::kAPhaseLeads   // Phase relationship (A phase leads or B phase leads, referring to the situation when
                                     // the motor is rotating forward)
);
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
  const int16_t rpm = 100;
  static auto s_state_changed_time = millis();
  static enum State : uint8_t {
    kNone,
    kForward,
    kBackward,
    kStateNum,
  } s_state = kForward;

  if (millis() - s_state_changed_time > 2000) {
    switch (s_state) {
      case kNone:
        g_encoder_motor_0.Stop();
        g_encoder_motor_1.Stop();
        g_encoder_motor_2.Stop();
        g_encoder_motor_3.Stop();
        break;
      case kForward:
        g_encoder_motor_0.RunSpeed(rpm);
        g_encoder_motor_1.RunSpeed(rpm);
        g_encoder_motor_2.RunSpeed(rpm);
        g_encoder_motor_3.RunSpeed(rpm);
        break;
      case kBackward:
        g_encoder_motor_0.RunSpeed(-rpm);
        g_encoder_motor_1.RunSpeed(-rpm);
        g_encoder_motor_2.RunSpeed(-rpm);
        g_encoder_motor_3.RunSpeed(-rpm);
        break;
      default:
        break;
    }
    s_state = static_cast<State>((static_cast<uint8_t>(s_state) + 1) % kStateNum);
    s_state_changed_time = millis();
  }

  printf("target speed rpm: %4" PRIi16 ", current speed rpm:[%4" PRId32 ", %4" PRId32 ", %4" PRId32 ", %4" PRId32
         "], pwm duties:[%5 " PRIi16 ", %5" PRIi16 ", %5" PRIi16 ", %5" PRIi16 "], pulse counts:[%" PRId64 ", %" PRId64
         ", %" PRId64 ", %" PRId64 "]\n",
         rpm,
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