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

#define NAV_BCK A(KC_LEFT)
#define NAV_FRW A(KC_RGHT)
#define PS_UNDO C(KC_Z)
#define PS_REDO C(S(KC_Z))
#define TAB_LFT C(S(KC_TAB))
#define TAB_RGT C(KC_TAB)
#define LCK_WIN G(KC_L)
#define LCK_LNX C(A(KC_DEL))

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _DL,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap _DL: Default Layer
 *
 * ,-------------------.
 * | F10| F11| F12|Back|
 * |----|----|----|----|
 * | F7 | F8 | F9 | Re |
 * |----|----|----| fr |
 * | F4 | F5 | F6 | esh|
 * |----|----|----|----|
 * | F1 | F2 | F3 |Forw|
 * |----|----|----|----|
 * |Lock|ScLf| Up |ScRt|
 * |----|----|----|----|
 * | Fn |Left|Down|Rght|
 * `-------------------'
 *
    [_DL] = LAYOUT_ortho_6x4(
        MO(_FN), KC_LEFT, KC_WH_L, VY_LOCK,
        VY_BACK, KC_DOWN, KC_UP,   C(KC_F5),
        VY_FORW, KC_RGHT, KC_WH_R, C(KC_F5),
        KC_F1,   KC_F4,   KC_F7,   KC_F10,
        KC_F2,   KC_F5,   KC_F8,   KC_F11,
        KC_F3,   KC_F6,   KC_F9,   KC_F12
    ),
     */

    [_DL] = LAYOUT_ortho_6x4(
        KC_F10,  KC_F11,  KC_F12,  NAV_BCK,
        KC_F7,   KC_F8,   KC_F9,   C(KC_F5),
        KC_F4,   KC_F5,   KC_F6,   C(KC_F5),
        KC_F1,   KC_F2,   KC_F3,   NAV_FRW,
        LCK_WIN, KC_WH_L, KC_UP,   KC_WH_R,
        MO(_FN), KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /*
 * ,-------------------.
 * | F22| F23| F24|Undo|
 * |----|----|----|----|
 * | F19| F20| F21| Re |
 * |----|----|----| se |
 * | F16| F17| F18| t  |
 * |----|----|----|----|
 * | F13| F14| F15|Redo|
 * |----|----|----|----|
 * | F14|TbLf|PgUp|TbRt|
 * |----|----|----|----|
 * | F15|Home|PgDn| End|
 * `-------------------'
 *
    [_FN] = LAYOUT_ortho_6x4(
        _______, KC_HOME, TAB_LFT, RESET,
        PS_UNDO, KC_PGDN, KC_PGUP, XXXXXXX,
        PS_REDO, KC_END,  TAB_RGT, XXXXXXX,
        KC_F13,  KC_F16,  KC_F19,  KC_F22,
        KC_F14,  KC_F17,  KC_F20,  KC_F23,
        KC_F15,  KC_F18,  KC_F21,  KC_F24
    )
     */

    [_FN] = LAYOUT_ortho_6x4(
        KC_F22,  KC_F23,  KC_F24,  PS_UNDO,
        KC_F19,  KC_F20,  KC_F21,  RESET,
        KC_F16,  KC_F17,  KC_F18,  RESET,
        KC_F13,  KC_F14,  KC_F15,  PS_REDO,
        LCK_LNX, TAB_LFT, KC_UP,   TAB_RGT,
        MO(_FN), KC_LEFT, KC_DOWN, KC_RGHT
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
