#include "annepro2.h"
#include "qmk_ap2_led.h"
#include <print.h>
#include <stdint.h>
#ifdef ANNEPRO2_C18
#include "eeprom_w25x20cl.h"
#endif

// eeprom memory layout
typedef union {
  uint32_t raw;
  struct {
    uint8_t magic : 8;
    uint8_t layer : 8;
  };
} user_config_t;

enum my_keycodes {
  KC_AP_WIN = AP2_SAFE_RANGE,
  KC_AP_LIN,
  KC_AP_MAC
};

enum my_tapdances{
  TD_GRAVE_ESC,
  TD_MAC_WIN
};

enum my_layers {
  _WIN_LAYER,
  _MAC_LAYER,
  _CAPS_LAYER,
  _FN1_LAYER,
  _FN2_LAYER,
};

// define out default user_config
user_config_t user_config = {.magic = 0xDE, .layer = 1 << _WIN_LAYER};

// clang-format off
/*
 * Layer _WIN_LAYER
 * ,-----------------------------------------------------------------------------------------.
 * | `   |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   |
 * |-----------------------------------------------------------------------------------------+
 * | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |   \    |
 * |-----------------------------------------------------------------------------------------+
 * | Esc     |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |    Shift       |
 * |-----------------------------------------------------------------------------------------+
 * | Ctrl  |  GUI  |  Alt  |               space             |  FN1  |  FN2  |  Alt  | Ctrl  |
 * \-----------------------------------------------------------------------------------------/
 */
const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_WIN_LAYER] = KEYMAP(/* Win */
        TD(TD_GRAVE_ESC), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        LT(_CAPS_LAYER, KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        TD(TD_MAC_WIN), KC_LGUI, KC_LALT, KC_SPC, TT(_FN1_LAYER), LT(_FN2_LAYER, KC_APP), KC_RALT, KC_RCTL),
    [_MAC_LAYER] = KEYMAP(/* Mac */
        TD(TD_GRAVE_ESC), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        LT(_CAPS_LAYER, KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        TD(TD_MAC_WIN), KC_LALT, KC_LGUI, KC_SPC, TT(_FN1_LAYER), LT(_FN2_LAYER, KC_APP), KC_RALT, KC_RCTL),

    [_CAPS_LAYER] = KEYMAP(/* Hold CapsLock */
        _______, _______, _______, _______, _______, KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE, KC_AUDIO_VOL_UP, _______, _______, _______, _______, _______, KC_DELETE,
        _______, _______, _______, _______, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_WWW_BACK, KC_WWW_HOME, KC_WWW_SEARCH, KC_PSCREEN, KC_HOME, KC_END, _______,
        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_PGUP, KC_PGDN, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INSERT, KC_DELETE, _______,
        _______, _______, _______, _______, _______, _______, _______, _______),
    [_FN1_LAYER]   = KEYMAP(/* FN1 */
        _______, _______, _______, _______, _______, _______, _______, _______, KC_KP_ASTERISK, KC_NUMLOCK, KC_KP_0, KC_KP_MINUS, KC_KP_PLUS, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_KP_4, KC_KP_5, KC_KP_6, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_SLASH, KC_UP,
        _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT),
    [_FN2_LAYER]   = KEYMAP(/* FN2 */
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_AP_WIN, _______, _______, _______, _______, _______, _______, _______, KC_PSCREEN, KC_HOME, KC_END, KC_AP_LED_ON,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_AP_LIN, KC_PGUP, KC_PGDN, KC_AP_LED_OFF,
        KC_AP2_USB, KC_AP2_BT_UNPAIR, KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, _______, KC_AP_MAC, _______, _______, _______, KC_AP_LED_NEXT_INTENSITY,
        _______, _______, _______, _______, _______, _______, _______, KC_AP_LED_SPEED),
};
// clang-format on

const uint16_t keymaps_size = sizeof(keymaps);

void matrix_init_user(void) {
}

void matrix_scan_user(void) {}

layer_state_t layer_state_set_user(layer_state_t layer) { return layer; }

/*!
 * @returns false   processing for this keycode has been completed.
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef ANNEPRO2_C18
  switch (keycode) {
  case KC_AP_WIN:
    if (record->event.pressed) {
      default_layer_set(1 << _WIN_LAYER);
    }
    return false;
  case KC_AP_LIN:
    if (record->event.pressed) {
      default_layer_set(1 << _WIN_LAYER);
    }
    return false;
  case KC_AP_MAC:
    if (record->event.pressed) {
      default_layer_set(1 << _MAC_LAYER);
    }
    return false;
  case KC_AP_LED_OFF:
    if (record->event.pressed) {
      //user_config.leds_on = false;
      eeprom_write((void *)&user_config, 0, sizeof(user_config_t));
    }
    return false;
  case KC_AP_LED_ON:
    if (record->event.pressed) {
      /*
      if (user_config.leds_on) {
        //user_config.leds_profile = (user_config.leds_profile + 1) % numProfiles;
      } else {
        user_config.leds_on = true;
      }
      */
      eeprom_write((void *)&user_config, 0, sizeof(user_config_t));
    }
    return false;
  case KC_AP_LED_NEXT_PROFILE:
    if (record->event.pressed) {
      //user_config.leds_profile = (user_config.leds_profile + 1) % numProfiles;
      eeprom_write((void *)&user_config, 0, sizeof(user_config_t));
    }
    return false;
  case KC_AP_LED_NEXT_INTENSITY:
    if (record->event.pressed) {
      annepro2LedNextIntensity();
    }
    return false;
  default:
    break;
  }
#endif
  return true;
}

void keyboard_post_init_user(void) {
#ifdef ANNEPRO2_C18
  // Read the user config from EEPROM
  eeprom_read((void *)&user_config, 0, sizeof(user_config_t));

  // initialize a new eeprom
  if (user_config.magic != 0xDE) {
    user_config.magic = 0xDE;
    user_config.layer = 1 << _WIN_LAYER;
    eeprom_write((void *)&user_config, 0, sizeof(user_config_t));
  }
#endif
}


// datew0`s edits

void mac_win_switch(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 3) {
    //eeprom_read((void *)&user_config, 0, sizeof(user_config_t));
    switch (user_config.layer){
      case (1<<_WIN_LAYER):
        user_config.layer = 1 << _MAC_LAYER;
        break;
      case (1<<_MAC_LAYER):
        user_config.layer = 1 << _WIN_LAYER;
        break;
    }
    default_layer_set(user_config.layer);
    reset_tap_dance(state);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_GRAVE_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRAVE),
  [TD_MAC_WIN] = ACTION_TAP_DANCE_FN(mac_win_switch)
};