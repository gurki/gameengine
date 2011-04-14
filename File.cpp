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
}

File::~File(void)
{
	if(data != 0)
	{
		delete[] data;

		data = 0;
	}
}

// methods
void File::LoadFromFile(const char* path)
{
	ifstream file;

	file.open(path, ios::in);

	if(file.good() == true)
	{
		file.seekg(0, ios::end);
		streamoff size = file.tellg();

		data = new char[(uint)size + 1];

		file.seekg(0, ios::beg);
		file.read(data, size);

		data[size] = '\0';

		int i = size;

		while(data[i] != '}')
		{
			i--;
		}

		data[i+1] = '\0';

		file.close();
	}
}

// getter
char* File::GetData(void) const
{
	return data;
}