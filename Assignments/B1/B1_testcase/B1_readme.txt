# B1 di seguito i comandi per verificare conformità ai test case allegati
./b1.out matrice1.txt < input2.txt | diff - output1.txt
./b1.out matrice2.txt < input2.txt | diff - output2.txt
./b1.out matrice4.txt < input3.txt | diff - output4.txt
./b1.out matrice5.txt < input2.txt | diff - output5a.txt
./b1.out matrice5.txt < input4.txt | diff - output5b.txt
./b1.out matrice6.txt < input3.txt | diff - output6.txt
./b1.out matrice7.txt < input3.txt | diff - output7.txt
./b1.out matrice8.txt < input3.txt | diff - output8.txt
./b1.out matrice9.txt < input3.txt | diff - output9.txt
./b1.out matrice10.txt < input2.txt | diff - output10.txt
./b1.out matrice11.txt < input2.txt | diff - output11.txt
./b1.out matrice12.txt < input3.txt | diff - output12.txt
./b1.out matrice13.txt < input2.txt | diff - output13.txt
./b1.out matrice3.txt < input2.txt | diff - output3.txt