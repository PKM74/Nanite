#!/bin/bash
echo --------
echo STARTING
echo --------
read -p "Do you want to clean old build files? (y/n) " yn

case $yn in 
	y )
	
	echo ---------------------------;
	echo Removing Old Build Files...;
	echo ---------------------------;

	make clean;
	echo -----;
	echo Done!;
	echo -----;
	;;
	n )
	echo ---------;
	echo Proceding;
	echo ---------;
	;;
esac
echo ------------
echo COMPILING OS
echo ------------

make -s

echo ---------
echo Finished!
echo ---------
read -p "Do you want to make to make a bootable image? [Requires sudo] (y/n) " yn 
case $yn in
	y)
	echo ----------------
	echo Installing GRUB!
	echo ----------------

	sudo losetup -d /dev/loop800
	dd if=/dev/zero of=build/main.img bs=512 count=50000
	mkdir -p build/mnt
	sudo losetup /dev/loop800 build/main.img
	sudo parted /dev/loop800 mktable msdos
	sudo parted /dev/loop800 mkpart primary fat16 2048s 100%
	sudo parted /dev/loop800p1 set 1 boot on
	sudo mkfs.fat -F16 /dev/loop800p1
	sudo mount /dev/loop800p1 build/mnt
	sudo mkdir build/mnt/boot
	sudo mkdir build/mnt/boot/grub
	sudo mkdir build/mnt/misc
	sudo mkdir build/mnt/misc/src
	sudo cp -r src/* build/mnt/src
	sudo cp -r grub/* build/mnt/grub
	sudo cp build/nanite.bin build/mnt/boot/nanite
	sudo grub-install \
		--modules="part_msdos" \
		--boot-directory=build/mnt/boot \
		--target=i386-pc \
		--bootloader-id=GRUB \
		/dev/loop800 -v
	sudo umount build/mnt
	sudo losetup -d /dev/loop800

	;;
	n ) echo exiting...;
		exit;;
	* ) echo invalid response;
		exit 1;;
esac
echo ---------
echo Finished!
echo ---------

read -p "Do you want to Start QEMU? (y/n) " yn

case $yn in 
	y )
	echo -------------
	echo STARTING QEMU
	echo -------------
	qemu-system-i386 \
	-chardev pty,id=serial1 \
	-serial mon:stdio \
	-serial chardev:serial1 \
	-audiodev pa,id=speaker \
	-machine pcspk-audiodev=speaker \
	-hda build/main.img \
	-m size=512M
	echo --------
	echo Finshed!
	echo --------

	;;
	n ) echo exiting...;
		exit;;
	* ) echo invalid response;
		exit 1;;
esac

