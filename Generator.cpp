#include <vector>
#include <string>
#include <iostream>


using namespace std;


string xor (string in1, string in2) {
	string output  ;
	for (int i = 0; i < in2.length(); i++) {
		if (in1[i] == in2[i]){
			output = output + "0";
		}
		else {
			output = output + "1";
		}
	}
	return output;
}

string generator(string td, string G) {
	int nbits = G.length();// Number of bits to be XORed at a time.

	//znbits is a string that contains zeroes for every occurence of a character in nbits
	string znbits;
	for (int i = 0; i < nbits; i++) {
		znbits="0"+znbits;
	}
	string temptd = td.substr(0, nbits);// Slicing the divident to appropriate length for particular step

	while (nbits < td.length()) {
		//replace the transmitted data by the result  of XOR and pull 1 bit down
		if (temptd[0] == '1') {
			temptd = xor(G, temptd) + td[nbits];
			temptd = temptd.substr(1, temptd.length());
		}

		//If the leftmost bit of the dividend(or the part used in each step) is 0,
		// the step cannot use the regular divisor; we need to divide by all zeroes
		else {
			temptd = xor((znbits), temptd) + td[nbits];
			temptd = temptd.substr(1, temptd.length());
		}
		nbits += 1;//increment nbits to move further		
	}
	//For the last bits after we have exceeded G, we have to carry it out normally as increased value of nbits will cause an Index Out of Bounds.
	if (temptd[0] == '1') {
		temptd = xor(G, temptd);
	}
	else {
		temptd = xor((znbits), temptd);
	}


	string verificationcode = temptd.substr(1, temptd.length());
	return verificationcode;
}




int main()
{
	string D;
	string G;
	string Padding; //check bits
	string Rm; //remainder in division operation

	cin >> D;
	cin >> G;
		
	for (int i = 0; i < G.length()-1; i++) {
		Padding = "0"+Padding;
	}
	
	string TransmittedData = D + Padding;
	
	Rm = generator(TransmittedData, G);
	cout << Rm;
	
	system("pause");
    return 0;
}
