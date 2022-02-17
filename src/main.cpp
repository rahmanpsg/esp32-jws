#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DMD32.h>
#include <WaktuSholat.h>
#include "time.h"
#include "SPIFFS.h"
#include "WebPage.h"
#include "fonts/HoboStd12.h"
#include "fonts/HoboStd16.h"
#include "fonts/Calibri10.h"
#include "fonts/CooperBlack10.h"

const char *ssid = "HUAWEI nova 5T";
const char *password = "leppangang1";

AsyncWebServer server(80);

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 28800; // GMT +8
const int daylightOffset_sec = 3600;

struct tm timeinfo;

char jam[3];
char menit[3];
char detik[3];

double times[sizeof(TimeName) / sizeof(char *)];
int indexTime[] = {0, 2, 3, 5, 6};
int indexTimeActive = 0;
int tempTimeActive = 0;

#define INTERVAL_CETAK_WAKTU_SHOLAT 5000
unsigned long time_now = 0;
unsigned long time_now2 = 0;

int tahun, bulan, tanggal;

float lat = -3.7861;
float lng = 119.6522;
byte zonaWaktu = 8;

// Fire up the DMD library as dmd
#define KOLOM 3
#define BARIS 1

DMD dmd(KOLOM, BARIS);

// Timer setup
// create a hardware timer  of ESP32
hw_timer_t *timer = NULL;

void initialisasiWaktuSholat();
void updateWaktu();
void cetakWaktu();
void cetakJamSholat();
void cetakInfo();
void IRAM_ATTR triggerScan();

// Replaces placeholder with LED state value
String processor(const String &var)
{
  Serial.println(var);
  return String();
}

void handleNotFound(AsyncWebServerRequest *request)
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += request->url();
  message += "\nMethod: ";
  message += (request->method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += request->args();
  message += "\n";

  for (uint8_t i = 0; i < request->args(); i++)
  {
    message += " " + request->argName(i) + ": " + request->arg(i) + "\n";
  }

  request->send(404, "text/plain", message);
}

bool loadFromSPIFFS(AsyncWebServerRequest *request, String path)
{
  String dataType = "text/html";

  Serial.print("Requested page -> ");
  Serial.println(path);
  if (SPIFFS.exists(path))
  {
    File dataFile = SPIFFS.open(path, "r");
    if (!dataFile)
    {
      handleNotFound(request);
      return false;
    }

    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, path, dataType);
    Serial.print("Real file path: ");
    Serial.println(path);

    request->send(response);

    dataFile.close();
  }
  else
  {
    handleNotFound(request);
    return false;
  }
  return true;
}

void handleRoot(AsyncWebServerRequest *request)
{
  loadFromSPIFFS(request, "/index.html");
}

void setup(void)
{
  Serial.begin(9600);

  // Initialize SPIFFS
  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

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

  // Route for root / web page
  server.on("/", handleRoot);
  // server.serveStatic("/", SPIFFS, "/").setDefaultFile("/index.html");

  // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  //           { request->send_P(200, "text/html", webpage); });

  // Start server
  server.begin();

  // init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  updateWaktu();

  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

  initialisasiWaktuSholat();

  // return the clock speed of the CPU
  uint8_t cpuClock = ESP.getCpuFreqMHz();

  // Use 1st timer of 4
  // devide cpu clock speed on its speed value by MHz to get 1us for each signal  of the timer
  timer = timerBegin(0, cpuClock, true);
  // Attach triggerScan function to our timer
  timerAttachInterrupt(timer, &triggerScan, true);
  // Set alarm to call triggerScan function
  // Repeat the alarm (third parameter)
  timerAlarmWrite(timer, 300, true);

  // Start an alarm
  timerAlarmEnable(timer);

  // clear/init the DMD pixels held in RAM
  dmd.clearScreen(true); // true is normal (all pixels off), false is negative (all pixels on)
}

void loop(void)
{
  cetakWaktu();
  cetakJamSholat();
  cetakInfo();
}

/*--------------------------------------------------------------------------------------
  Interrupt handler for Timer1 (TimerOne) driven DMD refresh scanning, this gets
  called at the period set in Timer1.initialize();
--------------------------------------------------------------------------------------*/
void IRAM_ATTR triggerScan()
{
  dmd.scanDisplayBySPI();
}

void initialisasiWaktuSholat()
{
  set_calc_method(Custom);
  set_asr_method(Shafii);
  set_high_lats_adjust_method(AngleBased);
  set_fajr_angle(20);
  set_isha_angle(18);

  get_prayer_times(tahun, bulan, tanggal, lat, lng, zonaWaktu, times);

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
    dmd.drawFilledBox(0, -3, ((7 * 32 - 13) / 32) * DMD_PIXELS_ACROSS - 1, 7, GRAPHICS_INVERSE);
  }

  int bx = 0;

  if (jam[0] == '0' || jam[0] == '4' || jam[0] == '6' || jam[0] == '8' || jam[0] == '9')
    bx += 4;
  if (jam[1] == '0' || jam[1] == '4' || jam[1] == '6' || jam[1] == '8' || jam[1] == '9')
    bx += 4;

  if (jam[0] == '2' || jam[0] == '3' || jam[0] == '5')
    bx += 3;
  if (jam[1] == '2' || jam[1] == '3' || jam[1] == '5')
    bx += 3;

  if (jam[0] == '7')
    bx += 2;
  if (jam[1] == '7')
    bx += 2;

  dmd.selectFont(HoboStd12);

  dmd.drawString(0, 1, jam, 3, GRAPHICS_NORMAL);

  dmd.selectFont(HoboStd16);
  dmd.drawChar(8 + bx, -3, ':', atoi(detik) % 2 == 0 ? GRAPHICS_OR : GRAPHICS_NOR);

  dmd.selectFont(HoboStd12);
  dmd.drawString(13 + bx, 1, menit, 2, GRAPHICS_NORMAL);
}

void cetakJamSholat()
{
  int hh, mm;
  char waktu[5];
  int index = indexTime[indexTimeActive];

  if (millis() >= time_now + INTERVAL_CETAK_WAKTU_SHOLAT)
  {
    time_now += INTERVAL_CETAK_WAKTU_SHOLAT;
    get_float_time_parts(times[index], hh, mm);
    sprintf(waktu, "%02d:%02d", hh, mm);

    dmd.selectFont(Calibri10);

    // clear
    dmd.drawFilledBox(37, -2, ((7 * 32 - 37) / 32) * DMD_PIXELS_ACROSS - 1, 7, GRAPHICS_INVERSE);

    dmd.drawString(37, -2, TimeName[index], strlen(TimeName[index]), GRAPHICS_OR);
    dmd.drawString(72, -2, waktu, 5, GRAPHICS_OR);

    if (indexTimeActive < (sizeof(indexTime) / sizeof(int *) - 1))
    {
      indexTimeActive++;
    }
    else
    {
      indexTimeActive = 0;
    }
  }
}

void cetakInfo()
{
  dmd.selectFont(CooperBlack10);
  const char *MSG = "MOHON MATIKAN HP ANDA...";
  dmd.drawMarquee(MSG, strlen(MSG), (32 * KOLOM) + 0, 8);
  boolean ret = false;
  long start = millis();
  long timer = start;

  while (!ret)
  {
    if ((timer + 70) < millis())
    {
      dmd.selectFont(CooperBlack10);
      ret = dmd.stepSplitMarquee(9, 15, 41);

      timer = millis();

      cetakWaktu();
      cetakJamSholat();
    }
  }
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

  // double currTime = timeinfo.tm_hour + timeinfo.tm_min / 60.0;

  // for (indexTimeActive = 0; indexTimeActive < sizeof(times) / sizeof(double); indexTimeActive++)
  // {
  //   if (times[indexTimeActive] >= currTime)
  //     break;
  // }
}
