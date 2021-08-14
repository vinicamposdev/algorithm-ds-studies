#include <iostream>
using namespace std;
// É necessário criar uma estrutura de dados contendo as palavras 
// que representam um dado número, podendo ser divididos em 
// grupos unitários, decimais, múltiplos de 10, potencias de 10. 
string one[] = { "", "one ", "two ", "three ", "four ",
				"five ", "six ", "seven ", "eight ",
				"nine ", "ten ", "eleven ", "twelve ",
				"thirteen ", "fourteen ", "fifteen ",
				"sixteen ", "seventeen ", "eighteen ",
				"nineteen " };

string ten[] = { "", "", "twenty ", "thirty ", "forty ",
				"fifty ", "sixty ", "seventy ", "eighty ",
				"ninety " };

string numToWords(int n, string s)
{
	string str = "";
	if (n > 19)
		str += ten[n / 10] + one[n % 10];
	else
		str += one[n];

	if (n)
		str += s;

	return str;
}

// Para cada iteração, se for descoberto que um dado número pertence a alguma desses grupos, é utilizado essa estrutura para traduzir a palavra referente ao dígito.
string convertToWords(long n)
{
	string out;

	out += numToWords(((n / 100000) % 100), "hundred ");

	out += numToWords(((n / 1000) % 100), "thousand ");

	out += numToWords(((n / 100) % 10), "hundred ");

	// se decide se vai colocar o conector a cada centena
	if (n > 100 && n % 100)
		out += "and ";

	out += numToWords((n % 100), "");

	return out;
}

void treatOutput(char **argv) {
	if (argv[1] && atoi(argv[1])) {
		if (atoi(argv[1]) <= 999999 && atoi(argv[1]) > 0) {
			int firstArgumentCommand = atoi(argv[1]);
			cout << convertToWords(firstArgumentCommand) << endl;
		} else {
			cout << "The information must be a Natural number in the range of 1-999999, please try again." << endl;
		}
	} else {
		cout << "Some number must be provided in the first argument, please try again." << endl;
	}
}

int main(int argc, char **argv)
{
	treatOutput(argv);

	return 0;
}
