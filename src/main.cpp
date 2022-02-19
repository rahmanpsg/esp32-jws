#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include "AsyncJson.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DMD32.h>
#include <WaktuSholat.h>
#include "time.h"
#include <LITTLEFS.h>
#include "WebPage.h"
#include "fonts/HoboStd12.h"
#include "fonts/HoboStd16.h"
#include "fonts/Calibri10.h"
#include "fonts/CooperBlack10.h"
#include "fonts/ElektronMart5x6.h"
#include "fonts/ElektronMart6x16.h"

#define SPIFFS LITTLEFS

const char *ssid = "HUAWEI nova 5T";
const char *password = "leppangang1";

AsyncWebServer server(80);

struct Config
{
  double latitude;
  double longitude;
  int zonaWaktu;
  String listInformasi;
};

const char *fileConfig = "/config.json";
Config config;
Config configShow;

bool updateInformasi;

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 28800; // GMT +8
const int daylightOffset_sec = 3600;

bool waktuLokal = false;

struct tm timeinfo;

char jam[3];
char menit[3];
char detik[3];

double times[sizeof(TimeName) / sizeof(char *)];
int indexTime[] = {0, 2, 3, 5, 6, 7};
int indexTimeActive = 0;
int tempTimeActive = 0;

#define INTERVAL_CETAK_WAKTU_SHOLAT 5000
unsigned long time_now = 0;
unsigned long time_now2 = 0;

int tahun, bulan, tanggal;

// Fire up the DMD library as dmd
#define KOLOM 3
#define BARIS 1

DMD dmd(KOLOM, BARIS);

// Timer setup
// create a hardware timer  of ESP32
hw_timer_t *timer = NULL;

void initLED(boolean first);
void initWaktuSholat();
void loadConfig(const char *fileConfig, Config &config);
void saveConfig(JsonObject json);
void updateWaktu();
void cetakWaktu();
void cetakTanggal();
void cetakJamSholat();
void cetakInfo();
void IRAM_ATTR triggerScan();
void textCenter(int y, char *Msg);

void handleGetIndex(AsyncWebServerRequest *request);
void handlePostWaktu(AsyncWebServerRequest *request);
void handleGetPostLokasi(AsyncWebServerRequest *request);
void handleGetPostInformasi(AsyncWebServerRequest *request);

void setup(void)
{
  Serial.begin(115200);

  delay(1000);

  // Initialize SPIFFS
  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  loadConfig(fileConfig, config);

  // connect to WiFi
  Serial.printf("Menghubungkan ke %s ...", ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Terhubung");
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleGetIndex);
  server.on("/waktu", handlePostWaktu);
  server.on("/lokasi", handleGetPostLokasi);
  server.on("/informasi", handleGetPostInformasi);

  // Start server
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server.begin();

  // init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  updateWaktu();

  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

  initWaktuSholat();
  initLED(true);
}

void loop(void)
{
  cetakWaktu();
  cetakJamSholat();
  cetakInfo();
}

// ====================================== WEB SERVER ===================//
void handleGetIndex(AsyncWebServerRequest *request)
{
  request->send_P(200, "text/html", webpage);
}

void handlePostWaktu(AsyncWebServerRequest *request)
{
  AsyncResponseStream *response = request->beginResponseStream("application/json");

  StaticJsonDocument<512> json;

  json["error"] = false;
  json["message"] = "Waktu berhasil diperbaharui";

  serializeJson(json, *response);
  json.clear();

  request->send(response);
}

void handleGetPostLokasi(AsyncWebServerRequest *request)
{
  AsyncResponseStream *response = request->beginResponseStream("application/json");

  StaticJsonDocument<512> json;

  if (request->method() == HTTP_GET)
  {
    json["latitude"] = config.latitude;
    json["longitude"] = config.longitude;
    json["zonaWaktu"] = config.zonaWaktu;
  }
  else if (request->method() == HTTP_POST)
  {
    config.latitude = request->getParam("latitude", true)->value().toDouble();
    config.longitude = request->getParam("longitude", true)->value().toDouble();
    config.zonaWaktu = request->getParam("zonaWaktu", true)->value().toInt();

    json["latitude"] = config.latitude;
    json["longitude"] = config.longitude;
    json["zonaWaktu"] = config.zonaWaktu;
    json["listInformasi"] = config.listInformasi;

    saveConfig(json.as<JsonObject>());
  }

  serializeJson(json, *response);
  json.clear();

  request->send(response);
}

void handleGetPostInformasi(AsyncWebServerRequest *request)
{
  AsyncResponseStream *response = request->beginResponseStream("application/json");

  StaticJsonDocument<512> json;

  if (request->method() == HTTP_GET)
  {
    deserializeJson(json, config.listInformasi);
  }
  else if (request->method() == HTTP_POST)
  {
    config.listInformasi = request->getParam("listInformasi", true)->value();

    Serial.println(config.listInformasi);

    json["latitude"] = config.latitude;
    json["longitude"] = config.longitude;
    json["zonaWaktu"] = config.zonaWaktu;
    json["listInformasi"] = config.listInformasi;
    saveConfig(json.as<JsonObject>());
    updateInformasi = true;
  }

  // json.shrinkToFit();
  serializeJson(json, *response);
  json.clear();

  request->send(response);
}

// ===================================================================== //

void loadConfig(const char *fileConfig, Config &config)
{
  File configFile = SPIFFS.open(fileConfig);

  if (!configFile)
  {
    Serial.println("Gagal membuka file config");
    return;
  }

  size_t size = configFile.size();
  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, buf.get());

  if (error)
  {
    Serial.println("Gagal parse file config");
    return;
  }

  Serial.println("Load data from config...");

  config.latitude = doc["latitude"];
  config.longitude = doc["longitude"];
  config.zonaWaktu = doc["zonaWaktu"];
  config.listInformasi = doc["listInformasi"].as<String>();

  configFile.close();
}

void saveConfig(JsonObject json)
{
  timerDetachInterrupt(timer);
  File configFile = SPIFFS.open(fileConfig, "w");

  if (!configFile)
  {
    Serial.println("Gagal membuka file config");
    json["error"] = true;
    json["message"] = "Gagal membuka file config";
  }

  serializeJson(json, configFile);
  configFile.close();
  json.clear();

  //
  json["error"] = false;
  json["message"] = "Data berhasil disimpan";

  initWaktuSholat();
  delay(500);
  initLED(false);
  time_now = 0;
}

void IRAM_ATTR triggerScan()
{
  dmd.scanDisplayBySPI();
}

void initLED(boolean first = true)
{
  if (first)
  {
    uint8_t cpuClock = ESP.getCpuFreqMHz();
    timer = timerBegin(0, cpuClock, true);
  }

  timerAttachInterrupt(timer, &triggerScan, true);
  timerAlarmWrite(timer, 300, true);

  timerAlarmEnable(timer);

  if (first)
    dmd.clearScreen(true);
}

void initWaktuSholat()
{
  set_calc_method(Custom);
  set_asr_method(Shafii);
  set_high_lats_adjust_method(AngleBased);
  set_fajr_angle(20);
  set_isha_angle(18);

  get_prayer_times(tahun, bulan, tanggal, config.latitude, config.longitude, config.zonaWaktu, times);

  double currTime = timeinfo.tm_hour + timeinfo.tm_min / 60.0;

  for (indexTimeActive = 0; indexTimeActive < sizeof(times) / sizeof(double); indexTimeActive++)
  {
    if (times[indexTimeActive] >= currTime)
      break;
  }

  if ((times[indexTimeActive] - currTime) < 0)
  {
    indexTimeActive = 0;
  }

  tempTimeActive = indexTimeActive;

  if (indexTimeActive == 1 || indexTimeActive == 4)
  {
    tempTimeActive++;
  }
  else if (indexTimeActive == 7)
  {
    tempTimeActive = 0;
  }

  for (size_t i = 0; i < (sizeof(indexTime) / sizeof(int *)); i++)
  {
    if (tempTimeActive == indexTime[i])
    {
      indexTimeActive = i;
    }
  }
}

/*--------------------------------------------------------------------------------------
  Fungsi untuk menampilkan waktu NTP ke LED
--------------------------------------------------------------------------------------*/
void cetakWaktu()
{
  int prevMenit = atoi(menit);
  updateWaktu();

  if (prevMenit != atoi(menit))
  {
    dmd.selectFont(HoboStd12);
    dmd.drawFilledBox(0, -3, ((7 * 32 - 13) / 32) * DMD_PIXELS_ACROSS, 7, GRAPHICS_INVERSE);
  }

  dmd.selectFont(ElektronMart6x16);

  dmd.drawString(0, 0, jam, 3, GRAPHICS_NORMAL);

  dmd.selectFont(HoboStd16);
  dmd.drawChar(14, -2, ':', atoi(detik) % 2 == 0 ? GRAPHICS_OR : GRAPHICS_NOR);

  dmd.selectFont(ElektronMart6x16);
  dmd.drawString(19, 0, menit, 2, GRAPHICS_NORMAL);
}

void cetakTanggal()
{
  if (indexTimeActive != -1)
    return;

  dmd.selectFont(ElektronMart5x6);

  char teks[10];
  sprintf(teks, "%d-%d-%d", tanggal, bulan, tahun);

  textCenter(0, teks);
  if (millis() >= time_now + INTERVAL_CETAK_WAKTU_SHOLAT * 2)
  {
    time_now += INTERVAL_CETAK_WAKTU_SHOLAT;
    indexTimeActive++;
  }
}

void cetakJamSholat()
{
  int hh, mm;
  char waktu[5];

  if (indexTimeActive == -1)
    return;

  int index = indexTime[indexTimeActive];

  if (millis() >= time_now + INTERVAL_CETAK_WAKTU_SHOLAT)
  {

    time_now += INTERVAL_CETAK_WAKTU_SHOLAT;
    get_float_time_parts(times[index], hh, mm);
    sprintf(waktu, "%02d:%02d", hh, mm);

    dmd.selectFont(ElektronMart5x6);

    // clear
    dmd.drawFilledBox(32, 0, 3 * DMD_PIXELS_ACROSS, 7, GRAPHICS_INVERSE);

    char teks[strlen(TimeName[index]) + strlen(waktu)];
    sprintf(teks, "%s %s", TimeName[index], waktu);

    textCenter(0, teks);

    // Fungsi untuk menampilkan jadwal sholat berikutnya
    if (indexTimeActive < (sizeof(indexTime) / sizeof(int *) - 1))
    {
      indexTimeActive++;
    }
    else
    {
      indexTimeActive = -1;
      // clear
      dmd.drawFilledBox(32, 0, 3 * DMD_PIXELS_ACROSS, 7, GRAPHICS_INVERSE);
    }
  }
}

void cetakInfo()
{
  Config _config = config;
  DynamicJsonDocument jsonInformasi(512);
  deserializeJson(jsonInformasi, _config.listInformasi);
  jsonInformasi.shrinkToFit();

  for (size_t i = 0; i < jsonInformasi.size(); i++)
  {
    dmd.selectFont(CooperBlack10);
    const char *MSG = jsonInformasi[i];
    dmd.drawMarquee(MSG, strlen(MSG), (32 * KOLOM) + 0, 8);
    boolean ret = false;
    long start = millis();

    while (!ret)
    {
      if ((start + 70) < millis())
      {
        dmd.selectFont(CooperBlack10);
        ret = dmd.stepSplitMarquee(9, 15, 39);

        start = millis();
      }

      if (updateInformasi)
      {
        ret = true;
        dmd.clearScreen(true);
      }

      cetakWaktu();
      cetakTanggal();
      cetakJamSholat();
    }
  }
  updateInformasi = false;
}

void updateWaktu()
{
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Gagal mengambil waktu dari server");
    return;
  }

  tahun = timeinfo.tm_year + 1900;
  bulan = timeinfo.tm_mon + 1;
  tanggal = timeinfo.tm_mday;

  strftime(jam, 3, "%H", &timeinfo);
  strftime(menit, 3, "%M", &timeinfo);
  strftime(detik, 3, "%S", &timeinfo);
}

void textCenter(int y, char *Msg)
{
  int width = 0;
  for (size_t i = 0; i < strlen(Msg); i++)
  {
    width += dmd.charWidth(Msg[i]);
  }

  int center = int(((31 * (KOLOM + 1)) - width) / 2);

  dmd.drawString(center, y, Msg, strlen(Msg), GRAPHICS_NORMAL);
}