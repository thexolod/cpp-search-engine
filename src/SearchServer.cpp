#include "SearchServer.h"
#include "InvertedIndex.h"

#include <sstream>
#include <map>
#include <set>
#include <algorithm>

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input) {
    std::vector<std::vector<RelativeIndex>> result;

    for (const auto& request : queries_input) {
        std::vector<RelativeIndex> cur_res;
        std::stringstream ss(request);
        std::set<std::string> unique_request; // уникальные слова

        {
            std::string temp;
            while (ss >> temp)
                unique_request.emplace(temp);
        }

        bool is_empty = false;
        std::map<std::size_t, std::size_t> docs;
        for (const auto& req : unique_request) { // перебираем все слова из одного запроса
            auto word_docs = _index.getWordCount(req);

            if (word_docs.empty()) { // если не нашли слово - пустой запрос
                is_empty = true;
                break;
            }

            decltype(docs) cur_doc;
            for (const auto& [doc, count] : word_docs) // строим doc_id -> count для текущего слова
                cur_doc.emplace(doc, count);

            if (docs.empty()) // первое слово запроса
                docs = std::move(cur_doc);

            else { // последующие слова запроса
                decltype(docs) to_docs;
                for (const auto& [doc, count] : docs)
                    if (cur_doc.find(doc) != cur_doc.end())
                        to_docs[doc] = count + cur_doc[doc];
                docs = std::move(to_docs);
            }

            if (docs.empty()) {
                is_empty = true;
                break;
            }
        }

        if (!is_empty) {
            std::size_t max_sum = std::max_element(docs.begin(), docs.end(),[](const std::pair<std::size_t, std::size_t>& a, const std::pair<std::size_t, std::size_t>& b) {
                return a.second < b.second;
            })->second;

            for (const auto& [doc, count] : docs) {
                float rank = 1. * count / max_sum;
                cur_res.emplace_back(RelativeIndex{doc, rank});
            }
        }

        std::sort(cur_res.begin(), cur_res.end(), [](const RelativeIndex& a, const RelativeIndex& b) {
            return a.rank > b.rank;
        });

        if (cur_res.size() > _limit)
            cur_res.resize(_limit);

        result.emplace_back(cur_res);
    }

    return result;
}
