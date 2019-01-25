mkdir /tmp/log
rm t t2
for file in `find /usr/bin` 
	#`find /Applications -type f -name '*.dylib'`;
do
	./ft_nm $file > t2 
	nm $file >t
	diff=`diff t t2`
	# echo $diff
	if [ ! -z "$diff" -a "$diff" != " " ]; then
		echo $diff > /tmp/log/$file.log
	fi
done
