#include "ConverterJSON.h"
#include "nlohmann/json.hpp"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

std::vector<std::string> ConverterJSON::getTextDocuments(){
    std::ifstream config_file("config.json");

    if (!config_file.is_open())
        throw std::runtime_error("Error opening file: config.json");

    std::vector<std::string> text_documents;
    nlohmann::json json;
    config_file >> json;

    if (json.find("files") == json.end() || !json["files"].is_array())
        throw std::runtime_error("config.json error!");

    for (const auto& file_path : json["files"]) {
        std::string cur_path = file_path.get<std::string>();
        std::ifstream file_read(cur_path);

        if (!file_read.is_open())
            throw std::runtime_error("Error opening file: " + cur_path);

        std::stringstream ss;
        ss << file_read.rdbuf();
        text_documents.emplace_back(ss.str());
    }

    return text_documents;
}


int ConverterJSON::getResponsesLimit(){
    std::ifstream config_file("config.json");

    if (!config_file.is_open())
        throw std::runtime_error("Error opening file: config.json");

    nlohmann::json json;
    config_file >> json;

    auto config = json.find("config");
    if (config == json.end() || !config->is_object())
        throw std::runtime_error("config.json error!");

    auto max_responses_iterator = config->find("max_responses");
    if (max_responses_iterator == config->end() || !max_responses_iterator->is_number_integer())
        return 5;

    return max_responses_iterator->get<int>();
}


std::vector<std::string> ConverterJSON::getRequests(){
    std::ifstream requests_file("requests.json");

    if (!requests_file.is_open())
        throw std::runtime_error("Error opening file: requests.json");

    nlohmann::json json;
    requests_file >> json;

    if (json.find("requests") == json.end() || !json["requests"].is_array())
        throw std::runtime_error("requests.json error!");

    std::vector<std::string> requests;
    for (const auto& request : json["requests"])
        requests.emplace_back(request.get<std::string>());

    return requests;
}

void ConverterJSON::putAnswers(const std::vector<std::vector<RelativeIndex>>& answers){
    std::ofstream answers_file("answers.json");

    if (!answers_file.is_open())
        throw std::runtime_error("Error opening file: answers.json");

    nlohmann::json json;
    json["answers"] = nlohmann::json::object();
    int i = 1;
    for (const auto& answer : answers) {
        std::ostringstream ss;
        ss << "request" << std::setw(3) << std::setfill('0') << i++;
        std::string request_id = ss.str();

        json["answers"][request_id] = nlohmann::json::object();
        json["answers"][request_id]["result"] = !answer.empty();
        if (!answer.empty()) {
            json["answers"][request_id]["relevance"] = nlohmann::json::array();

            for (const auto& [doc_id, rank] : answer)
                json["answers"][request_id]["relevance"].push_back({{"docid", doc_id}, {"rank", rank}});
        }
    }

    answers_file << json.dump(4);
}

