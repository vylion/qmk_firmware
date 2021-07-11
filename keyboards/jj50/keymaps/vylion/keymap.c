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
#define _GAME 1
#define _FN 2
#define _SYM 3
#define _PN 4

#define OS_LSFT OSM(MOD_LSFT)
#define OS_FN OSL(_FN)
#define MO_FN MO(_FN)
#define TO_GAME TO(_GAME)

#define LT_FN   LT(_FN, KC_SLSH)
#define LT_SYM  LT(_SYM, KC_DOT)
#define LT_TBPN LT(_PN, KC_TAB)
#define MT_LCTL MT(MOD_LCTL, KC_NUBS)

#define SP_PSTE S(KC_INS)
#define SP_COPY C(KC_INS)
#define AL_LEFT A(KC_LEFT)
#define AL_RGHT A(KC_RGHT)
#define TASKMGR C(S(KC_ESC))
#define WN_HELP A(C(KC_DEL))

#define ES_PLUS KC_RBRC
#define ES_GRV KC_LBRC
#define ES_ORD KC_GRV
#define ES_QUOT KC_MINS
#define ES_DLR S(KC_4)
#define ES_EUR ALGR(KC_E)
#define ES_BULT S(KC_3)
#define ES_IEXL KC_EQL
#define ES_IQUE S(ES_IEXL)
#define ES_CIRC S(ES_GRV)
#define ES_NOT ALGR(KC_6)

/* Unused:
#define MODS_ANY_MASK (MODS_SHIFT_MASK|MODS_CTRL_MASK|MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define MODS_CTRL_MASK (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTL))

#define OS_LCTL OSM(MOD_LCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_RALT OSM(MOD_RALT)
#define MT_SPAL MT(MOD_LALT, KC_SPC)
#define MT_ABCT MT(MOD_LCTL, KC_NUBS)
*/

static uint8_t shift_stash, shift_os;
static bool sym_stash = false;
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum custom_keycodes {
    CK_LCLR = SAFE_RANGE, // layers clear
    CK_GRVT,
    CK_SHRUG,
    CK_SDEL,
    CK_INTX,
    CK_TRI0,
    CK_PSLS,
    CK_QUOT,
    CK_ATPN,
    CK_PRNT,
    CK_SQBK,
    CK_CRBK,
    CK_NAND,
    CK_DIV,
    CT_TAB,
    CT_STAB,
    CTW_STB,
    AL_TAB,
    AL_STAB
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
        custom_shift_keycode(ES_GRV, ALGR(KC_4), record->event.pressed); // ` ~
        return false;
    case CK_INTX:
        custom_shift_keycode(S(KC_1), S(ES_QUOT), record->event.pressed); // ! ?
        return false;
    case CK_PSLS:
        custom_shift_keycode(ALGR(ES_ORD), ALGR(KC_1), record->event.pressed); // \ |
        return false;
    case CK_QUOT:
        custom_shift_keycode(ES_QUOT, S(KC_2), record->event.pressed); // ' "
        return false;
    case CK_ATPN:
        custom_shift_keycode(ALGR(KC_2), ALGR(KC_3), record->event.pressed); // @ #
        return false;
    case CK_PRNT:
        custom_shift_keycode(S(KC_8), S(KC_9), record->event.pressed); // ( )
        return false;
    case CK_SQBK:
        custom_shift_keycode(ALGR(ES_GRV), ALGR(ES_PLUS), record->event.pressed); // [ ]
        return false;
    case CK_CRBK:
        custom_shift_keycode(ALGR(KC_QUOT), ALGR(KC_NUHS), record->event.pressed); // { }
        return false;
    case CK_NAND:
        custom_shift_keycode(S(KC_6), S(KC_0), record->event.pressed); // & =
        return false;
    case CK_DIV:
        custom_shift_keycode(S(KC_7), S(KC_5), record->event.pressed); // / %
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
    case CT_TAB:
        if(record->event.pressed)
        {
            stash_mods();
            tap_code16(C(KC_TAB));
        }
        else
        {
            unstash_mods();
        }
        return false;
    case CT_STAB:
        if(record->event.pressed)
        {
            stash_mods();
            tap_code16(S(C(KC_TAB)));
        }
        else
        {
            unstash_mods();
        }
        return false;
    case CTW_STB:
        if(record->event.pressed)
        {
            stash_mods();
            tap_code16(C(KC_W));
        }
        else
        {
            tap_code16(C(S(KC_TAB)));
            unstash_mods();
        }
        return false;
    /*
    case AL_TAB:
        if (record->event.pressed) {
            if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                register_code(KC_LALT);
            }
            alt_tab_timer = timer_read();
            register_code(KC_TAB);
        } else {
            unregister_code(KC_TAB);
        }
        break;
    case AL_STAB:
        if (record->event.pressed) {
            if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                register_code(KC_LALT);
            }
            alt_tab_timer = timer_read();
            register_code16(S(KC_TAB));
        } else {
            unregister_code16(S(KC_TAB));
        }
        break;
    */
    default:
        if(record->event.pressed)
        {
            if(layer_state_is(_SYM))
            {
                stash_mods();
                sym_stash = true;
            }
        }
        else {
            if(sym_stash)
            {
                unstash_mods();
                sym_stash = false;
            }
        }
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
     * | Esc  |  \|  |  '"  |  @#  |  ()  |  []  |  {}  |  &=  |  /%  |  +*  |  ºª  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | à  ã |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | á  ä |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |Tab/Pn|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   Ñ  |   Ç  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Shft |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |  !?  |  Up  | Del  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |</Ctrl|  Win |  Alt | -_/Fn|    Space    |    Return   | ./Sym| Down | Down |Right |
     * `-----------------------------------------------------------------------------------'
     */
    [_DEFLT] = LAYOUT( \
        KC_ESC,  CK_PSLS, CK_QUOT, CK_ATPN, CK_PRNT, CK_SQBK, CK_CRBK, CK_NAND, CK_DIV,  ES_PLUS, ES_ORD,  KC_BSPC, \
        CK_GRVT, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT, \
        LT_TBPN, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_NUHS, \
        OS_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, CK_INTX, KC_UP,   KC_DEL,  \
        MT_LCTL, KC_LGUI, KC_LALT, LT_FN,   KC_SPC,  KC_SPC,  KC_ENT,  KC_ENT,  LT_SYM,  KC_LEFT, KC_DOWN, KC_RGHT  \
    ),

    /* FN
     * ,-----------------------------------------------------------------------------------.
     * |  F13 |  F14 |  F15 |  F16 |  F17 |  F18 |  F19 |  F20 |  F21 |  F22 |  F23 |  F24 |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |  AF1 |  AF2 |  AF3 |  AF4 |  AF5 |  AF6 |  AF7 |  AF8 |  AF9 | AF10 | AF11 | AF12 |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Caps |      |      |CtlIns|ShfIns|      |      |      |      |      | Home | Del++|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      | (Fn) |    Insert   | Layer Clear |      | PgUp | End  | PgDn |
     * `-----------------------------------------------------------------------------------'
     */

    [_FN] = LAYOUT( \
       KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,   KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,   KC_F24,  \
       A(KC_F1),A(KC_F2),A(KC_F3),A(KC_F4),A(KC_F5),A(KC_F6), A(KC_F7),A(KC_F8),A(KC_F9),A(KC_F10),A(KC_F11),A(KC_F12), \
       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  \
       KC_CAPS, _______, _______, SP_COPY, SP_PSTE, _______,  _______, _______, _______, _______, KC_HOME,  CK_SDEL, \
       _______, _______, _______, _______, KC_INS,   KC_INS,  CK_LCLR, CK_LCLR, _______, KC_PGUP, KC_END,   KC_PGDN  \
    ),

    /* SYM
     * ,-----------------------------------------------------------------------------------.
     * |      |   «  |   »  |   ·  |   ⟨  |   ⟩  |      |   ¬  |   ×  |   ÷  | Shrug|      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   7  |   8  |   9  | €(E) | ¤(R) | ™(T) | ¥(Y) |      |      |      |      |   â  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   4  |   5  |   6  | $(D) |      |      |      |      |      | £(L) |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   1  |   2  |   3  | ¢(C) | ✓(V) |      |      |      |   ¡  |   ¿  |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |  000 |   0  |      |  --- |             |             | (Sym)|      |      |      |
     * `-----------------------------------------------------------------------------------'
     */

    [_SYM] = LAYOUT( \
       _______, X(LGLM), X(RGLM), ES_BULT, X(LNGL), X(RNGL), _______, ES_NOT,  X(MULT), X(DIVIS),CK_SHRUG,_______,\
       KC_7,    KC_8,    KC_9,    ES_EUR, X(MONEY), X(TRDM), X(YEN),  _______, _______, _______, _______, ES_CIRC, \
       KC_4,    KC_5,    KC_6,    ES_DLR,  _______, _______, _______, _______, _______, X(POUND),_______, _______, \
       KC_1,    KC_2,    KC_3,    X(CENT), X(CHKM), _______, _______, _______, ES_IEXL, ES_IQUE, _______, _______, \
       CK_TRI0, KC_0,    _______, X(MDASH),_______, _______, _______, _______, _______, _______, _______, _______  \
    ),

    /* PN
     * ,-----------------------------------------------------------------------------------
     * | Reset|UN Lnx|UN WnC|UN Win|      |      |      |      |      |      |      |ImprPt|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |Ct+W,⇤|MouseL|Wheel+|MouseR|      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | (Pn) |Ctl ⇤ |Mouse1|Ctl ⇥ |      | Game |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Lock |Wheel←|Wheel-|Wheel→|      |      |      |      |      |      | Vol+ | Mute |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      | Play/Pause  |             |      |PlPrev| Vol- |PlNext|
     * `-----------------------------------------------------------------------------------'
     */
    [_PN] = LAYOUT( \
       RESET,   UC_M_LN, UC_M_WC, UC_M_WI, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, \
       CTW_STB, AL_LEFT, KC_WH_U, AL_RGHT,  _______, _______, _______, _______, _______, _______, _______, _______, \
       _______, CT_STAB, KC_BTN1, CT_TAB,  _______, TO_GAME, _______, _______, _______, _______, _______, _______, \
       KC_LOCK, KC_WH_L, KC_WH_D, KC_WH_R, _______, _______, _______, _______, _______, _______, KC_VOLU, KC_MUTE, \
       _______, _______, _______, _______, KC_MPLY, KC_MPLY, _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT  \
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
