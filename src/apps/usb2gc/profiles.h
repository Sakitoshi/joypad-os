// profiles.h - USB2GC Profile Definitions
//
// Button mapping profiles for USB to GameCube adapter.
// Uses console-specific button aliases for readability.
//
// GameCube button layout:
//   A (B1) - Large green button
//   B (B2) - Small red button
//   X (B4) - Right of A
//   Y (B3) - Above A
//   Z (R1) - Digital shoulder
//   L (L2) - Left trigger (analog + digital)
//   R (R2) - Right trigger (analog + digital)
//   Start (S2)
//   D-pad, Control stick, C-stick

#ifndef USB2GC_PROFILES_H
#define USB2GC_PROFILES_H

#include "core/services/profiles/profile.h"
#include "native/device/gamecube/gamecube_buttons.h"

// ============================================================================
// PROFILE: Mario Kart Wii - PS5 -> GameCube (Competitive)
// ============================================================================
// PS5 bindings (via USB2GC):
//   Circle -> A (accelerate)
//   Cross  -> B (brake / reverse)
//   R1     -> R (drift)
//   L1     -> X (use item)
//   L2     -> D-pad Up (wheelie / up trick)
//   D-pad Left  -> D-pad Left  (left trick)
//   D-pad Down  -> D-pad Down  (down trick)
//   D-pad Right -> D-pad Right (right trick)
//   Options -> Start
//
// Notes:
// - This is a pure PS5 -> GCN profile (what MKWii sees is a GameCube pad).
// - Digital R is preferred for consistent drifting in competitive MKWii.

static const button_map_entry_t gc_mkwii_map[] = {
    // Face buttons
    MAP_BUTTON(JP_BUTTON_B2, GC_BUTTON_A),   // Circle -> A (accelerate)
    MAP_BUTTON(JP_BUTTON_B1, GC_BUTTON_B),   // Cross  -> B (brake)

    // Core controls
    MAP_BUTTON(JP_BUTTON_R1, GC_BUTTON_R),   // R1 -> R (drift)
    MAP_BUTTON(JP_BUTTON_L1, GC_BUTTON_X),   // L1 -> X (use item)

    // Wheelie / trick (up)
    MAP_BUTTON(JP_BUTTON_L2, GC_BUTTON_DU),  // L2 -> D-pad Up

    // Trick directions (D-pad passes through by default)

    // System
    MAP_BUTTON(JP_BUTTON_S2, GC_BUTTON_START), // Options -> Start
    MAP_DISABLED(JP_BUTTON_S1),                // Share -> disabled (often profile switch)
};

static const profile_t gc_profile_mkwii = {
    .name = "mkwii_ps5_comp",
    .description = "MKWii PS5->GCN: O=A, X=B, R1=Drift, L1=Item, L2=Wheelie",
    .button_map = gc_mkwii_map,
    .button_map_count = sizeof(gc_mkwii_map) / sizeof(gc_mkwii_map[0]),

    // Triggers
    // We map L2 as a button to D-pad Up, so set it to instant so it actuates immediately.
    .l2_behavior = TRIGGER_INSTANT,
    .r2_behavior = TRIGGER_DISABLED,

    .l2_threshold = 10,
    .r2_threshold = 0,

    .l2_analog_value = 0,
    .r2_analog_value = 0,

    // Sticks (leave default)
    .left_stick_sensitivity = 1.0f,
    .right_stick_sensitivity = 1.0f,
    .left_stick_modifiers = NULL,
    .left_stick_modifier_count = 0,
    .right_stick_modifiers = NULL,
    .right_stick_modifier_count = 0,

    // Optional: keep off for consistency
    .adaptive_triggers = false,
};

// ============================================================================
// PROFILE SET
// ============================================================================

static const profile_t gc_profiles[] = {
    gc_profile_mkwii,
};

static const profile_set_t gc_profile_set = {
    .profiles = gc_profiles,
    .profile_count = sizeof(gc_profiles) / sizeof(gc_profiles[0]),
    .default_index = 0,
};

#endif // USB2GC_PROFILES_H
