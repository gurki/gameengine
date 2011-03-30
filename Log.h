//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#define Log CLog::GetInstance

class CLog
{
	public:

		void SetOutput(bool window, bool console, bool file);

	protected:

		bool window;
		bool console;
		bool file;

	public:
		
		// singleton
		static CLog& GetInstance(void) 
		{
			static CLog Singleton;
			return Singleton;
		};

	protected:

		CLog(void) {};
		CLog(CLog const&) {};
		CLog& operator = (CLog const&) { return *this; };
		~CLog(void) {};
};