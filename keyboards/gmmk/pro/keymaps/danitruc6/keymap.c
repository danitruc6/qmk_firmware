/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

// Two layers:
 // - _MAIN - normal operation
 // - _PROG - mode in which functionality assignment may be modified
enum layers {
     _MAIN,
     _PROG,
};

/*

enum custom_keycodes {
    ENC_TOGG = SAFE_RANGE,
};

#define NUM_ENC_MODES 3
enum encoder_modes {
    VOLUME,
    SCROLL,
    ZOOM,
};

static uint8_t encoder_mode = VOLUME;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ENC_TOGG:
      if (record->event.pressed) {
	// Go to the next encoder mode, looping around to the start.
	encoder_mode = (encoder_mode + 1) % NUM_ENC_MODES;
      }
      break;
    default:
      break;
  }
  return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { // First encoder
    switch(encoder_mode) {
    case VOLUME:
	if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
	break;
    case SCROLL:
	if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
	break;
    case ZOOM:
	if (clockwise) {
            tap_code(KC_WH_R);  // CTRL+NumpadPlus
        } else {
            tap_code(KC_WH_L);   // CTRL+NumpadMinus
        }
	break;
    default:
      break;
    }
  }
}

*/

//Change the functionality of the encoder based on a CTL Key press
void encoder_update_user(uint8_t index, bool clockwise) {
    if (get_mods() & MOD_MASK_CTRL) {  // If a CTRL is being held
        uint8_t mod_state = get_mods();// Store which mods are held
        del_mods(MOD_MASK_CTRL);       // Ignore all CTRL keys
        if (clockwise) {
            tap_code(KC_WH_D);         // Scroll Up on clockwise turn
        } else {
            tap_code(KC_WH_U);         // Scroll Down on counter-clockwise
        }
        set_mods(mod_state);           // Add back CTRL key(s)
    } else {                     // If no CTRL is held
        if (clockwise) {
            tap_code(KC_VOLU);   // Scroll Up/Down on clockwise turn
        } else {
            tap_code(KC_VOLD);   // VOLUMEDOWN on counterclockwise
        }
    }
}

/*

// encFn - describes a particular encoder functionality:
 //- string    - string desc. of the functionality to display on OLED
 //- clockwise - 16-bit tap code for clockwise (i.e., can be modded)
 //- countercw - 16-bit tap code for counter clockwise
 //- press     - 16-bit tap code for press

struct encFn {
   const char     *string;
   const uint16_t  clockwise;
   const uint16_t  countercw;
   const uint16_t  press;
};



static const char my_encFnS0[] PROGMEM = "Vol Up/Down/Mute\n";
//static const char my_encFnS1[] PROGMEM = "Zoom In/Out/Reset\n";
//static const char my_encFnS2[] PROGMEM = "Page Up/Down\n";
static const char my_encFnS1[] PROGMEM = "Scroll Up/Down\n";
static const char my_encFnS2[] PROGMEM = "Scroll Left/Right\n";
//static const char my_encFnS5[] PROGMEM = "F20/F21/F22\n";
//static const char my_encFnS6[] PROGMEM = "Track Nxt/Prv/Pause\n";
// static const char my_encFnS7[] PROGMEM = "App Next/Prev/All\n";


// my_Fn - array of functionality options for encoders
static struct encFn my_Fn[] = {
  { my_encFnS0, KC_VOLU, KC_VOLD, KC_MUTE }, // 0
  { my_encFnS1, KC_WH_D, KC_WH_U, KC_HOME }, // 1
  { my_encFnS2, KC_WH_R, KC_WH_L, KC_HOME }, // 2
  //{ my_encFnS3, LGUI(KC_EQUAL), LGUI(KC_MINUS), LGUI(KC_0) }, // 3
  //{ my_encFnS4, KC_PGDOWN, KC_PGUP, KC_HOME }, // 4
  //{ my_encFnS5, KC_F20, KC_F21, KC_F22 }, // 5
  //{ my_encFnS6, KC_MFFD, KC_MRWD, KC_MPLY }, // 6
  // { my_encFnS7, LGUI(KC_TAB), LGUI(S(KC_TAB)), LCTL(KC_UP) }, // 7
};
static uint16_t my_FnMax = (sizeof(my_Fn) / sizeof(struct encFn)) - 1;



// array holding current encoder functionality assignments
static int my_curEncFn[] = { 0, 1, 2 };

// Add keycodes for the encoder's presses:
enum my_keycodes {
  MY_S0 = SAFE_RANGE
};


enum layers {
     _MAIN,
     _PROG,
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MY_S0:
      if (record->event.pressed) {
        tap_code16(my_Fn[my_curEncFn[0]].press);
      }
      break;
    default:
      break;
  }
  return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index > 2) return;

  switch (get_highest_layer(layer_state)) {
    case _MAIN:
      if (clockwise) {
        tap_code16(my_Fn[my_curEncFn[index]].clockwise);
      } else {
        tap_code16(my_Fn[my_curEncFn[index]].countercw);
      }
      break;
    case _PROG:
      if (clockwise) {
        if (my_curEncFn[index] < (my_FnMax)) {
          my_curEncFn[index]++;
        } else {
          my_curEncFn[index] = 0;
        }
      } else {
        if (my_curEncFn[index] > 0) {
          my_curEncFn[index]--;
        } else {
          my_curEncFn[index] = my_FnMax;
        }
      }
      break;
    default:
      break;
  }

}

*/





const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    [_MAIN] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_HOME,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_MAIL,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_PROG),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_PROG] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,            _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),


};

/*
void encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
}

*/
//Adding functionalities to the rotatory encoder when KC_RALT is pressed
//Function 1: up/down volumen
//fucntion 2: scroll up/down
