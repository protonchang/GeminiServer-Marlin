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
#pragma once

/**
 * Arduino Mega with RAMPS v1.4 for Anycubic
 */

#define BOARD_INFO_NAME "Anycubic RAMPS 1.4"

// Board labeled pins:

#define TG_HEATER_BED_PIN                      8
#define TG_HEATER_0_PIN                       10
#define TG_HEATER_1_PIN                       45  // Anycubic Kossel: Unused

#define TG_FAN0_PIN                            9  // Anycubic Kossel: Usually the part cooling fan
#define TG_FAN1_PIN                            7  // Anycubic Kossel: Unused
#define TG_FAN2_PIN                           44  // Anycubic Kossel: Hotend fan

#ifndef CONTROLLER_FAN_PIN
  #define CONTROLLER_FAN_PIN           TG_FAN1_PIN
#endif

// ?? #define BEEPER_PIN                            31
#define SD_DETECT_PIN                         49
//
// Servos
//
#if MB(TRIGORILLA_14_11)
  #define SERVO0_PIN                           5
  #define SERVO1_PIN                           4
  #define SERVO2_PIN                          11
  #define SERVO3_PIN                           6
#endif

//
// PWM FETS
//
#if EITHER(FET_ORDER_EEF, FET_ORDER_EEB)
  #define MOSFET_B_PIN                        45  // HEATER1
#elif FET_ORDER_EFB
  #define MOSFET_B_PIN                         9  // FAN0
#else
  #define MOSFET_B_PIN                         7  // FAN1
#endif

#if FET_ORDER_EEB
  #define MOSFET_C_PIN                         8  // BED
#elif FET_ORDER_EFB
  #if DISABLED(ANYCUBIC_LCD_CHIRON)
    #define MOSFET_C_PIN                       8
  #else
    #define MOSFET_C_PIN                      45
  #endif
#else                                             // EEF, EFF
  #define MOSFET_C_PIN                         9
#endif

#if FET_ORDER_EEB
  #define FAN_PIN                              9  // Override pin 4 in pins_RAMPS.h
#endif

//
// Heaters / Fans
//
#if ANY(FET_ORDER_EEF, FET_ORDER_EEB, FET_ORDER_EFB)
  #define FAN1_PIN                             7
#endif
#define FAN2_PIN                              44
#ifndef E0_AUTO_FAN_PIN
  #define E0_AUTO_FAN_PIN                     44  // Used in Anycubic Kossel example config
#endif
#if ENABLED(ANYCUBIC_LCD_I3MEGA)
  #define CONTROLLER_FAN_PIN                   7
#endif

//
// AnyCubic standard pin mappings
//
//  On most printers, endstops are NOT all wired to the appropriate pins on the Trigorilla board.
//  For instance, on a Chiron, Y axis goes to an aux connector.
//  There are also other things that have been wired in creative ways.
//  To enable PIN definitions for a specific printer model, #define the appropriate symbol after
//  MOTHERBOARD in Configuration.h

//
// Limit Switches
//
//#define ANYCUBIC_4_MAX_PRO_ENDSTOPS

#if ENABLED(ANYCUBIC_4_MAX_PRO_ENDSTOPS)
  #define X_MAX_PIN                           43
  #define Y_STOP_PIN                          19
#elif EITHER(ANYCUBIC_LCD_CHIRON, ANYCUBIC_LCD_I3MEGA)
  #define Y_STOP_PIN                          42
  #define Z2_MIN_PIN                          43
  #ifndef Z_MIN_PROBE_PIN
    #define Z_MIN_PROBE_PIN                    2
  #endif
  #ifndef FIL_RUNOUT_PIN
    #if ENABLED(ANYCUBIC_LCD_CHIRON)
      #define FIL_RUNOUT_PIN                  33
    #else
      #define FIL_RUNOUT_PIN                  19
    #endif
  #endif
  #define BEEPER_PIN                          31
  #define SD_DETECT_PIN                       49
#endif

#include "pins_RAMPS.h"

#if ENABLED(ANYCUBIC_4MAX)
#ifdef FILWIDTH_PIN
 #undef FILWIDTH_PIN
 #define FILWIDTH_PIN      -1  // Trigorilla have 2 Analog Pins on AUX (D42 & D43!)
#endif                         // ATTENTION: Onboard Description D42 is D43 and describtion D43 ist D42! ).
                               // Set this if you need FILWIDTH. Else -1!

#if HAS_DRIVER(TMC2208)
/**
 * TMC2208 stepper drivers
 *
 * Software serial settings
 *
 * Info: Following Pins can be set for TX: D6, D11, D20, D21, D42, D43
 *                                         ATTENTION: The Onboard PIN Descriptions D42, D43 are wrong (reversed)!
 *                                         Onboard Pin Description D42 is D43 and Pin describtion D43 is D42!
 * Info: Following Pins can be set for RX: D12 ( Additional and alternatively (instead of using the SD-Card): 50, 51, 52, 53.  )
 *                                         You do not need RX Pins. But useful for testing purpose.
 *
 * Info: Recommendation is to use UART RX Pin only for the Extruder E0!
 */

 // Software serial  E0
  #ifdef E0_SERIAL_TX_PIN
    #undef E0_SERIAL_TX_PIN
    #define E0_SERIAL_TX_PIN    -1
  #endif
  #ifdef E0_SERIAL_RX_PIN
    #undef E0_SERIAL_RX_PIN
    #define E0_SERIAL_RX_PIN    -1
  #endif

 // Software serial  X
  #ifdef X_SERIAL_TX_PIN
   #undef X_SERIAL_TX_PIN
   #define X_SERIAL_TX_PIN    -1
  #endif
  #ifdef X_SERIAL_RX_PIN
   #undef X_SERIAL_RX_PIN
   #define X_SERIAL_RX_PIN    -1
  #endif

  // Software serial  Y
  #ifdef Y_SERIAL_TX_PIN
   #undef Y_SERIAL_TX_PIN
   #define Y_SERIAL_TX_PIN    -1
  #endif
  #ifdef Y_SERIAL_RX_PIN
   #undef Y_SERIAL_RX_PIN
   #define Y_SERIAL_RX_PIN    -1
  #endif

  // Software serial  Z
  #ifdef Z_SERIAL_TX_PIN
   #undef Z_SERIAL_TX_PIN
   #define Z_SERIAL_TX_PIN    -1
  #endif
  #ifdef Z_SERIAL_RX_PIN
   #undef Z_SERIAL_RX_PIN
   #define Z_SERIAL_RX_PIN    -1
  #endif

#endif //TMC2208

#ifdef BTN_EN1
  #undef BTN_EN1
  #define BTN_EN1          33  // Anycubic 4MAX specific
#endif

#ifdef BTN_EN2
  #undef BTN_EN2
  #define BTN_EN2          31  // Anycubic 4MAX specific
#endif

#ifdef KILL_PIN
  #undef KILL_PIN
  #define KILL_PIN         -1  // Anycubic 4MAX specific
#endif

#endif // IF ENABLED(ANYCUBIC_4MAX)

//
// AnyCubic made the following changes to 1.1.0-RC8
// If these are appropriate for your LCD let us know.
//
#if 0 && HAS_WIRED_LCD

  // LCD Display output pins
  #if BOTH(IS_NEWPANEL, PANEL_ONE)
    #undef LCD_PINS_D6
    #define LCD_PINS_D6                       57
  #endif

  // LCD Display input pins
  #if IS_NEWPANEL
    #if ANY(VIKI2, miniVIKI)
      #undef DOGLCD_A0
      #define DOGLCD_A0                       23
    #elif ENABLED(ELB_FULL_GRAPHIC_CONTROLLER)
      #undef BEEPER_PIN
      #define BEEPER_PIN                      33
      #undef LCD_BACKLIGHT_PIN
      #define LCD_BACKLIGHT_PIN               67
    #endif
  #elif ENABLED(MINIPANEL)
    #undef BEEPER_PIN
    #define BEEPER_PIN                        33
    #undef DOGLCD_A0
    #define DOGLCD_A0                         42
  #endif

#endif // HAS_WIRED_LCD
