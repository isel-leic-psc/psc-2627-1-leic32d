
final.txt: dest1.txt dest2.txt
	cat dest1.txt dest2.txt > final.txt

dest1.txt: source1.txt
	tr '[:upper:]' '[:lower:]' < source1.txt > dest1.txt

dest2.txt: source2.txt
	nl -ba < source2.txt > dest2.txt

