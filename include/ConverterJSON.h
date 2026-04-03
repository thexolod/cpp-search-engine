#pragma once

#include "RelativeIndex.h"

#include <vector>
#include <string>

class ConverterJSON{
public:
    ConverterJSON() = default;
    /**
    * Метод получения содержимого файлов
    * @return Возвращает список с содержимым файлов перечисленных
    * в config.json
    */
    std::vector<std::string> getTextDocuments();

    /**
    * Метод считывает поле max_responses для определения предельного
    * количества ответов на один запрос
    * @return возвращает максимальное количество
    * результатов для одного запроса
    */
    int getResponsesLimit();

    /**
    * Метод получения запросов из файла requests.json
    * @return возвращает список запросов из файла requests.json
    */
    std::vector<std::string> getRequests();

    /**
    * Положить в файл answers.json результаты поисковых запросов
    * @param answers вектор результатов, где для каждого запроса
    * содержится список документов с их релевантностью
    */
    void putAnswers(const std::vector<std::vector<RelativeIndex>>& answers);
};