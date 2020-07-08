set dir = "../week2"

if (! -d $dir) then
   echo $0\: $dir not a directory
   exit 1
endif

echo $dir\:
@ fcount = 0
@ dcount = 0

cd $dir
foreach file (*)
   if (-f $file) then
      @ fcount++
   else if (-d $file) then
      @ dcount++
   endif
end

echo $fcount files $dcount directories

if (-e $dir/a) then
	echo "Today is week4 second class" > $dir/a
endif
