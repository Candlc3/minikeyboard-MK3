// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <string.h>

enum layer_names {
    _BASE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     *	     ├───┼ 
     *       │ 1  │    
     *       └───┴
     * ├───┼    ┼───┤ 
     * │ 2  │    │ 3 │     5 (idk how to put box) 
     * └───┴    ┴───┘
     * 	     ├───┼    
     *       │ 4  │    
     *        ───┴
     */

      
    [_BASE] = LAYOUT(
    	KC_W,
   	KC_D, KC_A, KC_ENTER,
   	KC_S
    )
};

// Arrow history buffer
static char arrow_history[32] = "";
static char password_buffer[32] = "";
static uint8_t arrow_len = 0;
static uint8_t pass_len = 0;

// Your password:
static const char correct_password[] = "wdssa";

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    // ENTER = check password + clear screen
    if (keycode == KC_ENTER) {
        oled_clear();

        if (strcmp(password_buffer, correct_password) == 0) {
            oled_write_ln_P(PSTR("password correct"), false);
        } else {
            oled_write_ln_P(PSTR("try again"), false);
        }

        // Delay ~2 seconds
        wait_ms(2000);

        // Reset everything
        arrow_len = 0;
        pass_len = 0;
        arrow_history[0] = '\0';
        password_buffer[0] = '\0';
        oled_clear();

        return true;
    }

    // Map WASD → arrows + password characters
    const char *arrow = NULL;
    char pass_char = 0;

    switch (keycode) {
        case KC_W: arrow = "^"; pass_char = 'w'; break;
        case KC_A: arrow = "<"; pass_char = 'a'; break;
        case KC_S: arrow = "v"; pass_char = 's'; break;
        case KC_D: arrow = ">"; pass_char = 'd'; break;
    }

    // If key was one of WASD
    if (arrow) {
        // Append arrow to history
        if (arrow_len < sizeof(arrow_history) - 1) {
            strcat(arrow_history, arrow);
            arrow_len += strlen(arrow);
        }

        // Append password character
        if (pass_len < sizeof(password_buffer) - 1) {
            password_buffer[pass_len++] = pass_char;
            password_buffer[pass_len] = '\0';
        }

        // Draw updated arrow history
        oled_clear();
        oled_write_ln(arrow_history, false);
    }

    return true;
}


#ifdef OLED_ENABLE
bool oled_task_user(void) {
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("Default\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    return false;
}
#endif
