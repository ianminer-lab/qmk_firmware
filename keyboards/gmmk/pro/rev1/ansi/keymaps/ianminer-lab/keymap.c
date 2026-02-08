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
/* To flash keyboard:
put changes in and save file, then unplug keyboard and press escape, then when KB doesn't seem to turn on:
put in this command below:

qmk flash -kb gmmk/pro/rev1/ansi -km MyKeymap

*/
#include QMK_KEYBOARD_H

enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _DDO,
  _DDO4
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define DDO TG(_DDO)
#define DDO4 TG(_DDO4)

bool is_gui_shift_left_active = false;    /* ADD this near the begining of keymap.c */
uint16_t gui_shift_left_timer = 0;        /* we will be using them soon. */
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum custom_keycodes {             /* Make sure have the awesome keycode ready */
  GUI_SHIFT_LEFT = SAFE_RANGE,       /* Switch windows using mischeif managed */
  SEARCH,
  SSNIP,
  ALT_TAB,
  PWR_OFF,
  USE_TOP,
  FOUR_BANGER,
  FUCKQMK,
  FINISHERS,
  EXP,

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {               /* This will do most of the grunt work with the keycodes. */
	case GUI_SHIFT_LEFT:
	  if (record->event.pressed) {
	    if (!is_gui_shift_left_active) {
	      is_gui_shift_left_active = true;
	      register_code(KC_LGUI);
		  register_code(KC_LSFT);
	    }
	    gui_shift_left_timer = timer_read();
	    register_code(KC_LEFT);
	  } else {
	    unregister_code(KC_LEFT);
	  }
	  break;

	case SEARCH:
	  if (record->event.pressed){
	  	register_code(KC_LGUI);
      register_code(KC_S);
      unregister_code(KC_LGUI);
      unregister_code(KC_S);
	  } else {

	  }
	  break;
  case SSNIP:
      if (record->event.pressed){
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        register_code(KC_S);
        unregister_code(KC_LGUI);
        unregister_code(KC_LSFT);
        unregister_code(KC_S);
      } else {

      }
      break;
	case ALT_TAB:
	  if (record->event.pressed) {
	    if (!is_alt_tab_active) {
	      is_alt_tab_active = true;
	      register_code(KC_LALT);
	    }
	    alt_tab_timer = timer_read();
	    register_code(KC_TAB);
	  } else {
	    unregister_code(KC_TAB);
	  }
	  break;

	case PWR_OFF:
	  if (record->event.pressed){
	  	register_code(KC_LGUI);
		register_code(KC_X);
		unregister_code(KC_LGUI);
		unregister_code(KC_X);
		tap_code(KC_UP);
		tap_code(KC_UP);
		tap_code(KC_RGHT);
		tap_code(KC_UP);
		tap_code(KC_UP);
		tap_code(KC_ENT);
	  } else {

	  }
	  break;

	case USE_TOP:
	  if (record->event.pressed){
	  	tap_code(KC_1);
		tap_code(KC_2);
		tap_code(KC_3);
		tap_code(KC_4);
		tap_code(KC_5);
		tap_code(KC_6);
		tap_code(KC_7);
		tap_code(KC_8);
		tap_code(KC_9);
		tap_code(KC_0);
	  } else {

	  }
	  break;

	case FOUR_BANGER:
	  if (record->event.pressed){
	  	tap_code(KC_1);
		tap_code(KC_2);
		tap_code(KC_3);
		tap_code(KC_4);
	  } else {

	  }
	  break;


	case FINISHERS:
	  if (record->event.pressed){
	  	tap_code(KC_9);
		tap_code(KC_0);
	  } else {

	  }
	  break;

    case EXP:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("NON-Entry Level Experience Required");
        } else {
            // when keycode QMKBEST is released
        }
        break;

	  case FUCKQMK:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("QMK is the fucking BEST!");
        } else {
            // when keycode QMKBEST is released
        }
        break;
  }
  return true;
}
/* broke due to me fixing it weird I think it is now part of qmk  for gmmk  
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    rgb_matrix_set_color((LED_FLAG_KEYLIGHT), 3, 0, 12);
    rgb_matrix_set_color((LED_FLAG_UNDERGLOW), 3, 0, 12);
    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            if (g_led_config.flags[i] & LED_FLAG_MODIFIER) {
                rgb_matrix_set_color(i, 0, 12, 0);
            }
        }
    }else{
        rgb_matrix_set_color((LED_FLAG_MODIFIER), 3, 0, 12);
    }
} */

/*void matrix_init_user(void) { 
     rgb_matrix_enable();
     rgb_matrix_sethsv(3, 12, 12); 
     rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR); }
*/

/*void keyboard_post_init_user(void) {
    // Set the default RGB color to purple
    rgblight_enable();
    rgblight_sethsv(128, 255, 255);  // Purple color
} */

void matrix_scan_user(void) {     /* The very important timer. */
  if (is_gui_shift_left_active) {
    if (timer_elapsed(gui_shift_left_timer) > 1000) {
      unregister_code(KC_LGUI);
	  unregister_code(KC_LSFT);
      is_gui_shift_left_active = false;
    }
  }
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

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
    [0] = LAYOUT(
        KC_ESC,  SEARCH,   ALT_TAB, GUI_SHIFT_LEFT,   KC_F4,   KC_F5,   SSNIP,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_APP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          LOWER,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,       KC_ENT,              DDO,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,       KC_RSFT,    KC_UP,    RAISE,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_END, KC_AGIN,   KC_UNDO, KC_LEFT, KC_DOWN, KC_RGHT
    ),

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right

    [_LOWER] = LAYOUT(
        _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            EXP, _______, _______, _______, _______, _______
    ),

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right

    [_RAISE] = LAYOUT(
        RGB_TOG, RGB_MOD, RGB_RMOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right

    [_ADJUST] = LAYOUT(
        PWR_OFF, QK_MAKE,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right

    [_DDO] = LAYOUT(
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______,          _______,
        FOUR_BANGER, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        USE_TOP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

};

layer_state_t layer_state_set_user(layer_state_t state) {
  	return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
      tap_code(0x80);
    } else {
      tap_code(0x81);
    }
    return true;
}
