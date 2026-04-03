#include "InvertedIndex.h"

#include <sstream>
#include <thread>

void InvertedIndex::updateDocumentBase(const std::vector<std::string>& input_docs) {
    _freq_dictionary.clear();
    _docs.clear();

    for (const auto& cur_doc : input_docs)
        _docs.emplace_back(cur_doc);

    std::size_t i = 0;
    std::vector<std::thread> threads;
    for (const auto& doc : _docs) {
        threads.emplace_back([this](const std::string& doc, std::size_t i) {
            std::unordered_map<std::string, std::size_t> cur;
            std::stringstream ss(doc);
            std::string temp;

            while (ss >> temp)
                cur[temp]++;

            {
                std::lock_guard<std::mutex> lock(_index_mutex);
                for (auto [w, c] : cur)
                    _freq_dictionary[w].emplace_back(i, c);
            }
        }, doc, i);
        i++;
    }

    for (auto& t : threads)
        if (t.joinable())
            t.join();
}

std::vector<Entry> InvertedIndex::getWordCount(const std::string& word) const{
    auto word_find = _freq_dictionary.find(word);
    if (word_find == _freq_dictionary.end())
        return std::vector<Entry>{};

    return word_find->second;
}
