/* Copyright 2015-2017 Jack Humbert
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

#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

enum planck_layers {
    _COLEMAK,
    _LOWER,
    _RAISE,
    _NAV,
    _IDEA,
    _XMONAD
};

enum planck_keycodes {
    COLEMAK = SAFE_RANGE,
    LOWER,
    RAISE
};

// Key aliases for legibility
#define ___x___ KC_NO
#define _______ KC_TRNS

// IDEA SHORT_CUTS
#define IDE_FSC S(LCTL(KC_F12))  // full screen
#define IDE_PRO LALT(KC_1)       // project view
#define IDE_VCS LALT(KC_GRV)     // code versioning

#define IDE_TBP LCTL(KC_F8)      // toggle break point
#define IDE_STI KC_F7            // step into
#define IDE_STO KC_F8            // step over
#define IDE_STC S(KC_F8)         // step out
#define IDE_CON KC_F9            // contiue
#define IDE_ABP LCTL(S(KC_F8))   // view all break points

#define IDE_IMP LCTL(LALT(KC_B)) // implementation
#define IDE_DEL LCTL(KC_B)       // declaration
#define IDE_CLH LCTL(KC_H)       // type hierarchy
#define IDE_CAH LCTL(LALT(KC_N)) // call hierarchy

#define IDE_CLA LCTL(KC_N)       // class
#define IDE_FIL LCTL(S(KC_N))    // file
#define IDE_REC LCTL(KC_E)       // recent files
#define IDE_NAV LALT(KC_HOME)    // navigation

#define IDE_FOR LCTL(LALT(KC_L)) // format code
#define IDE_BUI LCTL(KC_F9)      // build project
#define IDE_DEC S(KC_F9)         // debug current configuration
#define IDE_RUC S(KC_F10)        // run current configuration
#define IDE_RUN LALT(S(KC_F10))  // run configurations

#define IDE_ACT LCTL(S(KC_A))    // actions

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base layer (Colemak)
     *                ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     *                │  ⇥  │  Q  │  W  │  F  │  P  │  G  │  J  │  L  │  U  │  Y  │  ;  │  '  │
     *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     * Tap for Esc -- │  ⌃  │  A  │  R  │  S  │  T  │  D  │  H  │  N  │  E  │  I  │O Nav│  ⌃  │ -- Tap for Enter
     *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *   Tap for ( -- │  ⇧  │  Z  │  X  │  C  │  V  │  B  │  K  │  M  │  ,  │  .  │  /  │  ⇧  │ -- Tap for )
     *                ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
     *   Tap for [ -- │ IDE │     │  ⌥  │  ⌘  │  ↓  │   Space   │  ↑  │  ⌘  │  ⌥  │     │  X  │ -- Tap for ]
     *                └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
     *                        /                                                     /
     *   Tap for ] [ --------'-----------------------------------------------------'
     */
    [_COLEMAK] = {
        {KC_TAB        , KC_Q,     KC_W,    KC_F,    KC_P,    KC_G,    KC_J,     KC_L,       KC_U,      KC_Y,        KC_SCLN,        KC_QUOT},
        {CTL_T(KC_ESC) , KC_A,     KC_R,    KC_S,    KC_T,    KC_D,    KC_H,     KC_N,       KC_E,      KC_I, LT(_NAV, KC_O),  CTL_T(KC_ENT)},
        {KC_LSPO       , KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,    KC_K,     KC_M,    KC_COMM,    KC_DOT,        KC_SLSH,        KC_RSPC},
        {MO(_IDEA)     ,  _______ ,  KC_LALT, KC_LGUI,   LOWER,  KC_SPC,  KC_SPC,    RAISE,    KC_RGUI,   KC_RALT,  _______ ,      MO(_XMONAD)}
    },
    /* Numeric layer
     *                ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     * Application -- │ ⌘-` │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │  #  │
     *      window    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *    switcher    │     │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │     │
     *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                │     │  -  │  =  │  `  │  \  │  :  │     │  {  │  [  │  ]  │  }  │     │
     *                ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
     *                │     │     │     │     │     │ Backspace │     │     │     │     │     │
     *                └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
     */
    [_LOWER] = {
        {LGUI(KC_GRV), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  S(KC_3)},
        {_______,      KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______},
        {_______,      KC_MINS, KC_EQL,  KC_GRV,  KC_BSLS, KC_COLN, _______, KC_LCBR, KC_LBRC, KC_RBRC,  KC_RCBR, _______},
        {_______,      _______, _______, _______, _______, KC_BSPC, KC_BSPC, _______, _______, _______, _______, _______}
    },

    /* Symbol layer
     *                ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     *                │     │ F11 │ F12 │ F13 │ F14 │ F15 │ F16 │ F17 │ F18 │ F19 │ F20 │  #  │
     *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                │     │  !  │  @  │  #  │  $  │  %  │  ^  │  &  │  *  │  '  │  "  │     │ \
     *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤  |-- Mostly shifted version
     *                │     │  _  │  +  │  ~  │  |  │  :  │     │     │  ,  │  .  │  /  │     │ /    of lower layer
     *                ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
     *                │     │     │     │     │     │  Delete   │     │     │     │     │     │
     *                └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
     */
    [_RAISE] = {
        {_______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,     S(KC_3)},
        {_______, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6), S(KC_7), S(KC_8), KC_QUOT, S(KC_QUOT), _______},
        {_______, KC_UNDS, KC_PLUS, KC_TILD, KC_PIPE, KC_COLN, _______, _______, KC_COMM, KC_DOT,  KC_SLSH,    _______},
        {_______, _______, _______, _______, _______, KC_DEL,  KC_DEL,  _______, _______, _______, _______,    _______}
    },
    /* Directional navigation layer
     *
     *         Large movements -----/```````````````````\   /```````````````````\----- Vim-style arrow keys
     *                ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     *                │     │     │     │     │     │     │     │     │     │     │     │     │
     *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                │     │Home │PgUp │PgDn │ End │ Ins │  ←  │  ↓  │  ↑  │  →  │     │     │
     *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                │     │     │     │     │     │     │     │     │     │     │     │     │
     *                ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
     *                │     │     │     │     │     │           │     │     │     │     │     │
     *                └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
     */
    [_NAV] = {
        {___x___, S(LCTL(KC_LEFT)), S(LCTL(KC_DOWN)), S(LCTL(KC_UP)), S(LCTL(KC_RGHT)), ___x___, LCTL(KC_LEFT), LCTL(KC_DOWN), LCTL(KC_UP), LCTL(KC_RGHT), ___x___, ___x___},
        {_______, KC_HOME, KC_PGUP, KC_PGDN, KC_END,   KC_INS,       KC_LEFT,       KC_DOWN,       KC_UP,       KC_RGHT, _______, _______},
        {_______, ___x___, ___x___, ___x___, ___x___, ___x___, LALT(KC_LEFT), LALT(KC_DOWN), LALT(KC_UP), LALT(KC_RGHT), ___x___, _______},
        {___x___, _______, _______, _______, ___x___, ___x___,       ___x___,       ___x___,     _______,       _______, _______, _______}
    },

    /* Directional navigation layer
     *
     *         Large movements -----/```````````````````\   /```````````````````\----- Vim-style arrow keys
     *                ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     *                │     │     │     │     │     │     │     │     │     │     │     │     │
     *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                │     │Home │PgUp │PgDn │ End │ Ins │  ←  │  ↓  │  ↑  │  →  │     │     │
     *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                │     │     │     │     │     │     │     │     │     │     │     │     │
     *                ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
     *                │     │     │     │     │     │           │     │     │     │     │     │
     *                └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
     */
    [_IDEA] = {
        {KC_TAB        , _______,     KC_W,    KC_F,    KC_P,    KC_G   , IDE_TBP, IDE_STI, IDE_STO, IDE_STC, IDE_CON, IDE_ABP},
        {CTL_T(KC_ESC) , IDE_PRO,     IDE_VCS,    KC_S,    KC_T, IDE_IMP, IDE_DEL, IDE_CLA, IDE_FIL, IDE_REC, _______, IDE_NAV},
        {KC_LSPO       , IDE_FSC,     KC_X,       KC_C, IDE_CLH, IDE_CAH, IDE_FOR, IDE_BUI, IDE_DEC, IDE_RUC, IDE_RUN, KC_RSPC},
        { _______    ,  _______ ,  KC_LALT, KC_LGUI,   LOWER,  KC_SPC,  KC_SPC, IDE_ACT, KC_RGUI, KC_RALT, _______, _______}
    },
    /* Adjust (Lower + Raise)
     * ,-----------------------------------------------------------------------------------.
     * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_XMONAD] = {
        {_______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL },
        {_______, LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4),  AG_NORM, AG_SWAP, _______,  COLEMAK,_______, _______, _______},
        {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______},
        {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
    }


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
            break;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _XMONAD);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _XMONAD);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _XMONAD);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _XMONAD);
            }
            return false;
            break;
    }
    return true;
}
