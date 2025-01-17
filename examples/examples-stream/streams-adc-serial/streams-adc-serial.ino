/**
 * @file streams-analog-serial.ino
 * @author Phil Schatzmann
 * @brief see https://github.com/pschatzmann/arduino-audio-tools/blob/main/examples/examples-stream/streams-adc-serial/README.md
 * @copyright GPLv3
 * #TODO retest is outstanding
 */

#include "Arduino.h"
#include "AudioTools.h"

AnalogAudioStream in; 
AudioInfo info(8000, 1, 16);
CsvOutput<int16_t> out(Serial); // ASCII output stream 
StreamCopy copier(out, in); // copy i2sStream to CsvOutput
ConverterAutoCenter<int16_t> center(2); // set avg to 0

// Arduino Setup
void setup(void) {
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Info);

  // RX automatically uses port 0 with pins GPIO34,GPIO35
  auto cfgRx = in.defaultConfig(RX_MODE);
  cfgRx.copyFrom(info);
  in.begin(cfgRx);

  // open output
  out.begin(info);

}

// Arduino loop - copy data 
void loop() {
  copier.copy(center);
}