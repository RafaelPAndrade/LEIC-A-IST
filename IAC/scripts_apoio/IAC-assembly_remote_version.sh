#!/bin/bash
clear

$USERNAME = <istxxxxx>
$PATH_TO_FOLDER = xxx/xxx/x/xxxx

done=0
upload=0

echo "P3 assembly assistant"
echo

echo "Starting download of Project..."
scp $USERNAME@sigma.tecnico.ulisboa.pt:$PATH_TO_FOLDER/working.as .
echo


echo "File to operate (working.*) downloaded."
echo



while [ $done = 0  ] ; do

echo "Choose (wisely):"
echo "1-Edit"
echo "2-Assembler  (aka assembler-P3-linux)"
echo "3-Simulator  (aka p3sim.jar)"
echo "4-exit"
echo "5-Upload new file..."



echo -n "Choice:  "
read choice
echo

if [ "$choice" = "1" ] ; then
	nano working.as
fi

if [ "$choice" = "2" ] ; then
	~/bin/assembler-P3-linux working.as
	echo
fi

if [ "$choice" = "3" ] ; then
	xiwi -T java -jar ~/bin/p3sim.jar working.exe
	clear

fi

if [ "$choice" = "4" ] ; then
	echo -n 'Upload working.as?(y/n) '
	read upload
	if [ "$upload" = "y" ] ; then
		scp working.as $USERNAME@sigma.tecnico.ulisboa.pt:$PATH_TO_FOLDER/working.as
		echo "Upload complete!"
		echo "Don't forget to assemble in local machine"
	fi
	done=1
fi


if [ "$choice" = "5" ] ; then
	echo "To upload new file, it must be on current directory"
	echo -n "Name:(complete) "
	read NAME
	scp $NAME $USERNAME@sigma.tecnico.ulisboa.pt:$PATH_TO_FOLDER/working.as
	echo 'Done!'
	echo "Don't forget to assemble in local machine"
	done=1

fi

done

rm working.*




