/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_H
#define CONFIG_H

#ifdef BLE60
#define KEYBOARD_60
#elif defined MODELM
#define KEYBOARD_MODELM
#else
#error PLEASE SPECIFIC ONE KEYBOARD
#endif

/* HID Device descriptor parameter */
#define VENDOR_ID       0x1915
#define PRODUCT_ID      0xEEEE
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Lotlab"
#define DESCRIPTION     BLE keyboard base t.m.k firmware

#ifdef KEYBOARD_60

    #define PRODUCT         "GT BLE60 rev.D"

    /* key matrix size */
    #define MATRIX_ROWS 5
    #define MATRIX_COLS 14

    #define KEYBOARD_REVD          //键盘硬件版本配置
    
    #define UART_SUPPORT
    #define BLE_LINK_SEC         //启用此选项，蓝牙配对时要求输入密码,并启用MITM
    #define WDT_ENABLE           //启用看门狗
#endif

#ifdef KEYBOARD_MODELM

    #define PRODUCT         "Model M BLE"

    /* key matrix size */
    #define MATRIX_ROWS 8
    #define MATRIX_COLS 16

    #define KEYBOARD_REV0           // PCB revision
    
    #define UART_SUPPORT
    #define BLE_LINK_SEC            // require password when pairing and enable MITM
    #define WDT_ENABLE              // watchdog enable
#endif


/* Using internal 32K crystal oscillator */
#define USE_RC_CLOCK

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    2

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

// Define Bootmagic key
#define BOOTMAGIC_KEY_BOOT              KC_U /* boot! */            // Defines the key to turn on Bluetooth at boot time (Space+U)
#define BOOTMAGIC_KEY_ERASE_BOND        KC_E /* erase bond info */  // Defines the key to erase Bluetooth pairing information at boot time (Space+E)

// Keyboard power saving parameters
#define SLEEP_SLOW_TIMEOUT 120                  // time to switch to slow scan mode after being idle (s)
#define SLEEP_OFF_TIMEOUT  900                  // time to automatically shut down after being idle (s)
//#define BLE_IDLE_TIMEOUT 60                   // time for Bluetooth to automatically shut down after being offline? (s), must be < SLEEP_OFF_TIMEOUT
#define KEYBOARD_FAST_SCAN_INTERVAL 4           // scan interval in normal mode (ms)
#define KEYBOARD_SLOW_SCAN_INTERVAL 100         // scan interval in slow mode (ms)


/**
 * Exit slow scan mode immediately after detecting a key change, rather than waiting for a full round of debounce.
 * May alleviate the issue of long response time after the first key press in slow scan mode.
 **/
#define SLOW_MODE_EARLY_EXIT

// LED auto off time (ms), set to 0 to disable
#define LED_AUTOOFF_TIME 0

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
#define NO_DEBUG

/* disable print */
#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

/* period of tapping(ms) */
#define TAPPING_TERM    150
/* tap count needed for toggling a feature */
#define TAPPING_TOGGLE  3
/* Oneshot timeout(ms) */
#define ONESHOT_TIMEOUT 300

/* Boot Magic salt key: Space */
#define BOOTMAGIC_KEY_SALT      KC_SPACE

#define BOOTMAGIC_ENABLE
#define EXTRAKEY_ENABLE
#define USB_6KRO_ENABLE
#define COMMAND_ENABLE

/* fix led state on android */
#define LED_STATE_FIX

#endif
