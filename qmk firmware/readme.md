# minikeyboardmk3

![minikeyboardmk3]https://files.catbox.moe/rzjbly.png 

*pretty sure someone else didnt make this yet. Arrow keys form a combination which can be used to activate things displayed on the oled. enter key is... self explainable.*

* Keyboard Maintainer: [Yihu](https://github.com/candlc3)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make minikeyboardmk3:default

Flashing example for this keyboard:

    make minikeyboardmk3:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
