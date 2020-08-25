#include "lib/writer/Writer.hh"

#include <fstream>

Writer::Writer(std::string filename) : filename_(std::move(filename))
{
    file_.open(filename_);
    if (!file_.is_open()) {
        throw std::runtime_error("Unable to write file " + filename);
    }
}

void Writer::write(const Buffer& data)
{
    file_.write(data.data(), data.size());
    file_.flush();
}

void Writer::write(const char* data, size_t len)
{
    file_.write(data, len);
    file_.flush();
}

Writer::~Writer() { file_.close(); }
