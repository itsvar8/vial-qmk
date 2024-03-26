# 5_4_macropad

![5_4_macropad](https://github.com/itsvar8/vial-qmk/assets/120035196/bbe42ad6-177b-405a-b880-26e5daa76587)

3x3 macropad with 4 encoders and per key rgb lighting

* Keyboard Maintainer: [Var](https://github.com/itsvar8)
* Hardware Supported: RP2040
* Hardware Availability: [Etsy](https://keeptyping.etsy.com/it/listing/1688938145/macropad-con-5-tasti-e-4-encoder)

Make example for this keyboard (after setting up your build environment):

    make 5_4_macropad:default

Flashing example for this keyboard:

    make 5_4_macropad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
