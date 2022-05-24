#pragma once

#include <Entry.hpp>

namespace shimori::packy {
    /**
     * The Bundle class is as the name suggests a bundle of Entries.
     *
     * It stores all entries and the file itself starts with the amount of total entries.
     */
    class Bundle {
    private:
        std::vector<std::unique_ptr<Entry>> _entries;

    public:
        Bundle() = default;
        explicit Bundle(std::vector<std::unique_ptr<Entry>> &entries): _entries(std::move(entries)) {}

        /**
         * Insert a new entry into this bundle.
         *
         * @param entry Entry unique pointer to be inserted into the bundle.
         */
        void insertEntry(std::unique_ptr<Entry> &entry);

        [[nodiscard]] const std::vector<std::unique_ptr<Entry>>& getEntries() const {
            return _entries;
        }

        /**
         * Save a Bundle to a specific path into the filesystem.
         *
         * This will truncate a file that already exists.
         *
         * @param bundle Bundle to be saved.
         * @param filePath Path of the file in which the bundle will be saved.
         */
        static void saveBundle(const Bundle& bundle, const std::string& filePath);

        /**
         * Load a Bundle from the filesystem.
         *
         * This will throw an exception if no file can be found.
         *
         * @param filePath Path of the file which will be loaded.
         * @return A loaded Bundle.
         */
        static Bundle loadBundle(const std::string& filePath);
    };
}