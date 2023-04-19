/* Good on you for modifying your layout! if you don't have
 * time to read the QMK docs, a list of keycodes can be found at
 *
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * There's also a template for adding new layers at the bottom of this file!
 */

#include QMK_KEYBOARD_H
#include "keymap.h"

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
#define ES_LBRC ALGR(ES_GRV)  // [
#define ES_RBRC ALGR(ES_PLUS) // ]
#define ES_LCBR ALGR(ES_ACUT) // {
#define ES_RCBR ALGR(ES_CCED) // }

#define SP_PSTE S(KC_INS)
#define SP_COPY C(KC_INS)
#define WN_ST_S S(G(KC_S))

#define TG_TMIC C(S(KC_M))
#define TG_TCAM C(S(KC_O))
#define TG_GMIC C(KC_D)
#define TG_GCAM C(KC_E)

#define ALT_S  MT(MOD_LALT, KC_S)
#define SHFT_E MT(MOD_LSFT, KC_E)
#define CTRL_R MT(MOD_LCTL, KC_R)
#define CTRL_N MT(MOD_RCTL, KC_N)
#define SHFT_I MT(MOD_RSFT, KC_I)
#define ALT_O  MT(MOD_LALT, KC_O)
#define OS_LSFT OSM(MOD_LSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_LALT OSM(MOD_LALT)

// Blank template at the bottom

#define BASE 0 // default layer
#define GAME 1
#define SYM  2 // symbols and macros
#define FN   3 // Fn and nav
#define XTRA 4 // numbers and media

#define LT_SYM  LT(SYM, KC_ESC)
#define LEFT_XT LT(XTRA, KC_COMM)
#define RGHT_XT LT(XTRA, KC_DOT)
#define LT_FN   LT(FN, ES_CCED)
#define TGAME   TG(GAME)

enum customKeycodes {
    VY_DOTS = SAFE_RANGE,
    VY_000,
    VY_SIGN,
    VY_PRN,
    VY_BRC,
    VY_CBR,
    VY_SLSH
};


static uint8_t shift_stash = 0;

void stash_mods(void) {
    shift_stash |= get_mods() & MOD_MASK_SHIFT;
    set_mods(get_mods() & ~(MOD_MASK_SHIFT));
};

void unstash_mods(void) {
    register_mods(shift_stash);
    shift_stash = 0;
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
    case VY_PRN:
        custom_shift_keycode(ES_LPRN, ES_RPRN, record->event.pressed); // ( )
        return false;
        break;
    case VY_BRC:
        custom_shift_keycode(ES_LBRC, ES_RBRC, record->event.pressed); // [ ]
        return false;
        break;
    case VY_CBR:
        custom_shift_keycode(ES_LCBR, ES_RCBR, record->event.pressed); // { }
        return false;
        break;
    case VY_SLSH:
        custom_shift_keycode(ES_SLSH, ES_BSLS, record->event.pressed); // /
        return false;
        break;
    case VY_SIGN:
        custom_shift_keycode(ES_EXLM, ES_QUES, record->event.pressed); // ! ?
        return false;
        break;
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
/* Keymap 0: Basic layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |   Tab  |   Q  |   W  |   D  |   F  |   G  |                         |   Y  |   J  |   U  |   L  |   à  |   Del  |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |  Ctrl  |   A  |   S  |   E  |   R  |   T  | (  ) |           | [  ] |   H  |   N  |   I  |   O  |   á  |   - _  |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |  Shift |   Z  |   X  |   C  |   V  |   B  | /  \ |           | {  } |   K  |   M  |   P  |   Ñ  | !  ? | Return |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                      .--------.   .-------.                                 .-------.   .------.
 *                      |  Ç_Fn  |   | ,_Xtr |                                 | ._Xtr |   | Ç_Fn |
 *                      '--------'   '-------'                                 `-------.   '------'
 *                                        ,-------.                      ,-------.
 *                                        |  Esc  |                      |  Esc  |
 *                                 ,------|-------|                      |-------|------.
 *                                 |      |       |                      |       |      |
 *                                 | Space|  SYM  |                      |  SYM  | Back |
 *                                 |      |       |                      |       | Space|
 *                                 |      |       |                      |       |      |
 *                                 `--------------'                      `--------------'
 */
[BASE] = LAYOUT_gergo(
    KC_TAB,  KC_Q,  KC_W,  KC_D,  KC_F,   KC_G,                                          KC_Y,   KC_J,   KC_U,   KC_L,    ES_ACUT, KC_DEL,
    KC_LCTL, KC_A,  ALT_S, SHFT_E,CTRL_R, KC_T,   VY_PRN,                       VY_BRC,  KC_H,   CTRL_N, SHFT_I, ALT_O,   ES_GRV,  ES_MINS,
    KC_LGUI, KC_Z,  KC_X,  KC_C,  KC_V,   KC_B,   VY_SLSH, KC_ESC,     KC_ESC,  VY_CBR,  KC_K,   KC_M,   KC_P,   ES_NTIL, VY_SIGN, KC_ENT,
                                  LT_FN,  LEFT_XT,KC_SPC,  MO(SYM),    MO(SYM), KC_BSPC, RGHT_XT,LT_FN
    ),

/* Keymap 1: Gaming (Qwerty)
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |   Q  |   W  |   E  |   R  |   T  |                         |   Y  |   U  |   I  |   O  |      |        |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |        |   A  |   S  |   D  |   F  |   G  |   ;  |           |      |   H  |   J  |   K  |   L  |      |        |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |  Shift |      |      |      |      |      |  Win |           |      |   N  |   M  |   P  |   Ñ  |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |      |   | LAlt |                                 |      |   |     |
 *                        '------'   '------'                                 `------.   '-----'
 *                                        ,-------.       ,-------.
 *                                        |       |       |       |
 *                                 ,------|-------|       |-------|------.
 *                                 |      |       |       |       |      |
 *                                 |      |       |       |       |      |
 *                                 |      |       |       |       |      |
 *                                 `--------------'       `--------------'
 */
[GAME] = LAYOUT_gergo(
    _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                                KC_Y,    KC_U,    KC_I,    KC_O,    _______, _______,
    _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_COMM,                           _______, KC_H,    KC_J,    KC_K,    KC_L,    _______, _______,
    _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LGUI, _______,         _______, _______, KC_N,    KC_M,    KC_P,    _______, _______, _______,
                                        _______, KC_LALT, _______, _______,         _______, _______, _______, _______
    ),


/* Keymap 1: Symbols layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |    ¿   |  |   |  @   |  #   |  $   |  ~   |                         |   ½  |  %   |  &   |  +   |  *   |   =    |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |    ¡   |  º   |  {   |  [   |  (   |  \   | TMIC |           | GMIC |   /  |  )   |  ]   |  }   |  '   |   -    |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |        |  ª   |  ¬   |  <   |  ¿   |  ¡   | TCAM |           | GCAM |   !  |  ?   |  >   |  ·   | ...  |   _    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .------.
 *                        |      |   |   "  |                                 |  '   |   | Comp.|
 *                        '------'   '------'                                 `------.   '------'
 *                                        ,-------.                     ,-------.
 *                                        |  F13  |                     |  F14  |
 *                                 ,------|-------|                     |-------|------.
 *                                |       |       |                     |       |      |
 *                                |  F15  | (SYM) |                     | (SYM) | F16  |
 *                                |       |       |                     |       |      |
 *                                `---------------'                     `--------------'
 */
[SYM] = LAYOUT_gergo(
    _______, ES_PIPE, ES_AT,   ES_HASH, ES_TILD, ES_EUR,                                             ES_DLR,  ES_PERC, ES_AMPR, ES_PLUS, ES_ASTR, ES_EQL,
    KC_CAPS, ES_MORD, ES_LCBR, ES_LBRC, ES_LPRN, ES_BSLS, TG_TMIC,                          TG_GMIC, ES_SLSH, ES_RPRN, ES_RBRC, ES_RCBR, ES_QUOT, ES_MINS,
    KC_LGUI, ES_FORD, ES_NOT,  ES_LABK, ES_IQUE, ES_IEXL, TG_TCAM, KC_F13,         KC_F14,  TG_GCAM, ES_EXLM, ES_QUES, ES_RABK, ES_BULT, VY_DOTS, ES_UNDS,
                                        XXXXXXX, ES_DQUO, KC_F15,  _______,        _______, KC_F16,  ES_QUOT, KC_MENU
    ),
/* Keymap 2: Function layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |    F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                         |  F7  |  F8  |  F9  | F10  | F11  |  F12   |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |CapsLock|      |  Alt | Shft | Ctrl |      |      |           |      |      |      |  Up  |      |      |        |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |   GUI  |      |      | ^Ins | ⇧Ins |      |      |           |      |      | Left | Down | Rght |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .------.
 *                        |      |   | (FN) |                                 | (FN) |   |      |
 *                        '------'   '------'                                 `------.   '------'
 *                                        ,-------.       ,-------.
 *                                        |       |       |       |
 *                                 ,------|-------|       |-------|------.
 *                                 |      |       |       |       |      |
 *                                 |      |       |       |       | Ins  |
 *                                 |      |       |       |       |      |
 *                                 `--------------'       `--------------'
 */
[FN] = LAYOUT_gergo(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                                              KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_CAPS, XXXXXXX, KC_LALT, KC_LSFT, KC_LCTL, XXXXXXX, XXXXXXX,                          XXXXXXX, XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX,
    KC_LGUI, XXXXXXX, XXXXXXX, SP_COPY, SP_PSTE, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,
                                        XXXXXXX, _______, XXXXXXX, XXXXXXX,        XXXXXXX, KC_INS,  _______, XXXXXXX
    ),

/* Keymap 3: Extra layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |   0    |   7  |   8  |   9  |   +  |   *  |                         |      |      |      |      |      | PrntSn |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |   .    |   4  |   5  |   6  |   -  |   /  | TGame|           | Reset|      |      |      |      |      |  ⊞⇧S   |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |   ,    |   1  |   2  |   3  |   &  |   !  | Enter|           |      |      | Mute | Vol- | Vol+ |Prv.Tr|Next Tr.|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .------.
 *                        |(XTRA)|   |      |                                 |      |   |(XTRA)|
 *                        '------'   '------'                                 `------.   '------'
 *                                        ,-------.       ,-------.
 *                                        |   ~   |       |       |
 *                                 ,------|-------|       |-------|------.
 *                                 |      |       |       |       |      |
 *                                 |Play/ |       |       |       |      |
 *                                 |Pause |       |       |       | Stop |
 *                                 |      |       |       |       |      |
 *                                 `--------------'       `--------------'
 */
[XTRA] = LAYOUT_gergo(
    KC_COMM, KC_7,    KC_8,    KC_9,    KC_PPLS, KC_PAST,                                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR,
    KC_0,    KC_4,    KC_5,    KC_6,    KC_PMNS, KC_PSLS, TGAME,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, WN_ST_S,
    KC_DOT,  KC_1,    KC_2,    KC_3,    ES_AMPR, ES_EXLM, KC_ENT,  ES_TILD,         RESET,   XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MNXT,
                                        ES_PERC, XXXXXXX, KC_MPLY, XXXXXXX,         XXXXXXX, KC_MSTP, XXXXXXX, XXXXXXX
    )
};

/* Keymap template
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |      |      |      |      |      |                         |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |      |   |      |                                 |      |   |     |
 *                        '------'   '------'                                 `------.   '-----'
 *                                        ,-------.       ,-------.
 *                                        |       |       |       |
 *                                 ,------|-------|       |-------|------.
 *                                 |      |       |       |       |      |
 *                                 |      |       |       |       |      |
 *                                 |      |       |       |       |      |
 *                                 `--------------'       `--------------'
[SYMB] = LAYOUT_gergo(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
 */
