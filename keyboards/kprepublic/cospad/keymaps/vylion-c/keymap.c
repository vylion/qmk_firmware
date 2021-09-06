#include QMK_KEYBOARD_H
#include "keymap.h"

#define ES_PLUS KC_RBRC // +
#define ES_MORD KC_GRV  // º
#define ES_GRV  KC_LBRC // ` (dead)
#define ES_ACUT KC_QUOT // ´ (dead)
#define ES_CCED KC_NUHS // Ç
#define ES_QUOT KC_MINS // '
#define ES_COLN S(KC_DOT)
#define ES_SCLN S(KC_COMMA)
#define ES_GTHN S(KC_NUBS)
#define ES_UNDS S(KC_SLSH)
#define ES_LPRN S(KC_8)    // (
#define ES_RPRN S(KC_9)    // )
#define ES_PERC S(KC_5)    // %
#define ES_AMPR S(KC_6)    // &
#define ES_BSLS ALGR(ES_MORD) // (backslash)
#define ES_PIPE ALGR(KC_1)    // |
#define ES_AT   ALGR(KC_2)    // @
#define ES_HASH ALGR(KC_3)    // #
#define ES_TILD ALGR(KC_4)    // ~
#define ES_EXLM S(KC_1)       // !
#define ES_EQL  S(KC_0)       // =
#define ES_DQUO S(KC_2)       // "
#define ES_ASTR S(ES_PLUS)    // *
#define ES_LBRC ALGR(ES_GRV)  // [
#define ES_RBRC ALGR(ES_PLUS) // ]
#define ES_LCBR ALGR(ES_ACUT) // {
#define ES_RCBR ALGR(ES_CCED) // }
#define ES_QUES S(ES_QUOT)    // ?
#define SCRN_ST G(S(KC_S))

#define ESC_FN  LT(_FN, KC_ESC)

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _NL,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap _NL: (Number Layer) Default Layer
 * Intended to be used in upright position
 * ,-------------------.
 * |Bspc|  > |  ) | FN |
 * |----|----|----|----|
 * |  ' |  < |  ( |    |
 * |----|----|----|  ␣ |
 * |  9 |  6 |  3 |    |
 * |----|----|----|----|
 * |  8 |  5 |  2 |  + |
 * |----|----|----|----|
 * |  7 |  4 |  1 |  - |
 * |----|----|----|----|
 * |  / |  0 |  . |  , |
 * `-------------------'
     */
    [_NL] = LAYOUT_ortho_6x4(
        KC_BSPC, ES_GTHN, ES_RPRN, ESC_FN,
        ES_QUOT, KC_NUBS, ES_LPRN, KC_SPC,
        KC_9,    KC_6,    KC_3,    KC_SPC,
        KC_8,    KC_5,    KC_2,    KC_PPLS,
        KC_7,    KC_4,    KC_1,    KC_PMNS,
        KC_0,    KC_DOT,  KC_COMM, KC_PSLS
    ),

    /*
 * ,-------------------.
 * | Del|  } |  ] |    |
 * |----|----|----|----|
 * |  ? |  { |  [ |    |
 * |----|----|----|Entr|
 * |  = |  & |  # |    |
 * |----|----|----|----|
 * |  | |  % |  " |  _ |
 * |----|----|----|----|
 * |  \ |  ~ |  ! |  * |
 * |----|----|----|----|
 * | RST|  @ |  : |  ; |
 * `-------------------'
     */

    [_FN] = LAYOUT_ortho_6x4(
        KC_DEL,  ES_RCBR, ES_RBRC, _______,
        ES_QUES, ES_LCBR, ES_LBRC, KC_PENT,
        ES_EQL,  ES_AMPR, ES_HASH, KC_PENT,
        ES_PIPE, ES_PERC, ES_DQUO, ES_UNDS,
        ES_BSLS, ES_TILD, ES_EXLM, ES_ASTR,
        RESET,   ES_AT,   ES_COLN, ES_SCLN
    )

    /*
    [_PN] = LAYOUT_ortho_6x4(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______
    )*/
};

layer_state_t layer_state_set_user(layer_state_t state) {
    if(IS_LAYER_ON_STATE(state, _FN)) {
        rgblight_setrgb(5, 210, 0); // Green
    }
    /*else if(IS_LAYER_ON_STATE(state, _PN)) {
        rgblight_setrgb(255, 131, 0); // Orange
    }*/
    else {
        rgblight_setrgb(55, 94, 255); // Blue
    }

    return state;
};
