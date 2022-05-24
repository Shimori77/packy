#pragma once

#include <string>
#include <vector>
#include <memory>

#include <EntryType.hpp>

namespace shimori::packy {
    /**
     * This class represents an Entry inside a bundle.
     *
     * An Entry is basically a file with some metadata as a header.
     */
    class Entry {
    private:
        EntryType _entryType;
        std::string _entryName;
        std::vector<uint8_t> _data;

    public:
        Entry(EntryType entryType, const std::string& entryName, std::vector<uint8_t>& data) {
            this->_entryType = entryType;
            this->_entryName = entryName;

            this->_data = std::move(data);
        }

        [[nodiscard]] EntryType getEntryType() const {
            return _entryType;
        }

        [[nodiscard]] const std::string& getEntryName() const {
            return _entryName;
        }

        [[nodiscard]] const std::vector<uint8_t>& getData() const {
            return _data;
        }
    };
}