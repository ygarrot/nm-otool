mkdir /tmp/log
mkdir /tmp/log/otool
rm t t2
	#`find /Applications -type f -name '*.dylib'`;
for file in `find /usr`;
do
	# base=$(basename $file)
	./ft_otool $file > t2 
	otool -t $file >t
	diff=`diff t t2`
	if [ ! -z "$diff" -a "$diff" != " " ]; then
		echo $file >> "/tmp/log/otool/summary"
		echo $diff >> "/tmp/log/otool/"$(basename $file)".log"
	fi
done
