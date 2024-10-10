echo ------------
echo COMPILING OS
echo ------------

sudo make

echo ---------
echo Finished!
echo ---------
read -p "Do you want to Start Bochs? (Y/n) " yn

case $yn in 
	y )
	echo -------------
	echo STARTING Bochs
	echo -------------
	sudo bochs -f bochs_config
	echo --------
	echo Finshed!
	echo --------

	;;
	n ) echo exiting...;
		exit;;
	* ) echo invalid response;
		exit 1;;
esac
