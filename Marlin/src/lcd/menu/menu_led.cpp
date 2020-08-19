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

//
// LED Menu
//

#include "../../inc/MarlinConfigPre.h"

#if HAS_LCD_MENU && EITHER(LED_CONTROL_MENU, CASE_LIGHT_MENU)

#include "menu.h"
#if ENABLED(LED_CONTROL_MENU)
  #include "../../feature/leds/leds.h"
// meine änderungen // <<<<<<< HEAD
// meine änderungen // =======

  #if ENABLED(LED_COLOR_PRESETS)
    void menu_led_presets() {
      START_MENU();
      #if LCD_HEIGHT > 2
        STATIC_ITEM(MSG_LED_PRESETS, SS_DEFAULT|SS_INVERT);
      #endif
      BACK_ITEM(MSG_LED_CONTROL);
      ACTION_ITEM(MSG_SET_LEDS_WHITE, leds.set_white);
      ACTION_ITEM(MSG_SET_LEDS_RED, leds.set_red);
      ACTION_ITEM(MSG_SET_LEDS_ORANGE, leds.set_orange);
      ACTION_ITEM(MSG_SET_LEDS_YELLOW,leds.set_yellow);
      ACTION_ITEM(MSG_SET_LEDS_GREEN, leds.set_green);
      ACTION_ITEM(MSG_SET_LEDS_BLUE, leds.set_blue);
      ACTION_ITEM(MSG_SET_LEDS_INDIGO, leds.set_indigo);
      ACTION_ITEM(MSG_SET_LEDS_VIOLET, leds.set_violet);
      END_MENU();
    }

  #endif

  void menu_led_custom() {
    START_MENU();
    BACK_ITEM(MSG_LED_CONTROL);
    EDIT_ITEM(uint8, MSG_INTENSITY_R, &leds.color.r, 0, 255, leds.update, true);
    EDIT_ITEM(uint8, MSG_INTENSITY_G, &leds.color.g, 0, 255, leds.update, true);
    EDIT_ITEM(uint8, MSG_INTENSITY_B, &leds.color.b, 0, 255, leds.update, true);
    #if EITHER(RGBW_LED, NEOPIXEL_LED)
      EDIT_ITEM(uint8, MSG_INTENSITY_W, &leds.color.w, 0, 255, leds.update, true);
      #if ENABLED(NEOPIXEL_LED)
        EDIT_ITEM(uint8, MSG_LED_BRIGHTNESS, &leds.color.i, 0, 255, leds.update, true);
      #endif
    #endif
    END_MENU();
  }
//>>>>>>> upstream/bugfix-2.0.x
#endif
#if ENABLED(CASE_LIGHT_MENU)
  #include "../../feature/caselight.h"
#endif

// meine änderungen // <<<<<<< HEAD
// meine änderungen // #if ENABLED(LED_CONTROL_MENU)
// meine änderungen // void menu_led_custom() {
// meine änderungen //   START_MENU();
// meine änderungen //   BACK_ITEM(MSG_LED_CONTROL);
// meine änderungen //   EDIT_ITEM_FAST(percent, MSG_INTENSITY_R, &leds.color.r, 0, 255, leds.update, true);
// meine änderungen //   EDIT_ITEM_FAST(percent, MSG_INTENSITY_G, &leds.color.g, 0, 255, leds.update, true);
// meine änderungen //   EDIT_ITEM_FAST(percent, MSG_INTENSITY_B, &leds.color.b, 0, 255, leds.update, true);
// meine änderungen //   #if EITHER(RGBW_LED)
// meine änderungen //     EDIT_ITEM_FAST(percent, MSG_INTENSITY_W, &leds.color.w, 0, 255, leds.update, true);
// meine änderungen //   #endif
// meine änderungen //   END_MENU();
// meine änderungen // }
// meine änderungen // void menu_led_presets() {
// meine änderungen //   START_MENU();
// meine änderungen //   /*  // Nice but really no needful.
// meine änderungen //   #if LCD_HEIGHT > 2
// meine änderungen //     STATIC_ITEM(MSG_LED_PRESETS, SS_CENTER|SS_INVERT);
// meine änderungen //   #endif
// meine änderungen //   */
// meine änderungen //   BACK_ITEM(MSG_LED_CONTROL);
// meine änderungen //   ACTION_ITEM(MSG_SET_LEDS_DEFAULT, leds.set_default);
// meine änderungen //   #if ENABLED(LED_COLOR_PRESETS)
// meine änderungen //     ACTION_ITEM(MSG_SET_LEDS_WHITE, leds.set_white);
// meine änderungen //     ACTION_ITEM(MSG_SET_LEDS_RED, leds.set_red);
// meine änderungen //     ACTION_ITEM(MSG_SET_LEDS_ORANGE, leds.set_orange);
// meine änderungen //     ACTION_ITEM(MSG_SET_LEDS_YELLOW,leds.set_yellow);
// meine änderungen //     ACTION_ITEM(MSG_SET_LEDS_GREEN, leds.set_green);
// meine änderungen //     ACTION_ITEM(MSG_SET_LEDS_BLUE, leds.set_blue);
// meine änderungen //     ACTION_ITEM(MSG_SET_LEDS_INDIGO, leds.set_indigo);
// meine änderungen //     ACTION_ITEM(MSG_SET_LEDS_VIOLET, leds.set_violet);
// meine änderungen // =======
  #if DISABLED(CASE_LIGHT_NO_BRIGHTNESS)
    void menu_case_light() {
      START_MENU();
      BACK_ITEM(MSG_CONFIGURATION);
      EDIT_ITEM(percent, MSG_CASE_LIGHT_BRIGHTNESS, &caselight.brightness, 0, 255, caselight.update_brightness, true);
      EDIT_ITEM(bool, MSG_CASE_LIGHT, (bool*)&caselight.on, caselight.update_enabled);
      END_MENU();
    }
//>>>>>>> upstream/bugfix-2.0.x
  #endif
  //END_MENU();
//}
//#endif

void menu_led() {
  START_MENU();
// meine änderungen // <<<<<<< HEAD
// meine änderungen //   BACK_ITEM(MSG_CONFIGURATION);
// meine änderungen //   bool led_on;
// meine änderungen //   #if ENABLED(CASE_LIGHT_MENU)
// meine änderungen //     #if DISABLED(CASE_LIGHT_NO_BRIGHTNESS)
// meine änderungen //     if (true
// meine änderungen //       #if DISABLED(CASE_LIGHT_USE_NEOPIXEL)
// meine änderungen //         && PWM_PIN(CASE_LIGHT_PIN)
// meine änderungen //       #endif
// meine änderungen //     )
// meine änderungen //     {
// meine änderungen //       #if DISABLED(CASE_LIGHT_NO_BRIGHTNESS)
// meine änderungen //         EDIT_ITEM(bool, MSG_CASE_LIGHT, (bool*)&case_light_on, update_case_light);
// meine änderungen //         led_on=case_light_on;
// meine änderungen //         if(led_on) {
// meine änderungen //           EDIT_ITEM(percent, MSG_CASE_LIGHT_BRIGHTNESS, &case_light_brightness, 0, 255, update_case_light, true);
// meine änderungen //         }
// meine änderungen //       #else
// meine änderungen //         #if ENABLED(LED_CONTROL_MENU)
// meine änderungen //           led_on = leds.lights_on;
// meine änderungen //           EDIT_ITEM(bool, MSG_LEDS, &led_on, leds.toggle);
// meine änderungen //         #endif
// meine änderungen //       #endif
// meine änderungen //     }
// meine änderungen //     else
// meine änderungen //   #endif
// meine änderungen //     {
// meine änderungen //       EDIT_ITEM(bool, MSG_CASE_LIGHT, (bool*)&case_light_on, update_case_light);
// meine änderungen //       led_on=case_light_on;
// meine änderungen //     }
// meine änderungen //   #endif
// meine änderungen // 
// meine änderungen //   #if ENABLED(LED_CONTROL_MENU)
// meine änderungen //     if(led_on) {
// meine änderungen //       #if ENABLED(NEOPIXEL_LED) 
// meine änderungen //         #if !(ENABLED(CASE_LIGHT_MENU) && DISABLED(CASE_LIGHT_NO_BRIGHTNESS))
// meine änderungen //           EDIT_ITEM_FAST(percent, MSG_LED_BRIGHTNESS,  &leds.color.i, 0, 255, leds.update, true);
// meine änderungen //         #endif
// meine änderungen //       #endif
// meine änderungen //       SUBMENU(MSG_CUSTOM_LEDS, menu_led_custom);
// meine änderungen //       SUBMENU(MSG_LED_PRESETS, menu_led_presets);
// meine änderungen //       #if ENABLED(NEOPIXEL_TEST_PIXEL)
// meine änderungen //         ACTION_ITEM(MSG_LED_TEST_NEOPIXEL, leds.test_neo_pixel);
// meine änderungen //       #endif
// meine änderungen //     }
// meine änderungen // 
// meine änderungen // =======
  BACK_ITEM(MSG_MAIN);
  #if ENABLED(LED_CONTROL_MENU)
    bool led_on = leds.lights_on;
    EDIT_ITEM(bool, MSG_LEDS, &led_on, leds.toggle);
    ACTION_ITEM(MSG_SET_LEDS_DEFAULT, leds.set_default);
    #if ENABLED(LED_COLOR_PRESETS)
      SUBMENU(MSG_LED_PRESETS, menu_led_presets);
    #endif
    SUBMENU(MSG_CUSTOM_LEDS, menu_led_custom);
  #endif
  //
  // Set Case light on/off/brightness
  //
  #if ENABLED(CASE_LIGHT_MENU)
    #if DISABLED(CASE_LIGHT_NO_BRIGHTNESS)
      if (TERN1(CASE_LIGHT_USE_NEOPIXEL, PWM_PIN(CASE_LIGHT_PIN)))
        SUBMENU(MSG_CASE_LIGHT, menu_case_light);
      else
    #endif
        EDIT_ITEM(bool, MSG_CASE_LIGHT, (bool*)&caselight.on, caselight.update_enabled);
//>>>>>>> upstream/bugfix-2.0.x
  #endif
  END_MENU();
}

#endif // HAS_LCD_MENU && EITHER(LED_CONTROL_MENU, CASE_LIGHT_MENU)
