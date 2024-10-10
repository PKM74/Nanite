echo ------------
echo COMPILING OS
echo ------------

sudo make

echo ---------
echo Finished!
echo ---------
read -p "Do you want to write the IMG to Floppy? (/dev/sdb) (Y/n) " yn

case $yn in 
	y )
	echo ---------------------
	echo Writing IMG to Floppy
	echo ---------------------

	sudo dd if=./build/main_floppy.img of=/dev/sdb

	echo ---------
	echo Finished!
	echo ---------

	;;
	n ) echo exiting...;
		exit;;
	* ) echo invalid response;
		exit 1;;
esac


