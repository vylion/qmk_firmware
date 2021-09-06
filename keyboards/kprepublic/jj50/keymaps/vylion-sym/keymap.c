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
#include "keymap_spanish.h"

#define ______ KC_TRNS
#define _DEFLT 0
#define _FN 2
#define _PN 3
#define _GAME 1

#define OS_LSFT OSM(MOD_LSFT)
#define OS_FN OSL(_FN)
#define MO_FN MO(_FN)
#define TO_GAME TO(_GAME)

#define LM_ALFN LM(_FN, MOD_LALT)
#define LT_TBPN LT(_PN, KC_TAB)

#define SP_PASTE C(KC_INS)

/* Unused:
#define MODS_ANY_MASK (MODS_SHIFT_MASK|MODS_CTRL_MASK|MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define MODS_CTRL_MASK (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTL))

#define OS_LCTL OSM(MOD_LCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_RALT OSM(MOD_RALT)
#define MT_SPAL MT(MOD_LALT, KC_SPC)
#define MT_ABCT MT(MOD_LCTL, KC_NUBS)
#define LT_ENFN LT(_FN, KC_ENT)
*/

static uint8_t shift_stash, shift_os;
static bool sym_stash = false;

enum custom_keycodes {
    CK_LCLR = SAFE_RANGE, // layers clear
    CK_GRVT,
    CK_SHRUG,
    CK_SDEL,
    CK_INTX,
    CK_PRNT,
    CK_SQBK,
    CK_CRBK,
    CK_QUOT,
    CK_TRI0,
    CK_ANOR,
    CK_DIV,
    CK_RES
};

enum unicode_names {
    DIVIS,
    MULT,
    CHKM,
    TRDM,
    POUND,
    YEN,
    CENT,
    MONEY,
    MDASH,
    LGLM,
    RGLM,
    LNGL,
    RNGL,
    CMCRN
};

const uint32_t PROGMEM unicode_map[] = {
    [DIVIS]  = 0x20F7, // ÷
    [MULT]   = 0x00D7, // ×
    [CHKM]   = 0x2713, // ✓
    [TRDM]   = 0x2122, // ™
    [POUND]  = 0x00A3, // £
    [YEN]    = 0x00A5, // ¥
    [CENT]   = 0x00A2, // ¢
    [MONEY]  = 0x00A4, // ¤
    [MDASH]  = 0x2014, // —
    [LGLM]   = 0x00AB, // «
    [RGLM]   = 0x00BB, // »
    [LNGL]   = 0x27E8, // ⟨
    [RNGL]   = 0x27E9, // ⟩
    [CMCRN]  = 0x030C  // ◌̌
};

void stash_mods(void) {
    shift_stash |= get_mods() & MOD_MASK_SHIFT;
    set_mods(get_mods() & ~(MOD_MASK_SHIFT));
    shift_os |= get_oneshot_mods() & MOD_MASK_SHIFT;
    set_oneshot_mods(get_oneshot_mods() & ~(MOD_MASK_SHIFT));
}

void unstash_mods(void) {
    register_mods(shift_stash);
    shift_stash = 0;
    shift_os = 0;
    clear_oneshot_mods();
}

bool custom_shift_keycode(int16_t unshifted, int16_t shifted, bool pressed) {
    uint16_t is_shifted = 0;

    if(pressed) {
        stash_mods();
        is_shifted = (shift_stash | shift_os);

        if(is_shifted) {
            register_code16(shifted);
        }
        else {
            register_code16(unshifted);
        }
    }
    else {
        is_shifted = (shift_stash | shift_os);

        if(is_shifted) {
            unregister_code16(shifted);
        }
        else {
            unregister_code16(unshifted);
        }
        unstash_mods();
    }

    return is_shifted;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode)
    {
    case CK_LCLR:
        if(record->event.pressed)
        {
            unstash_mods();
            layer_clear();
            clear_mods();
        }
        return false;
        break;
    case CK_GRVT:
        custom_shift_keycode(ES_GRV, ES_TILD, record->event.pressed);
        return false;
    case CK_INTX:
        custom_shift_keycode(ES_EXLM, ES_QUES, record->event.pressed);
        return false;
    case CK_PRNT:
        custom_shift_keycode(ES_LPRN, ES_RPRN, record->event.pressed);
        return false;
    case CK_SQBK:
        custom_shift_keycode(ES_LBRC, ES_RBRC, record->event.pressed);
        return false;
    case CK_CRBK:
        custom_shift_keycode(ES_LCBR, ES_RCBR, record->event.pressed);
        return false;
    case CK_QUOT:
        custom_shift_keycode(ES_QUOT, ES_DQUO, record->event.pressed);
        return false;
    case CK_ANOR:
        custom_shift_keycode(ES_AMPR, ES_PIPE, record->event.pressed);
        return false;
    case CK_DIV:
        custom_shift_keycode(ES_SLSH, ES_PERC, record->event.pressed);
        return false;
    case CK_RES:
        custom_shift_keycode(ES_MINS, ES_EQL, record->event.pressed);
        return false;
    case CK_TRI0:
        if(record->event.pressed)
        {
            SEND_STRING("000");
        }
        return false;
    case CK_SHRUG:
        if(record->event.pressed)
        {
            send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF");
        }
        return false;
        break;
    case CK_SDEL:
        if(record->event.pressed)
        {
            stash_mods();
            tap_code16(C(KC_A));
        }
        else
        {
            tap_code16(KC_DEL);
            unstash_mods();
        }
        return false;
        break;
    default:
        if(record->event.pressed)
        {
            if(layer_state_is(_FN))
            {
                stash_mods();
                sym_stash = true;
            }
        }
        else if(sym_stash)
        {
            unstash_mods();
            sym_stash = false;
        }
        break;
    }

    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
     * ,-----------------------------------------------------------------------------------.
     * | Esc  |  !?  |  '"  |  ()  |  []  |  {}  |  <>  |  &|  |  /%  |  +*  |  -=  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | à, ã |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | á  ä |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |Tab/Pn|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   Ñ  |   Ç  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Shft |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  | Del  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Ctrl |  Win |  Alt |Alt+Fn|    Space    |    Return   |  Fn  | Down | Down |Right |
     * `-----------------------------------------------------------------------------------'
     */
    [_DEFLT] = LAYOUT( \
        KC_ESC,  CK_INTX, CK_QUOT, CK_PRNT, CK_SQBK, CK_CRBK, ES_LABK, CK_ANOR, CK_DIV,  ES_PLUS, CK_RES,  KC_BSPC, \
        CK_GRVT, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    ES_ACUT, \
        LT_TBPN, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    ES_NTIL, ES_CCED, \
        OS_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_DEL,  \
        KC_LCTL, KC_LGUI, KC_LALT, LM_ALFN, KC_SPC,  KC_SPC,  KC_ENT,  KC_ENT,  OS_FN,   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),

    /* FN
     * ,-----------------------------------------------------------------------------------.
     * |   º  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |PrtScr|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   ª  |   7  |   8  |   9  |Bullet|   ¢  |   ¥  |   ¬  |   ×  |   ÷  | Shrug|   â  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   \  |   4  |   5  |   6  |   #  |   €  |   £  |   ¤  |   ⟨  |   ⟩  |   ¡  |   ¿  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |   1  |   2  |   3  |   @  |   $  |   ™  |   ✓  |   «  |   »  | Home |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |  000 |   0  | (Fn) |      _      |     ---     |(AlFn)| PgUp | End  | PgDn |
     * `-----------------------------------------------------------------------------------'
     */

    [_FN] = LAYOUT( \
       ES_MORD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_PSCR, \
       ES_FORD, KC_7,    KC_8,    KC_9,    ES_BULT, X(CENT), X(YEN),  ES_NOT,  X(MULT), X(DIVIS),CK_SHRUG,ES_CIRC, \
       ES_BSLS, KC_4,    KC_5,    KC_6,    ES_HASH, ES_EURO, X(POUND),X(MONEY),X(LNGL), X(RNGL), ES_IEXL, ES_IQUE, \
       _______, KC_1,    KC_2,    KC_3,    ES_AT,   ES_DLR,  X(TRDM), X(CHKM), X(LGLM), X(RGLM), KC_HOME, _______, \
       _______, CK_TRI0, KC_0,    _______, ES_UNDS, ES_UNDS, X(MDASH),X(MDASH),_______, KC_PGUP, KC_END,  KC_PGDN  \
    ),

    /* Func
     * ,-----------------------------------------------------------------------------------
     * | Reset|  F11 |  F12 |  F13 |  F14 |  F15 |  F16 |  F17 |  F18 |  F19 |  F20 |ImprPt|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Lock |UN Lnx|UN WnC|UN Win|      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | (Pn) |      |      |      |      |      |      |      |      |      |      | Ins  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |CtlIns|      |      |      |      |      | Vol+ | Mute |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      | Play/Pause  | Layer Clear |      |PlPrev| Vol- |PlNext|
     * `-----------------------------------------------------------------------------------'
     */
    [_PN] = LAYOUT( \
       RESET,   KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  CK_SDEL, \
       KC_LOCK, UC_M_LN, UC_M_WC, UC_M_WI, _______, _______, _______, _______, _______, _______, _______, _______, \
       _______, _______, _______, _______, _______, TO_GAME, _______, _______, _______, _______, _______, KC_INS,  \
       _______, _______, _______, _______, SP_PASTE,_______, _______, _______, _______, _______, KC_VOLU, KC_MUTE, \
       _______, _______, _______, _______, KC_MPLY, KC_MPLY, CK_LCLR, CK_LCLR, _______, KC_MPRV, KC_VOLD, KC_MNXT  \
    ),


    /* Gaming
     * ,-----------------------------------------------------------------------------------
     * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Shft |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |             |             |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_GAME] = LAYOUT( \
       _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
       KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
    )
};
