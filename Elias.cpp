#include <iostream>
#include <string>
#include <vector>

using namespace std;

void SanitizeInput(string& input_string)
{
	while (input_string.find(' ') != string::npos) //пока есть в строке пробелы
		input_string.erase(input_string.find(' '), 1); //удаляем пробелы
}

vector<string>ParseElias(string normalized_elias) //разбиваем элиас по на числа в 2СС
{
	int leftBorder = 0;
	int rightBorder = 0;
	vector<string>parsed;

	while (rightBorder < normalized_elias.size())
	{
		if (normalized_elias[leftBorder] == '0') //пропускаем ведущие нули
			leftBorder++;
		else
		{
			int value_length = leftBorder - rightBorder + 1; //считаем длину числа
			rightBorder = leftBorder;
			leftBorder += value_length; //смещаем новую границу на конец числа
			string temp;

			while (value_length > 0)
			{
				temp.push_back(normalized_elias[rightBorder]);
				rightBorder++;
				value_length--;
			}
			parsed.push_back(temp);
		}
	}
	return parsed;
}

vector<int>GetDecimalElias(vector<string>p_elias) //2СС в 10СС, кодирование длинн серий
{
	vector<int> decimal;
	for (int i = 0; i < p_elias.size(); i++)
	{
		decimal.push_back(stoi(p_elias[i], nullptr, 2));
	}
	return decimal;
}

string GetBinaryEncodedString(vector<int> rle, int starting_bit)
{
	string binary_string = "";
	for (int i = 0; i < rle.size(); i++)
	{
		while (rle[i] > 0)
		{
			binary_string += starting_bit + '0';
			rle[i]--;
		}
		starting_bit ^= 1; //меняем стартовый бит через xor 0^1=1; 1^1=0
	}
	return binary_string;
}

void GetCharacters(string binary_string)
{
	for (int i = 0; i < binary_string.size(); i += 8)
	{
		string temp = binary_string.substr(i, 8);

		int ascii_value = stoi(temp, nullptr, 2);

		cout << char(ascii_value);
	}
}

int main()
{

	setlocale(LC_ALL, "");
	string elias_code;

	getline(cin, elias_code);

	SanitizeInput(elias_code);
	char starting_value = elias_code[0] - '0'; //получаем стартовый бит в виде числа 
	elias_code.erase(0, 1);

	vector<string> parsed_elias = ParseElias(elias_code);

	cout << "Elias parsed by numbers (binary): ";
	for (auto var : parsed_elias)
	{
		cout << var << " ";
	}
	cout << endl;

	vector<int> run_length = GetDecimalElias(parsed_elias);

	cout << "Run-length-code in decimal: ";
	for (auto var : run_length)
	{
		cout << var << " ";
	}
	cout << endl;

	string binary_encoded_string = GetBinaryEncodedString(run_length, starting_value);

	cout << "Binary encoded string: ";
	cout << binary_encoded_string;
	cout << endl;

	cout << "Answer: ";
	GetCharacters(binary_encoded_string);
	cout << endl;
}