#include "lib/writer/Writer.hh"

#include <fstream>

void Writer::write(const Data& data)
{
    std::ofstream file;
    file.open(data.filename());
    file.write(data.access(), data.size());
    file.close();
}
