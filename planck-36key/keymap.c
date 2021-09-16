/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum planck_layers {
  _BASE,
  _LOWER,
  _NUM,
  _NAVIGATE,
  _SETTINGS,
  _EMPTY
};

enum planck_keycodes {
  ST_MACRO_0 = SAFE_RANGE,
  ST_MACRO_1,
  ST_MACRO_2,
  ST_MACRO_3
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum tap_dance_codes {
  TD_A,
  TD_B,
  TD_C,
  TD_D,
  TD_E,
  TD_F,
  TD_G,
  TD_H,
  TD_I,
  TD_J,
  TD_K,
  TD_L,
  TD_M,
  TD_N,
  TD_O,
  TD_P,
  TD_Q,
  TD_R,
  TD_S,
  TD_T,
  TD_U,
  TD_V,
  TD_W,
  TD_X,
  TD_Y,
  TD_Z,
  TD_LFT,
  TD_RGT
};

td_state_t cur_dance(qk_tap_dance_state_t *state);
void finish_dance(qk_tap_dance_state_t *state, td_tap_t key_state, uint16_t press, uint16_t hold);
void reset_dance(qk_tap_dance_state_t * state, td_tap_t key_state, uint16_t press, uint16_t hold);

#define LOWER OSL(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Colemak
  * ,-----------------------------------------------------------------------.
  * |  Q  |  W  |  F  |  P  |  B  |     |     |  J  |  L  |  U  |  Y  | Bksp|
  * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
  * |  A  |  R  |  S  |  T  |  G  |     |     |  M  |  N  |  E  |  I  |  O  |
  * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
  * |  Z  |  X  |  C  |  D  |  V  |     |     |  K  |  H  |  ,  |  .  |  /  |
  * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
  * |     |     | Meh |Space| RSft|           | ROpt|LOWER| RCtl|     |     |
  * `-----------------------------------------------------------------------'
  */
  [_BASE] = LAYOUT_planck_grid(
      TD(TD_Q), TD(TD_W), TD(TD_F), TD(TD_P), TD(TD_B), KC_NO,   KC_NO,   TD(TD_J), TD(TD_L), TD(TD_U), TD(TD_Y), KC_BSPC,
      TD(TD_A), TD(TD_R), TD(TD_S), TD(TD_T), TD(TD_G), KC_NO,   KC_NO,   TD(TD_M), TD(TD_N), TD(TD_E), TD(TD_I), TD(TD_O),
      TD(TD_Z), TD(TD_X), TD(TD_C), TD(TD_D), TD(TD_V), KC_NO,   KC_NO,   TD(TD_K), TD(TD_H), KC_COMM,  KC_DOT,   KC_SLSH,
      KC_NO,    KC_NO,    KC_MEH,   KC_SPC,   KC_RSFT,  KC_NO,   KC_NO,   KC_ROPT,  LOWER,    KC_RCTL,  KC_NO,    KC_NO
  ),

  /* Lower
  * ,-----------------------------------------------------------------------.
  * | Esc |  @  |  #  |     |  %  |     |     |  ^  |  &  |  *  |  ;  |  :  |
  * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
  * | Tab |  _  |  ‘  |  ’  |     |     |     |     |     |     |     |Enter|
  * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
  * |  ~  |  £  |  “  |  ”  |  "  |     |     |  [  |  (  |  )  |  ]  |     |
  * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
  * |     |     |  !  |  -  | RSft|           | NAV | NUM | RCtl|     |     |
  * `-----------------------------------------------------------------------'
  */
  [_LOWER] = LAYOUT_planck_grid(
      KC_ESC,   KC_AT,     KC_HASH,   KC_NO,     KC_PERC,  KC_NO,    KC_NO,    KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_SCOLON,LSFT(KC_SCOLON),
      KC_TAB,   KC_UNDS,   ST_MACRO_0,ST_MACRO_1,KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_ENTER,
      KC_TILD,  LSFT(KC_2),ST_MACRO_2,ST_MACRO_3,KC_DQUO,  KC_NO,    KC_NO,    KC_LBRC,  KC_LPRN,  KC_RPRN,  KC_RBRC,  KC_NO,
      KC_NO,    KC_NO,     KC_EXLM,   KC_MINUS,  KC_RSFT,  KC_NO,    KC_NO,    TO(_NAVIGATE),TO(_NUM),KC_RCTL,KC_NO,   KC_NO
  ),

  /* Num
  * ,-----------------------------------------------------------------------.
  * | Esc | Play|  << | >>  |  _  |     |     |  -  |  7  |  8  |  9  | Bksp|
  * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
  * | Tab | Mute|Vol -|Vol +|  +  |     |     |  =  |  4  |  5  |  6  |Enter|
  * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
  * |SETTI|  *  |Brt +|Brt -|num .|     |     |  0  |  1  |  2  |  3  |  /  |
  * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
  * |     |     | BASE| Cmd | RSft|           |     |     | RCtl|     |     |
  * `-----------------------------------------------------------------------'
  */
  [_NUM] = LAYOUT_planck_grid(
      KC_ESC,   KC_MPLY,   KC_MPRV,   KC_MNXT,   KC_UNDS,  KC_NO,    KC_NO,    KC_MINUS, KC_7,    KC_8,    KC_9,    KC_BSPC,
      KC_TAB,   KC_MUTE,   KC_VOLD,   KC_VOLU,   KC_PLUS,  KC_NO,    KC_NO,    KC_EQUAL, KC_4,    KC_5,    KC_6,    KC_ENTER,
      TO(_SETTINGS),KC_PAST,KC_BRIU,  KC_BRID,   KC_KP_DOT,KC_NO,    KC_NO,    KC_0,     KC_1,    KC_2,    KC_3,    KC_SLSH,
      KC_NO,    KC_NO,     TO(_BASE), KC_LGUI,   KC_RSFT,  KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_RCTL, KC_NO,   KC_NO
  ),

  /* Navigate
  * ,-----------------------------------------------------------------------.
  * |     |     |MS UP|     |     |     |     |Cmd+[| CST |  CS |Cmd+]| Bksp|
  * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
  * |     |MS LT|MS DN|MS RT|     |     |     | LEFT|  DN |  UP |RIGHT|Enter|
  * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
  * |     |RT CK|WHLUP|WHLDN|     |     |     |LT CK|MS A0|MS A1|MS A2|     |
  * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
  * |     |     | BASE|     | RSft|           |     |     |     |     |     |
  * `-----------------------------------------------------------------------'
  */
  [_NAVIGATE] = LAYOUT_planck_grid(
      KC_NO,    KC_NO,    KC_MS_UP, KC_NO,    KC_NO,    KC_NO,    KC_NO,    LGUI(KC_LBRC), LCTL(LSFT(KC_TAB)), RCTL(KC_TAB), LGUI(KC_RBRC), KC_BSPC,
      KC_NO,    KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT,KC_NO,KC_NO,    KC_NO,    TD(TD_LFT),KC_DOWN, KC_UP,    TD(TD_RGT),KC_ENTER,
      KC_NO,    KC_MS_BTN2,KC_MS_WH_UP,KC_MS_WH_DOWNKC_NO,    KC_NO,    KC_NO,    KC_MS_BTN1,KC_MS_ACCEL0,KC_MS_ACCEL1,KC_MS_ACCEL2,    KC_NO,
      KC_NO,    KC_NO,    TO(_BASE),KC_NO,    KC_RSFT,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO
  ),

  /* Settings
  * ,-----------------------------------------------------------------------.
  * |     |     |     |     |     |     |     |     |     |     |     |RESET|
  * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
  * |     |     |     |     |     |     |     |     |     |     |     |     |
  * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
  * |     |     |     |     |     |     |     |     |     |     |     |     |
  * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
  * |     |     | BASE|     |     |           |     |     |     |     |     |
  * `-----------------------------------------------------------------------'
  */
  [_SETTINGS] = LAYOUT_planck_grid(
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    RESET,
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
      KC_NO,    KC_NO,    TO(_BASE),KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO
  ),

  /* Empty
  * ,-----------------------------------------------------------------------.
  * |     |     |     |     |     |     |     |     |     |     |     |     |
  * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
  * |     |     |     |     |     |     |     |     |     |     |     |     |
  * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
  * |     |     |     |     |     |     |     |     |     |     |     |     |
  * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
  * |     |     |     |     |     |           |     |     |     |     |     |
  * `-----------------------------------------------------------------------'
  */
  [_EMPTY] = LAYOUT_planck_grid(
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ST_MACRO_0:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_RBRACKET)));

      }
      break;
    case ST_MACRO_1:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_LSFT(SS_TAP(X_RBRACKET))));

      }
      break;
    case ST_MACRO_2:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_LBRACKET)));

      }
      break;
    case ST_MACRO_3:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_LSFT(SS_TAP(X_LBRACKET))));

      }
      break;
  }
  return true;
}

td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

void finish_dance(qk_tap_dance_state_t *state, td_tap_t key_state, uint16_t press, uint16_t hold) {
  key_state.state = cur_dance(state);
  switch(key_state.state) {
    case TD_SINGLE_TAP: register_code16(press); break;
    case TD_SINGLE_HOLD: register_code16(hold); break;
    case TD_DOUBLE_TAP: register_code16(press); register_code16(press); break;
    case TD_DOUBLE_HOLD: register_code16(hold); break;
    case TD_DOUBLE_SINGLE_TAP: register_code16(press); register_code16(press); break;
    default: register_code16(press); register_code16(press);
  }
}

void reset_dance(qk_tap_dance_state_t * state, td_tap_t key_state, uint16_t press, uint16_t hold) {
  switch (key_state.state) {
    case TD_SINGLE_TAP: unregister_code16(press); break;
    case TD_SINGLE_HOLD: unregister_code16(hold); break;
    case TD_DOUBLE_TAP: unregister_code16(press); break;
    case TD_DOUBLE_HOLD: unregister_code16(hold); break;
    case TD_DOUBLE_SINGLE_TAP: unregister_code16(press); break;
    default: unregister_code16(press);
  }
  key_state.state = TD_NONE;
}

static td_tap_t atap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void a_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, atap_state, KC_A, LGUI(KC_A));
};
void a_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, atap_state, KC_A, LGUI(KC_A));
};

static td_tap_t btap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void b_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, btap_state, KC_B, LGUI(KC_B));
};
void b_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, btap_state, KC_B, LGUI(KC_B));
};

static td_tap_t ctap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void c_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, ctap_state, KC_C, LGUI(KC_C));
};
void c_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, ctap_state, KC_C, LGUI(KC_C));
};

static td_tap_t dtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void d_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, dtap_state, KC_D, LGUI(KC_D));
};
void d_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, dtap_state, KC_D, LGUI(KC_D));
};

static td_tap_t etap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void e_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, etap_state, KC_E, LGUI(KC_E));
};
void e_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, etap_state, KC_E, LGUI(KC_E));
};

static td_tap_t ftap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void f_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, ftap_state, KC_F, LGUI(KC_F));
};
void f_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, ftap_state, KC_F, LGUI(KC_F));
};

static td_tap_t gtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void g_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, gtap_state, KC_G, LGUI(KC_G));
};
void g_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, gtap_state, KC_G, LGUI(KC_G));
};

static td_tap_t htap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void h_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, htap_state, KC_H, LGUI(KC_H));
};
void h_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, htap_state, KC_H, LGUI(KC_H));
};

static td_tap_t itap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void i_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, itap_state, KC_I, LGUI(KC_I));
};
void i_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, itap_state, KC_I, LGUI(KC_I));
};

static td_tap_t jtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void j_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, jtap_state, KC_J, LGUI(KC_J));
};
void j_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, jtap_state, KC_J, LGUI(KC_J));
};

static td_tap_t ktap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void k_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, ktap_state, KC_K, LGUI(KC_K));
};
void k_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, ktap_state, KC_K, LGUI(KC_K));
};

static td_tap_t ltap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void l_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, ltap_state, KC_L, LGUI(KC_L));
};
void l_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, ltap_state, KC_L, LGUI(KC_L));
};

static td_tap_t mtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void m_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, mtap_state, KC_M, LGUI(KC_M));
};
void m_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, mtap_state, KC_M, LGUI(KC_M));
};

static td_tap_t ntap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void n_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, ntap_state, KC_N, LGUI(KC_N));
};
void n_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, ntap_state, KC_N, LGUI(KC_N));
};

static td_tap_t otap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void o_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, otap_state, KC_O, LGUI(KC_O));
};
void o_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, otap_state, KC_O, LGUI(KC_O));
};

static td_tap_t ptap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void p_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, ptap_state, KC_P, LGUI(KC_P));
};
void p_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, ptap_state, KC_P, LGUI(KC_P));
};

static td_tap_t qtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void q_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, qtap_state, KC_Q, LGUI(KC_Q));
};
void q_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, qtap_state, KC_Q, LGUI(KC_Q));
};

static td_tap_t rtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void r_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, rtap_state, KC_R, LGUI(KC_R));
};
void r_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, rtap_state, KC_R, LGUI(KC_R));
};

static td_tap_t stap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void s_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, stap_state, KC_S, LGUI(KC_S));
};
void s_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, stap_state, KC_S, LGUI(KC_S));
};

static td_tap_t ttap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void t_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, ttap_state, KC_T, LGUI(KC_T));
};
void t_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, ttap_state, KC_T, LGUI(KC_T));
};

static td_tap_t utap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void u_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, utap_state, KC_U, LGUI(KC_U));
};
void u_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, utap_state, KC_U, LGUI(KC_U));
};

static td_tap_t vtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void v_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, vtap_state, KC_V, LGUI(KC_V));
};
void v_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, vtap_state, KC_V, LGUI(KC_V));
};

static td_tap_t wtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void w_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, wtap_state, KC_W, LGUI(KC_W));
};
void w_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, wtap_state, KC_W, LGUI(KC_W));
};

static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void x_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, xtap_state, KC_X, LGUI(KC_X));
};
void x_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, xtap_state, KC_X, LGUI(KC_X));
};

static td_tap_t ytap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void y_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, ytap_state, KC_Y, LGUI(KC_Y));
};
void y_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, ytap_state, KC_Y, LGUI(KC_Y));
};

static td_tap_t ztap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void z_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, ztap_state, KC_Z, LGUI(KC_Z));
};
void z_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, ztap_state, KC_Z, LGUI(KC_Z));
};

static td_tap_t lefttap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void left_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, ztap_state, KC_LEFT, LGUI(KC_LEFT));
};
void left_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, ztap_state, KC_LEFT, LGUI(KC_LEFT));
};

static td_tap_t rightttap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void right_finished(qk_tap_dance_state_t *state, void *user_data) {
  finish_dance(state, ztap_state, KC_RIGHT, LGUI(KC_RIGHT));
};
void right_reset(qk_tap_dance_state_t *state, void *user_data) {
  reset_dance(state, ztap_state, KC_RIGHT, LGUI(KC_RIGHT));
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_A] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, a_finished, a_reset),
  [TD_B] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, b_finished, b_reset),
  [TD_C] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, c_finished, c_reset),
  [TD_D] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, d_finished, d_reset),
  [TD_E] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, e_finished, e_reset),
  [TD_F] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f_finished, f_reset),
  [TD_G] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, g_finished, g_reset),
  [TD_H] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, h_finished, h_reset),
  [TD_I] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, i_finished, i_reset),
  [TD_J] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, j_finished, j_reset),
  [TD_K] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, k_finished, k_reset),
  [TD_L] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, l_finished, l_reset),
  [TD_M] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, m_finished, m_reset),
  [TD_N] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, n_finished, n_reset),
  [TD_O] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, o_finished, o_reset),
  [TD_P] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, p_finished, p_reset),
  [TD_Q] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, q_finished, q_reset),
  [TD_R] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, r_finished, r_reset),
  [TD_S] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, s_finished, s_reset),
  [TD_T] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, t_finished, t_reset),
  [TD_U] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, u_finished, u_reset),
  [TD_V] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, v_finished, v_reset),
  [TD_W] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, w_finished, w_reset),
  [TD_X] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset),
  [TD_Y] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, y_finished, y_reset),
  [TD_Z] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, z_finished, z_reset),
  [TD_LFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, left_finished, left_reset),
  [TD_RGT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, right_finished, right_reset),
};
