#!/bin/csh
echo "Program to find Factorial"

set flag = 1
set fact = 1
while(1)
	echo ""	
	echo -n "Input : "	
	set input = $<

	if ($input == 0) then
		echo "quit"
		break
	endif

	while ( $input > 1 )
	  @ fact=$fact * $input  #fact = fact * num
	  @ input=$input - 1      #num = num - 1
	end

	echo $fact
end
