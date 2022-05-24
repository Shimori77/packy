#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <algorithm>

#include <Bundle.hpp>

using namespace shimori::packy;

void Bundle::insertEntry(std::unique_ptr<Entry> &entry) {
    // TODO: Do not insert if a Entry with the same name already exists.
    this->_entries.push_back(std::move(entry));
}

void Bundle::saveBundle(const Bundle& bundle, const std::string &filePath) {
    std::ofstream outFile;
    outFile.open(filePath, std::ios::binary | std::ios::out | std::ios::trunc);

    if (!outFile.is_open()) {
        throw std::runtime_error("Unable to open file: '" + filePath + "'!");
    }

    uint64_t entryCount = bundle.getEntries().size();
    outFile.write(reinterpret_cast<char *>(&entryCount), sizeof(uint64_t));
    outFile.flush();

    char eol = '\0';

    std::for_each(bundle.getEntries().cbegin(),
                  bundle.getEntries().cend(),
                  [&eol, &outFile] (const std::unique_ptr<Entry> &entry) {
        uint16_t type = entry->getEntryType();
        uint64_t nameSize = entry->getEntryName().size();
        uint64_t dataSize = entry->getData().size();

        outFile.write(reinterpret_cast<char *>(&type), sizeof(uint16_t));
        outFile.write(reinterpret_cast<char *>(&nameSize), sizeof(uint64_t));
        outFile.write(reinterpret_cast<char *>(&dataSize), sizeof(uint64_t));

        outFile.write(entry->getEntryName().c_str(), (long) entry->getEntryName().size());
        outFile.write(&eol, 1);
        outFile.write(reinterpret_cast<const char *>(entry->getData().data()), (long) entry->getData().size());

        outFile.flush();
    });

    outFile.close();
}

Bundle Bundle::loadBundle(const std::string &filePath) {
    std::ifstream inFile;
    inFile.open(filePath, std::ios::binary | std::ios::in | std::ios::ate);

    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open file '" + filePath + "'!");
    }

    uint64_t entryCount;

    inFile.seekg(0, std::ios::beg);
    inFile.read(reinterpret_cast<char *>(&entryCount), sizeof(uint64_t));

    std::vector<std::unique_ptr<Entry>> entries(entryCount);

    for (uint64_t i = 0; i < entryCount; i++) {
        uint16_t type;
        uint64_t nameSize, dataSize;

        inFile.read(reinterpret_cast<char *>(&type), sizeof(uint16_t));
        inFile.read(reinterpret_cast<char *>(&nameSize), sizeof(uint64_t));
        inFile.read(reinterpret_cast<char *>(&dataSize), sizeof(uint64_t));

        char name[nameSize];
        std::vector<uint8_t> data(dataSize);

        inFile.read(name, (long) nameSize + 1);
        inFile.read(reinterpret_cast<char *>(data.data()), (long) dataSize);

        auto* entry = new Entry(static_cast<EntryType>(type), std::string(name), data);
        std::unique_ptr<Entry> entryPtr(entry);
        entries[i] = (std::move(entryPtr));
    }

    return Bundle(entries);
}
