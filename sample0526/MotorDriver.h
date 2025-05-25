//=====================================================================
//  MotorDriver.h - DRV8835（デュアル DC モータドライバ）用ヘルパークラス
//  -------------------------------------------------------------------
//  Arduino‑ESP32 v3.0 以降の新 LEDC API 対応版
//    * ledcSetup / ledcAttachPin は削除 → ledcAttach() に統合
//    * ledcWrite() の第 1 引数は channel ではなく pin
//  公式ガイド: https://docs.espressif.com/projects/arduino-esp32/en/latest/migration_guides/2.x_to_3.0.html#ledc
//
//  【接続】
//    DRV8835 IN1 → GPIO14  (モータA 前進)
//              IN2 → GPIO12 (モータA 後退)
//              IN3 → GPIO27 (モータB 前進)
//              IN4 → GPIO33 (モータB 後退)
//
//  【使い方】
//    MotorDriver::begin();              // setup() で 1 回呼び出す
//    MotorDriver::setMotor(0, 150);     // モータA を正転 150/255
//    MotorDriver::setMotor(1, -200);    // モータB を逆転 200/255
//    MotorDriver::stopAll();            // 全停止
//
//  周波数 / 分解能は begin() の引数で変更可（デフォルト 20 kHz / 8 bit）。
//=====================================================================

#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <Arduino.h>

class MotorDriver {
public:
  //-------------------------------------------------------------------
  // ドライバ入力ピン（定数）
  //-------------------------------------------------------------------
  static constexpr uint8_t IN1_PIN = 14;   // モータA : 正転
  static constexpr uint8_t IN2_PIN = 12;   // モータA : 逆転
  static constexpr uint8_t IN3_PIN = 27;   // モータB : 正転
  static constexpr uint8_t IN4_PIN = 33;   // モータB : 逆転

  //-------------------------------------------------------------------
  // 初期化
  //   freq       : PWM 周波数 [Hz] (1 ～ 40 MHz / 20 kHz 推奨)
  //   resolution : PWM 分解能 [bit] (1 ～ 20 bit) 8bit→0‑255
  //-------------------------------------------------------------------
  static void begin(uint32_t freq = 20000, uint8_t resolution = 8) {
    // 4 つのピンを LEDC に登録（チャンネルは自動割当て）
    ledcAttach(IN1_PIN, freq, resolution);
    ledcAttach(IN2_PIN, freq, resolution);
    ledcAttach(IN3_PIN, freq, resolution);
    ledcAttach(IN4_PIN, freq, resolution);

    // 初期 duty = 0（停止）
    ledcWrite(IN1_PIN, 0);
    ledcWrite(IN2_PIN, 0);
    ledcWrite(IN3_PIN, 0);
    ledcWrite(IN4_PIN, 0);
  }

  //-------------------------------------------------------------------
  // モータ制御
  //   motor : 0 = モータA, 1 = モータB
  //   speed : -255 ～ 255（負: 逆転, 正: 正転, 0: 停止）
  //-------------------------------------------------------------------
  static void setMotor(uint8_t motor, int16_t speed) {
    speed = constrain(speed, -255, 255);
    uint8_t duty = abs(speed);

    // モータごとの正転 / 逆転ピンを取得
    uint8_t pinFwd = (motor == 0) ? IN1_PIN : IN3_PIN;
    uint8_t pinRev = (motor == 0) ? IN2_PIN : IN4_PIN;

    if (speed > 0) {
      // 正転: 前進ピンに duty、後退ピンは 0
      ledcWrite(pinFwd, duty);
      ledcWrite(pinRev, 0);
    } else if (speed < 0) {
      // 逆転: 後退ピンに duty、前進ピンは 0
      ledcWrite(pinFwd, 0);
      ledcWrite(pinRev, duty);
    } else {
      // 停止: 両ピン 0
      ledcWrite(pinFwd, 0);
      ledcWrite(pinRev, 0);
    }
  }

  //-------------------------------------------------------------------
  // 全モータ停止
  //-------------------------------------------------------------------
  static void stopAll() {
    ledcWrite(IN1_PIN, 0);
    ledcWrite(IN2_PIN, 0);
    ledcWrite(IN3_PIN, 0);
    ledcWrite(IN4_PIN, 0);
  }
};

#endif // MOTOR_DRIVER_H
