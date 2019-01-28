mkdir /tmp/log
mkdir /tmp/log/nm
rm t t2
#`find /Applications -type f -name '*.dylib'`;
for file in `find /usr`;
do
	./ft_nm $file > t2 
	nm $file >t
	diff=`diff t t2`
	if [ ! -z "$diff" -a "$diff" != " " ]; then
		echo $file >> "/tmp/log/nm/summary"
		echo $diff >> "/tmp/log/nm/"$(basename $file)".log"
	fi
done
