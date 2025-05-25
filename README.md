# DRV8835 + ESP32 モータードライバーデモ

このプロジェクトは、ESP32マイコンとDRV8835デュアルDCモータードライバーを使用して2つのDCモーターを制御するサンプルプログラムです。

## GitHubからのダウンロード方法

このプロジェクトをGitHubからダウンロードする手順は以下の通りです：

1. GitHubのリポジトリページにアクセスします。
2. 緑色の「Code」ボタンをクリックします。
   ![Code Button](https://docs.github.com/assets/cb-20363/images/help/repository/code-button.png)
3. 「Download ZIP」オプションを選択します。
   ![Download ZIP](https://github.com/wasa-cansat/Sample2025-05-26/archive/refs/heads/main.zip)
4. ダウンロードしたZIPファイルを適当な場所に展開します。
5. Arduino IDEで `.ino` ファイルを開きます。

## プロジェクト構成

このプロジェクトは以下のファイルで構成されています：

- `sample0526.ino` - メインのArduinoスケッチファイル
- `MotorDriver.h` - モーター制御用のヘルパークラス

## ハードウェア接続

DRV8835とESP32の接続は以下の通りです：

- **モータA**:
  - 前進: DRV8835 IN1 → ESP32 GPIO14
  - 後退: DRV8835 IN2 → ESP32 GPIO12
  
- **モータB**:
  - 前進: DRV8835 IN3 → ESP32 GPIO27
  - 後退: DRV8835 IN4 → ESP32 GPIO33

## 使用方法

1. 上記の接続図に従ってDRV8835とESP32を接続します。
2. Arduino IDEでプロジェクトを開きます。
3. ESP32ボードを選択して、コードをアップロードします。
4. アップロード後、モーターは以下のシーケンスを繰り返します：
   - 前進（2秒間）
   - 停止（1秒間）
   - 後退（2秒間）
   - 停止（1秒間）

## 注意事項

- このプロジェクトはArduino-ESP32 v3.0以降の新LEDC APIに対応しています。
- モーター駆動に十分な電力供給が必要です。
