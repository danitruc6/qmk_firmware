

#include QMK_KEYBOARD_H
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

// Custom keycodes for layer keys
// Dual function escape with left command


enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  MACRO1,
  SNAP
};

enum {
    TD_PC,
    TD_COMI,
    TD_SLA,
};

//char wpm_str[10];

#define KC_CTLTB LCTL_T(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   KC_CTLTB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,  TD(TD_PC), TD(TD_COMI),
  //---------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT,  TD(TD_SLA), RSFT_T(KC_ENT),
  //---------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                    LALT_T(KC_LGUI), MO(1), KC_SPC,     KC_RSFT, MO(2), KC_RCTL
                                      //|--------------------------|  |--------------------------|


  ),

  [_LOWER] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_F2  ,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,       KC_7,    KC_8,       KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, LCTL(KC_A), SNAP,  KC_DEL, LCTL(KC_F), KC_HOME,                   KC_VOLU, LWIN(KC_P),  MACRO1, LWIN(KC_L),   KC_UP,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_END,           KC_VOLD,    KC_MUTE, KC_MYCM,    KC_LEFT, KC_DOWN, KC_RGHT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_LGUI, KC_TRNS, _______,    _______ , MO(3), _______
                                      //|--------------------------|  |--------------------------|
  ),

  [_RAISE] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_GRV,  KC_EXLM, KC_AT,  KC_HASH, KC_DLR, KC_PERC,                        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_F12,    KC_F1, KC_F2,    KC_F3,  KC_F4,   KC_F5,                        KC_MINS, KC_EQL, KC_LBRC,  KC_LBRC, KC_RBRC, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_F6,     KC_F7, KC_F8,    KC_F9, KC_F10,   KC_F11,                       KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_BSLS, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, MO(3), _______,    _______, _______, _______
                                      //|--------------------------|  |--------------------------|
  ),

  [_ADJUST] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,                       XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX,   KC_PWR,   XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, RGB_MOD,                       XXXXXXX,  KC_MPRV,  KC_MPLY,   KC_MNXT,  XXXXXXX,   RESET,  \
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_CAPS, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX,                       XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         _______, _______, _______,    _______, _______, _______ \
                                      //|--------------------------|  |--------------------------|
  )
};


// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for ;, twice for :
    [TD_PC] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, LSFT(KC_SCLN)),
    [TD_COMI] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, LSFT(KC_QUOT)),
    [TD_SLA] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, LSFT(KC_SLSH)),
};


#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return OLED_ROTATION_270;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer"), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Main"), false);
            break;
        case L_LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adj"), false);
            break;
    }
}


void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
    oled_write_P(PSTR("-----"), false);
    oled_write_P(PSTR("WPM: "), false);
    char wpm[6];
    itoa(get_current_wpm(), wpm, 10);
    oled_write_ln(wpm, false);
}

void render_logo_left(void) {
    static const char PROGMEM corne_logo_left[] = {
        0x99, 0x9a, 0x9b, 0x9c, 0x9d,
        0xb9, 0xba, 0xbb, 0xbc, 0xbd,
        0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0};
    oled_write_P(corne_logo_left, false);
}
void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}


bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_P(PSTR("-----"), false);
        oled_render_layer_state();
        //oled_render_keylog();
        oled_write_P(PSTR("-----"), false);
        oled_write_P(PSTR("OS   "), false);
        render_bootmagic_status(true);
        oled_write_P(PSTR("-----"), false);
        oled_write_P(PSTR(" QMK "), false);
        render_logo_left();
    } else {
        oled_render_logo();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case SNAP:
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_LSFT("s")));
        } else {

        }
        return false;
         case MACRO1:
        if (record->event.pressed) {
            SEND_STRING("Zxwe5634!");
        } else {

        }
        return false;
      break;
  }


  return true;
}
#endif // OLED_DRIVER_ENABLE
