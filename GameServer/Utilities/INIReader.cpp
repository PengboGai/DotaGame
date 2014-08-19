#include "INIReader.h"
#include "Convert.h"

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

namespace Utilities {

INIReader::INIReader(const std::string& path)
: m_path(path)
{
}

INIReader::~INIReader()
{
}

std::string INIReader::GetString(const std::string& key, const std::string& def)
{
	std::string output;
#ifdef _WIN32
	char* tmp = new char[100];
	memset(tmp, 0, 100);
	GetPrivateProfileString(m_section.c_str(), key.c_str(), def.c_str(), tmp, 100, m_path.c_str());
	output = tmp;
	delete[] tmp;
#endif // _WIN32

	return output;
}

float INIReader::GetFloat(const std::string& key, float def)
{
	return Convert::ToFloat(GetString(key, Convert::ToString(def)));
}

double INIReader::GetDouble(const std::string& key, double def)
{
	return Convert::ToDouble(GetString(key, Convert::ToString(def)));
}

long INIReader::GetInt32(const std::string& key, long def)
{
	return Convert::ToInt32(GetString(key, Convert::ToString(def)));
}

unsigned long INIReader::GetUInt32(const std::string& key, unsigned long def)
{
	return Convert::ToUInt32(GetString(key, Convert::ToString(def)));
}

long long INIReader::GetInt64(const std::string& key, long long def)
{
	return Convert::ToInt64(GetString(key, Convert::ToString(def)));
}

unsigned long long INIReader::GetUInt64(const std::string& key, unsigned long long def)
{
	return Convert::ToUInt64(GetString(key, Convert::ToString(def)));
}

} // namespace Utilities