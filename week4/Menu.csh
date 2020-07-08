#!/bin/csh
# 사용법: menu.csh
# 메뉴에 따라 해당 명령어를 실행
echo "Let's make the Menu to control simple commands"
set file = `cat use.txt`
set i = 1
set stop = 0
while ($stop == 0)
	foreach line ("`cat use.txt`")
		echo $line
	end
	echo -n "input : "
	set reply = $<
	switch ($reply)
	case "d" :
		date "+%Y-%m-%d %H:%M:%S"
		echo ""
		breaksw
	case "l":
		ls
		echo ""
		breaksw
	case "w":		
		set SHELL_PATH = `pwd -P`
		echo $SHELL_PATH	
		echo ""
		breaksw
	case "q":
		echo "Quit the Menu"
		set stop = 1
		echo ""
		breaksw
	default:
		echo "Please enter the satisfied keys"
		echo ""
	endsw
end
