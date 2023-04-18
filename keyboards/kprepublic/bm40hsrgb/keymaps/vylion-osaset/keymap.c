/* Copyright 2020 tominabox1
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
#include "keymap.h"

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    //TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    //TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP // Send two single taps
    //TD_TRIPLE_TAP,
    //TD_TRIPLE_HOLD
} td_state_t;

enum layers {
  _QWERTY,
  _GAME,
  _SYM,
  _FN,
  _XTRA
};

enum customKeycodes {
    VY_DOTS = SAFE_RANGE,
    VY_000
};

#define ES_MORD KC_GRV  // º
#define ES_QUOT KC_MINS // '
#define ES_IEXL KC_EQL  // ¡
#define ES_GRV  KC_LBRC // ` (dead)
#define ES_PLUS KC_RBRC // +
#define ES_NTIL KC_SCLN // Ñ
#define ES_ACUT KC_QUOT // ´ (dead)
#define ES_CCED KC_NUHS // Ç
#define ES_LABK KC_NUBS // <
#define ES_MINS KC_SLSH // -
#define ES_PLUS KC_RBRC // +

#define ES_FORD S(ES_MORD) // ª
#define ES_EXLM S(KC_1)    // !
#define ES_DQUO S(KC_2)    // "
#define ES_BULT S(KC_3)    // ·
#define ES_DLR  S(KC_4)    // $
#define ES_PERC S(KC_5)    // %
#define ES_AMPR S(KC_6)    // &
#define ES_SLSH S(KC_7)    // /
#define ES_LPRN S(KC_8)    // (
#define ES_RPRN S(KC_9)    // )
#define ES_EQL  S(KC_0)    // =
#define ES_QUES S(ES_QUOT) // ?
#define ES_IQUE S(ES_IEXL) // ¿
#define ES_UNDS S(ES_MINS) // _
#define ES_RABK S(ES_LABK) // >
#define ES_ASTR S(ES_PLUS) // *
#define ES_BSLS ALGR(ES_MORD) // (backslash)
#define ES_PIPE ALGR(KC_1)    // |
#define ES_AT   ALGR(KC_2)    // @
#define ES_HASH ALGR(KC_3)    // #
#define ES_TILD ALGR(KC_4)    // ~
#define ES_EUR  ALGR(KC_5)    // €
#define ES_NOT  ALGR(KC_6)    // ¬
#define ES_CIRC S(ES_GRV)  // ^ (dead)
#define ES_DIAE S(ES_ACUT) // ¨ (dead)
#define ES_LBRC ALGR(ES_GRV)  // [
#define ES_RBRC ALGR(ES_PLUS) // ]
#define ES_LCBR ALGR(ES_ACUT) // {
#define ES_RCBR ALGR(ES_CCED) // }

#define SP_PSTE S(KC_INS)
#define SP_COPY C(KC_INS)
#define WN_ST_S S(G(KC_S))

#define LT_SYM  LT(_SYM, KC_ESC)
#define LEFT_XT LT(_XTRA, KC_COMM)
#define RGHT_XT LT(_XTRA, KC_DOT)
#define LT_FN   LT(_FN, ES_CCED)
#define GAME    TG(_GAME)

#define ALT_S  MT(MOD_LALT, KC_S)
#define SHFT_E MT(MOD_LSFT, KC_E)
#define CTRL_T MT(MOD_LCTL, KC_T)
#define CTRL_N MT(MOD_RCTL, KC_N)
#define SHFT_I MT(MOD_RSFT, KC_I)
#define ALT_O  MT(MOD_LALT, KC_O)
#define OS_LSFT OSM(MOD_LSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_LALT OSM(MOD_LALT)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode)
    {
    case VY_DOTS:
        if(record->event.pressed)
        {
            SEND_STRING("...");
        }
        return false;
    case VY_000:
        if(record->event.pressed)
        {
            SEND_STRING("000");
        }
        return false;
    default:
        break;
    }

    return true;
};

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT_FN:
        case LEFT_XT:
        case RGHT_XT:
            return true;
        default:
            return false;
    }
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base -- ASET
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   J  |   F  |   G  |   Y  |   R  |   U  |   L  |   à  | Del  |
 * |------+------+------+------+------+------+------+------+------+-----+------+------|
 * | Ctrl |   A  |  ⎇ S |  ⇧ E |  ^ T |   D  |   H  |  ^ N |  ⇧ I |  ⎇ O |   á  | - _  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   P  |   Ñ  |  Up  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Super|   Ç  | Tab  | , ;  |Space |     Sym     | Bspc | . :  | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_mit(
    KC_TAB,  KC_Q,    KC_W,    KC_J,    KC_F,    KC_G,    KC_Y,    KC_R,    KC_U,    KC_L,    ES_GRV, KC_DEL,
    OS_LCTL, KC_A,    ALT_S,   SHFT_E,  CTRL_T,  KC_D,    KC_H,    CTRL_N,  SHFT_I,  ALT_O,   ES_ACUT, ES_MINS,
    OS_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_P,    ES_NTIL, KC_UP,   KC_ENT,
    KC_LGUI, LT_FN,   OS_LALT, LEFT_XT, KC_SPC,     MO(_SYM),      KC_BSPC, RGHT_XT, KC_LEFT, KC_DOWN, KC_RGHT
),

/* Game -- QWERTY
 * ,-----------------------------------------------------------------------------------.
 * |      |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   à  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   á  | - _  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   P  |   Ñ  |  Up  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Super|   Ç  | Tab  | , ;  |Space |     Esc     | Bspc | . :  | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_GAME] = LAYOUT_planck_mit(
    _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    _______, _______,
    _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    _______, _______,
    _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_P,    _______, _______, _______,
    _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
),

/* SYM
 */
[_SYM] = LAYOUT_planck_mit(
    KC_ESC,  ES_PIPE, ES_AT,   ES_HASH, ES_TILD, ES_DLR,  ES_EUR,  ES_PERC, ES_AMPR, ES_ASTR, ES_PLUS, ES_EQL,
    KC_CAPS, ES_MORD, ES_LCBR, ES_LBRC, ES_LPRN, ES_SLSH, ES_BSLS, ES_RPRN, ES_RBRC, ES_RCBR, ES_QUOT, ES_DQUO,
    _______, ES_FORD, ES_NOT,  ES_LABK, ES_IQUE, ES_IEXL, ES_EXLM, ES_QUES, ES_RABK, ES_BULT, VY_DOTS, KC_MENU,
    _______, _______, ES_BULT, ES_DQUO, _______,     _______,      _______, ES_QUOT, _______, _______, _______
),

/* FN
 */
[_FN] = LAYOUT_planck_mit(
    XXXXXXX, KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX, XXXXXXX, KC_RCTL, KC_RSFT, KC_LALT, XXXXXXX, XXXXXXX,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX,
    _______, _______, _______, XXXXXXX, XXXXXXX,     KC_INS,       XXXXXXX, KC_MNXT, KC_HOME, KC_PGDN, KC_END
),

/* XTRA
 */
[_XTRA] = LAYOUT_planck_mit(
    ES_SLSH, KC_COMM, KC_7,    KC_8,    KC_9,    GAME,    RESET,   RGB_VAI, RGB_SAI, RGB_HUI, RGB_MOD, KC_PSCR,
    VY_000,  KC_0,    KC_4,    KC_5,    KC_6,    SP_COPY, RGB_TOG, RGB_VAD, RGB_SAD, RGB_HUD, RGB_RMOD,WN_ST_S,
    ES_MINS, KC_DOT,  KC_1,    KC_2,    KC_3,    SP_PSTE, XXXXXXX, KC_MUTE, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,
    ES_UNDS, XXXXXXX, XXXXXXX, _______, XXXXXXX,     KC_INS,       XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX
)

/* Empty Layer Template
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 *
[_LAYER] = LAYOUT_planck_mit(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
)
*/

};

