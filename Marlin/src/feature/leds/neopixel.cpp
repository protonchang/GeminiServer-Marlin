/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

/**
 * Marlin RGB LED general support
 */

#include "../../inc/MarlinConfig.h"

#if ENABLED(NEOPIXEL_LED)
  #include "leds.h"
#endif

#if EITHER(NEOPIXEL_STARTUP_TEST, NEOPIXEL2_STARTUP_TEST)
  #include "../../core/utility.h"
#endif

Marlin_NeoPixel neo;
pixel_index_t Marlin_NeoPixel::neoindex;

Adafruit_NeoPixel Marlin_NeoPixel::adaneo1(NEOPIXEL_PIXELS, NEOPIXEL_PIN, NEOPIXEL_TYPE + NEO_KHZ800);
#if CONJOINED_NEOPIXEL
  Adafruit_NeoPixel Marlin_NeoPixel::adaneo2(NEOPIXEL_PIXELS, NEOPIXEL2_PIN, NEOPIXEL2_TYPE + NEO_KHZ800);
#endif

#ifdef NEOPIXEL_BKGD_INDEX_FIRST

  void Marlin_NeoPixel::set_background_color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t w) {
    for (int background_led = NEOPIXEL_BKGD_INDEX_FIRST; background_led <= NEOPIXEL_BKGD_INDEX_LAST; background_led++)
      set_pixel_color(background_led, adaneo1.Color(r, g, b, w));
    
    #if MULTIPLE_NEOPIXEL_TYPES
    for  (int background_led = NEOPIXEL_BKGD_INDEX_FIRST; background_led <= NEOPIXEL_BKGD_INDEX_LAST; background_led++)
      set_pixel_color(background_led,  adaneo2.Color(r, g, b, w));
    #endif
  }

  void Marlin_NeoPixel::reset_background_color() {
    constexpr uint8_t background_color[4] = NEOPIXEL_BKGD_COLOR;
    set_background_color(background_color);
  }

#endif

void Marlin_NeoPixel::set_color(const uint32_t color) {
  if (neoindex >= 0) {
    set_pixel_color(neoindex, color);
    neoindex = -1;
  }
  else {
    for (uint16_t i = 0; i < pixels(); ++i) {
      #ifdef NEOPIXEL_BKGD_INDEX_FIRST
        if (i == NEOPIXEL_BKGD_INDEX_FIRST && TERN(NEOPIXEL_BKGD_ALWAYS_ON, true, color != 0x000000)) {
          reset_background_color();
          i += NEOPIXEL_BKGD_INDEX_LAST - (NEOPIXEL_BKGD_INDEX_FIRST);
          continue;
        }
      #endif
      set_pixel_color(i, color);
    }
  }
  show();
}

void Marlin_NeoPixel::set_color_startup(const uint32_t color) {
  for (uint16_t i = 0; i < neo.pixels(); i++){  // i: set_pixel_color --> n Pixel index is starting from 0.
    set_pixel_color(i, color);
    #if MULTIPLE_NEOPIXEL_TYPES
      if( i < neo.pixels(1)) set_pixel_color(i, color, 1);
    #endif
  }
  show();
}

#if ENABLED(NEOPIXEL_TEST_PIXEL)
void Marlin_NeoPixel::set_pixel_color_startup(const uint32_t color) {
  for ( uint16_t i= 0; i < pixels(); i++){  // i: set_pixel_color --> n  Pixel index is starting from 0.
    set_pixel_color(i, color); 
    #if MULTIPLE_NEOPIXEL_TYPES
      if( i < pixels(1)) set_pixel_color(i, color, 1);
    #endif
    show();
    safe_delay(NEOPIXEL_TEST_PIXEL_DELAY);
  }
  #if ENABLED(NEOPIXEL_TEST_PIXEL_ROTATE_BACK)
    for ( uint16_t i= pixels(); i>0; i--){  // i: set_pixel_color --> n  Pixel index is starting from 0.
      set_pixel_color(i-1, adaneo1.Color(0, 0, 0, 0)); 
      #if MULTIPLE_NEOPIXEL_TYPES
        if( i < pixels(1)) set_pixel_color(i-1, adaneo2.Color(0, 0, 0, 0), 1); ;
      #endif
      show();
      safe_delay(NEOPIXEL_TEST_PIXEL_DELAY);
    }
  #endif
}

void Marlin_NeoPixel::test_neopixel() {
  #ifdef NEOPIXEL_TEST_PIXEL_COLOR_1
    uint8_t text_pixel_color1[4] = NEOPIXEL_TEST_PIXEL_COLOR_1;
    set_pixel_color_startup(adaneo1.Color(text_pixel_color1[0], text_pixel_color1[1], text_pixel_color1[2], text_pixel_color1[3]));
    #ifdef NEOPIXEL_TEST_PIXEL_COLOR_2
      uint8_t text_pixel_color2[4] = NEOPIXEL_TEST_PIXEL_COLOR_2;
      set_pixel_color_startup(adaneo1.Color(text_pixel_color2[0], text_pixel_color2[1], text_pixel_color2[2], text_pixel_color2[3]));
      #ifdef NEOPIXEL_TEST_PIXEL_COLOR_3
        uint8_t text_pixel_color3[4] = NEOPIXEL_TEST_PIXEL_COLOR_3;
        set_pixel_color_startup(adaneo1.Color(text_pixel_color3[0], text_pixel_color3[1], text_pixel_color3[2], text_pixel_color3[3]));
      #endif
    #endif
  #else // !EITHER(NEOPIXEL_TEST_PIXEL_COLOR_1, NEOPIXEL_TEST_PIXEL_COLOR_2, NEOPIXEL_TEST_PIXEL_COLOR_3)
    uint8_t text_pixel_color[4]= { 255, 0, 0, 0 };
    set_pixel_color_startup(adaneo1.Color(text_pixel_color[0], text_pixel_color[1], text_pixel_color[2], text_pixel_color[3));
  #endif
}
#endif // ENABLED(NEOPIXEL_TEST_PIXEL)

void Marlin_NeoPixel::init() {
  neoindex = -1;                       // -1 .. NEOPIXEL_PIXELS-1 range
  set_brightness(NEOPIXEL_BRIGHTNESS); //  0 .. 255 range
  begin();
  show();  // initialize to all off

  #if ENABLED(NEOPIXEL_STARTUP_TEST)
    set_color_startup(adaneo1.Color(255, 0, 0, 0));  // red
/*    safe_delay(1000);
    fill_color(adaneo1.Color(0, 255, 0, 0),0,pixels());  // green
    safe_delay(1000);
    fill_color(adaneo1.Color(0, 0, 255, 0),0,pixels());  // blue
    safe_delay(1000);
    */
    safe_delay(500);
    set_color_startup(adaneo1.Color(0, 255, 0, 0));  // green
    safe_delay(500);
    set_color_startup(adaneo1.Color(0, 0, 255, 0));  // blue
    safe_delay(500);
    #if HAS_WHITE_LED
      set_color_startup(adaneo1.Color(0, 0, 0, 255));  // white
      safe_delay(500);
    #endif
  #endif
  
  #if ENABLED(NEOPIXEL_STARTUP_TEST_PIXEL)
    test_neopixel();
  #endif


  #ifdef NEOPIXEL_BKGD_INDEX_FIRST
    reset_background_color();
  #endif

  set_color(adaneo1.Color
    TERN(LED_USER_PRESET_STARTUP,
      (LED_USER_PRESET_RED, LED_USER_PRESET_GREEN, LED_USER_PRESET_BLUE, LED_USER_PRESET_WHITE),
      (255, 255, 255, 255))
  );
}

#if ENABLED(NEOPIXEL2_SEPARATE)

  Marlin_NeoPixel2 neo2;

  pixel_index_t Marlin_NeoPixel2::neoindex;
  Adafruit_NeoPixel Marlin_NeoPixel2::adaneo(NEOPIXEL2_PIXELS, NEOPIXEL2_PIN, NEOPIXEL2_TYPE);

  void Marlin_NeoPixel2::set_color(const uint32_t color) {
    if (neoindex >= 0) {
      set_pixel_color(neoindex, color);
      neoindex = -1;
    }
    else {
      for (uint16_t i = 0; i < pixels(); ++i)
        set_pixel_color(i, color);
    }
    show();
  }

  void Marlin_NeoPixel2::set_color_startup(const uint32_t color) {
    for (uint16_t i = 0; i < pixels(); ++i)
      set_pixel_color(i, color);
    show();
  }

  void Marlin_NeoPixel2::init() {
    neoindex = -1;                        // -1 .. NEOPIXEL2_PIXELS-1 range
    set_brightness(NEOPIXEL2_BRIGHTNESS); //  0 .. 255 range
    begin();
    show();  // initialize to all off

    #if ENABLED(NEOPIXEL2_STARTUP_TEST)
      set_color_startup(adaneo.Color(255, 0, 0, 0));  // red
      safe_delay(500);
      set_color_startup(adaneo.Color(0, 255, 0, 0));  // green
      safe_delay(500);
      set_color_startup(adaneo.Color(0, 0, 255, 0));  // blue
      safe_delay(500);
      #if HAS_WHITE_LED2
        set_color_startup(adaneo.Color(0, 0, 0, 255));  // white
        safe_delay(500);
      #endif
    #endif

    set_color(adaneo.Color
      TERN(NEO2_USER_PRESET_STARTUP,
        (NEO2_USER_PRESET_RED, NEO2_USER_PRESET_GREEN, NEO2_USER_PRESET_BLUE, NEO2_USER_PRESET_WHITE),
        (0, 0, 0, 0))
    );
  }

#endif // NEOPIXEL2_SEPARATE