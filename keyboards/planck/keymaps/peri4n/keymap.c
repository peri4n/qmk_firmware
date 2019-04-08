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
    _NAV1,
    _NAV2
};

enum planck_keycodes {
    COLEMAK = SAFE_RANGE,
    LOWER,
    RAISE
};

// Key aliases for legibility
#define ___x___ KC_NO
#define _______ KC_TRNS

#define A(x) LALT(x)
#define C(x) LCTL(x)
#define CA(x) C(A(x))
#define X(x) LGUI(x)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base layer (Colemak)
     *                ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     *                │  ⇥  │  Q  │  W  │  F  │  P  │  G  │  J  │  L  │  U  │  Y  │  ;  │  '  │
     *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     * Tap for Esc -- │  ⌃  │  A  │  R  │  S  │  T  │  D  │  H  │  N  │  E  │  I  │O Nav│  ⌃  │ -- Tap for Enter
     *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *   Tap for ( -- │  ⇧  │  Z  │  X  │  C  │  V  │  B  │  K  │  M  │  ,  │  .  │  /  │  ⇧  │ -- Tap for )
     *                ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
     *   Tap for [ -- │ Nav1│     │  ⌥  │  ⌘  │  ↓  │   Space   │  ↑  │  ⌘  │  ⌥  │     │ Nav2│ -- Tap for ]
     *                └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
     *                        /                                                     /
     *   Tap for ] [ --------'-----------------------------------------------------'
     */
    [_COLEMAK] = {
        {KC_TAB        , KC_Q,     KC_W,    KC_F,    KC_P,   KC_G,    KC_J,     KC_L,       KC_U,      KC_Y,  KC_SCLN,        KC_QUOT},
        {CTL_T(KC_ESC) , KC_A,     KC_R,    KC_S,    KC_T,   KC_D,    KC_H,     KC_N,       KC_E,      KC_I,     KC_O,  CTL_T(KC_ENT)},
        {KC_LSPO       , KC_Z,     KC_X,    KC_C,    KC_V,   KC_B,    KC_K,     KC_M,    KC_COMM,    KC_DOT,  KC_SLSH,        KC_RSPC},
        {MO(_NAV1)     , _______,  KC_LGUI, KC_LALT, LOWER,  KC_SPC,  KC_SPC,   RAISE,   KC_RALT,   KC_RGUI,  _______,      MO(_NAV2)}
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
    [_NAV1] = {
        {___x___, ___x___, ___x___, ___x___, ___x___, ___x___     ,    C(KC_F12), C(KC_LEFT), C(KC_DOWN), C(KC_UP), C(KC_RGHT), C(S(KC_F12))},
        {_______, X(KC_1), X(KC_2), X(KC_3), X(KC_4), ___x___     ,   C(S(KC_A)),    KC_LEFT,    KC_DOWN,    KC_UP,    KC_RGHT,    A(KC_ENT)},
        {_______, ___x___, ___x___, ___x___, ___x___, ___x___     , C(S(KC_GRV)), A(KC_LEFT), A(KC_DOWN), A(KC_UP), A(KC_RGHT),    A(KC_INS)},
        {_______, _______, _______, _______, ___x___, C(S(KC_SPC)), C(S(KC_SPC)), A(KC_HOME),    _______,  _______,    _______,      _______}
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
    [_NAV2] = {
        {_______,       KC_HOME,       KC_PGDN,     KC_PGUP,        KC_END, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___ },
        {___x___, C(S(KC_LEFT)), C(S(KC_DOWN)), C(S(KC_UP)), C(S(KC_RGHT)), ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___ },
        {_______, C(A(KC_LEFT)), C(A(KC_DOWN)), C(A(KC_UP)), C(A(KC_RGHT)), ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___ },
        {_______,       _______,       _______,     _______,       ___x___, ___x___, ___x___, ___x___, _______, _______, _______, _______}
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
                update_tri_layer(_LOWER, _RAISE, _NAV1);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _NAV1);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _NAV1);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _NAV1);
            }
            return false;
            break;
    }
    return true;
}
