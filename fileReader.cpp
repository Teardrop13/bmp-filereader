#include <iostream>
#include <fstream>

using namespace std;

int getData(int byteNumber, int length, ifstream &ifs) {
	int data;
	ifs.seekg(byteNumber, ios::beg);
	ifs.read(reinterpret_cast<char *>(&data), length);
	ifs.seekg(0, ios::beg);
	return data;
}

int main() {
	ifstream fs_in;
	string filename;

	cout << "File name: "; cin >> filename;

	fs_in.open(filename, ios::binary);
	if (!fs_in) {
		cout << "input file error" << endl;
		return 1;
	}

	int bfOffBits = getData(10, 4, fs_in); // Picture data position, end of header
	int bFsize = getData(2, 4, fs_in); // File length
	int biHeight = getData(22, 4, fs_in);
	int pictureWidth = (bFsize - bfOffBits) / biHeight;

	fs_in.seekg(bfOffBits, ios::beg);

	int separator = 0;

	unsigned char byte;

	while (!fs_in.eof()) {
		for (int i = 0; i < pictureWidth; i++) {
			separator++;
			fs_in.read(reinterpret_cast<char *>(&byte), 1);
			cout << (int)byte << " ";
			if (separator == 3) {
				separator = 0;
				cout << "| ";
			}
		}
		cout << endl
			 << endl;
		separator = 0;
	}

	fs_in.close();
	return 0;
}