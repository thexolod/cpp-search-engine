#pragma once

#include "RelativeIndex.h"

#include <vector>
#include <string>

class InvertedIndex;

class SearchServer{
public:
    /**
    * @param idx ссылка наиндекс документов
    * @param lim максимальное количество результатов для одного запроса
    */
    SearchServer(InvertedIndex& idx, int lim): _index(idx), _limit(lim){};

    /**
    * Метод обработки поисковых запросов
    * @param queries_input поисковые запросы взятые
    из файла requests.json
    * @return возвращает отсортированный список релевантных ответов для
    заданных запросов
    */
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);

private:
    int _limit;
    InvertedIndex& _index;
};


