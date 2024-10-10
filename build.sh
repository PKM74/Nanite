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

	sudo make clean;
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

sudo make -s

echo ---------
echo Finished!
echo ---------
read -p "Do you want to Start QEMU? (y/n) " yn

case $yn in 
	y )
	echo -------------
	echo STARTING QEMU
	echo -------------
	sudo qemu-system-i386 -fda build/main_floppy.img
	echo --------
	echo Finshed!
	echo --------

	;;
	n ) echo exiting...;
		exit;;
	* ) echo invalid response;
		exit 1;;
esac
