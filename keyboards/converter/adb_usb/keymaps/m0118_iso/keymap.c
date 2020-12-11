#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_m0118_iso(
                                                    KC_EJCT,
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_NLCK, KC_PEQL, KC_PSLS, KC_PAST,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_ENT,    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    KC_LCAP, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS,            KC_P4,   KC_P5,   KC_P6,   KC_PMNS,
    KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,     KC_P1,   KC_P2,   KC_P3,
    KC_LCTL, KC_LALT, KC_LGUI,                                     KC_SPC,                             KC_LEFT, KC_RGHT, KC_DOWN,   KC_P0,            KC_PDOT, KC_PENT
    ),
};
