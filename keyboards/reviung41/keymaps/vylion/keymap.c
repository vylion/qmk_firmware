/* Copyright 2020 gtips
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

enum layer_names {
    _BASE,
    _GAME,
    _SYM,
    _FN,
    _XTRA
};

enum customKeycodes {
    VY_INTE = SAFE_RANGE,
    VY_EXCL,
    VY_QUOT,
    VY_DOTS
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
#define LT_XTRA LT(_XTRA, KC_DOT)
#define LT_FN   LT(_FN, KC_COMM)
#define ALT_S  MT(MOD_LALT, KC_S)
#define SHFT_E MT(MOD_LSFT, KC_E)
#define CTRL_R MT(MOD_LCTL, KC_R)
#define CTRL_U MT(MOD_RCTL, KC_U)
#define SHFT_I MT(MOD_RSFT, KC_I)
#define ALT_O  MT(MOD_LALT, KC_O)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode)
    {
    case VY_DOTS:
        if(record->event.pressed)
        {
            SEND_STRING("...");
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
        case LT_XTRA:
            return true;
        default:
            return false;
    }
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_reviung41(
    KC_TAB,   KC_Q,     KC_W,     KC_D,     KC_F,      KC_G,               KC_Y,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_DEL,
    KC_LCTL,  KC_A,     ALT_S,    SHFT_E,   CTRL_R,    KC_T,               KC_H,     CTRL_U,   SHFT_I,   ALT_O,    KC_UP,    ES_CCED,
    KC_LGUI,  KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,               KC_N,     KC_M,     KC_P,     KC_LEFT,  KC_DOWN,  KC_RIGHT,
                                            LT_FN,     KC_SPC,   LT_SYM,   KC_BSPC,  LT_XTRA
  ),

  [_GAME] = LAYOUT_reviung41(
    _______,  _______,  _______,  _______,  _______,   _______,            _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  KC_S,     KC_E,     KC_R,      _______,            _______,  KC_U,     KC_I,     KC_O,     _______,  _______,
    KC_LSFT,  _______,  _______,  _______,  _______,   _______,            _______,  _______,  _______,  _______,  _______,  _______,
                                            LT_XTRA,   _______,  _______,  _______,  LT_FN
  ),

  [_SYM] = LAYOUT_reviung41(
    ES_BULT,  ES_PIPE,  ES_AT,    ES_HASH,  ES_TILD,   ES_DLR,             ES_EUR,   ES_PERC,  ES_AMPR,  ES_ASTR,  ES_PLUS,  ES_EQL,
    ES_MINS,  ES_MORD,  ES_LCBR,  ES_LBRC,  ES_LPRN,   ES_SLSH,            ES_BSLS,  ES_RPRN,  ES_RBRC,  ES_RCBR,  ES_GRV,   ES_ACUT,
    ES_UNDS,  ES_FORD,  ES_NOT,   ES_LABK,  ES_IQUE,   ES_IEXL,            ES_EXLM,  ES_QUES,  ES_RABK,  VY_DOTS,  ES_CIRC,  ES_DIAE,
                                            ES_DQUO,   XXXXXXX,  _______,  KC_MENU,  ES_QUOT
  ),

  [_FN] = LAYOUT_reviung41(
    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,              KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
    KC_CAPS,  XXXXXXX,  KC_LALT,  KC_LSFT,  KC_LCTL,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_PGUP,  KC_ENT,
    KC_LGUI,  XXXXXXX,  XXXXXXX,  SP_COPY,  SP_PSTE,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_HOME,  KC_PGDN,  KC_END,
                                            _______,   XXXXXXX,  KC_INS,   XXXXXXX,  XXXXXXX
  ),

  [_XTRA] = LAYOUT_reviung41(
    ES_SLSH,   KC_COMM,   KC_7,    KC_8,     KC_9,     TG(_GAME),          RESET,    RGB_VAI,   RGB_SAI, RGB_HUI,  RGB_MOD,  KC_PSCR,
    ES_MINS,   KC_0,      KC_4,    KC_5,     KC_6,     XXXXXXX,            RGB_TOG,  RGB_VAD,   RGB_SAD, RGB_HUD,  RGB_RMOD, WN_ST_S,
    ES_UNDS,   KC_DOT,    KC_1,    KC_2,     KC_3,     XXXXXXX,            XXXXXXX,  KC_MUTE,   KC_VOLD, KC_VOLU,  KC_MPRV,  KC_MNXT,
                                            _______,   KC_MPLY,  XXXXXXX,  KC_MSTP,  _______
  ),
};


