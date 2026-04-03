# Search Engine (C++)

Простой поисковый движок на C++, реализующий поиск по текстовым документам с использованием инвертированного индекса.
## Как запустить

1. Склонировать репозиторий
```
git clone https://github.com/thexolod/cpp-search-engine
cd cpp-search-engine
```
2. Собрать проект
```
mkdir build
cd build
cmake ..
cmake --build .
```  
3. Запустить

Linux / Mac
```
./build/search_engine
```
Windows(PowerShell)
```
.\build\Debug\search_engine.exe
```
## Формат входных данных

### config.json
```json
{
  "config": {
    "name": "search_engine",
    "version": "1.0",
    "max_responses": 5
  },
  "files": [
    "resources/file1.txt",
    "resources/file2.txt"
  ]
}
```

### requests.json
```json
{
  "requests": [
    "search",
    "engine",
    "search engine",
    "test",
    "document",
    "someword"
  ]
}
```
## Результат

После запуска создаётся файл answers.json:
```json
{
    "answers": {
        "request001": {
            "relevance": [
                {
                    "docid": 0,
                    "rank": 1.0
                },
                {
                    "docid": 1,
                    "rank": 1.0
                }
            ],
            "result": true
        }
    }
}
```
## Как это работает

1. Загружаются документы из config.json
2. Строится инвертированный индекс
3. Обрабатываются запросы из requests.json
4. Для каждого документа считается релевантность
5. Результаты сортируются и записываются в answers.json
