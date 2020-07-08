#!/bin/csh

echo "Program to find Fibonacci Series"
while(1)
	echo ""
	echo -n "Input : "
	set input = $<

	set x = 0
	set y = 1
	set i = 2
	
	if ($input == 0) then
		echo "quit"
		break
	endif

	echo "Fibonacci Series up to $ input terms:"
	echo -n "$y "
	

	while ($i <= $input)
		@ i=$i + 1
		@ z=`expr $x + $y`
		echo -n "$z "
		@ x=$y
		@ y=$z
	end
	echo ""
end

