#include "annepro2.h"
#include "qmk_ap2_led.h"
#include <limits.h>
#include <stdint.h>

#ifdef ANNEPRO2_C18
#include "eeprom_w25x20cl.h"
#endif

#ifdef CONSOLE_ENABLE
#include <print.h>
#endif

/*
My personal Anne Pro 2 keymap. Will be improved.
TODO List:
- DOTA2 macro keybinds
*/

typedef union {
  uint32_t raw;
  struct {
    uint8_t magic : 8;
    uint16_t writes_count : 8;
    bool isMac : 1;
  };
} user_config_t;

enum my_tapdances{
  TD_GRAVE_ESC,
  TD_SHIFT_CAPS,
  TD_MAC_WIN_FN
};

enum my_layers {
  _WIN_LAYER,
  _MAC_LAYER,
  _NAV_LAYER,
  _MEDIA_LAYER,
  _FN_LAYER,
  _HW_LAYER
};

user_config_t default_config = {.magic = 0xAF, .writes_count = 0, .isMac = false};
user_config_t user_config;

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_WIN_LAYER] = KEYMAP(/* Win */
        TD(TD_GRAVE_ESC), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
        LT(_MEDIA_LAYER, KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, LT(_HW_LAYER, KC_BSLS),
        LT(_NAV_LAYER, KC_BSPC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOT, KC_ENT,
        TD(TD_SHIFT_CAPS), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT, LT(_NAV_LAYER, KC_SPC), TD(TD_MAC_WIN_FN), KC_LEFT, KC_DOWN, KC_RIGHT),
    [_MAC_LAYER] = KEYMAP(/* Mac */
        TD(TD_GRAVE_ESC), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
        LT(_MEDIA_LAYER, KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, LT(_HW_LAYER, KC_BSLS),
        LT(_NAV_LAYER, KC_BSPC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOT, KC_ENT,
        TD(TD_SHIFT_CAPS), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_UP,
        KC_LCTL, KC_LALT, KC_LGUI, LT(_NAV_LAYER, KC_SPC), TD(TD_MAC_WIN_FN), KC_LEFT, KC_DOWN, KC_RIGHT),

    [_NAV_LAYER] = KEYMAP(/* Navigation */
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_UP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______),
    [_MEDIA_LAYER]   = KEYMAP(/* Media Control */
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE, KC_AUDIO_VOL_UP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______),
    [_FN_LAYER]   = KEYMAP(/* Functional */
        KC_PWR, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
        _______, _______, _______, KC_END, _______, _______, _______, _______, KC_INSERT, _______, KC_PSCREEN, _______, _______, _______,
        _______, _______, _______, KC_DEL, _______, _______, KC_HOME, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, _______, KC_RSFT,
        _______, _______, _______, _______, _______, KC_APP, KC_RALT, KC_RCTL),
    [_HW_LAYER]   = KEYMAP(/* Hardware Control */
        KC_AP2_USB, KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, _______, _______, _______, _______, _______, KC_AP2_BT_UNPAIR, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______),
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
  //debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  
  // At 0x0 - latest user config address
  uint32_t addr = 0;
  eeprom_read((void *)&addr, 0, sizeof(addr));

  if (!addr) {
    #ifdef CONSOLE_ENABLE
    uprintf("[ERROR] Config address reading failed, switching to defaults\n");
    #endif
    user_config = default_config;
  }
  else {
    #ifdef CONSOLE_ENABLE
    uprintf("[INFO] Reading config from: %x\n", addr);
    #endif
    eeprom_read((void *)&user_config, addr, sizeof(user_config_t));
    if (user_config.magic == 0xAF) {
      #ifdef CONSOLE_ENABLE
      uprintf("[INFO] Loaded config:\n\tisMac: %d\n\twritesCount: %u\n", user_config.isMac, user_config.writes_count);
      #endif
      if (user_config.writes_count == UINT16_MAX) {
        addr++;
        user_config.writes_count = 0;
        eeprom_write((void*)&addr,0,sizeof(addr));
      }
    }
    else {
      user_config = default_config;
      addr = 1 + rand() % 240000;
      #ifdef CONSOLE_ENABLE
      uprintf("[ERROR] Magic mismatch, switching to defaults and RAND new address: %x\n", addr);
      #endif
      eeprom_write((void*)&addr, 0, sizeof(addr));
    }
    
  }
  default_layer_set(1UL << user_config.isMac);
#endif
}

typedef enum {
  TD_NONE,
  TD_SINGLE_HOLD,
  TD_TRIPLE_TAP
} td_state_t;

static td_state_t mwfn_state;

void mwfn_finished(qk_tap_dance_state_t* state, void* user_data) {
  mwfn_state = TD_NONE;
  if(state->count == 1) {
    if(state->pressed && !state->interrupted) mwfn_state = TD_SINGLE_HOLD;
  }
  if(state->count == 3) {
    if(!state->pressed || state->interrupted) mwfn_state = TD_TRIPLE_TAP;
  }

  switch (mwfn_state) {
    case TD_SINGLE_HOLD:
      layer_on(_FN_LAYER);
      #ifdef CONSOLE_ENABLE
      uprintf("[INFO] FN layer enabled\n");
      #endif
      break;
    case TD_TRIPLE_TAP:
      user_config.isMac ^= 1;
      default_layer_set(1UL << user_config.isMac);
      #ifdef CONSOLE_ENABLE
      uprintf("[INFO] Mac/Win switched\n");
      #endif
      break;
    default:
      break;
  }
}

void mwfn_reset(qk_tap_dance_state_t* state, void* user_data) {
  switch (mwfn_state) {
    case TD_SINGLE_HOLD:
      layer_off(_FN_LAYER);
      #ifdef CONSOLE_ENABLE
      uprintf("[INFO] FN layer disabled\n");
      #endif
      break;
    case TD_TRIPLE_TAP:
      #ifdef CONSOLE_ENABLE
      uprintf("[INFO] Saving config...\n");
      #endif
      asm("nop");
      uint32_t addr = 0;
      eeprom_read(&addr, 0, sizeof(addr));
      if (addr) {
        user_config.writes_count++;
        eeprom_write((void *)&user_config, addr, sizeof(user_config_t));
      }
      #ifdef CONSOLE_ENABLE
      else uprintf("[ERROR] Reading address at 0x00 failed\n");
      #endif
      break;
    default:
      break;
  }
  mwfn_state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_GRAVE_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRAVE),
  [TD_SHIFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPSLOCK),
  [TD_MAC_WIN_FN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mwfn_finished, mwfn_reset)
};