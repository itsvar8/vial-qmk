# cornepad

![cornepad-2000px](https://github.com/user-attachments/assets/e6f865d7-0b66-499b-b8ae-9dc743c66138)
Build guide and 3D files --> https://varotto.work/projects/cornepad

Single piece 36 keys Corne layout with a center 4*4 numpad, 2 rotary encoders and RGB. ( -7.5 | 0 | +7.5 ) deg. rotation

* Keyboard Maintainer: [Var](https://github.com/itsvar8)
* Hardware Supported: RP2040
* Hardware Availability: See build guide

Make example for this keyboard (after setting up your build environment):

    make cornepad:default

Flashing example for this keyboard:

    make cornepad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
