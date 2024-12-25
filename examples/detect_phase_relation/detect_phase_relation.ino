/**
 * @~Chinese
 * @file detect_phase_relation.ino
 * @brief 示例：将编码电机按照示例程序中的说明接入到指定位置E0，程序运行成功后，会根据电机正转时编码器AB相的实际相位关系，
 * 在串口打印输出是使用 @ref kAPhaseLeads 还是 @ref
 * kBPhaseLeads，以此帮助用户确定在创建EncoderMotor对象时phase_relation参数应设置的值。
 * @example detect_phase_relation.ino
 * 将编码电机按照示例程序中的说明接入到指定位置E0，程序运行成功后，会根据电机正转时编码器AB相的实际相位关系，
 * 在串口打印输出是使用 @ref kAPhaseLeads 还是 @ref
 * kBPhaseLeads，以此帮助用户确定在创建EncoderMotor对象时phase_relation参数应设置的值。
 */
/**
 * @~English
 * @file detect_phase_relation.ino
 * @brief
 * Example: Connect the encoded motor to the specified positions E0 as described in the example program.
 * After the program runs successfully, it will print out whether kAPhaseLeads or kBPhaseLeads should be used based on the
 * actual phase relationship between the A and B phases of the encoder during forward rotation of the motor, helping the user
 * determine the value that should be set for the phase_relation parameter when creating an EncoderMotor object.
 * @example detect_phase_relation.ino
 * Connect the encoded motor to the specified positions E0 as described in the example program.
 * After the program runs successfully, it will print out whether kAPhaseLeads or kBPhaseLeads should be used based on the
 * actual phase relationship between the A and B phases of the encoder during forward rotation of the motor, helping the user
 * determine the value that should be set for the phase_relation parameter when creating an EncoderMotor object.
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
}  // namespace

void setup() {
  Serial.begin(115200);
  printf("setting up\n");
  printf("Emakefun Encoder Motor Library Version: %s\n", em::esp_encoder_motor_lib::Version().c_str());
  g_encoder_motor_0.Init();
  g_encoder_motor_0.RunPwmDuty(4095);
  printf("setup completed\n");
}

void loop() {
  const auto rpm = g_encoder_motor_0.SpeedRpm();
  if (rpm > 0) {
    printf(
        "[%lu] RPM: %d . The phase of A leads B. Constructed with the em::EncoderMotor::PhaseRelation::kAPhaseLeads "
        "enum.\n",
        millis(),
        rpm);
  } else if (rpm < 0) {
    printf(
        "[%lu] RPM: %d . The phase of B leads A. Constructed with the em::EncoderMotor::PhaseRelation::kBPhaseLeads "
        "enum.\n",
        millis(),
        rpm);
  } else {
    printf("The motor is not running currently.\n");
  }
  delay(200);
}