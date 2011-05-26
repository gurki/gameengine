//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Timer.h"
#include "Types.h"
#include <iostream>

using namespace std;

#define Log CLog::GetInstance()

class CLog
{
	SimpleSingleton(CLog);
};