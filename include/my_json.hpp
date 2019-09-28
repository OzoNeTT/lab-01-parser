// Copyright 2018 Your Name <your_email>

#pragma once

#include <string>
#include <experimental/any>
#include <vector>
#include <map>
#include <exception>

class WrongJson:public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

using namespace std::experimental;

class Json {
public:
    // Пустой конструктор
    Json() = default;
    // Конструктор из строки, содержащей Json-данные.
    Json(const std::string& s);
    // Метод возвращает true, если данный экземпляр содержит в себе JSON-массив. Иначе false.
    bool is_array() const;
    // Метод возвращает true, если данный экземпляр содержит в себе JSON-объект. Иначе false.
    bool is_object() const;

    bool is_empty() const;

    size_t GetArrSize() const;

    // Метод возвращает значение по ключу key, если экземпляр является JSON-объектом.
    // Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
    // Если экземпляр является JSON-массивом, генерируется исключение.
    any& operator[](const std::string& key);

    // Метод возвращает значение по индексу index, если экземпляр является JSON-массивом.
    // Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
    // Если экземпляр является JSON-объектом, генерируется исключение.
    any& operator[](int index);

    // Метод возвращает объект класса Json из строки, содержащей Json-данные.
    static Json parse(const std::string& s);

    // Метод возвращает объекта класса Json из файла, содержащего Json-данные в текстовом формате.
    static Json parseFile(const std::string& path_to_file);

private:
    std::vector<any> GetArray(const std::string & s, int start) const;
    std::map<std::string, any> GetMap(const std::string & s, int start) const;

    std::vector<any> _arr;
    std::map<std::string, any> _obj;
    bool _isArray;
};

