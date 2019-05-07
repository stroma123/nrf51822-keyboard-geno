/**
 * @brief 键盘内置功能
 * 
 * @file keyboard_fn.c
 * @author Jim Jiang
 * @date 2018-05-13
 */
#include "keyboard_fn.h"
#include <stdint.h>

#include "main.h"
#include "matrix.h"
#include "uart_driver.h"
#include "keymap_common.h"
#include "action_util.h"

#define MODS_SHIFT_MASK (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    static uint8_t tricky_esc_registered;
    switch (id) {
        case AF_POWER_SLEEP:
            if (!record->event.pressed) {
                //sleep_mode_enter(true);
                system_off_mode_enter(true);
            }
            break;
        case AF_POWER_OFF:
            if (!record->event.pressed) {
                system_off_mode_enter(false);
            }
            break;
        case AF_SWITCH_MODE:
            if (!record->event.pressed) {
            #ifdef UART_SUPPORT
                uart_switch_mode();
            #endif
            }
            break;
        case AF_TRICKY_ESC:
            if (record->event.pressed) {
                if (get_mods() & MODS_SHIFT_MASK) {
                    tricky_esc_registered = KC_GRV;
                }
                else {
                    tricky_esc_registered = KC_ESC;
                }
                register_code(tricky_esc_registered);
                send_keyboard_report();
            }
            else {
                unregister_code(tricky_esc_registered);
                send_keyboard_report();
            }
            break;
        default:
            break;
    }
}
