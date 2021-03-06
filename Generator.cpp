#include"stdafx.h"
#include <vector>
#include <string>
#include <iostream>


using namespace std;


string Xor(string in1, string in2) {
	string output;
	for (int i = 0; i < in2.length(); i++) {
		if (in1[i] == in2[i]) {
			output = output + "0";
		}
		else {
			output = output + "1";
		}
	}
	return output;
}

string division(string td, string G) {
	int nbits = G.length();// Number of bits to be Xored at a time.

						   //znbits is a string that contains zeroes for every occurence of a character in nbits
	string znbits;
	for (int i = 0; i < nbits; i++) {
		znbits = "0" + znbits;
	}
	string temptd = td.substr(0, nbits);// Slicing the transmitted data to appropriate length for particular step

	while (nbits < td.length()) {
		//replace the transmitted data by the result  of Xor and pull 1 bit down
		if (temptd[0] == '1') {
			temptd = Xor(G, temptd) + td[nbits];
			temptd = temptd.substr(1, temptd.length());
		}

		//If the leftmost bit of the dividend(or the part used in each step) is 0,
		// the step cannot use the regular divisor; we need to divide by all zeroes
		else {
			temptd = Xor((znbits), temptd) + td[nbits];
			temptd = temptd.substr(1, temptd.length());
		}
		nbits += 1;//increment nbits to move further		
	}
	//For the last bits after we have exceeded G, we have to carry it out normally as increased value of nbits will cause an Index Out of Bounds.
	if (temptd[0] == '1') {
		temptd = Xor(G, temptd);
	}
	else {
		temptd = Xor((znbits), temptd);
	}


	string verificationcode = temptd.substr(1, temptd.length());
	return verificationcode;
}

string generator(string D, string G)
{
	string Padding, Rm; //check bits
	for (int i = 0; i < G.length() - 1; i++) {
		Padding = "0" + Padding;
	}
	string TransmittedData = D + Padding;
	Rm = division(TransmittedData, G);
	return Rm;
}

string verifier(string D, string G)
{
	string Rm = division(D, G);
	// cout << "remainder in verifier" << Rm << endl;
	for (int i = 0; i < Rm.length(); i++)
	{
		// cout << "Rm[i]" << Rm[i] << endl;
		if (Rm[i] == '1')
		{
			return "Wrong Data";
		}
		
	}
	return "Correct data";
}

string alter(string s, int num)
{
	if (s[num - 1] == '1')
		s[num - 1] = '0';
	else
		s[num - 1] = '1';

	return s;
}

int main()
{
	string D, G, Rm; //remainder in division operation
	int num;
	cout << "please enter data without padding: " << endl;
	cin >> D;
	cout << "please enter your polynomial: " << endl;
	cin >> G;
	Rm = generator(D, G);
	cout << Rm << endl;

	string verification = verifier(D + Rm, G);
	cout << verification << endl;

	
	
	cout << "original data = " << D + Rm << endl;
	cout << "please enter the bit you want to change: " << endl;
	cin >> num;
	string altered = alter(D + Rm, num);
	cout << "altered data = " << altered << endl;
	verification = verifier(altered, G);
	cout << verification << endl;
	system("pause");
	return 0;
}