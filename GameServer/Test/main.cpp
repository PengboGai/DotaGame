#include <iostream>

#include "Convert.h"
#include "Debug.h"
#include "File.h"
#include "INIReader.h"
#include "StringTool.h"
using namespace Utilities;

int main()
{
	std::string s = Utilities::Convert::ToString(1231);
	std::cout << s.c_str() << std::endl;

	Debug::EchoInfo("sdfsdfsdfs");

	// Debug::Log("");

	getchar();
	return 0;
}