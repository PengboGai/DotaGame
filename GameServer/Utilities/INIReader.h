#ifndef _UTILITIES_INI_READER_H_
#define _UTILITIES_INI_READER_H_

#include <string>

namespace Utilities {

class INIReader
{
public:
	INIReader(const std::string& path);
	~INIReader();

	void SetSection(const std::string& section_name) { m_section = section_name; }
	const std::string& GetSection() { return m_section; }

	std::string GetString(const std::string& key, const std::string& def = "");

	float GetFloat(const std::string& key, float def = 0.f);
	double GetDouble(const std::string& key, double def = 0.0);
	
	long GetInt32(const std::string& key, long def = 0);
	unsigned long GetUInt32(const std::string& key, unsigned long def = 0);
	
	long long GetInt64(const std::string& key, long long def = 0);
	unsigned long long GetUInt64(const std::string& key, unsigned long long def = 0);

private:
	std::string m_path;
	std::string m_section;
};

}; // namespace Utilities

#endif // _UTILITIES_INI_READER_H_