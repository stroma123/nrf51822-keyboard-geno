/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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
#include <stdint.h>
#include <stdbool.h>
#include "wait.h"
#include "keycode.h"
#include "host.h"
#include "keymap.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "timer.h"
#include "keyboard.h"
#include "bootloader.h"
#include "action_layer.h"
#include "action_util.h"
#include "eeconfig.h"
#include "command.h"
#include "main.h"
#include "uart_driver.h"
#include "../tmk/tmk_core/common/bootloader.h"

static bool command_common(uint8_t code);
static bool command_console(uint8_t code);


static void switch_default_layer(uint8_t layer);


command_state_t command_state = ONESHOT;


bool command_proc(uint8_t code)
{
    switch (command_state) {
        case ONESHOT:
            if (!IS_COMMAND())
                return false;
            return (command_extra(code) || command_common(code));
        case CONSOLE:
            if (IS_COMMAND())
                return (command_extra(code) || command_common(code));
            else
                return (command_console_extra(code) || command_console(code));
        default:
            command_state = ONESHOT;
            return false;
    }
}

/* TODO: Refactoring is needed. */
/* This allows to define extra commands. return false when not processed. */
bool command_extra(uint8_t code) __attribute__ ((weak));
bool command_extra(uint8_t code)
{
    (void)code;
    return false;
}

bool command_console_extra(uint8_t code) __attribute__ ((weak));
bool command_console_extra(uint8_t code)
{
    (void)code;
    return false;
}


/***********************************************************
 * Command common
 ***********************************************************/
static bool command_common(uint8_t code)
{
#ifdef KEYBOARD_LOCK_ENABLE
    static host_driver_t *host_driver = 0;
#endif
	  switch (code) {
#ifdef KEYBOARD_LOCK_ENABLE
        case KC_CAPSLOCK:
            if (host_get_driver()) {
                host_driver = host_get_driver();
                clear_keyboard();
                host_set_driver(0);
                print("Locked.\n");  
            } else {
                host_set_driver(host_driver);
                print("Unlocked.\n");
            }
            break;
#endif
        case KC_PAUSE:
            clear_keyboard();
            print("\n\nbootloader... ");
            wait_ms(1000);
            bootloader_jump(); // not return
            break;
        case KC_0:
        case KC_F10:
            switch_default_layer(0);
            break;
        case KC_ESC:
        case KC_GRV:
            sleep_mode_enter(true);
            break;
        //case KC_TAB:  //切换到蓝牙后，USB会滞留在MOD键按下状态。暂时不采用此方式切换设备
        //        #ifdef UART_SUPPORT
        //        uart_switch_mode();
        //        #endif
        //    break;
        case KC_1:
            switch_default_layer((code - KC_1) + 1);
            break;
        case KC_F1:
            switch_default_layer((code - KC_F1) + 1);
            break;
        default:
            print("?");
            return false;
    }
    return true;
}


/***********************************************************
 * Command console
 ***********************************************************/
static void command_console_help(void)
{
    print("\n\t- Console -\n"
          "ESC/q:	quit\n"
#ifdef MOUSEKEY_ENABLE
          "m:	mousekey\n"
#endif
    );
}

static bool command_console(uint8_t code)
{
    switch (code) {
        case KC_H:
        case KC_SLASH: /* ? */
            command_console_help();
            break;
        case KC_Q:
        case KC_ESC:
            command_state = ONESHOT;
            return false;
#ifdef MOUSEKEY_ENABLE
        case KC_M:
            mousekey_console_help();
            print("M> ");
            command_state = MOUSEKEY;
            return true;
#endif
        default:
            print("?");
            return false;
    }
    print("C> ");
    return true;
}
static void switch_default_layer(uint8_t layer)
{
    xprintf("L%d\n", layer);
    default_layer_set(1UL<<layer);
    clear_keyboard();
}
