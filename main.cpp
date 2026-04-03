#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"
#include <iostream>

int main() {
    ConverterJSON converter;

    try {
        auto docs = converter.getTextDocuments();

        InvertedIndex inverted_index;
        inverted_index.updateDocumentBase(docs);

        int limit = converter.getResponsesLimit();

        SearchServer server(inverted_index, limit);

        auto requests = converter.getRequests();

        auto answers = server.search(requests);

        converter.putAnswers(answers);
    }catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}