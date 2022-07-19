/* Copy*******************************right 2021 Simon Arlott
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
#include QMK_KEYBOARD_H

enum layer_names {
    L_NUM,
    L_FN,
    L_RGB
};

/**
Base Layer                               Function Layer 1                         Function Layer 2
             .-----.                                  .-----.                                  .-----.
             | USB |                                  | USB |                                  | USB |
,-------------------------------.        ,-------------------------------.        ,-------------------------------.
| Esc   | Calc  | Fn 1  | Fn 2  |        |       |       |▒▒▒▒▒▒▒|       |        |       |       |       |▒▒▒▒▒▒▒|
|       |       |       |       |        |       |       |▒▒▒▒▒▒▒|       |        |       |       |       |▒▒▒▒▒▒▒|
|-------+-------+-------+-------|        |-------+-------+-------+-------|        |-------+-------+-------+-------|
| Num   | /     | *     | -     |        |       |       |       |       |        |       |       |       |       |
| Lock  |       |       |       |        |       |       |       |       |        |       |       |       |       |
|-------+-------+-------+-------|        |-------+-------+-------+-------|        |-------+-------+-------+-------|
| 7     | 8     | 9     | +     |        |       | BL    |       | BL    |        |       |Mode   |       |Bright |
| Home  | Up    | PgUp  |       |        |       | On    |       | Inc   |        |       |Forward|       |Inc    |
|-------+-------+-------+-------|        |-------+-------+-------+-------|        |-------+-------+-------+-------|
| 4     | 5     | 6     | +     |        |       | BL    |       | BL    |        |       |Toggle |       |Bright |
| Left  |       | Right |       |        |       | Togg  |       | Inc   |        |       |On/Off |       |Inc    |
|-------+-------+-------+-------|        |-------+-------+-------+-------|        |-------+-------+-------+-------|
| 1     | 2     | 3     | Ent   |        |       | BL    |       | BL    |        |       |Mode   |       |Bright |
| End   | Down  | PgDn  |       |        |       | Off   |       | Dec   |        |       |Back   |       |Dec    |
|-------+-------+-------+-------|        |-------+-------+-------+-------|        |-------+-------+-------+-------|
| 0     | 0     | .     | Ent   |        | BL    |       |       | BL    |        |Mode   |       |       |Bright |
| Ins   | Ins   | Del   |       |        | Breath|       |       | Dec   |        |Rainbow|       |       |Dec    |
`-------------------------------'        `-------------------------------'        `-------------------------------'
**/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_NUM] = LAYOUT_ortho_6x4(
        KC_ESC,  _______, TO(L_FN), MO(L_RGB),
        KC_NLCK, KC_PSLS, KC_PAST, KC_BSPC,
        KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,   KC_TAB,
        KC_P0,   KC_P0,   KC_PDOT, KC_PENT
    ),
    [L_FN] = LAYOUT_ortho_6x4(
        _______, TO(L_NUM), TO(L_FN), MO(L_RGB),
        KC_F10,   KC_F11,   KC_F12,   _______,
        KC_F7,   KC_F8,   KC_F9,   _______,
        KC_F4,   KC_F5,   KC_F6,   _______,
        KC_F1,   KC_F2,   KC_F3,   _______,
        _______, _______, _______, _______
    ),
    [L_RGB] = LAYOUT_ortho_6x4(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, RGB_MOD, _______, RGB_VAI,
        _______, RGB_TOG, _______, RGB_VAI,
        _______, RGB_RMOD,_______, RGB_VAD,
        RGB_M_R, _______, RESET  , RGB_VAD
    )
};


void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // Enables RGB, without saving settings
  rgblight_sethsv_noeeprom(0,   0, 100);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case L_NUM:
            rgblight_sethsv(0,   0, rgblight_get_val());
            break;
        case L_FN:
            rgblight_sethsv(191, 255, rgblight_get_val());
            break;
        default: // for any other layers, or the default layer
            rgblight_sethsv (170, 255, rgblight_get_val());
            break;
    }
  return state;
}

//ORIGINAL
// const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//     [L_NUM] = LAYOUT_ortho_6x4(
//         KC_ESC,  KC_CALC, MO(L_BL),MO(L_RGB),
//         KC_NLCK, KC_PSLS, KC_PAST, KC_BSPC,
//         KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
//         KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
//         KC_P1,   KC_P2,   KC_P3,   KC_TAB,
//         KC_P0,   KC_P0,   KC_PDOT, KC_PENT
//     ),
//     [L_BL] = LAYOUT_ortho_6x4(
//         _______, _______, _______, _______,
//         _______, _______, _______, _______,
//         _______, BL_ON,   _______, BL_INC,
//         _______, BL_TOGG, _______, BL_INC,
//         _______, BL_OFF,  _______, BL_DEC,
//         BL_BRTG, _______, _______, BL_DEC
//     ),
//     [L_RGB] = LAYOUT_ortho_6x4(
//         _______, _______, _______, _______,
//         _______, _______, _______, _______,
//         _______, RGB_MOD, _______, RGB_VAI,
//         _______, RGB_TOG, _______, RGB_VAI,
//         _______, RGB_RMOD,_______, RGB_VAD,
//         RGB_M_R, _______, RESET  , RGB_VAD
//     )
// };
