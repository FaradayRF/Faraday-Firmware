# Faraday Firmware Readme

This repository holds the main firmware for the CC430 base Farady digital radio. This main repository contains the most up-to-date and feature rich variant of the codebase. Smaller repositories may exist that focus on more specific optimizations or uses of the digital radio.

## Firmware Operation Overview

TBD - Information overviewing the functions of the firmware.

## Texas Instruments Code Composer Studio

Initial developement is being performed in the Code Composer Studio IDE provided by Texas Instruments. At initial release the proprietary compiler is being used although a significant goal for the project is to move the codebase to the open source GCC base MSP430 compiler. This should be simple but will require proper setup of linking and other configurations to ensure the program compiles efficiently without unneeded or redundantly linked files causes the binary to become extreamly large.


## Licensing

The Faraday digital radio firmware is licensed under GPLv3 with a few minor additions specified. Please read the licensing informition provided in the repository for details.

#Resources
Below are resources that are useful for programing, testing, and otherwise developing the embedded C code for the Faraday digital radio.

##  Texas Instruments Code Composer

* [Code Composer Download](http://www.ti.com/tool/ccstudio)
* [Code Composer Files - Source Control Information](http://processors.wiki.ti.com/index.php/Source_control_with_CCS)
  * Which files from a code composer studio project to include in a source control repository. Binaries and other files that may not be ideal for source control are specified.
* [Git Ignore Templates](https://github.com/github/gitignore)
* [Git Ignore Directories](http://stackoverflow.com/questions/343646/ignoring-directories-in-git-repos-on-windows)

