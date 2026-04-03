#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <cstddef>

struct Entry{
    std::size_t doc_id, count;
    Entry(std::size_t doc_id, std::size_t count): doc_id(doc_id), count(count) {}
};

class InvertedIndex {
public:
    InvertedIndex() = default;

    /**
    * Обновить или заполнить базу документов, по которой
    * будем совершать поиск
    * @param input_docs содержимое документов
    */
    void updateDocumentBase(const std::vector<std::string>& input_docs);

    /**
    * Метод определяет количество вхождений слова word в
    загруженной базе документов
    * @param word слово,частоту вхождений которого необходимо определить
    * @return возвращает подготовленный список с частотой слов
    */
    std::vector<Entry> getWordCount(const std::string& word) const;

private:
    std::mutex _index_mutex;
    std::vector<std::string> _docs; // список содержимого документов
    std::unordered_map<std::string,std::vector<Entry>> _freq_dictionary; //частотный словарь
};