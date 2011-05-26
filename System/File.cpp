//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "File.h"


// constructors
File::File(void)
{
	data = 0;
	size = 0;
}

File::~File(void)
{
	if(data != 0)
	{
		delete[] data;

		data = 0;
	}

	size = 0;
}

// methods
void File::LoadFromTextFile(const char* path)
{
	ifstream file;

	file.open(path, ios::in);

	if(file.good() == true)
	{
		this->~File();

		file.clear();
		file.seekg(0, ios::end);
		
		size = (uint)file.tellg();
		data = new char[size + 1];

		file.clear();
		file.seekg(0, ios::beg);
		file.read(data, size);
		file.close();

		data[size] = '\0';
	}
}

void File::LoadFromTextFile(const char* path)
{
	ifstream file;

	file.open(path, ios::in | ios::binary);

	if(file.good() == true)
	{
		this->~File();

		file.clear();
		file.seekg(0, ios::end);
		
		size = (uint)file.tellg();
		data = new char[size];

		file.clear();
		file.seekg(0, ios::beg);
		file.read(data, size);
		file.close();
	}
}

// getter
char* File::GetData(void) const
{
	return data;
}

uint File::GetSize(void) const
{
	return size;
}