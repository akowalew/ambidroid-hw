#include <Adafruit_NeoPixel.h>
#include <string.h>

#define MEASURE_SPEED

constexpr auto NeopixelPin = 6;
constexpr auto NeopixelCount = 48;
constexpr auto NeopixelConfig = (NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NeopixelCount, NeopixelPin, NeopixelConfig);

constexpr auto SerialBaudrate = 57600;
constexpr auto SerialConfig = SERIAL_8E1;

constexpr auto PixelCount = NeopixelCount;
constexpr auto BytesPerPixel = 3;
constexpr auto BufferSize = ((BytesPerPixel * PixelCount));
byte buffer[BufferSize];

void setup() {
  Serial.begin(SerialBaudrate, SerialConfig);
  Serial.println("Initializing...");
  
  strip.begin();
  strip.show();
  Serial.println("Initialized");
}

void loop() {
  size_t bytesRead = Serial.readBytes(buffer, BufferSize);
  if(bytesRead < BufferSize) {
    Serial.println("Could not read bytes");
    return;
  }

#ifdef MEASURE_SPEED
  const auto beginTime = micros();
#endif

  auto pixels = strip.getPixels();
  memcpy(pixels, &buffer[0], sizeof(buffer));
  strip.show();

#ifdef MEASURE_SPEED
  const auto endTime = micros();
  const auto duration = (endTime - beginTime);
  Serial.println(duration);
#endif
}
