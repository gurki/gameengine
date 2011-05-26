//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#ifndef _FILE_H
#define _FILE_H

#include "Types.h"

#include <iostream>
#include <fstream>

using namespace std;

class File
{
	public:

		// constructors
		File(void);
		~File(void);

		// methods
		void LoadFromTextFile(const char* path);
		void LoadFromBinaryFile(const char* path);

		// getter
		char* GetData(void) const;
		uint GetSize(void) const;

	// protected:

		// variables
		char* data;
		uint size;
};

#endif
