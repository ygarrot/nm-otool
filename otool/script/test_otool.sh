mkdir /tmp/log
rm t t2
for file in `find /Applications -type f -name '*.dylib'`;
do
	# base=$(basename $file)
	./ft_otool $file > t2 
	otool -t $file >t
	diff=`diff t t2`
	if [ ! -z "$diff" -a "$diff" != " " ]; then
		echo "/tmp/log/"$(basename $file)".log"
		echo $diff >> "/tmp/log/"$(basename $file)".log"
	fi
done
