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

Ported to QMK by Peter Roe <pete@13bit.me>
*/

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "util.h"
#include "debug.h"
#include "adb.h"
#include "matrix.h"
#include "report.h"
#include "host.h"
#include "led.h"
#include "timer.h"

static bool is_iso_layout = false;

// matrix state buffer(1:on, 0:off)
static matrix_row_t matrix[MATRIX_ROWS];

static void register_key(uint8_t key);

__attribute__ ((weak))
void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

static void device_scan(void) {
    xprintf("\nScan:\n");
    for (uint8_t addr = 0; addr < 16; addr++) {
        uint16_t reg3 = adb_host_talk(addr, ADB_REG_3);
        if (reg3) {
            xprintf(" addr:%d, reg3:%04X\n", addr, reg3);
        }
    }
}

void matrix_init(void)
{
    adb_host_init();

    // AEK/AEKII(ANSI/ISO) startup is slower. Without proper delay
    // it would fail to recognize layout and enable Extended protocol.
    // 200ms seems to be enough for AEKs. 1000ms is used for safety.
    // Tested with devices:
    // M0115J(AEK), M3501(AEKII), M0116(Standard), M1242(Adjustable),
    // G5431(Mouse), 64210(Kensington Trubo Mouse 5)
    _delay_ms(1000);

    device_scan();

    //
    // Keyboard
    //
    xprintf("\nKeyboard:\n");
    // Determine ISO keyboard by handler id, most ids here are unknown and taken on from:
    // https://github.com/torvalds/linux/blob/v5.9/drivers/macintosh/adbhid.c#L802
    uint8_t handler_id = (uint8_t) adb_host_talk(ADB_ADDR_KEYBOARD, ADB_REG_3);
    switch (handler_id) {
        case ADB_HANDLER_STD_ISO:
        case ADB_HANDLER_AEK_ISO:
        case 0x07:
        case 0x09:
        case 0x0D:
        case 0x11:
        case 0x14:
        case 0x19:
        case 0x1D:
        case 0xC1:
        case 0xC4:
        case 0xC7:
            is_iso_layout = true;
            break;
        default:
            is_iso_layout = false;
            break;
    }
    xprintf("handler: %02X, ISO: %s\n", handler_id, (is_iso_layout ? "yes" : "no"));

    // Enable keyboard left/right modifier distinction on AEKs
    // Listen Register3
    //  upper byte: reserved bits 0000, keyboard address 0010
    //  lower byte: device handler 00000011
    // Note: This will change the keyborads handler ID which may cause trouble with recognition of swapping codes on ISO boards.
    //       Problems will occur when converter MCU is resetted without powercycling the keyboard itsself.
    if (handler_id == ADB_HANDLER_AEK || handler_id == ADB_HANDLER_AEK_ISO)
    {
        adb_host_listen(ADB_ADDR_KEYBOARD, ADB_REG_3, ADB_ADDR_KEYBOARD, ADB_HANDLER_AEK_RMOD);
        device_scan();
    }

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    matrix_init_quantum();
}

#ifdef ADB_MOUSE_ENABLE

#ifdef MAX
#undef MAX
#endif
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

static report_mouse_t mouse_report = {};

void adb_mouse_task(void)
{
    uint16_t codes;
    int16_t x, y;
    static int8_t mouseacc;

    /* tick of last polling */
    static uint16_t tick_ms;

    // polling with 12ms interval
    if (timer_elapsed(tick_ms) < 12) return;
    tick_ms = timer_read();

    codes = adb_host_mouse_recv();
    // If nothing received reset mouse acceleration, and quit.
    if (!codes) {
        mouseacc = 1;
        return;
    };
    // Bit sixteen is button.
    if (~codes & (1 << 15))
        mouse_report.buttons |= MOUSE_BTN1;
    if (codes & (1 << 15))
        mouse_report.buttons &= ~MOUSE_BTN1;
    // lower seven bits are movement, as signed int_7.
    // low byte is X-axis, high byte is Y.
    y = (codes>>8 & 0x3F);
    x = (codes>>0 & 0x3F);
    // bit seven and fifteen is negative
    // usb does not use int_8, but int_7 (measuring distance) with sign-bit.
    if (codes & (1 << 6))
          x = (x-0x40);
    if (codes & (1 << 14))
         y = (y-0x40);
    // Accelerate mouse. (They weren't meant to be used on screens larger than 320x200).
    x *= mouseacc;
    y *= mouseacc;
    // Cap our two bytes per axis to one byte.
    // Easier with a MIN-function, but since -MAX(-a,-b) = MIN(a,b)...
	 // I.E. MIN(MAX(x,-127),127) = -MAX(-MAX(x, -127), -127) = MIN(-MIN(-x,127),127)
    mouse_report.x = -MAX(-MAX(x, -127), -127);
    mouse_report.y = -MAX(-MAX(y, -127), -127);
    if (debug_mouse) {
            print("adb_host_mouse_recv: "); print_bin16(codes); print("\n");
            print("adb_mouse raw: [");
            phex(mouseacc); print(" ");
            phex(mouse_report.buttons); print("|");
            print_decs(mouse_report.x); print(" ");
            print_decs(mouse_report.y); print("]\n");
    }
    // Send result by usb.
    host_mouse_send(&mouse_report);
    // increase acceleration of mouse
    mouseacc += ( mouseacc < ADB_MOUSE_MAXACC ? 1 : 0 );
    return;
}
#endif

uint8_t matrix_scan(void)
{
    /* extra_key is volatile and more convoluted than necessary because gcc refused
    to generate valid code otherwise. Making extra_key uint8_t and constructing codes
    here via codes = extra_key<<8 | 0xFF; would consistently fail to even LOAD
    extra_key from memory, and leave garbage in the high byte of codes. I tried
    dozens of code variations and it kept generating broken assembly output. So
    beware if attempting to make extra_key code more logical and efficient. */
    static volatile uint16_t extra_key = 0xFFFF;
    uint16_t codes;
    uint8_t key0, key1;

    /* tick of last polling */
    static uint16_t tick_ms;

    codes = extra_key;
    extra_key = 0xFFFF;

    if ( codes == 0xFFFF )
    {
        // polling with 12ms interval
        if (timer_elapsed(tick_ms) < 12) return 0;
        tick_ms = timer_read();

        codes = adb_host_kbd_recv();
    }

    key0 = codes>>8;
    key1 = codes&0xFF;

    if (debug_matrix && codes) {
        print("adb_host_kbd_recv: "); phex16(codes); print("\n");
    }

    if (codes == 0) {                           // no keys
        return 0;
    } else if (codes == 0x7F7F) {   // power key press
        register_key(0x7F);
    } else if (codes == 0xFFFF) {   // power key release
        register_key(0xFF);
    } else if (key0 == 0xFF) {      // error
        xprintf("adb_host_kbd_recv: ERROR(%d)\n", codes);
        // something wrong or plug-in
        matrix_init();
        return key1;
    } else {
        /* Swap codes for ISO keyboard
         * https://github.com/tmk/tmk_keyboard/issues/35
         *
         * ANSI
         * ,-----------    ----------.
         * | *a|  1|  2     =|Backspa|
         * |-----------    ----------|
         * |Tab  |  Q|     |  ]|   *c|
         * |-----------    ----------|
         * |CapsLo|  A|    '|Return  |
         * |-----------    ----------|
         * |Shift   |      Shift     |
         * `-----------    ----------'
         *
         * ISO
         * ,-----------    ----------.
         * | *a|  1|  2     =|Backspa|
         * |-----------    ----------|
         * |Tab  |  Q|     |  ]|Retur|
         * |-----------    -----`    |
         * |CapsLo|  A|    '| *c|    |
         * |-----------    ----------|
         * |Shif| *b|      Shift     |
         * `-----------    ----------'
         *
         *         ADB scan code   USB usage
         *         -------------   ---------
         * Key     ANSI    ISO     ANSI    ISO
         * ---------------------------------------------
         * *a      0x32    0x0A    0x35    0x35
         * *b      ----    0x32    ----    0x64
         * *c      0x2A    0x2A    0x31    0x31(or 0x32)
         */
        if (is_iso_layout) {
            if ((key0 & 0x7F) == 0x32) {
                key0 = (key0 & 0x80) | 0x0A;
            } else if ((key0 & 0x7F) == 0x0A) {
                key0 = (key0 & 0x80) | 0x32;
            }
        }
        register_key(key0);
        if (key1 != 0xFF)       // key1 is 0xFF when no second key.
            extra_key = key1<<8 | 0xFF; // process in a separate call
    }

    matrix_scan_quantum();
    return 1;
}

void matrix_print(void){

}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

inline
static void register_key(uint8_t key)
{
    uint8_t col, row;
    col = key&0x07;
    row = (key>>3)&0x0F;
    if (key&0x80) {
        matrix[row] &= ~(1<<col);
    } else {
        matrix[row] |=  (1<<col);
    }
}

void led_set(uint8_t usb_led)
{
    adb_host_kbd_led(~usb_led);
}
