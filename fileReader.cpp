#include <iostream>
#include <fstream>

using namespace std;


int getData(int bit, int length, ifstream& ifs) {
	int data;
	ifs.seekg(bit, ios::beg);
	ifs.read(reinterpret_cast<char*>(&data), length);
	ifs.seekg(0, ios::beg);
	return data;
}

/*
Odczytanie poczatku danych obrazowych pliku. 4 bajty
*/
int readPictureDataPosition(ifstream& ifs) {
	return getData(10,4, ifs);
}


int readPictureWidth(ifstream& ifs) {
	return getData(18, 4, ifs);
}

int readPictureHeight(ifstream& ifs) {
	return getData(22, 4, ifs);
}

int readPictureBFsize(ifstream& ifs) {
	return getData(2, 4, ifs);
}


int main()
{
	ifstream fs_in;

	int pictureDataStart;
	
	string filename;
	cout << "File name: "; cin >> filename;

	fs_in.open(filename, ios::binary);
	if (!fs_in)
	{
		cout << "input file error" << endl;
		return 1;
	}	

	int picWidth = (readPictureBFsize(fs_in) - readPictureDataPosition(fs_in))/ readPictureHeight(fs_in); 
	
	pictureDataStart = readPictureDataPosition(fs_in);

	fs_in.seekg(pictureDataStart, ios::beg);

	int separator = 0;

	unsigned char byte;

	while (!fs_in.eof())
	{
		for(int i=0; i<picWidth; i++) {
			separator++;
			fs_in.read(reinterpret_cast<char*>(&byte), 1);
			cout << (int)byte << " ";
			if(separator == 3) {
				separator = 0;
				cout << "| ";
			}
		}
		cout << endl << endl;
		separator = 0;
	}

	fs_in.close();
	return 0;
}
