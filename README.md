# About

This is a microcontroller project template generated using using STM32CubeMX from STMicroelectronics. This template targets the STM32F042K6 part as found on the NUCLEO-F042K6 development board.

STM32CubeMX currently exports build files for a few embedded-centric IDEs, which is not so helpful for people using gcc **from the command-line** or in my case, inside Emacs. I have added my own attempt at a CMake build script to handle generating a firmware binary, and flashing it to a development board using OpenOCD.

**CMakeLists.txt** here is the only noteworthy file; the generated firmware source code is simply convenient to test the build process with. Using this script with other targets should be a matter of using STM32CubeMX to generate code for your target, changing some file paths, and adjusting your compiler/linker flags.

# References

[STM32CubeMX](http://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-configurators-and-code-generators/stm32cubemx.html)

[NUCLEO-F042K6 development board](http://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-eval-tools/stm32-mcu-eval-tools/stm32-mcu-nucleo/nucleo-f042k6.html)

[OpenOCD](http://openocd.org/)

# License

MIT license unless designated otherwise. Generated files maintain their original licenses. Contributions welcome.
