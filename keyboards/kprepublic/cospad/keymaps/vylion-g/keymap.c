#include QMK_KEYBOARD_H
#include "keymap.h"

#define SH_TAB  S(KC_TAB)
#define FN_GRV  LT(_FN, KC_GRAVE)
#define PN_3    LT(_PN, KC_3)
#define PN_ESC  LT(_PNG, KC_ESC)
#define ES_COLN S(KC_DOT)
#define ES_SCLN S(KC_COMMA)
#define ES_GTHN S(KC_NUBS)
#define ES_UNDS S(KC_SLSH)
#define SCRN_ST G(S(KC_S))

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _NL,
    _PN,
    _GL,
    _FN,
    _PNG,
    _FL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap _NL: (Number Layer) Default Layer
 * Intended to be used in upright position
 * ,-------------------.
 * | Esc|  % |  ⌦ |  ⌫ |
 * |----|----|----|----|
 * |  ⇥ |  / |  * |    |
 * |----|----|----|  ↩ |
 * |  ⇤ |  - |  + |    |
 * |----|----|----|----|
 * |  , |  7 |  8 |  9 |
 * |----|----|----|----|
 * |  . |  4 |  5 |  6 |
 * |----|----|----|----|
 * |  0 |  1 |  2 |  3 |
 * `-------------------'
     */
    [_NL] = LAYOUT_ortho_6x4(
        KC_ESC,  S(KC_5), KC_DEL,  KC_BSPC,
        KC_TAB,  KC_PSLS, KC_PAST, KC_PENT,
        SH_TAB,  KC_PMNS, KC_PPLS, KC_PENT,
        KC_COMM, KC_7,    KC_8,    KC_9,
        KC_DOT,  KC_4,    KC_5,    KC_6,
        KC_0,    KC_1,    KC_2,    PN_3
    ),

    /*
 * ,-------------------.
 * | Esc|  ( |  ) |RSET|
 * |----|----|----|----|
 * |  < |  & |  ! |    |
 * |----|----|----|    |
 * |  > |  _ |  = |    |
 * |----|----|----|----|
 * |  , |Bri↑|Vol↑|    |
 * |----|----|----|----|
 * |  . |Bri↓|Vol↓|    |
 * |----|----|----|----|
 * |  ␣ |    |Mute|    |
 * `-------------------'
     */

    [_PN] = LAYOUT_ortho_6x4(
        TG(_GL), S(KC_8), S(KC_9), RESET,
        KC_NUBS, S(KC_6), S(KC_1), _______,
        ES_GTHN, ES_UNDS, KC_PEQL, _______,
        ES_SCLN, KC_BRIU, KC_VOLU, _______,
        ES_COLN, KC_BRID, KC_VOLD, _______,
        KC_SPC,  _______, KC_MUTE, _______
    ),

    /* Keymap _GL: Game Layer
 *  Intended to be used while tilted 90 degrees
 * ,-------------------.
 * |  T |  G |  B | Esc|
 * |----|----|----|----|
 * |  R |  F |  V |    |
 * |----|----|----| Spc|
 * |  E |  D |  C |    |
 * |----|----|----|----|
 * |  W |  S |  X | Alt|
 * |----|----|----|----|
 * |  Q |  A |  Z | Win|
 * |----|----|----|----|
 * | Tab|  ` |Shft|Ctrl|
 * `-------------------'
    */
    [_GL] = LAYOUT_ortho_6x4(
        KC_T,    KC_G,    KC_B,    PN_ESC,
        KC_R,    KC_F,    KC_V,    KC_SPACE,
        KC_E,    KC_D,    KC_C,    KC_SPACE,
        KC_W,    KC_S,    KC_X,    KC_LALT,
        KC_Q,    KC_A,    KC_Z,    KC_LGUI,
        KC_TAB,  FN_GRV,  KC_LSFT, KC_LCTL
    ),


    [_FN] = LAYOUT_ortho_6x4(
        KC_F5,   KC_5,    KC_0,    _______,
        KC_F4,   KC_4,    KC_9,    SCRN_ST,
        KC_F3,   KC_3,    KC_8,    SCRN_ST,
        KC_F2,   KC_2,    KC_7,    _______,
        KC_F1,   KC_1,    KC_6,    _______,
        _______, _______, _______, _______
    ),


    [_PNG] = LAYOUT_ortho_6x4(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        TG(_GL), _______, _______, _______
    )
};

void keyboard_post_init_user(void) {
    rgblight_setrgb(125, 174, 255);
};

layer_state_t layer_state_set_user(layer_state_t state) {
    if(IS_LAYER_ON_STATE(state, _FN)) {
        rgblight_setrgb(5, 210, 0); // Green
    }
    else if(IS_LAYER_ON_STATE(state, _GL)) {
        rgblight_setrgb(255, 131, 0); // Orange
    }
    else {
        rgblight_setrgb(125, 174, 255); // Blue
    }

    return state;
};
