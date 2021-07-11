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
#define _SHFT 1
#define _SYM 2
#define _SHSYM 3
#define _FUNC 4
#define _FN 5

#define MODS_SHIFT_MASK (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT))
#define MODS_CTRL_MASK (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTL))
#define MODS_ANY_MASK (MODS_SHIFT_MASK|MODS_CTRL_MASK|MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define LAYER_ABOVE_SHSYM 1Ul<<_FUNC;

enum custom_keycodes {
    CK_LCLR = SAFE_RANGE, // layers clear
    CK_SYM,
    CK_FUNC,
    CK_FN,
    CK_GRVT,
    CK_DTCM,
    SHSM_TRNS,
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
    EMDASH,
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
    [EMDASH] = 0x2014, // —
    [L_GLLM] = 0x00AB, // «
    [R_GLLM] = 0X00BB, // »
    [L_ANGL] = 0x27E8, // ⟨
    [R_ANGL] = 0x27E9, // ⟩
    [CB_CRN] = 0x030C  // ◌̌
};

static enum custom_modes mode_ctrl, mode_shift, mode_sym, mode_alt, mode_func, mode_altgr, mode_fn;
static bool mode_dirty;
static uint16_t fallthrough;

void mode_clear(void)
{
    if(mode_ctrl == MODE_ONESHOT)
    {
        mode_ctrl = MODE_CLEAR;
        unregister_code(KC_LCTRL);
    }
    if(mode_shift == MODE_ONESHOT)
    {
        mode_shift = MODE_CLEAR;
        layer_off(_SHFT);
        update_tri_layer(_SHFT, _SYM, _SHSYM);
        unregister_code(KC_LSHIFT);
    }
    if(mode_sym == MODE_ONESHOT)
    {
        mode_sym = MODE_CLEAR;
        layer_off(_SYM);
        update_tri_layer(_SHFT, _SYM, _SHSYM);
    }
    if(mode_alt == MODE_ONESHOT)
    {
        mode_alt = MODE_CLEAR;
        unregister_code(KC_LALT);
    }
    if(mode_func == MODE_ONESHOT)
    {
        mode_func = MODE_CLEAR;
        layer_off(_FUNC);
    }
    if(mode_altgr == MODE_ONESHOT)
    {
        mode_altgr = MODE_CLEAR;
        unregister_code(KC_RALT);
    }
    if(mode_fn == MODE_ONESHOT)
    {
        mode_fn = MODE_CLEAR;
        layer_off(_FN);
    }
};

void mode_unset(void)
{
    layer_clear();
    clear_mods();
}

void mode_restore(void)
{
    if(mode_ctrl != MODE_CLEAR)
    {
        register_code(KC_LCTRL);
    }
    if(mode_shift != MODE_CLEAR)
    {
        layer_on(_SHFT);
        register_code(KC_LSHIFT);
        update_tri_layer(_SHFT, _SYM, _SHSYM);
    }
    if(mode_sym != MODE_CLEAR)
    {
        layer_on(_SYM);
        update_tri_layer(_SHFT, _SYM, _SHSYM);
    }
    if(mode_alt != MODE_CLEAR)
    {
        register_code(KC_LALT);
    }
    if(mode_func != MODE_CLEAR)
    {
        layer_on(_FUNC);
    }
    if(mode_altgr != MODE_CLEAR)
    {
        register_code(KC_RALT);
    }
    if(mode_fn != MODE_CLEAR)
    {
        layer_on(_FN);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t layer;
    bool res = true;

    switch (keycode)
    {
    case CK_LCLR:
        if(record->event.pressed)
        {
            layer_clear();
            if(keyboard_report->mods & MODS_ANY_MASK)
            {
                clear_mods();
            }
        }
        return false;
        break;
    case KC_ESC:
        if(keyboard_report->mods & MODS_ANY_MASK)
        {
            if(record->event.pressed)
            {
                clear_mods();
            }
            return false;
        }
        return true; // Behave as Esc only if it doesn't clear Mods or Layers
        break;
    case KC_LCTL:
        if(record->event.pressed)
        {
            switch (mode_ctrl)
            {
            case MODE_CLEAR:
                mode_alt = MODE_ONESHOT;
                register_code(KC_LCTL);
                break;
            case MODE_ONESHOT:
                mode_alt = MODE_LOCK;
                break;
            case MODE_LOCK:
                mode_alt = MODE_CLEAR;
                unregister_code(KC_LCTL);
            default:
                break;
            }
        }
        return false;
        break;
    case KC_LSFT:
        if(record->event.pressed)
        {
            switch (mode_shift)
            {
            case MODE_CLEAR:
                mode_shift = MODE_ONESHOT;
                register_code(KC_LSHIFT);
                layer_on(_SHFT);
                break;
            case MODE_ONESHOT:
                mode_shift = MODE_LOCK;
                break;
            case MODE_LOCK:
                mode_shift = MODE_CLEAR;
                layer_off(_SHFT);
                unregister_code(KC_LSHIFT);
            default:
                break;
            }
        }
        update_tri_layer(_SHFT, _SYM, _SHSYM);
        return false;
        break;
    case CK_SYM:
        if(record->event.pressed)
        {
            switch (mode_sym)
            {
            case MODE_CLEAR:
                mode_sym = MODE_ONESHOT;
                layer_on(_SYM);
                break;
            case MODE_ONESHOT:
                mode_sym = MODE_LOCK;
                break;
            case MODE_LOCK:
                mode_sym = MODE_CLEAR;
                layer_off(_SYM);
            default:
                break;
            }
        }
        update_tri_layer(_SHFT, _SYM, _SHSYM);
        return false;
        break;
    case KC_LALT:
        if(record->event.pressed)
        {
            switch (mode_alt)
            {
            case MODE_CLEAR:
                mode_alt = MODE_ONESHOT;
                register_code(KC_LALT);
                break;
            case MODE_ONESHOT:
                mode_alt = MODE_LOCK;
                break;
            case MODE_LOCK:
                mode_alt = MODE_CLEAR;
                unregister_code(KC_LALT);
            default:
                break;
            }
        }
        return false;
        break;
    case CK_FUNC:
        if(record->event.pressed)
        {
            switch (mode_func)
            {
            case MODE_CLEAR:
                mode_func = MODE_ONESHOT;
                layer_on(_FUNC);
                break;
            case MODE_ONESHOT:
                mode_func = MODE_LOCK;
                break;
            case MODE_LOCK:
                mode_func = MODE_CLEAR;
                layer_off(_FUNC);
            default:
                break;
            }
        }
        return false;
        break;
    case KC_RALT:
        if(record->event.pressed)
        {
            switch (mode_altgr)
            {
            case MODE_CLEAR:
                mode_altgr = MODE_ONESHOT;
                register_code(KC_RALT);
                break;
            case MODE_ONESHOT:
                mode_altgr = MODE_LOCK;
                break;
            case MODE_LOCK:
                mode_altgr = MODE_CLEAR;
                unregister_code(KC_RALT);
            default:
                break;
            }
        }
        return false;
        break;
    case CK_FN:
        if(record->event.pressed)
        {
            switch (mode_func)
            {
            case MODE_CLEAR:
                mode_fn = MODE_ONESHOT;
                layer_on(_FN);
                break;
            case MODE_ONESHOT:
                mode_fn = MODE_LOCK;
                break;
            case MODE_LOCK:
                mode_fn = MODE_CLEAR;
                layer_off(_FN);
            default:
                break;
            }
        }
        return false;
        break;
    case CK_GRVT:
        if(record->event.pressed)
        {
            mode_unset();
            if(mode_shift != MODE_CLEAR)
            {
                register_code16(ES_TILD);
            }
            else
            {
                register_code16(ES_GRV);
            }
        }
        else
        {
            if(mode_shift != MODE_CLEAR)
            {
                unregister_code16(ES_TILD);
            }
            else
            {
                unregister_code16(ES_GRV);
            }
            mode_dirty = true;
            mode_restore();
        }
        res = false;
        break;
    case CK_DTCM:
        if(record->event.pressed)
        {
            mode_unset();
            if(mode_shift != MODE_CLEAR)
            {
                register_code16(ES_COMM);
            }
            else
            {
                register_code16(ES_DOT);
            }
        }
        else
        {
            if(mode_shift != MODE_CLEAR)
            {
                unregister_code16(ES_COMM);
            }
            else
            {
                unregister_code16(ES_DOT);
            }
            mode_dirty = true;
            mode_restore();
        }
        res = false;
        break;
    case SHSM_TRNS:
        if (record->event.pressed)
        {
          // OR these two because layer_state does not include the default layer
            uint32_t state = (layer_state | default_layer_state);
            uint8_t next_active_layer = biton32(state ^ (1Ul<<biton32(state)));

            fallthrough = keymap_key_to_keycode(next_active_layer, record->event.key);

            res = process_record_user(fallthrough, record);
        } else {
            res = process_record_user(fallthrough, record);
        }
        break;
    case CK_SHRUG:
        if(record->event.pressed)
        {
            send_unicode_string("¯\\_(ツ)_/¯");
        }
        return false;
        break;
    case CK_SDEL:
        if(record->event.pressed)
        {
            tap_code16(C(KC_A));
        }
        else
        {
            tap_code16(KC_DEL);
        }
        return false;
        break;
    default:
        if(!record->event.pressed)
        {
            mode_dirty = true;
        }
        break;
    }

    //_SHSYM has been shifted by the _SHFT handling, so the layer keys need to be excluded
    layer = biton32(layer_state);
    if (layer & _SHSYM) {
        // Every key that needed to keep the shift was processed as SHSM_TRNS, exclude everything else
        if (record->event.pressed) {
            //unregister_mods(MOD_LSFT);
            mode_unset();
            register_code16(keycode);
        } else {
            //register_mods(MOD_LSFT);
            unregister_code16(keycode);
            mode_dirty = true;
            mode_restore();
        }
    }

    if(mode_dirty)
    {
        mode_clear();
        mode_dirty = false;
    }

    return res;
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
     * | Ctrl | _SYM | Win  | Alt  |_FUNC |    Space    |AltGr | _FN  | Down | Down |Right |
     * `-----------------------------------------------------------------------------------'
     */
    [_DEFLT] = LAYOUT( \
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_BSPC, \
        CK_GRVT, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    ES_ACUT, \
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    ES_NTIL, KC_ENT,  \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    ES_CCED, CK_DTCM, KC_UP,   KC_DEL,  \
        KC_LCTL, CK_SYM,  KC_LGUI, KC_LALT, CK_FUNC, KC_SPC,  KC_SPC,  KC_RALT, CK_FN,   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),

    /* SHFT
     * ,-----------------------------------------------------------------------------------.
     * | LCLR |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */

    [_SHFT] = LAYOUT( \
       CK_LCLR, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______   \
    ),

    /* SYM
     * ,-----------------------------------------------------------------------------------.
     * | LCLR |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   º  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  â   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |   @  |   #  |   €  |   _  |   &  |   -  |   +  |   (  |   )  |   /  |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |   *  |   "  |   '  |   :  |   ;  |   !  |   ?  |   <  |   >  |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */

    [_SYM] = LAYOUT( \
       CK_LCLR, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
       ES_MORD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    ES_CIRC,  \
       _______, ES_AT,   ES_HASH, ES_EURO, ES_UNDS, ES_AMPR, ES_MINS, ES_PLUS, ES_LPRN, ES_RPRN, ES_SLSH, _______,  \
       _______, ES_ASTR, ES_DQUO, ES_QUOT, ES_COLN, ES_SCLN, ES_EXLM, ES_QUES, ES_LABK, ES_RABK, _______, _______,  \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______   \
    ),

    /* SHSYM
     * ,-----------------------------------------------------------------------------------.
     * | LCLR |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   ª  |      |      |   |  |   ·  |   ¬  |   ÷  |   ×  |   {  |   }  | Shrug|  ǎ*  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |   £  |   ¥  |   $  |   ¢  |   ¤  |  --  |   =  |   [  |   ]  |   \  |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |   %  |   «  |   »  |   ™  |  ✓  |  ¡   |   ¿  |   ⟨  |   ⟩  |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     * Shrug: ¯\_(ツ)_/¯
     */

    [_SHSYM] = LAYOUT( \
       CK_LCLR,  SHSM_TRNS,SHSM_TRNS,SHSM_TRNS,SHSM_TRNS,SHSM_TRNS,SHSM_TRNS,SHSM_TRNS,SHSM_TRNS,SHSM_TRNS,SHSM_TRNS,SHSM_TRNS,  \
       ES_FORD,  SHSM_TRNS,SHSM_TRNS,ES_PIPE,  ES_BULT,  ES_NOT,   X(DIVIS), X(MULT),  ES_LCBR,  ES_RCBR,  CK_SHRUG, X(CB_CRN),  \
       SHSM_TRNS,X(POUND), X(YEN),   ES_DLR,   X(CENT),  X(MONEY), X(EMDASH),ES_EQL,   ES_LBRC,  ES_RBRC,  ES_SLSH,  SHSM_TRNS,  \
       SHSM_TRNS,ES_PERC,  X(L_GLLM),X(R_GLLM),X(TRDM),  X(CHKM),  ES_IEXL,  ES_IQUE,  X(L_ANGL),X(R_ANGL),SHSM_TRNS,SHSM_TRNS,  \
       SHSM_TRNS,SHSM_TRNS,SHSM_TRNS,SHSM_TRNS,SHSM_TRNS,SHSM_TRNS,SHSM_TRNS,SHSM_TRNS,SHSM_TRNS,SHSM_TRNS,SHSM_TRNS,SHSM_TRNS   \
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
     * |      |      |      |      |      |      |      |      |      | PgUp | End  | PgDn |
     * `-----------------------------------------------------------------------------------'
     */
    [_FUNC] = LAYOUT( \
       CK_LCLR, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_PSCR, \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,  \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, CK_SDEL, \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_END,  KC_PGDN  \
    ),

    /* Fn
     * ,-----------------------------------------------------------------------------------.
     * | LCLR |      |      |      |      |      |      |      |      |      |      | RESET|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      | UC_LX| UC_WN| UC_WI|      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |Ply/Ps| Vol+ | Mute |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      | Prev | Vol- | Next |
     * `-----------------------------------------------------------------------------------'
     */
    [_FN] = LAYOUT( \
       CK_LCLR, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,   \
       _______, UC_M_LN, UC_M_WC, UC_M_WI, _______, _______, _______, _______, _______, _______, _______, _______, \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, KC_VOLU, KC_MUTE, \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT  \
    )
};
