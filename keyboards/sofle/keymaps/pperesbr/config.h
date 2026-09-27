#pragma once

// The half with the USB cable is the left one
#define MASTER_LEFT

// Double-tap reset to enter the UF2 bootloader
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

// Sync layer and modifier state to the right half (for its OLED)
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_MODS_ENABLE

// Number of layers available in VIA
#define DYNAMIC_KEYMAP_LAYER_COUNT 5

// Time to tell a tap from a hold (Esc/Ctrl on the Caps key)
#define TAPPING_TERM 200
