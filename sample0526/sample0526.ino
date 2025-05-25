/*
  DualMotorDemo.ino - DRV8835 + ESP32 動作デモ
  ------------------------------------------------
  MotorDriver クラスを使って 2 基の DC モータを
  前進 → 停止 → 後退 を 2 秒ごとに繰り返すサンプルです。

  【配線】
    モータA: IN1 = GPIO14, IN2 = GPIO12
    モータB: IN3 = GPIO27, IN4 = GPIO33

  MotorDriver ライブラリの使い方:
    1. setup() 内で MotorDriver::begin() を呼んで PWM を初期化
    2. モータ制御は MotorDriver::setMotor(モータ番号, 速度) を使用
       ・モータ番号: 0 = A, 1 = B
       ・速度: -255 (最大逆転) ～ 255 (最大前進)
    3. MotorDriver::stopAll() で両モータを同時に停止
*/

#include "MotorDriver.h"  // ヘッダファイルをインクルード

void setup() {
  Serial.begin(115200);           // シリアルモニタ初期化（デバッグ用）
  MotorDriver::begin();           // モータードライバ初期化
  Serial.println("DRV8835 demo ready");
}

void loop() {
  // === 前進 ===
  MotorDriver::setMotor(0, 200);  // モータA 正転 (約80%出力)
  MotorDriver::setMotor(1, 200);  // モータB 正転
  delay(2000);                    // 2 秒待機

  // === 停止（ブレーキ）===
  MotorDriver::stopAll();         // 両モータ停止
  delay(1000);                    // 1 秒待機

  // === 後退 ===
  MotorDriver::setMotor(0, -200); // モータA 逆転
  MotorDriver::setMotor(1, -200); // モータB 逆転
  delay(2000);                    // 2 秒待機

  // === 停止 ===
  MotorDriver::stopAll();         // 両モータ停止
  delay(1000);
}
