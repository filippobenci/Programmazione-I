#C1 di seguito i comandi per verificare conformità ai test case allegati
./c1.out input1.csv 8 | diff - output1.txt
./c1.out input3.csv 8 | diff - output3.txt
./c1.out input4.csv 0 | diff - output4.txt
./c1.out input5.csv 0 | diff - output5.txt
./c1.out input2.csv 8 | diff - output2.txt
