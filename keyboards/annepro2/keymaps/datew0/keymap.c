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

/*
enum my_keycodes {
  //= AP2_SAFE_RANGE,
};
*/

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

user_config_t user_config;

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_WIN_LAYER] = KEYMAP(/* Win */
        TD(TD_GRAVE_ESC), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        LT(_CAPS_LAYER, KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, TT(_FN1_LAYER), LT(_FN2_LAYER, KC_APP), KC_DOWN, TD(TD_MAC_WIN)),
    [_MAC_LAYER] = KEYMAP(/* Mac */
        TD(TD_GRAVE_ESC), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        LT(_CAPS_LAYER, KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, TT(_FN1_LAYER), LT(_FN2_LAYER, KC_APP), KC_RALT, TD(TD_MAC_WIN)),

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
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCREEN, KC_HOME, KC_END, KC_AP_LED_ON,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_PGDN, KC_AP_LED_OFF,
        KC_AP2_USB, KC_AP2_BT_UNPAIR, KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, _______, _______, _______, _______, _______, KC_AP_LED_NEXT_INTENSITY,
        _______, _______, _______, _______, _______, _______, _______, KC_AP_LED_SPEED),
};

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
  default:
    break;
  }
#endif
  return true;
}

void keyboard_post_init_user(void) {
#ifdef ANNEPRO2_C18
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;

  // Read the user config from EEPROM
  eeprom_read((void *)&user_config, 0, sizeof(user_config_t));

  // initialize a new eeprom
  if (user_config.magic != 0xDE) {
    user_config.magic = 0xDE;
    user_config.layer = 1 << _WIN_LAYER;
    eeprom_write((void *)&user_config, 0, sizeof(user_config_t));
  }
  uprintf("Config read from EEPROM:\nLayer: %u\n", user_config.layer);
  default_layer_set(1UL << user_config.layer);
#endif
}


// datew0`s edits

void mac_win_switch(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 3) {
    //eeprom_read((void *)&user_config, 0, sizeof(user_config_t));
    uprintf("Current state:\nLayer: %u\n", user_config.layer);
    switch (user_config.layer){
      case (_WIN_LAYER):
        uprintf("Trying switch to MAC\n");
        user_config.layer = _MAC_LAYER;
        break;
      case (_MAC_LAYER):
        uprintf("Trying switch to WIN\n");
        user_config.layer = _WIN_LAYER;
        break;
      default:
        break;
    }
    default_layer_set(1UL << user_config.layer);
    eeprom_write((void *)&user_config, 0, sizeof(user_config_t));
    reset_tap_dance(state);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_GRAVE_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRAVE),
  [TD_MAC_WIN] = ACTION_TAP_DANCE_FN(mac_win_switch)
};