#include <stdint.h>
#include "annepro2.h"
#include "qmk_ap2_led.h"
#include "config.h"

#define _____ KC_TRNS

enum my_layers {
  _BL,
  _MACL,
  _FN1L,
  _FN2L
};
 const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [_BL] = LAYOUT(
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, ACTION_TAP_DANCE_DUAL_ROLE(KC_BSLS, _MACL),
    LT(_FN1L,KC_CAPS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_UP),
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, LT(_FN1L,KC_LEFT), LT(_FN2L,KC_DOWN), RCTL_T(KC_RGHT)
),
 [_MACL] = LAYOUT(
    _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____,
    _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, ACTION_TAP_DANCE_DUAL_ROLE(KC_BSLS, _BL),
    _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____,
    _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____,
    _____, KC_LALT, KC_LGUI, _____, _____, _____, _____, _____
)
/*
 [_FN1L] = LAYOUT(
    _____, KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, _____, _____, _____, KC_AP_LED_OFF, KC_AP_LED_ON, KC_AP_LED_NEXT_INTENSITY, KC_AP_LED_SPEED, _____, _____,
    MO(_FN2L), _____, KC_UP, _____, _____, _____, _____, _____, _____, _____, KC_PSCR, KC_HOME, KC_END, _____,
    _____, KC_LEFT, KC_DOWN, KC_RGHT, _____, _____, _____, _____, _____, _____, KC_PGUP, KC_PGDN, _____,
    _____, _____, _____, _____, _____, _____, _____, _____, _____, KC_INS, KC_DEL, _____,
    _____, _____, _____, _____, _____, MO(_FN1L), MO(_FN2L), _____
 ),
 [_FN2L] = LAYOUT(
    _____, KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, _____, _____, _____, KC_AP_LED_OFF, KC_AP_LED_ON, KC_AP_LED_NEXT_INTENSITY, KC_AP_LED_SPEED, _____, _____,
    MO(_FN2L), _____, KC_UP, _____, _____, _____, _____, _____, _____, _____, KC_PSCR, KC_HOME, KC_END, _____,
    _____, KC_LEFT, KC_DOWN, KC_RGHT, _____, _____, _____, _____, _____, _____, KC_PGUP, KC_PGDN, _____,
    _____, _____, _____, _____, _____, _____, _____, _____, _____, KC_INS, KC_DEL, _____,
    _____, _____, _____, _____, _____, MO(_FN1L), MO(_FN2L), _____
 )
 */
};
const uint16_t keymaps_size = sizeof(keymaps);


void matrix_init_user(void) {

}

void matrix_scan_user(void) {
}

// Code to run after initializing the keyboard
void keyboard_post_init_user(void) {
    // Here are two common functions that you can use. For more LED functions, refer to the file "qmk_ap2_led.h"

    // annepro2-shine disables LEDs by default. Uncomment this function to enable them at startup.
    // annepro2LedEnable();

    // Additionally, it also chooses the first LED profile by default. Refer to the "profiles" array in main.c in
    // annepro2-shine to see the order. Replace "i" with the index of your preferred profile. (i.e the RED profile is index 0)
    // annepro2LedSetProfile(i);
}

layer_state_t layer_state_set_user(layer_state_t layer) {
    return layer;
}
