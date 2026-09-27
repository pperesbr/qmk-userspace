// Sofle v2 (rev1) + RP2040 Pro Micro — pperesbr keymap
// US layout, tuned for vim, WezTerm and Zed.

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _NAV,
    _SYM,
    _ADJUST,
};

// Tap for Esc, hold for Ctrl (sits on the Caps Lock position)
#define CTL_ESC CTL_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BASE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Esc/Ct|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------| Mute  |    |       |------+------+------+------+------+------|
 * |Shift |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |Shift |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | GUI  | Alt  | Ctrl | NAV  | / Space /       \ Enter\  | SYM  | Bspc | Alt  | GUI  |
 *            `----------------------------------'           '------''---------------------------'
 */
[_BASE] = LAYOUT(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,     KC_5,                       KC_6,    KC_7,     KC_8,    KC_9,    KC_0,    KC_EQL,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,                       KC_Y,    KC_U,     KC_I,    KC_O,    KC_P,    KC_BSPC,
  CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,     KC_G,                       KC_H,    KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,    KC_MUTE, XXXXXXX,  KC_N,    KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                    KC_LGUI, KC_LALT, KC_LCTL,  MO(_NAV), KC_SPC, KC_ENT,   MO(_SYM), KC_BSPC, KC_RALT, KC_RGUI
),

/* NAV — arrows on hjkl (vim-style), modifiers under the left hand
 * Right: Home/PgDn/PgUp/End on yuio, Del on the far right
 * Left:  GUI / Alt / Ctrl / Shift on a s d f (combine with arrows to select)
 */
[_NAV] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                     KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, KC_DEL,
  _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______
),

/* SYM — programming symbols
 * Home row: brackets mirrored around the center  - _ { ( [  |  ] ) } = +
 */
[_SYM] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                     KC_CIRC, KC_AMPR, KC_ASTR, KC_TILD, KC_GRV,  _______,
  _______, KC_MINS, KC_UNDS, KC_LCBR, KC_LPRN, KC_LBRC,                     KC_RBRC, KC_RPRN, KC_RCBR, KC_EQL,  KC_PLUS, _______,
  _______, KC_BSLS, KC_PIPE, KC_LT,   KC_GT,   KC_COLN, _______,   _______, _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______
),

/* ADJUST — hold NAV + SYM together
 * F-keys, media, Caps Word, bootloader
 */
[_ADJUST] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                       KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  QK_BOOT, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, CW_TOGG,                     KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY, _______,
  _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______
),
};

// NAV + SYM held together activates ADJUST
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _NAV, _SYM, _ADJUST);
}

#ifdef ENCODER_MAP_ENABLE
// Left encoder first, right encoder second
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_NAV]    = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_SYM]    = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_ADJUST] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
};
#endif

#ifdef OLED_ENABLE
// Vertical OLED: 5 characters per line, so labels stay at 4 chars max
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

static void render_layer(void) {
    switch (get_highest_layer(layer_state)) {
        case _BASE:   oled_write_ln_P(PSTR("BASE"), false); break;
        case _NAV:    oled_write_ln_P(PSTR("NAV"), false);  break;
        case _SYM:    oled_write_ln_P(PSTR("SYM"), false);  break;
        case _ADJUST: oled_write_ln_P(PSTR("ADJ"), false);  break;
        default:      oled_write_ln_P(PSTR("?"), false);    break;
    }
}

static void render_mods(void) {
    uint8_t mods = get_mods();
    // Highlighted (inverted) while the modifier is held
    oled_write_ln_P(PSTR("CTL"), mods & MOD_MASK_CTRL);
    oled_write_ln_P(PSTR("SFT"), mods & MOD_MASK_SHIFT);
    oled_write_ln_P(PSTR("ALT"), mods & MOD_MASK_ALT);
    oled_write_ln_P(PSTR("GUI"), mods & MOD_MASK_GUI);
}

bool oled_task_user(void) {
    render_layer();
    oled_write_ln_P(PSTR(""), false);
    render_mods();
    oled_write_ln_P(PSTR(""), false);
    // Caps Word state is only tracked on the master (left) half
    oled_write_ln_P(PSTR("CAPS"), is_caps_word_on());
    // Returning false skips the keyboard's default OLED rendering
    return false;
}
#endif
