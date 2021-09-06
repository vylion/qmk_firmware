/*
Base Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
Modified 2017 Andrew Novak <ndrw.nvk@gmail.com>
Modified 2018 Wayne Jones (WarmCatUK) <waynekjones@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public LicensezZZ
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "keymap.h"

#define ______ KC_TRNS
#define _DEFLT 0
#define _RED 1
#define _GRN 2

#define MO_RED MO(_RED)
#define MO_GRN MO(_GRN)

#define BR_ACUT KC_LBRC // ´ (dead)
#define BR_LBRC KC_RBRC // [
#define BR_CCED KC_SCLN // Ç
#define BR_TILD KC_QUOT // ~ (dead)
#define BR_RBRC KC_BSLS // ]
#define BR_BSLS KC_NUBS // (backslash)
#define BR_SCLN KC_SLSH // ;
#define BR_SLSH KC_INT1 // /
#define BR_DQUO S(KC_GRV)  // "
#define BR_PLUS S(KC_EQL)  // +
#define BR_LCBR S(BR_LBRC) // {
#define BR_RCBR S(BR_RBRC) // }
#define BR_PIPE S(BR_BSLS) // |
#define BR_LABK S(KC_COMM) // <
#define BR_RABK S(KC_DOT)  // >
#define BR_COLN S(BR_SCLN) // :
#define BR_SECT ALGR(KC_EQL)  // §
#define BR_FORD ALGR(BR_LBRC) // ª
#define BR_MORD ALGR(BR_RBRC) // º

/* Unused:
#define MODS_ANY_MASK (MODS_SHIFT_MASK|MODS_CTRL_MASK|MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define MODS_CTRL_MASK (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTL))
*/

enum custom_keycodes {
    VD_BSPC = SAFE_RANGE,
    VD_DOT,
    VD_COMM
};

static uint8_t shift_stash;

void stash_mods(void) {
    shift_stash |= get_mods() & MOD_MASK_SHIFT;
    set_mods(get_mods() & ~(MOD_MASK_SHIFT));
};

void unstash_mods(void) {
    register_mods(shift_stash);
    shift_stash = 0;
    clear_oneshot_mods();
};

bool custom_shift_keycode(int16_t unshifted, int16_t shifted, bool pressed) {
    if(pressed) {
        stash_mods();

        if(shift_stash) {
            register_code16(shifted);
        }
        else {
            register_code16(unshifted);
        }
    }
    else {
        if(shift_stash) {
            unregister_code16(shifted);
        }
        else {
            unregister_code16(unshifted);
        }
        unstash_mods();
    }

    return shift_stash;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode)
    {
    case VD_BSPC:
        custom_shift_keycode(KC_BSPACE, KC_DELETE, record->event.pressed); // Backspace Delete
        return false;
    case VD_DOT:
        custom_shift_keycode(KC_DOT, BR_COLN, record->event.pressed);
        return false;
    case VD_COMM:
        custom_shift_keycode(KC_COMM, BR_SCLN, record->event.pressed);
        return false;
    case KC_RSHIFT:
        if(record->event.pressed)
        {
            if(get_mods() & MOD_BIT(KC_LSHIFT))
            {
                tap_code(KC_CAPSLOCK);
            }
            return true;
        }
    case KC_LSHIFT:
        if(record->event.pressed)
        {
            if(get_mods() & MOD_BIT(KC_RSHIFT))
            {
                tap_code(KC_CAPSLOCK);
            }
            return true;
        }
    default:
        break;
    }

    return true;
};

/*
void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
     * ,-----------------------------------------------------------------------------------.
     * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   ´  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | -  _ |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ~  | Enter|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |LShift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  |RShift|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | LCtrl|  Win |  Alt | _GRN | _RED |    Space    | AltGr| RCtrl| Left | Down | Right|
     * `-----------------------------------------------------------------------------------'
     */
    [_DEFLT] = LAYOUT( \
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    VD_BSPC, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    BR_ACUT, \
        KC_MINS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    BR_TILD, KC_ENT,  \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    VD_COMM, VD_DOT,  KC_UP,   KC_RSFT, \
        KC_LCTL, KC_LGUI, KC_LALT, MO_GRN,  MO_RED,  KC_SPC,  KC_SPC,  KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT  \
    ),

    /* _GRN
     * ,-----------------------------------------------------------------------------------.
     * | Reset|  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |  F11 |  F12 |      |      |      |      |      |      |   º  |   {  |   }  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |  F1  |   ª  |      |      |      |      |      |      |      |      |   [  |   ]  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |   Ç  |      |      |      |      |   <  |   >  | PgUp |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      | _GRN |      |             | Reset|      | Home | PgDn | End  |
     * `-----------------------------------------------------------------------------------'
     */

    [_GRN] = LAYOUT( \
       _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F24,  \
       _______, KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, BR_MORD, BR_LCBR, BR_RCBR, \
       KC_EQL,  BR_FORD, _______, _______, _______, _______, _______, _______, _______, _______, BR_LBRC, BR_RBRC, \
       _______, _______, _______, BR_CCED, _______, _______, _______, _______, BR_LABK, BR_RABK, KC_PGUP, _______, \
       _______, _______, _______, _______, _______, _______, _______, RESET,   _______, KC_HOME, KC_PGDN, KC_END   \
    ),

    /* _RED
     * ,-----------------------------------------------------------------------------------.
     * |   "  | AF1  | AF2  | AF3  | AF4  | AF5  | AF6  | AF7  | AF8  | AF9  | AF10 |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      | AF11 | AF12 |      |      |      |      |      |   \  |   |  |   +  |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   §  |      |      |      |      |      |   ⏮  |  ⏭  |  ⏯️  |   ■  |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      | Mute | Vol- | Vol+ | PgUp |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      | _RED |             |      |      | Home | PgDn | End  |
     * `-----------------------------------------------------------------------------------'
     */

    [_RED] = LAYOUT( \
       BR_DQUO, A(KC_F1), A(KC_F2), A(KC_F3),A(KC_F4),A(KC_F5),A(KC_F6),A(KC_F7),A(KC_F8),A(KC_F9),A(KC_F10),S(KC_DEL),\
       _______, A(KC_F11),A(KC_F12),_______, _______, _______, _______, _______, BR_BSLS, BR_PIPE, BR_PLUS,  KC_GRV,  \
       BR_SECT, _______,  _______,  _______, _______, _______, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, _______,  _______, \
       _______, _______,  _______,  _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,  _______, \
       _______, _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______,  _______  \
    )

};
