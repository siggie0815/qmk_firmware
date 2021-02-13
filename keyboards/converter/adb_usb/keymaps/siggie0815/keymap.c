#include QMK_KEYBOARD_H

#define DE_AT   ALGR(KC_Q)
#define DE_BSLS ALGR(KC_MINS)
#define DE_EURO ALGR(KC_E)
#define DE_PIPE ALGR(KC_NUBS)
#define DE_TILD ALGR(KC_RBRC)
#define DE_LCBR ALGR(KC_7)
#define DE_RCBR ALGR(KC_0)
#define DE_LBRC ALGR(KC_8)
#define DE_RBRC ALGR(KC_9)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // AEK - L1
    [0] = LAYOUT_ext_all(
    KC_ESC, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,             KC_PSCR,KC_SLCK,KC_PAUS,                            MO(1),
    KC_NUBS,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC,    KC_INS, KC_HOME,KC_PGUP,    KC_NLCK,KC_PEQL,KC_PSLS,KC_PAST,
    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,    KC_DEL, KC_END, KC_PGDN,    KC_P7,  KC_P8,  KC_P9,  KC_PMNS,
    KC_LCAP,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,        KC_ENT,                                 KC_P4,  KC_P5,  KC_P6,  KC_PPLS,
    KC_LSFT,XXXXXXX,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,        KC_RSFT,            KC_UP,              KC_P1,  KC_P2,  KC_P3,
    KC_LCTL,KC_LALT,LT(1,KC_LGUI),                  KC_SPC,                                         KC_RALT,KC_RCTL,    KC_LEFT,KC_DOWN,KC_RGHT,    KC_P0,          KC_PDOT,KC_PENT
    ),
    // AEK - L2
    [1] = LAYOUT_ext_all(
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,              KC_VOLD,KC_VOLU,KC_MUTE,                            KC_TRNS,
    KC_GRV, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,      KC_NO,  KC_NO,  KC_NO,      KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,      KC_NO,  KC_NO,  KC_NO,      KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_TRNS,KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,          KC_NO,                                  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_TRNS,XXXXXXX,KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,          KC_TRNS,            KC_PGUP,            TO(0),  TO(2),  TO(4),
    KC_TRNS,KC_TRNS,KC_TRNS,                        KC_NO,                                          KC_TRNS,KC_TRNS,    KC_HOME,KC_PGDN,KC_END,     KC_NO,          KC_NO,  KC_NO
    ),

    // AEK II ISO - L1
    [2] = LAYOUT_ext_all(
    KC_ESC, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,             KC_PSCR,KC_SLCK,KC_PAUS,                            MO(3),
    KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC,    KC_INS, KC_HOME,KC_PGUP,    KC_NLCK,KC_PEQL,KC_PSLS,KC_PAST,
    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,    KC_DEL, KC_END, KC_PGDN,    KC_P7,  KC_P8,  KC_P9,  KC_PMNS,
    KC_LCAP,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,        KC_ENT,                                 KC_P4,  KC_P5,  KC_P6,  KC_PPLS,
    KC_LSFT,KC_NUBS,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,        KC_RSFT,            KC_UP,              KC_P1,  KC_P2,  KC_P3,
    KC_LCTL,KC_LALT,LT(3,KC_LGUI),                  KC_SPC,                                         KC_RALT,KC_RCTL,    KC_LEFT,KC_DOWN,KC_RGHT,    KC_P0,          KC_PDOT,KC_PENT
    ),
    // AEK II ISO - L2
    [3] = LAYOUT_ext_all(
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,              KC_VOLD,KC_VOLU,KC_MUTE,                            KC_TRNS,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,      KC_NO,  KC_NO,  KC_NO,      KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,      KC_NO,  KC_NO,  KC_NO,      KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,          KC_NO,                                  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,          KC_NO,              KC_PGUP,            TO(0),  TO(2),  TO(4),
    KC_NO,  KC_NO,  KC_NO,                          KC_NO,                                          KC_NO,  KC_NO,      KC_HOME,KC_PGDN,KC_END,     KC_NO,          KC_NO,  KC_NO
    ),

    // M0118D - L1
    [4] = LAYOUT_ext_all(
    KC_ESC, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,            XXXXXXX,XXXXXXX,XXXXXXX,                              MO(5),
    XXXXXXX,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC,    XXXXXXX,XXXXXXX,XXXXXXX,    KC_DEL,  KC_PEQL,KC_PSLS, KC_PAST,
    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,    XXXXXXX,XXXXXXX,XXXXXXX,    KC_P7,   KC_P8,  KC_P9,   KC_PMNS,
    KC_LCAP,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,        KC_ENT,                                 KC_P4,   KC_P5,  KC_P6,   KC_PPLS,
    KC_LSFT,KC_NUBS,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,        XXXXXXX,            KC_UP,              KC_P1,   KC_P2,  KC_P3,
    KC_LCTL,KC_LALT,LT(5,KC_LGUI),                  KC_SPC,                                         XXXXXXX,XXXXXXX,    KC_LEFT,KC_RGHT,KC_DOWN,    KC_P0,           KC_PDOT, KC_PENT
    ),
    // M0118D - L2
    [5] = LAYOUT_ext_all(
    KC_GRV, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,            XXXXXXX,XXXXXXX,XXXXXXX,                            KC_TRNS,
    XXXXXXX,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_NO,      XXXXXXX,XXXXXXX,XXXXXXX,    KC_NLCK,KC_VOLD,KC_VOLU,KC_MUTE,
    KC_NO,  DE_AT,  KC_NO,  DE_EURO,KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  DE_LBRC,DE_RBRC,DE_TILD,DE_BSLS,    XXXXXXX,XXXXXXX,XXXXXXX,    KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  DE_LCBR,DE_RCBR,        KC_NO,                                  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_RSFT,DE_PIPE,KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,          XXXXXXX,            KC_PGUP,            TO(0),  TO(2),  TO(4),
    KC_RCTL,KC_RALT,KC_TRNS,                        KC_NO,                                          XXXXXXX,XXXXXXX,    KC_HOME,KC_END, KC_PGDN,    KC_NO,          KC_NO,  KC_NO
    ),
};
