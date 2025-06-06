# Nanite
![GitHub Issues or Pull Requests by label](https://img.shields.io/github/issues/PKM74/Nanite)
![GitHub Commits](https://img.shields.io/github/commit-activity/t/PKM74/Nanite)
![language count](https://img.shields.io/github/languages/count/PKM74/Nanite)
![top language](https://img.shields.io/github/languages/top/PKM74/Nanite)
![repo size](https://img.shields.io/github/repo-size/PKM74/Nanite)
![license](https://img.shields.io/github/license/PKM74/Nanite)

A Very small OS that can run on X86 Hardware.

Good luck figuring out the spagetti code i write... (sorry not sorry ;D)

Designed for older computers such as a Pentium (i586) Class Machine. I however would recomend atleast a Pentium 2 Class System or higher.

## Features
- Support for the GNU GRUB 2 Bootloader and Multiboot V2
- Custom Theme for GRUB (Coming Soon!)
- Basic Memory Paging
- Support for Floppy Disk Drives (FDDs)
- Basic Serial (RS-232) Support
- Keyboard Input

Note: Kernel is currently under very heavy development.
All things are subject to change at any time.

## Building
Run `./build.sh` inside main directory of repo

To write to a disk, use `./write.sh` WARNING: **is hard coded to /dev/sdb** (sorry i suck at scripting)

You could also run `make all` but the scripts a bit better tbh, it even automates starting QEMU.

### Build Requirements
- make
- gcc (or really any C compiler)
- nasm

#### Image Only

- grub2
- parted

## How is Testing Done
Testing is mostly done with QEMU These days, but I do sometimes pull out my Dell Latitude D610 to test on (for anyone wondering its completely maxed out. [2GB of ram Pentium M @ 2.23GHz])

## Thanks! 
Resources I've Used Throughout the Project
- Nanobyte's Youtube Channel: https://www.youtube.com/@nanobyte-dev
- OSDEV Wiki: https://wiki.osdev.org/Expanded_Main_Page
- BrokenThorn: http://www.brokenthorn.com

And thanks to some of my favorite bands for some nice ass music!
- King Gizzard and The Lizzard Wizzard
- Nine Inch Nails
- The Strokes

(and if your wondering, yes im a massive nerd about music)