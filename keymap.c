#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern uint8_t is_master;

enum layer_number {
  _DVORAK = 0,
  _QWERTY,
  _LOWER,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* ----- DVORAK 
*
*  ,-----------------------------------------.                    ,-----------------------------------------.
* |  -_  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  +=  |
* |------+------+------+------+------+------|                    |------+------+------+------+------+------|
* | Tab  |  /?  |   ,  |   .  |   P  |   Y  |                    |   F  |   G  |   C  |   R  |   L  |  '"  |
* |------+------+------+------+------+------|                    |------+------+------+------+------+------|
* | ESC  |   A  |   O  |   E  |   U  |   I  |-------.    ,-------|   D  |   H  |   T  |   N  |   S  |  [{  |
* |------+------+------+------+------+------|LOWER  |    | ENTER |------+------+------+------+------+------|
* |LShift|  ;:  |   Q  |   J  |   K  |   X  |-------|    |-------|   B  |   M  |   W  |   V  |   Z  |  ALT |
* `-----------------------------------------/       /     \      \-----------------------------------------'
*                   |QWERTY|  UP  | DOWN | /Space  /       \BKSPS \  | LEFT |RIGHT | CTRL |
*                   |      |      |      |/       /         \      \ |      |      |      |
*                   `----------------------------'           '------''--------------------'
*/

[_DVORAK] = LAYOUT( \
    KC_MINS,    KC_1,       KC_2,    KC_3,   KC_4,  KC_5,                              KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_EQUAL, \
    KC_TAB,     KC_SLSH,    KC_COMM, KC_DOT, KC_P,  KC_Y,                              KC_F,   KC_G,   KC_C,   KC_R,   KC_L,   KC_QUOT, \
    KC_ESC,     KC_A,       KC_O,    KC_E,   KC_U,  KC_I,                              KC_D,   KC_H,   KC_T,   KC_N,   KC_S,   KC_LBRC, \
    KC_LSFT,    KC_SCLN,    KC_Q,    KC_J,   KC_K,  KC_X,   MO(_LOWER),     KC_ENT,    KC_B,   KC_M,   KC_W,   KC_V,   KC_Z,   KC_ROPT, \

                                DF(_QWERTY),  KC_UP,  KC_DOWN,   KC_SPC,     KC_BSPC,   KC_LEFT,  KC_RIGHT,   KC_LCTRL \
), 


/* SPECIAL KEYS = _SPCKYS = LOWER
 * ,------+------+------+------+------+------.                    ,------+------+------+------+------+------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |-----------------------------------------|                    |-----------------------------------------|
 * | DEL  | MPRV | MNXT |V DWN | V UP | PLAY |                    |   {  |  [   |   (  |   +  |   %  |  ?   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |  _   |   !  |   &  |   ;  |   "  |-------.    ,-------| LEFT | DOWN |  UP  | RIGHT|   =  |  \   |
 * |------+------+------+------+------+------|       |    | ENTER |------+------+------+------+------+------|
 * | SHIFT|  ~   |   `  |   |  |   :  |   '  |-------|    |-------|   }  |   ]  |   )  |   -  |   /  |   *  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LCTRL| LCOMM| LOPT | /Space  /       \BKSPC \  | COPY | PSTE | UNDO |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
 
[_LOWER] = LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,       KC_F5,       KC_F6,                        KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
  KC_DEL,  KC_MRWD, KC_MFFD, KC__VOLDOWN, KC__VOLUP,   KC_MPLY,                      KC_LCBR, KC_LBRC, KC_LPRN, KC_PLUS, KC_PERC, KC_QUES, \
  KC_ESC,  KC_UNDS, KC_EXLM, KC_AMPR,     KC_SCLN,     KC_DQUO,                      KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_EQL,  KC_BSLS, \
  KC_LSFT, KC_TILD, KC_GRV,  KC_PIPE,     KC_COLN,     KC_QUOT, _______,    KC_ENT,  KC_RCBR, KC_RBRC, KC_RPRN, KC_MINS, KC_SLSH, KC_ASTR, \
                              KC_LCTRL,   KC_LCMD,     KC_LOPT, KC_SPC,     KC_BSPC, KC_COPY,  KC_PSTE, KC_UNDO \
),


///* QWERTY 
// 
// * ,-----------------------------------------.                    ,-----------------------------------------.
// * |  -_  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  +=  |
// * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
// * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  '"  |
// * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
// * | ESC  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  [{  |
// * |------+------+------+------+------+------| LOWER |    | ENTER |------+------+------+------+------+------|
// * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  | CMD  | KC_LGUI
// * `-----------------------------------------/       /     \      \-----------------------------------------'
// *                   |DVORAK|  UP  | DOWN | /Space  /       \BKSPC \  | LEFT | RIGHT| CTRL |
// *                   |      |      |      |/       /         \      \ |      |      |      |
// *                   `----------------------------'           '------''--------------------'
// */

[_QWERTY] = LAYOUT( \
  KC_MINS,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT, \
  KC_ESC,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_LBRC, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, MO(_LOWER),  KC_ENT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_ROPT, \
                        DF(_DVORAK), KC_UP, KC_DOWN , KC_SPC,      KC_BSPC,   KC_LEFT,   KC_RIGHT, KC_RCTRL \
),


/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |_____ | ____ | ___  | /_____  /       \_____ \  |______| ____ |_____ |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 *
 *
 * [_ADJUST] = LAYOUT( \
 *  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
 * XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
 * XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
 * XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
 *                            _______, _______, _______, _______, _______,  _______, _______, _______ \
 * )
 */
};



//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }

    return rotation;
}



static void render_lily58_logo(void) {
    static const char PROGMEM lily58_logo[] = {
    // 'logo', 128x32px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xc0, 0x40, 0x40, 0xc0, 0x80, 0x80, 0x80, 0x00, 0x00,
    0x80, 0xe0, 0x70, 0x3c, 0x0e, 0x06, 0x0e, 0x3c, 0x70, 0xe0, 0x80, 0x00, 0x00, 0xc0, 0xc0, 0x00,
    0xc0, 0xc0, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x80,
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfc, 0xc0, 0x80, 0x80, 0x80, 0x81, 0x83, 0x83,
    0x07, 0x07, 0x0c, 0x18, 0x70, 0xe0, 0x80, 0x00, 0x00, 0x01, 0xff, 0xfc, 0x80, 0xb6, 0xb6, 0x80,
    0xb0, 0xb0, 0x00, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf1, 0x00, 0x00, 0x00, 0x00, 0xff,
    0xff, 0x00, 0x00, 0x00, 0x30, 0xf0, 0xf0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xf0, 0xf0,
    0x30, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xe1, 0x71, 0x71, 0xf1, 0xf1, 0xe1, 0xc1, 0x81, 0x00, 0x00,
    0x00, 0x00, 0x0c, 0x3f, 0xff, 0xf3, 0xe1, 0xc1, 0xc1, 0x81, 0x81, 0xc3, 0xff, 0x7f, 0x1c, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x70, 0x78, 0xdc, 0xcc, 0x86, 0x06, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x03, 0x02, 0x06, 0x84, 0xe1, 0xfb, 0x38, 0x1c, 0x0c, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x03, 0x03, 0x06, 0x86, 0xcc, 0xdc, 0x78, 0x70, 0x20, 0x00, 0xff, 0xff, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff,
    0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1f, 0x7e, 0xf8, 0xe0, 0xf0, 0x7e, 0x1f, 0x03, 0x00,
    0x00, 0x00, 0x00, 0xe0, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0xc0, 0xe1, 0xff, 0x7f, 0x3f, 0x00,
    0x00, 0x00, 0x3e, 0xff, 0xff, 0xc1, 0xc0, 0x80, 0x81, 0x81, 0xc3, 0xc3, 0xff, 0xfe, 0x3c, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x06, 0x06, 0x06, 0x04, 0x04, 0x04, 0x04, 0x06,
    0x06, 0x02, 0x03, 0x01, 0x01, 0x00, 0x01, 0x01, 0x03, 0x02, 0x06, 0x06, 0x04, 0x04, 0x04, 0x04,
    0x06, 0x06, 0x06, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x01, 0x01, 0x00, 0x00, 0x60, 0x60, 0x70, 0x38, 0x1f, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00
};
    oled_write_raw_P(lily58_logo, sizeof(lily58_logo));
}


const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);


void oled_task_user(void) {
    // Host Keyboard Layer Status
  if (is_keyboard_master()) {
    oled_write_P(PSTR("Layer = "), false);

    switch (get_highest_layer(layer_state)) {
        case _DVORAK:
            oled_write_P(PSTR("DVORAK\n"), false);
            break;
        case _QWERTY:
            oled_write_P(PSTR("QWERTY\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("SPECIAL KEYS\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    /*led_t led_state = host_keyboard_led_state();*/
    /*oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);*/
    /*oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);*/
    /*oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);*/
    /*oled_write_ln(read_layer_state(), false);*/
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);

  } else {

    render_lily58_logo();
    /*oled_scroll_left();*/
  }
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
