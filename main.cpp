#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class matrix
{
public:
	int magic_number = 0;
	unsigned char type_of_data = '\0';
	unsigned char number_of_dimensions = '\0';


	matrix()
	{

	}

	~matrix()
	{

	}
};

int main()
{
	ifstream file;
	file.open("IDX/test-images.idx3-ubyte", ios::binary);

	if (!file.is_open())
	{
		cout << "Oh no! I couldn't open this file! :c\n";
	}

	// Read this file into a vector of unsigned chars
	vector<unsigned char> bytes;
	char byte;
	while (!file.eof())
	{
		file.read(&byte, 1);
		bytes.push_back((unsigned char)byte);
	}

	cout << "The file has " << bytes.size() << " bytes.\n\n";
	
	for (int i = 0; i < 16; i++)
	{
		cout << (unsigned)bytes[i] << "\n";
		if ((i+1) % 4 == 0) { cout << "\n"; }
	}

	int* head = reinterpret_cast<int*>(&bytes[0]);
	for (int* ptr = head; ptr < head + 4; ptr++)
	{
		cout << *ptr << "\n";
	}

	return 0;
}