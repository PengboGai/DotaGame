#include <sys/stat.h>
#include <sys/types.h>
#include "File.h"

namespace Utilities {

File::File(const std::string& path)
: m_file(nullptr)
{
	Open(path, "rb");
}

File::File(const std::string& path, const std::string& mode)
: m_file(nullptr)
{
	Open(path, mode);
}

File::~File()
{
	Close();
}

bool File::Open(const std::string& path, const std::string& mode)
{
	if (m_path == path && m_mode == mode) {
		return false;
	}

	Close();
	m_path = path;
	m_mode = mode;

#ifdef _WIN32
	if (fopen_s(&m_file, path.c_str(), mode.c_str()))
		m_file = nullptr;
#else
	m_file = fopen(path.c_str(), mode.c_str());
#endif

	return m_file ? true : false;
}

void File::Close()
{
	if (m_file) {
		fclose(m_file);
		m_file = nullptr;
	}
}

bool File::Seek(size_t offset, SeekOrigin origin)
{
	return !!fseek(m_file, offset, (int)origin);
}

size_t File::Position()
{
	return ftell(m_file);
}

off_t File::Length()
{
	if (m_path.empty()) {
		return 0;
	}
	struct stat st;
	if (stat(m_path.c_str(), &st) == -1) {
		return 0;
	}
	return st.st_size;
}

int File::ReadByte()
{
	return fgetc(m_file);
}

bool File::ReadLine(char* buf, size_t count)
{
	return fgets(buf, count + 1, m_file) != nullptr;
}

size_t File::Read(char* buf, size_t offset, size_t count)
{
	size_t r = 0;
	if (m_file) {
		Seek(offset, SeekOrigin::BEGIN);
		r = fread(buf, 1, count, m_file);
	}
	return r;
}

int File::WriteByte(int byte)
{
	return fputc(byte, m_file);
}

bool File::WriteLine(const char* buf)
{
	return fputs(buf, m_file) != File::EOF;
}

size_t File::Write(const char* buf, size_t offset, size_t count)
{
	size_t r = 0;
	if (m_file) {
		Seek(offset, SeekOrigin::BEGIN);
		r = fwrite(buf, count, 1, m_file);
	}
	return r;
}

bool File::Flush()
{
	return fflush(m_file) != File::EOF;
}

} // namespace Utilities