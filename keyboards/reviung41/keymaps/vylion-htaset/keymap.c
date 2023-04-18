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
    VY_DOTS = SAFE_RANGE
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

#define LEFT_XT LT(_XTRA, KC_COMM)
#define RGHT_XT LT(_XTRA, KC_DOT)

void dance_home_lalt_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_S);
    }
}

void dance_home_lalt_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_S);
    } else {
        set_oneshot_mods(MOD_LALT | get_oneshot_mods());
    }
}

void dance_home_lsft_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_E);
    }
}

void dance_home_lsft_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_E);
    } else {
        set_oneshot_mods(MOD_LSFT | get_oneshot_mods());
    }
}

void dance_home_lctl_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_T);
    }
}

void dance_home_lctl_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_T);
    } else {
        set_oneshot_mods(MOD_LCTL | get_oneshot_mods());
    }
}

void dance_home_rctl_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_N);
    }
}

void dance_home_rctl_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_N);
    } else {
        set_oneshot_mods(MOD_RCTL | get_oneshot_mods());
    }
}

void dance_home_rsft_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_I);
    }
}

void dance_home_rsft_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_I);
    } else {
        set_oneshot_mods(MOD_RSFT | get_oneshot_mods());
    }
}

void dance_home_ralt_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_O);
    }
}

void dance_home_ralt_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_O);
    } else {
        set_oneshot_mods(MOD_LALT | get_oneshot_mods());
    }
}

enum dances {
    HOME_LALT,
    HOME_LSFT,
    HOME_LCTL,
    HOME_RCTL,
    HOME_RSFT,
    HOME_RALT
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [HOME_LALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_home_lalt_finished, dance_home_lalt_reset),
    [HOME_LSFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_home_lsft_finished, dance_home_lsft_reset),
    [HOME_LCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_home_lctl_finished, dance_home_lctl_reset),
    [HOME_RCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_home_rctl_finished, dance_home_rctl_reset),
    [HOME_RSFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_home_rsft_finished, dance_home_rsft_reset),
    [HOME_RALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_home_ralt_finished, dance_home_ralt_reset)
};

#define ALT_S  TD(HOME_LALT)
#define SHFT_E TD(HOME_LSFT)
#define CTRL_T TD(HOME_LCTL)
#define CTRL_N TD(HOME_RCTL)
#define SHFT_I TD(HOME_RSFT)
#define ALT_O  TD(HOME_RALT)

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
        case LEFT_XT:
        case RGHT_XT:
            return true;
        default:
            return false;
    }
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // ASSET
  [_BASE] = LAYOUT_reviung41(
    KC_TAB,   KC_Q,     KC_W,     KC_J,     KC_F,      KC_G,               KC_Y,     KC_P,     KC_U,     KC_L,     ES_GRV,   KC_DEL,
    KC_LCTL,  KC_A,     ALT_S,    SHFT_E,   CTRL_T,    KC_D,               KC_H,     CTRL_N,   SHFT_I,   ALT_O,    ES_ACUT,  ES_MINS,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,               KC_K,     KC_M,     KC_R,     KC_SCLN,  ES_CCED,  KC_ENT,
                                            LEFT_XT,   KC_SPC,  MO(_SYM),  KC_BSPC,  RGHT_XT
  ),

    // QWERTY
  [_GAME] = LAYOUT_reviung41(
    _______,  KC_Q,     KC_W,     KC_E,     KC_R,      KC_G,               KC_Y,     KC_J,     KC_K,     KC_L,     ES_GRV,   _______,
    _______,  KC_A,     KC_S,     KC_D,     KC_F,      _______,            KC_H,     KC_U,     KC_I,     KC_O,     ES_ACUT,  _______,
    _______,  KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,               KC_N,     KC_M,     KC_P,     KC_SCLN,  ES_CCED,  _______,
                                            _______,   _______,  _______,  _______,  _______
  ),

  [_SYM] = LAYOUT_reviung41(
    KC_ESC,   ES_PIPE,  ES_AT,    ES_HASH,  ES_TILD,   ES_DLR,             ES_EUR,   ES_PERC,  ES_AMPR,  ES_ASTR,  ES_PLUS,  ES_EQL,
    KC_CAPS,  ES_MORD,  ES_LCBR,  ES_LBRC,  ES_LPRN,   ES_SLSH,            ES_BSLS,  ES_RPRN,  ES_RBRC,  ES_RCBR,  ES_QUOT,  ES_DQUO,
    KC_LGUI,  ES_FORD,  ES_NOT,   ES_LABK,  ES_IQUE,   ES_IEXL,            ES_EXLM,  ES_QUES,  ES_RABK,  ES_BULT,  VY_DOTS,  KC_MENU,
                                            ES_DQUO,   _______,  _______,  _______,  ES_QUOT
  ),

  [_XTRA] = LAYOUT_reviung41(
    ES_SLSH,   KC_COMM,   KC_7,    KC_8,     KC_9,     TG(_GAME),          RESET,    RGB_VAI,   RGB_SAI, RGB_HUI,  RGB_MOD,  KC_PSCR,
    ES_MINS,   KC_0,      KC_4,    KC_5,     KC_6,     SP_COPY,            RGB_TOG,  RGB_VAD,   RGB_SAD, RGB_HUD,  RGB_RMOD, WN_ST_S,
    ES_UNDS,   KC_DOT,    KC_1,    KC_2,     KC_3,     SP_PSTE,            XXXXXXX,  KC_MUTE,   KC_MPRV, KC_VOLD,  KC_VOLU,  KC_MNXT,
                                            _______,   KC_MPLY,  KC_INS,   KC_MSTP,  _______
  ),
};


