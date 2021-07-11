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
#define _CODE 1
#define _SYM 2
#define _SYM2 3
#define _FUNC 4
#define _SPEC 5
#define _GAMR 6

#define MODS_SHIFT_MASK (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT))
#define MODS_CTRL_MASK (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTL))
#define MODS_ANY_MASK (MODS_SHIFT_MASK|MODS_CTRL_MASK|MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))

#define OS_LSFT OSM(MOD_LSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_RALT OSM(MOD_RALT)
#define OS_SYM  OSL(_SYM)
#define OS_SYM2 OSL(_SYM2)
#define MO_FUNC MO(_FUNC)
#define MO_SPEC MO(_SPEC)
#define TO_GAMR TO(_GAMR)
#define MT_SFSL MT(MOD_LALT, KC_SLSH)
#define LT_SPDT MT(_SPEC, KC_DOT)

static uint8_t mods_stash, mods_os;
static bool sym_stash = false;

enum custom_keycodes {
    CK_LCLR = SAFE_RANGE, // layers clear
    CK_GRVT,
    CK_DTCM,
    CK_SHRUG,
    CK_SDEL
};

enum custom_modes {
    MODE_CLEAR,
    MODE_ONESHOT,
    MODE_LOCK
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
    L_GLLM,
    R_GLLM,
    L_ANGL,
    R_ANGL,
    CB_CRN
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
    [L_GLLM] = 0x00AB, // «
    [R_GLLM] = 0X00BB, // »
    [L_ANGL] = 0x27E8, // ⟨
    [R_ANGL] = 0x27E9, // ⟩
    [CB_CRN] = 0x030C  // ◌̌
};

void stash_mods(void) {
    mods_stash |= get_mods();
    clear_mods();
    mods_os |= get_oneshot_mods();
    clear_oneshot_mods();
}

void unstash_mods(void) {
    register_mods(mods_stash);
    mods_stash = 0;
    mods_os = 0;
}

bool custom_shift_keycode(int16_t unshifted, int16_t shifted, bool pressed) {
    uint16_t is_shifted = 0;

    if(pressed) {
        stash_mods();
        is_shifted = (mods_stash | mods_os) & MODS_SHIFT_MASK;

        if(is_shifted) {
            register_code16(shifted);
        }
        else {
            register_code16(unshifted);
        }
    }
    else {
        is_shifted = (mods_stash | mods_os) & MODS_SHIFT_MASK;

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
            layer_clear();
            clear_mods();
            clear_oneshot_mods();
            mods_stash = 0;
            mods_os = 0;
        }
        return false;
        break;
    case CK_GRVT:
        custom_shift_keycode(ES_GRV, ES_TILD, record->event.pressed);
        return false;
        break;
    case CK_DTCM:
        custom_shift_keycode(KC_DOT, KC_COMM, record->event.pressed);
        return false;
        break;
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
            if(layer_state_is(_SYM) || layer_state_is(_SYM2))
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
     * | Esc  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | à, ã |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | á, ä |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   Ñ  |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |Shift |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   Ç  | .  , |  Up  | Del  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Ctrl | WIN  | _SYM | Alt  |_FUNC |    Space    |AltGr | _SPC | Down | Down |Right |
     * `-----------------------------------------------------------------------------------'
     */
    [_DEFLT] = LAYOUT( \
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_BSPC, \
        CK_GRVT, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    ES_ACUT, \
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    ES_NTIL, KC_ENT,  \
        OS_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    ES_CCED, CK_DTCM, KC_UP,   KC_DEL,  \
        KC_LCTL, KC_LGUI, OS_SYM,  KC_LALT, MO_FUNC, KC_SPC,  KC_SPC,  KC_RALT, MO_SPEC, KC_LEFT, KC_DOWN, KC_RGHT  \
    ),

    /* SYM
     * ,-----------------------------------------------------------------------------------.
     * | LCLR |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   º  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  â   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |   @  |   #  |   €  |   _  |   &  |   -  |   +  |   (  |   )  |   /  |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |_SYM2 |   *  |   "  |   '  |   :  |   ;  |   !  |   ?  |   <  |   >  |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |  NO  |      |      |  NO  |      |             |  NO  |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */

    [_SYM] = LAYOUT( \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
       ES_MORD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    ES_CIRC,  \
       _______, ES_AT,   ES_HASH, ES_EURO, ES_UNDS, ES_AMPR, ES_MINS, ES_PLUS, ES_LPRN, ES_RPRN, ES_SLSH, _______,  \
       OS_SYM2, ES_ASTR, ES_DQUO, ES_QUOT, ES_COLN, ES_SCLN, ES_EXLM, ES_QUES, ES_LABK, ES_RABK, _______, _______,  \
       KC_NO,   _______, _______, KC_NO,   _______, _______, KC_NO,   _______, _______, _______, _______, _______   \
    ),

    /* SYM2
     * ,-----------------------------------------------------------------------------------.
     * | LCLR |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   ª  |   |  |      |      |   ·  |   ¬  |   ÷  |   ×  |   {  |   }  | Shrug|  ǎ*  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |   £  |   ¥  |   $  |   ¢  |   ¤  |  --  |   =  |   [  |   ]  |   \  |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |   %  |   «  |   »  |   ™  |  ✓  |  ¡   |   ¿  |   ⟨  |   ⟩  |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     * Shrug: ¯\_(ツ)_/¯
     */

    [_SYM2] = LAYOUT( \
       _______, _______, _______,  _______,  _______, _______, _______, _______, _______,  _______,  _______, _______,  \
       ES_FORD, ES_PIPE, _______,  _______,  ES_BULT, ES_NOT,  X(DIVIS),X(MULT), ES_LCBR,  ES_RCBR,  CK_SHRUG,X(CB_CRN),  \
       _______, X(POUND),X(YEN),   ES_DLR,   X(CENT), X(MONEY),X(MDASH),ES_EQL,  ES_LBRC,  ES_RBRC,  ES_BSLS, _______,  \
       _______, ES_PERC, X(L_GLLM),X(R_GLLM),X(TRDM), X(CHKM), ES_IEXL, ES_IQUE, X(L_ANGL),X(R_ANGL),_______, _______,  \
       _______, _______, _______,  _______,  _______, _______, _______, _______, _______,  _______,  _______, _______   \
    ),

    /* Func
     * ,-----------------------------------------------------------------------------------.
     * | LCLR |      |      |      |      |      |      |      |      |      |      |ImprPt|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      | Ins  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      | Home | Del++|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |      | PgUp | End  | PgDn |
     * `-----------------------------------------------------------------------------------'
     */
    [_FUNC] = LAYOUT( \
       _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_PSCR, \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,  \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, C(KC_INS),\
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, CK_SDEL, \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_END,  KC_PGDN  \
    ),

    /* Special
     * ,-----------------------------------------------------------------------------------.
     * | LCLR |      |      |      |      |      |      |      |      |      |      | RESET|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |UC_LNX|UC_WNC|UC_WIN|      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |_GAMR |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      | Vol+ | Mute |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      | Play/Pause  |      |      | Prev | Vol- | Next |
     * `-----------------------------------------------------------------------------------'
     */
    [_SPEC] = LAYOUT( \
       CK_LCLR, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,   \
       _______, UC_M_LN, UC_M_WC, UC_M_WI, _______, _______, _______, _______, _______, _______, _______, _______, \
       _______, _______, _______, _______, _______, TO_GAMR, _______, _______, _______, _______, _______, _______, \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, KC_MUTE, \
       _______, _______, _______, _______, _______, KC_MPLY, KC_MPLY, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT  \
    ),


    /* Gaming
     * ,-----------------------------------------------------------------------------------.
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_GAMR] = LAYOUT( \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
       KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
       KC_LCTL, _______, _______, KC_LALT, KC_SPC,  _______, _______, _______, _______, _______, _______, _______  \
    )
};
