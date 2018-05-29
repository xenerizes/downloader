#include "lib/writer/Writer.hh"

#include <fstream>

Writer::Writer(std::string filename) : filename_(std::move(filename))
{
    file_.open(filename_);
}

void Writer::write(const Buffer& data)
{
    file_.write(data.data(), data.size());
}

void Writer::write(const char* data, size_t len)
{
    file_.write(data, len);
}

Writer::~Writer() { file_.close(); }
