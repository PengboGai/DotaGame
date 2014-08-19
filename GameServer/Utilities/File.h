#ifndef _UTILITIES_FILE_H_
#define _UTILITIES_FILE_H_

#include <stdio.h>
#include <string>

namespace Utilities {

enum class SeekOrigin
{
	BEGIN = 0,
	CURRENT,
	END
};

class File
{

#ifdef EOF
#undef EOF
#endif // EOF

public:
	const static int EOF = -1;

public:
	File(const std::string& path);
	File(const std::string& path, const std::string& mode);
	~File();

	/* Open file */
	bool Open(const std::string& path, const std::string& mode);

	/* Close the file */
	void Close();

	/* Set the stream position of the file */
	bool Seek(size_t offset, SeekOrigin origin);

	/* Get the stream position to the beginning of the file */
	size_t Position();

	/* Get the length of the file */
	off_t Length();

	/* Read a byte from the file */
	int ReadByte();

	/* Read a line from the file */
	bool ReadLine(char* buf, size_t count);

	/* Read the data from the file */
	size_t Read(char* buf, size_t offset, size_t count);

	/* Write a byte to the file */
	int WriteByte(int byte);

	/* Write a line to the file */
	bool WriteLine(const char* buf);

	/* Write the data to the file */
	size_t Write(const char* buf, size_t offset, size_t count);

	/* Clear the read write buffer, write the data to the file  */
	bool Flush();

private:
	File(const File&);
	File& operator=(const File&);

private:
	FILE* m_file;
	std::string m_path;
	std::string m_mode;
};

}; // namespace Utilities

#endif // _UTILITIES_FILE_H_