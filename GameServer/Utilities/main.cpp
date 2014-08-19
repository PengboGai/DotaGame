#include <iostream>
#include "File.h"
#include "Convert.h"
#include "String.h"
#include "Debug.h"
#include "INIReader.h"
#include "Timer/Timer.h"
#include "Timer/TimerManager.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
	//=============================================================
	// File Demo
#if 0
	File wfile("c:\\1234.txt", "ab+");
	
	std::string wcontent = "This is a GPL licensed C++ class "
		"library wrapping the berkeley sockets C API, "
		"and therefore works on most unixes and also win32. "
		"The library is in use in a number of real world "
		"applications, both commercial and open source.";

	/* Write all data to the file */
	wfile.Write(wcontent.c_str(), 0, wcontent.size());
	wfile.Flush();

	/* Write a line to the file */
	wfile.WriteLine(wcontent.c_str());
	wfile.Flush();

	/* Write a byte to the file */
	for (unsigned int i = 0; i < wcontent.size(); ++i) {
		wfile.WriteByte(wcontent[i]);
	}
	wfile.Flush();
	
	File file("c:\\1234.txt");

	/* Read all data from the file */
	char* content = new char[file.Length() + 1];
	memset(content, 0, file.Length() + 1);
	file.Read(content, 0, file.Length());
	std::cout << content << std::endl;

	/* Read line from the file */
	char line[1024] = { 0 };
	while (file.ReadLine(line, sizeof(line))) {
		std::cout << line;
		memset(&line, 0, sizeof(line));
	}

	/* Read a byte from the file */
	int ch = file.ReadByte();
	while (ch != File::EOF) {
		std::cout << (char)ch;
		ch = file.ReadByte();
	}

	// Read Write JPG image
	File file("c:\\Android.jpg", "rb+");
	char* data = new char[file.Length()];
	file.Read(data, 0, file.Length());
	file.Flush();

	File wfile("C:\\1231.jpg", "wb+");
	wfile.Write(data, 0, file.Length());
	wfile.Flush();
#endif
	//=============================================================
	
	//=============================================================
	// Convert Demo
#if 0
	std::string a = Convert::ToString(12.f);
	std::string b = Convert::ToString(1231.0);
	std::string c = Convert::ToString(123U);
	std::string d = Convert::ToString(12);
	std::string e = Convert::ToString(1211L);
	std::string f = Convert::ToString(1211UL);
	std::string g = Convert::ToString(1211LL);
	std::string h = Convert::ToString(1211ULL);
#endif
	//=============================================================

	//=============================================================
	// INIReader Demo
	/*
		user.ini:
		[game]
		ip = 127.0.0.1
		port = 9000

		[login]
		ip = 127.0.0.1
		port = 9001


		[dbgame]
		host = 192.168.25.202
		user = root
		passwd = 123456
		name = slot
		connect = 2

		[gamelog]
		host = 192.168.25.202
		user = root
		passwd = 123456
		name = slot
	*/
#if 0
	INIReader reader("C:\\user.ini");
	reader.SetSection("game");
	std::string ip = reader.GetString("ip");
	long port = reader.GetInt32("port");
#endif
	//=============================================================

	//=============================================================
	// Timer Demo
#if 0
	TimerManager tm;

	Timer t1([](time_t dt) {
		std::cout << "t1 interval: " << dt << std::endl;
	}, 200, 3);
	Timer t2([](time_t dt) {
		std::cout << "t2 interval: " << dt << std::endl;
	}, 500, Timer::REPEAT_FOREVER);

	tm.AddTimer(&t1);
	tm.AddTimer(&t2);

	for (;;) {
		tm.Tick();
#ifdef _WIN32
		Sleep(1);
#endif
	}
#endif
	//=============================================================

	getchar();

	return 0;
}