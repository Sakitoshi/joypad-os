// profiles.h - N642USB App Profiles
//
// Profile definitions for N64 to USB adapter.

#ifndef N642USB_PROFILES_H
#define N642USB_PROFILES_H

#include "core/services/profiles/profile.h"

// ============================================================================
// PROFILE 1: DEFAULT (DC-style face buttons)
// ============================================================================
// A=B1, C-Down=B2, B=B3, C-Left=B4, C-Up=L3, C-Right=R3
// C-buttons also map to right stick

// Hack needed to make Start work with profile combos
static const button_map_entry_t n642usb_default_map[] = {
    // Hack: N64 "Select" (S1) -> USB Start (S2)
    MAP_BUTTON(JP_BUTTON_S1, JP_BUTTON_S2),
};

// ============================================================================
// PROFILE 2: DUAL STICK (C-buttons as right stick only)
// ============================================================================
// A=B1, B=B2, C-buttons=right stick only (no button output)

static const button_map_entry_t n642usb_dualstick_map[] = {
    // Hack: N64 "Select" (S1) -> USB Start (S2)
    MAP_BUTTON(JP_BUTTON_S1, JP_BUTTON_S2),
    // N64 B (B3) -> USB B (B2)
    MAP_BUTTON(JP_BUTTON_B3, JP_BUTTON_B2),
    // Remove C-button mappings (they still control right stick via analog)
    MAP_BUTTON(JP_BUTTON_B2, 0),   // C-Down -> nothing
    MAP_BUTTON(JP_BUTTON_B4, 0),   // C-Left -> nothing
    MAP_BUTTON(JP_BUTTON_L3, 0),   // C-Up -> nothing
    MAP_BUTTON(JP_BUTTON_R3, 0),   // C-Right -> nothing
};

// ============================================================================
// PROFILE 3: WII U (Suitable to play Wii U Games)
// ============================================================================
// A=B1, C-Down=B2, B=B3, C-Left=B4, C-Up=L3, C-Right=R3
// L=L1, R=R1, Z=L2
// no right stick

static const button_map_entry_t n642usb_wiiu_map[] = {
    // Hack: N64 "Select" (S1) -> USB Start (S2)
    MAP_BUTTON(JP_BUTTON_S1, JP_BUTTON_S2),
    MAP_BUTTON(JP_BUTTON_L1, 0),   // nothing
    MAP_BUTTON(JP_BUTTON_L2, JP_BUTTON_L1),   // L -> L1
    MAP_BUTTON(JP_BUTTON_R1, JP_BUTTON_L2),   // Z -> L2
    MAP_BUTTON(JP_BUTTON_R2, JP_BUTTON_R1),   // R -> R1

};

// ============================================================================
// PROFILE 4: WII U VC (Suitable to play Wii U VC)
// ============================================================================
// A=B1, C-Down=B2, B=B3, C-Left=B4, C-Up=L3, C-Right=R3
// L=L1, R=R1, Z=L2
// C-buttons also map to right stick

static const button_map_entry_t n642usb_wiiuvc_map[] = {
    // Hack: N64 "Select" (S1) -> USB Start (S2)
    MAP_BUTTON(JP_BUTTON_S1, JP_BUTTON_S2),
    MAP_BUTTON(JP_BUTTON_L1, 0),   // nothing
    MAP_BUTTON(JP_BUTTON_L2, JP_BUTTON_L1),   // L -> L1
    MAP_BUTTON(JP_BUTTON_R1, JP_BUTTON_L2),   // Z -> L2
    MAP_BUTTON(JP_BUTTON_R2, JP_BUTTON_R1),   // R -> R1

};

// ============================================================================
// PROFILE DEFINITIONS
// ============================================================================

static const profile_t n642usb_profiles[] = {
    // Profile 0: Default (DC-style)
    {
        .name = "default",
        .description = "DC-style: A/B/C-Down/C-Left as face buttons",
        .button_map = n642usb_default_map,
        .button_map_count = sizeof(n642usb_default_map) / sizeof(n642usb_default_map[0]),
        .combo_map = NULL,
        .combo_map_count = 0,
        //PROFILE_TRIGGERS_DEFAULT,
        .l2_behavior = TRIGGER_DIGITAL_ONLY,
        .r2_behavior = TRIGGER_DIGITAL_ONLY,
        .l2_threshold = 128,
        .r2_threshold = 128,
        .l2_analog_value = 0,
        .r2_analog_value = 0,
        PROFILE_ANALOG_DEFAULT,
        .adaptive_triggers = false,
    },
    // Profile 1: Dual Stick
    {
        .name = "dualstick",
        .description = "Dual stick: A/B as face, C-pad as right stick",
        .button_map = n642usb_dualstick_map,
        .button_map_count = sizeof(n642usb_dualstick_map) / sizeof(n642usb_dualstick_map[0]),
        .combo_map = NULL,
        .combo_map_count = 0,
        //PROFILE_TRIGGERS_DEFAULT,
        .l2_behavior = TRIGGER_DIGITAL_ONLY,
        .r2_behavior = TRIGGER_DIGITAL_ONLY,
        .l2_threshold = 128,
        .r2_threshold = 128,
        .l2_analog_value = 0,
        .r2_analog_value = 0,
        PROFILE_ANALOG_DEFAULT,
        .adaptive_triggers = false,
    },
    // Profile 2: Wii U
    {
        .name = "wii u",
        .description = "Wii U: L,R and Z to L1, R1 and L2, no right stick",
        .button_map = n642usb_wiiu_map,
        .button_map_count = sizeof(n642usb_wiiu_map) / sizeof(n642usb_wiiu_map[0]),
        .combo_map = NULL,
        .combo_map_count = 0,
        //PROFILE_TRIGGERS_DEFAULT,
        .l2_behavior = TRIGGER_DIGITAL_ONLY,
        .r2_behavior = TRIGGER_DIGITAL_ONLY,
        .l2_threshold = 128,
        .r2_threshold = 128,
        .l2_analog_value = 0,
        .r2_analog_value = 0,
        .left_stick_sensitivity = 1.0f,
        .right_stick_sensitivity = 0.0f,
        .left_stick_modifiers = NULL,
        .left_stick_modifier_count = 0,
        .right_stick_modifiers = NULL,
        .right_stick_modifier_count = 0,
        .adaptive_triggers = false,
    },
    // Profile 3: Wii U VC
    {
        .name = "wii u vc",
        .description = "Wii U VC: L,R and Z to L1, R1 and L2",
        .button_map = n642usb_wiiuvc_map,
        .button_map_count = sizeof(n642usb_wiiu_map) / sizeof(n642usb_wiiu_map[0]),
        .combo_map = NULL,
        .combo_map_count = 0,
        //PROFILE_TRIGGERS_DEFAULT,
        .l2_behavior = TRIGGER_DIGITAL_ONLY,
        .r2_behavior = TRIGGER_DIGITAL_ONLY,
        .l2_threshold = 128,
        .r2_threshold = 128,
        .l2_analog_value = 0,
        .r2_analog_value = 0,
        PROFILE_ANALOG_DEFAULT,
        .adaptive_triggers = false,
    },
};

// ============================================================================
// PROFILE SET
// ============================================================================

static const profile_set_t n642usb_profile_set = {
    .profiles = n642usb_profiles,
    .profile_count = sizeof(n642usb_profiles) / sizeof(n642usb_profiles[0]),
    .default_index = 0,
};

#endif // N642USB_PROFILES_H
