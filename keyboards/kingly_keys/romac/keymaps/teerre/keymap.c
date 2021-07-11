/* Copyright 2018 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include <sendstring_spanish.h>

#define _BASE 0
#define _FN1 1
#define KC_COPY C(KC_C)
#define KC_PASTE C(KC_V)

enum custom_keycodes {
    SW_FACT = SAFE_RANGE, // layers clear
    SW_CONT,
    SW_NOMI,
    CK_NEXT
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
};

void dip_switch_update_user(uint8_t index, bool active)
{
 switch (index) {
        case 0:		//ENC0_SW
        if(active) //ENC0 pressed
		{
			tap_code(KC_MUTE);
		}
        break;
    }
};

void run_program(uint16_t keycode) {
    tap_code16(G(KC_R));
    SEND_STRING(SS_DELAY(150)"C:\\Software DELSOL\\");

    switch(keycode) {
        case SW_FACT:
            SEND_STRING("FACTUSOL\\FACTUSOL.exe");
            break;
        case SW_CONT:
            SEND_STRING("CONTASOL\\CONTASOL.exe");
            break;
        case SW_NOMI:
            SEND_STRING("NOMINASOL\\NOMINASOL.exe");
            break;
        default:
            break;
    }

    tap_code(KC_ENTER);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode)
    {
    case SW_FACT:
    case SW_CONT:
    case SW_NOMI:
        if(!record->event.pressed) {
            run_program(keycode);
        }
        return false;
        break;
    case CK_NEXT:
        if(record->event.pressed) {
            tap_code16(A(KC_M));
        }
        else {
            tap_code(KC_ESC);
        }
        return false;
        break;
    default:
        break;
    }

    return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_BASE] = LAYOUT(
		SW_FACT, SW_CONT, SW_NOMI, \
		KC_F1,   KC_F2,   CK_NEXT, \
		KC_COPY, KC_UP,   KC_PASTE, \
		KC_LEFT, KC_DOWN, KC_RIGHT  \
	)
};
