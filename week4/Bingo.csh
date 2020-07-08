#!/bin/csh
set num = (`/bin/bash -c 'echo $RANDOM'`)
@ new = $num % 100
echo "Choose the predicted number to get the answer"
set flag = 1
while($flag == 1)
	echo -n "input : "
	set input = $<

	if( $input < $new ) then
		echo "Higher than!"
		echo ""	
	else if ( $input > $new ) then
		echo "Lower than!"
		echo ""
	else if ( $input == $new ) then
		set flag=0
		echo "Bingo!"
	endif
end

