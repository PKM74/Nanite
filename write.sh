read -p "Do you want to write the IMG to A Disk? [Requires sudo] (y/n) " yn
	echo ------------
	echo COMPILING OS
	echo ------------

	make

	echo ---------
	echo Finished!
	echo ---------

	echo -------------------------
	echo Installing GRUB To Image!
	echo -------------------------

	sudo losetup -d /dev/loop800
	dd if=/dev/zero of=build/main.img bs=512 count=50000
	mkdir -p build/mnt
	sudo losetup -P /dev/loop800 build/main.img
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
	sudo cp -r grub/* build/mnt/boot/grub
	sudo cp build/nanite.bin build/mnt/boot/nanite
	sudo grub-install \
		--modules="part_msdos" \
		--boot-directory=build/mnt/boot \
		--target=i386-pc \
		--bootloader-id=GRUB \
		/dev/loop800 -v
	sudo umount build/mnt
	sudo losetup -d /dev/loop800

	echo ---------
	echo Finished!
	echo ---------



case $yn in 
	y )
	read -p "What Drive? (ex: /dev/sda) " disk
	echo ---------------------
	echo Writing IMG to Disk
	echo ---------------------

	sudo dd if=./build/main.img of=$disk status=progress

	echo ---------
	echo Finished!
	echo ---------

	;;
	n ) echo exiting...;
		exit;;
	* ) echo invalid response;
		exit 1;;
esac


