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
    _ADJUST
};

enum planck_keycodes {
    COLEMAK = SAFE_RANGE,
    LOWER,
    RAISE,
    BACKLIT,
};

// Key aliases for legibility
#define ___x___ KC_NO
#define _______ KC_TRNS

// Dashes
#define KC_NDSH LALT(KC_MINS)
#define KC_MDSH S(LALT(KC_MINS))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base layer (Colemak)
     *                ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     *                │  ⇥  │  Q  │  W  │  F  │  P  │  G  │  J  │  L  │  U  │  Y  │  ;  │  '  │
     *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     * Tap for Esc -- │  ⌃  │  A  │  R  │  S  │  T  │  D  │  H  │  N  │  E  │  I  │O Nav│  ⌃  │ -- Tap for Enter
     *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *   Tap for ( -- │  ⇧  │  Z  │  X  │  C  │  V  │  B  │  K  │  M  │  ,  │  .  │  /  │  ⇧  │ -- Tap for )
     *                ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
     *   Tap for [ -- │ GUI │Hyper│  ⌥  │  ⌘  │  ↓  │   Space   │  ↑  │  ⌘  │  ⌥  │Hyper│ GUI │ -- Tap for ]
     *                └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
     *                        /                                                     /
     *   Tap for ] [ --------'-----------------------------------------------------'
     */
    [_COLEMAK] = {
        {KC_TAB        , KC_Q,     KC_W,    KC_F,    KC_P,    KC_G,    KC_J,     KC_L,    KC_U,      KC_Y,      KC_SCLN,        KC_QUOT},
        {CTL_T(KC_ESC) , KC_A,     KC_R,    KC_S,    KC_T,    KC_D,    KC_H,     KC_N,    KC_E,      KC_I,      LT(_NAV, KC_O), CTL_T(KC_ENT)},
        {KC_LSPO       , KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,    KC_K,     KC_M,    KC_COMM,   KC_DOT,    KC_SLSH,        KC_RSPC},
        {KC_LBRC       , KC_RBRC,  KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,   RAISE,   KC_RGUI,   KC_RALT,   KC_LBRC,        KC_RBRC}
    },
    /* Numeric layer
     *                ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     * Application -- │ ⌘-` │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │  #  │
     *      window    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *    switcher    │     │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │     │
     *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                │     │  -  │  =  │  `  │  \  │  :  │ndash│mdash│  ,  │  .  │  /  │     │
     *                ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
     *                │     │     │     │     │     │ Backspace │     │     │     │     │     │
     *                └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
     */
    [_LOWER] = {
        {LGUI(KC_GRV), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  S(KC_3)},
        {_______,      KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______},
        {_______,      KC_MINS, KC_EQL,  KC_GRV,  KC_BSLS, KC_COLN, KC_NDSH, KC_MDSH, KC_COMM, KC_DOT,  KC_SLSH, _______},
        {_______,      _______, _______, _______, _______, KC_BSPC, KC_BSPC, _______, _______, _______, _______, _______}
    },

    /* Symbol layer
     *                ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     *                │     │ F11 │ F12 │ F13 │ F14 │ F15 │ F16 │ F17 │ F18 │ F19 │ F20 │  #  │
     *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                │     │  !  │  @  │  #  │  $  │  %  │  ^  │  &  │  *  │  '  │  "  │     │ \
     *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤  |-- Mostly shifted version
     *                │     │  _  │  +  │  ~  │  |  │  :  │ndash│mdash│  ,  │  .  │  /  │     │ /    of lower layer
     *                ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
     *                │     │     │     │     │     │  Delete   │     │     │     │     │     │
     *                └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
     */
    [_RAISE] = {
        {_______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,     S(KC_3)},
        {_______, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6), S(KC_7), S(KC_8), KC_QUOT, S(KC_QUOT), _______},
        {_______, KC_UNDS, KC_PLUS, KC_TILD, KC_PIPE, KC_COLN, KC_NDSH, KC_MDSH, KC_COMM, KC_DOT,  KC_SLSH,    _______},
        {_______, _______, _______, _______, _______, KC_DEL,  KC_DEL,  _______, _______, _______, _______,    _______}
    },
    /* Directional navigation layer
     *
     *         Large movements -----/```````````````````\   /```````````````````\----- Vim-style arrow keys
     *                ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     *                │     │     │     │     │     │     │     │     │     │     │     │     │
     *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                │     │     │Home │PgUp │PgDn │ End │  ←  │  ↓  │  ↑  │  →  │     │     │
     *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                │     │     │     │     │     │     │     │     │     │     │     │     │
     *                ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
     *                │     │     │     │     │     │           │     │     │     │     │     │
     *                └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
     */
    [_NAV] = {
        {___x___, ___x___, ___x___, ___x___, ___x___, ___x___, LCTL(KC_LEFT), LCTL(KC_DOWN), LCTL(KC_UP), LCTL(KC_RGHT), ___x___, ___x___},
        {_______, ___x___, KC_HOME, KC_PGUP, KC_PGDN, KC_END,        KC_LEFT,       KC_DOWN,       KC_UP,       KC_RGHT, _______, _______},
        {_______, ___x___, ___x___, ___x___, ___x___, ___x___, LALT(KC_LEFT), LALT(KC_DOWN), LALT(KC_UP), LALT(KC_RGHT), ___x___, _______},
        {___x___, _______, _______, _______, ___x___, ___x___,       ___x___,       ___x___,     _______,       _______, _______, _______}
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
    [_ADJUST] = {
        {_______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL },
        {_______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______,  COLEMAK,_______, _______, _______},
        {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______},
        {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
    }


};

#ifdef AUDIO_ENABLE
float plover_song[][2]     = SONG(PLOVER_SOUND);
float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

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
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case BACKLIT:
            if (record->event.pressed) {
                register_code(KC_RSFT);
#ifdef BACKLIGHT_ENABLE
                backlight_step();
#endif
            } else {
                unregister_code(KC_RSFT);
            }
            return false;
            break;
    }
    return true;
}
