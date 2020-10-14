// Futaba S.BUS Decoder for Helec Wifi Kit 32
//
// Masahiro Furukawa
// June 12, 2020

// Hardware :
//
// WiFi Kit 32
// https://heltec-automation-docs.readthedocs.io/en/latest/esp32+arduino/wifi_kit_32/hardware_update_log.html#v2-1
// [PinOut] https://resource.heltec.cn/download/WiFi_Kit_32/WIFI%20Kit%2032_pinoutDiagram_V1.pdf
//

// S.BUS Protocol by Futaba
// https://blog.rikei-tawamure.com/entry/2020/03/17/120606
//
// S.BUS Decoder sample sketch
// http://www.hoihoido.com/blog/wp/?tag=s-bus
//
// https://github.com/zendes/SBUS
//
//
//
// 100000bps
// data:8bit
// stopbit:1.5
// parity:even
// http://www.ooishoo.org/wordpress/2018/08/03/sbus-to-usb-hid%E3%82%B3%E3%83%B3%E3%83%90%E3%83%BC%E3%82%BF%E3%81%AE%E5%88%B6%E4%BD%9C/
//

#include <U8x8lib.h>
#include "sbus.h"

// the OLED used
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16); // pin numbers

SBUS sbus(Serial);

void setup()
{
  u8x8.begin();

  // Font Garally (faster)
  // https://github.com/olikraus/u8g2/wiki/fntlist8x8
  u8x8.setFont(u8x8_font_chroma48medium8_r);

  // Font Garally (Medium : medium speed)
  // https://github.com/olikraus/u8g2/wiki/fntlist8x8
  u8x8.setFont(u8x8_font_profont29_2x3_f);

  // Font Garally (LARGE : super slow)
  // https://github.com/olikraus/u8g2/wiki/fntlist8x8
  u8x8.setFont(u8x8_font_inb46_4x8_n);

  u8x8.setFont(u8x8_font_saikyosansbold8_n);

  //  Serial.begin(100000, SERIAL_8E2); // SBUS requires 100000bps
  sbus.begin(false);
}

int i = 0;
char str[16];

static void doSomeWork(int val)
{
  // '\0' IS ABSOLUTELY NECESSARY
  // otherwise, arduino reboots !!
  //  sprintf(str, "%d\0", i++);
  sprintf(str, "%d\0", val);

  u8x8.drawString(0, 0, str);

  // Wait a bit before scanning again
  delay(1);
}


void loop()
{
  sbus.process();

//  Serial.print(sbus.getChannel(1));
  
  sprintf(str, "%l\0", sbus.getLastTime());
  u8x8.drawString(0, 0, str);
  sprintf(str, "%d\0", sbus.getChannel(2));
  u8x8.drawString(0, 1, str);
  sprintf(str, "%d\0", sbus.getChannel(3));
  u8x8.drawString(0, 2, str);
  sprintf(str, "%d\0", sbus.getChannel(4));
  u8x8.drawString(0, 3, str);
  sprintf(str, "%d\0", i++);
  u8x8.drawString(0, 5, str);

}
