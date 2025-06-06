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
read -p "Do you want to make to make image bootable? [Requires sudo] (y/n) " yn 
case $yn in
	y)
	echo ----------------
	echo Installing GRUB!
	echo ----------------

	sudo losetup -d /dev/loop500
	sudo losetup /dev/loop500 build/main.img
	sudo grub-install \
		--modules="part_msdos" \
		--boot-directory=build/mnt/boot \
		--target=i386-pc \
		--bootloader-id=GRUB \
		/dev/loop500 -v
	sudo losetup -d /dev/loop500

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

