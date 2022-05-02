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
#include "big_led.h"
#include "common/remote_kb.h"


enum layer_names {
  _MAIN,
  _FN,
  _MA
};

enum custom_keycodes {
  KC_CUST = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAIN] = LAYOUT_all(
					QK_GESC,  KC_1,		KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_GRAVE,
	KC_MPLY,		KC_TAB,  KC_Q,		KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
	KC_NO,			KC_CAPS, KC_A,  	KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_HOME,
	KC_PGUP,		KC_LSFT, MO(_MA), 	KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
    CTL_T(KC_PGDN), KC_LCTL, KC_LGUI,	KC_LALT,                   KC_SPC,             			       MO(_FN), KC_CALC, MO(_FN), KC_LEFT, KC_DOWN, KC_RGHT
  ),
  [_FN] = LAYOUT_all(
             A(KC_F4),  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______, _______,
    KC_MUTE, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, C(KC_W),
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_WREF,
    RGB_HUI, KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    RGB_SAI, RGB_VAI, _______, _______,                   _______,               		      _______, _______, _______, C(KC_PGUP), _______, C(KC_PGDN)
  ),
  [_MA] = LAYOUT_all(
             C(S(KC_ESC)), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______,   KC_F8,	 KC_F9,  KC_F10,  KC_F11, _______, _______, _______, _______, _______, _______, _______, _______, _______, C(KC_DEL),
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    C(KC_Y), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    C(KC_Z), _______, _______, _______,                   _______,                  		  _______, _______, _______, _______, _______, _______
  ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (layer_state_is(_MAIN)) {
        if (clockwise) {
			tap_code(KC_VOLU);
		} else {
			tap_code(KC_VOLD);
		}
	} else if (layer_state_is(_FN)) {
		if (clockwise) {
			tap_code(KC_MNXT);
		} else {
			tap_code(KC_MPRV);
		}
	} else if (layer_state_is(_MA)) {
		if (clockwise) {
			tap_code(KC_RBRC);
		} else {
			tap_code(KC_LBRC);
		}
	}
    return true;
}

void set_big_LED_by_layer(enum layer_names custom_layer) {
  switch (custom_layer) {
    case _MAIN:
      set_big_LED_rgb(LED_OFF, LED_OFF, LED_OFF);
      break;
    case _FN:
      set_big_LED_rgb(LED_ON, LED_OFF, LED_OFF);
      break;
    case _MA:
      set_big_LED_rgb(LED_ON, LED_ON, LED_OFF);
      break;
    default:
      break;
	}
}

bool led_update_user(led_t led_state) {    
  if (led_state.caps_lock) {
    set_big_LED_rgb(LED_OFF, LED_OFF, LED_ON);
	} else {
    set_big_LED_by_layer(get_highest_layer(layer_state));
	}  
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case _MAIN:
      set_big_LED_rgb(LED_OFF, LED_OFF, LED_OFF);
      break;
    case _FN:
      set_big_LED_rgb(LED_ON, LED_OFF, LED_OFF);
      break;
    case _MA:
      set_big_LED_rgb(LED_ON, LED_ON, LED_OFF);
      break;
    default:
      break;
	}
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Send keystrokes to host keyboard, if connected (see readme)
  process_record_remote_kb(keycode, record);
  switch(keycode) {
    case KC_CUST: //custom macro
      if (record->event.pressed) {
      }
    break;

    case RM_1: //remote macro 1
      if (record->event.pressed) {
      }
    break;

    case RM_2: //remote macro 2
      if (record->event.pressed) {
      }
    break;

    case RM_3: //remote macro 3
      if (record->event.pressed) {
      }
    break;

    case RM_4: //remote macro 4
      if (record->event.pressed) {
      }
    break;

  }
return true;
}


void matrix_init_user(void) {
  // Initialize remote keyboard, if connected (see readme)
  matrix_init_remote_kb();
}

void matrix_scan_user(void) {
  // Scan and parse keystrokes from remote keyboard, if connected (see readme)
  matrix_scan_remote_kb();
}