# Practise-codes
1.	get a temperature as data from the user.(in Celcius)
2.	convert the temperature into bit stream.
3.	calculate the number of bits of the given temperature which will  be the DLC(data length) and append the temperature data(in bits) to it.
4.	Append ID=1011 to the previous data.
5.	Print the final bitstream
6.	Send it to a function 
7.	In that function check if the ID is 1011 , remove the ID and print the remaining data.
8.	Check the DLC with the number of bits of temperature(data) if true print “dlc is correct”, else print “wrong”
9.	Remove the dlc
10.	Convert the remaining data to Fahrenheit and print it. 
