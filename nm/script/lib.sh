for file in `find /Applications -name '*.dylib'`                                                                                                                                                                   ygarrot@e3r7p1
do
nm $file >>their && ./ft_nm $file >> mine
done
