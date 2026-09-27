# qmk-userspace

Personal QMK userspace: keymaps and firmware for my split keyboards.

Firmware is built by GitHub Actions on every push. No local toolchain required.

## Keyboards

| Keyboard | Controller | Keymap |
|---|---|---|
| Sofle v2 (`sofle/rev1`) | RP2040 Pro Micro (16 MB) | `pperesbr` |

## Hardware — Sofle v2

- PCB: Sofle v2 (no per-key RGB)
- Controller: RP2040 Pro Micro, USB-C, 16 MB flash
  - Pin-compatible with the ATmega32U4 Pro Micro through QMK's `promicro_rp2040` converter
  - Only the 12 pins per side starting at `GP0` / `5V` are used; `GP10`, `GP11` and the bottom row are left without headers
- OLED: SSD1306 0.91" on both halves
- Encoders: EC11 on both halves
- Split connection: TRRS (serial on `GP1`)

## Repository layout

```
.
├── .github/workflows/build_binaries.yaml   # CI build + release
├── qmk.json                                # build targets
└── keyboards/
    └── sofle/
        └── keymaps/
            └── pperesbr/
                ├── keymap.c                # layers, encoders, OLED
                ├── rules.mk                # features + RP2040 converter
                └── config.h                # split, bootloader, tapping
```

## Build

Push to `main`. The workflow:

1. Checks out upstream `qmk/qmk_firmware` (`master`)
2. Overlays this repository and builds every target in `qmk.json`
3. Publishes the resulting `.uf2` files to the `latest` release

Build targets (`qmk.json`):

```json
{
  "userspace_version": "1.0",
  "build_targets": [
    ["sofle/rev1", "pperesbr"]
  ]
}
```

## Flashing

The same `.uf2` goes on both halves (`MASTER_LEFT`, so the USB cable always goes on the left half).

1. Download the `.uf2` from the latest release
2. Plug the USB cable into the half you want to flash
3. Double-tap the reset button (or press `QK_BOOT` on ADJUST, left half only) — the controller mounts as a drive
4. Drag the `.uf2` onto the drive; it reboots by itself
5. Repeat for the other half

## Features

`rules.mk`:

- `CONVERT_TO = promicro_rp2040` — RP2040 instead of the 32U4
- `VIA_ENABLE` — live remapping at [usevia.app](https://usevia.app)
- `OLED_ENABLE`, `ENCODER_ENABLE`, `ENCODER_MAP_ENABLE`
- `CAPS_WORD_ENABLE`

`config.h`:

- `MASTER_LEFT` — left half is the USB side
- RP2040 double-tap reset into the UF2 bootloader
- Layer and modifier state synced to the right half (OLED)
- 5 dynamic layers for VIA
- `TAPPING_TERM 200`

## Layers

Tuned for vim, WezTerm and Zed (vim mode). US layout.

| Layer | Access | Contents |
|---|---|---|
| BASE | default | QWERTY; `Esc` on tap / `Ctrl` on hold in the Caps Lock position |
| NAV | hold left inner thumb | Arrows on `hjkl`, Home/PgDn/PgUp/End above; GUI/Alt/Ctrl/Shift on `asdf` |
| SYM | hold right inner thumb | Programming symbols; home row `- _ { ( [` / `] ) } = +` |
| ADJUST | NAV + SYM | F1–F12, media, Caps Word, `QK_BOOT` |

Thumb cluster:

```
Left:  GUI  Alt  Ctrl  NAV  Space        Right:  Enter  SYM  Bspc  Alt  GUI
```

Encoders:

| Layer | Left | Right |
|---|---|---|
| BASE | Volume (click: mute) | PgUp / PgDn |
| NAV | Previous / next track | Left / Right |

OLED (vertical): active layer, held modifiers (inverted), Caps Word.

## VIA

VIA changes are stored on the keyboard but are **reset when new firmware is flashed**. Experiment in VIA, then port what sticks into `keymap.c`.

On Linux, Chrome needs a udev rule to access the keyboard over HID.

## OS setup

The US-International layout turns `' " ` ~ ^` into dead keys, which breaks vim. Use a variant without them:

- macOS: **ABC – Extended** (accents via Option)
- Linux / Hyprland (Omarchy): `kb_layout = us`, `kb_variant = altgr-intl` in `~/.config/hypr/input.conf`
- Windows: US + [WinCompose](https://github.com/samhocevar/wincompose)

## Local development (optional)

Only needed for faster builds or editor support. Zed/clangd shows false errors without it, since QMK headers are unknown outside the QMK build.

```sh
brew install qmk/qmk/qmk
qmk setup
qmk config user.overlay_dir="$(pwd)"
qmk compile -kb sofle/rev1 -km pperesbr
qmk generate-compilation-database -kb sofle/rev1 -km pperesbr
```

Symlink the generated `compile_commands.json` into the repo root so clangd finds it.
