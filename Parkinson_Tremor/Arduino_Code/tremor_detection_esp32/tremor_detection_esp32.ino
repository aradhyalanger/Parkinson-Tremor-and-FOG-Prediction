#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ================= WIFI =================
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_PASSWORD";

// ================= TELEGRAM =================
String botToken = "YOUR_BOT_TOKEN";
String chatID   = "YOUR_CHAT_ID";

// ================= OLED =================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ================= BATTERY =================
#define BAT_ADC_PIN 34
#define ADC_MAX 4095.0
#define ADC_REF 3.3
#define DIVIDER_RATIO 2.0

// ================= MPU6050 =================
const int MPU_ADDR = 0x68;
const int MOTOR_PIN = 25;

// ================= SIGNAL PROCESSING =================
const int FILTER_SIZE = 10;
const int RMS_WINDOW = 50;
const float TREMOR_THRESHOLD = 10.0;

float gyroBuffer[FILTER_SIZE];
int filterIndex = 0;

float rmsBuffer[RMS_WINDOW];
int rmsIndex = 0;

// Telegram spam prevention
bool tremorAlertSent = false;

// ---------------- WiFi ----------------
void connectWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");
  Serial.println(WiFi.localIP());
}

// ---------------- Telegram ----------------
void sendTelegramMessage(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = "https://api.telegram.org/bot" + botToken +
                 "/sendMessage?chat_id=" + chatID +
                 "&text=" + message;

    http.begin(url);
    int httpCode = http.GET();

    Serial.print("Telegram HTTP Code: ");
    Serial.println(httpCode);

    http.end();
  }
}

// ---------------- Battery Voltage ----------------
float readBatteryVoltage() {
  int adcValue = analogRead(BAT_ADC_PIN);
  float voltage = (adcValue / ADC_MAX) * ADC_REF * DIVIDER_RATIO;
  return voltage;
}

// ---------------- OLED ----------------
void updateOLED(float gx, float rms, bool tremor) {
  float battery = readBatteryVoltage();

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0,0);
  display.println("Tremor Monitor");

  display.setCursor(0,16);
  display.print("GyroX: ");
  display.println(gx, 1);

  display.setCursor(0,28);
  display.print("RMS: ");
  display.println(rms, 2);

  display.setCursor(0,40);
  display.print("Battery: ");
  display.print(battery, 2);
  display.println("V");

  display.setCursor(0,54);
  if (tremor) {
    display.println("Status: TREMOR");
  } else {
    display.println("Status: NORMAL");
  }

  display.display();
}

// ---------------- MPU6050 ----------------
float readGyroX() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 2, true);

  int16_t raw = Wire.read() << 8 | Wire.read();
  return raw / 131.0;
}

// ---------------- Moving Average ----------------
float movingAverage(float x) {
  gyroBuffer[filterIndex] = x;
  filterIndex = (filterIndex + 1) % FILTER_SIZE;

  float sum = 0;
  for (int i = 0; i < FILTER_SIZE; i++) {
    sum += gyroBuffer[i];
  }

  return sum / FILTER_SIZE;
}

// ---------------- RMS ----------------
float computeRMS(float x) {
  rmsBuffer[rmsIndex] = x * x;
  rmsIndex = (rmsIndex + 1) % RMS_WINDOW;

  float sum = 0;
  for (int i = 0; i < RMS_WINDOW; i++) {
    sum += rmsBuffer[i];
  }

  return sqrt(sum / RMS_WINDOW);
}

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  Wire.begin();

  pinMode(MOTOR_PIN, OUTPUT);
  digitalWrite(MOTOR_PIN, LOW);

  analogReadResolution(12);

  // Wake up MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED not found");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Starting...");
  display.display();

  // WiFi
  connectWiFi();

  sendTelegramMessage("ESP32 Tremor Monitoring Device Started");

  Serial.println("Tremor Detection Started");
}

// ================= LOOP =================
void loop() {
  float gx = readGyroX();
  float filtered = movingAverage(gx);
  float rms = computeRMS(filtered);

  bool tremorDetected = rms > TREMOR_THRESHOLD;

  Serial.print("GyroX: ");
  Serial.print(filtered);
  Serial.print(" deg/s | RMS: ");
  Serial.println(rms);

  // Motor control
  if (tremorDetected) {
    digitalWrite(MOTOR_PIN, HIGH);

    if (!tremorAlertSent) {
      String msg = "Tremor detected! RMS = " + String(rms, 2);
      sendTelegramMessage(msg);
      tremorAlertSent = true;
    }

  } else {
    digitalWrite(MOTOR_PIN, LOW);
    tremorAlertSent = false;
  }

  // OLED update
  updateOLED(filtered, rms, tremorDetected);

  delay(10); // 100 Hz sampling
}
