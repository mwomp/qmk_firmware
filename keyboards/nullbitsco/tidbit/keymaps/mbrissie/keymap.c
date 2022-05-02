/* Copyright 2021 Jay Greco
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
#include "common/remote_kb.h"


enum layers {
    _BASE = 0,
    _FUNC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
								KC_CALC, KC_PAST, KC_PSLS, 
    KC_VOLD, KC_VOLU, 	KC_P7, KC_P8,   KC_P9,   KC_MINS, 
    ___,	___, 		KC_P4, KC_P5,   KC_P6,   KC_PPLS, 
    ___,	___,		KC_P1, KC_P2,   KC_P3,   KC_PENT, 
    ___,	___,		KC_P0, LT(_FUNC, KC_DEL),   KC_PDOT, KC_PENT
    ),

    [_FUNC] = LAYOUT(
                   RGB_TOG, ___, ___, 
    ___, ___, ___, ___, ___, ___, 
    ___, ___, ___, ___, ___, ___, 
    ___, ___, ___, ___, ___, ___, 
    ___, ___, ___, ___, ___, ___  
    ),
};