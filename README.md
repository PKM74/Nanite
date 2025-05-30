# Nanite
![GitHub Issues or Pull Requests by label](https://img.shields.io/github/issues/PKM74/Nanite)
![language count](https://img.shields.io/github/languages/count/PKM74/Nanite)
![top language](https://img.shields.io/github/languages/top/PKM74/Nanite)
![repo size](https://img.shields.io/github/repo-size/PKM74/Nanite)
![license](https://img.shields.io/github/license/PKM74/Nanite)

Very small OS that can run on X86 Hardware.
Designed to run from just one 1.44MB floppy disk, ATA support coming soon! (TM)

Good luck figuring out the spagetti code i write... (sorry not sorry ;D)

Designed for older computers such as a Pentium (i586) Class Machine. I would recomend atleast a Pentium 2 Class or higher system however.

## Features
A funtioning Bootloader and half working kernel.
Also some tools for the FAT filesystem (host system).
Kernel is currently under heavy development.

## How To Build
You Basically Run `./build.sh` to build it

If you wanted to write it to a floppy disk you can use `write.sh` tho be careful as the value for what drive it uses is hard coded as /dev/sdb

## How is Testing Done
Testing is mostly done with QEMU These days, but I do sometimes pull out my Dell Latitude D610 to test on (for anyone wondering its completely maxed out. [2GB of ram Pentium M @ 2.23GHz])

## Thanks! 
Nanobyte and the OSDEV wiki for providing resources for me to be able to make this.
- Nanobyte's Youtube Channel: https://www.youtube.com/@nanobyte-dev
- OSDEV Wiki: https://wiki.osdev.org/Expanded_Main_Page

And thanks to some of my favorite bands for some nice ass music!
- King Gizzard and The Lizzard Wizzard
- Nine Inch Nails
- The Strokes
(and if your wondering, yes im a massive nerd about music)