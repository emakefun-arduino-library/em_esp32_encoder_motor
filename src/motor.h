#pragma once

#ifndef _EM_MOTOR_H_
#define _EM_MOTOR_H_

/**
 * @file motor.h
 */

#include <WString.h>

#include <cmath>
#include <cstdint>

namespace em {
/**
 * @~Chinese
 * @class Motor
 * @brief 两路PWM电机驱动类
 */
/**
 * @~English
 * @class Motor
 * @brief A two-channel PWM motor driver class.
 */
class Motor {
 public:
  /**
   * @~Chinese
   * @brief PWM的分辨率，决定了PWM占空比可调节的精细程度，单位为位，这里设置为10位。
   * /
  /**
   * @~English
   * @brief The resolution of PWM, which determines the fine-tuning level of the PWM duty cycle, in bits. Here it is set to 10
   * bits.
   */
  static constexpr uint8_t kPwmResolution = 10;
  /**
   * @~Chinese
   * @brief PWM的频率，单位为赫兹，这里设置为75000赫兹，用于控制电机驱动的PWM信号频率。
   * @~English
   * @brief The frequency of PWM, in Hertz. Here it is set to 75000 Hz, used to control the frequency of the PWM signal for
   * motor driving.
   */
  static constexpr uint8_t kPwmFrequency = 75000;

  static_assert(kPwmResolution > 1);
  /**
   * @~Chinese
   * @brief 根据PWM分辨率计算出的最大PWM占空比数值，通过公式 \(2^{PWM分辨率} - 1\) 得出。
   * @~English
   * @brief The maximum PWM duty cycle value calculated based on the PWM resolution, obtained by the formula \(2^{PWM分辨率} -
   * 1\).
   */  /**
   * @~Chinese
   * @brief 根据PWM分辨率计算出的最大PWM占空比数值，通过公式 \(2^{PWM分辨率} - 1\) 得出。
   * @~English
   * @brief The maximum PWM duty cycle value calculated based on the PWM resolution, obtained by the formula \(2^{PWM分辨率} - 1\).
   */
  static constexpr int16_t kMaxPwmDuty = pow(2, kPwmResolution) - 1;

  /**
   * @~Chinese
   * @brief 构造函数，用于创建一个 Motor 对象。
   * @param[in] positive_pin 电机正极引脚编号。
   * @param[in] negative_pin 电机负极引脚编号。
   */
  /**
   * @~English
   * @brief Constructor for creating an Motor object.
   * @param[in] positive_pin The pin number of the motor's positive pole.
   * @param[in] negative_pin The pin number of the motor's negative pole.
   */
  explicit Motor(const uint8_t positive_pin, const uint8_t negative_pin);

  ~Motor() = default;

  /**
   * @~Chinese
   * @brief 初始化电机设置。
   */
  /**
   * @~English
   * @brief Initialize motor settings.
   */
  void Init();

  /**
   * @~Chinese
   * @brief 直接设置电机的PWM占空比。
   * @param[in] pwm_duty PWM占空比（取值范围 -1023到1023）。
   */
  /**
   * @~English
   * @brief Set motor PWM directly.
   * @param[in] pwm_duty PWM duty cycle (-1023 to 1023).
   */
  void PwmDuty(const int16_t pwm_duty);

  /**
   * @~Chinese
   * @brief 获取电机驱动器的PWM占空比。
   * @return 电机驱动器的PWM占空比。
   */
  /**
   * @~English
   * @brief Get the PWM pwm_duty cycle of the motor driver.
   * @return The PWM pwm_duty cycle of the motor driver.
   */
  int16_t PwmDuty() const;

  /**
   * @~Chinese
   * @brief 停止电机运行。
   */
  /**
   * @~English
   * @brief Stop motor.
   */
  void Stop();

 private:
  const uint8_t positive_pin_ = 0xFF;
  const uint8_t negative_pin_ = 0xFF;
  int16_t pwm_duty_ = 0;
};
}  // namespace em

#endif