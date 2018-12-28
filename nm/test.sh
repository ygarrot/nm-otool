for file in `find /Applications -name '*.dylib'`
do
	echo $file
	./ft_nm $file 2&>/dev/null
done
