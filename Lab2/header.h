#pragma once

#include <iostream> 
#include <fstream> 
#include <string> 
#include <vector>
#include <unordered_map>
#include <map>
#include <sstream>
#include <filesystem>
#include <format>

template <typename Stream>
class redirect_stream_wrapper
{
    Stream& stream;
    std::streambuf* const old_buf;
public:
    redirect_stream_wrapper(Stream& src)
        :old_buf(src.rdbuf()), stream(src)
    {
    }

    ~redirect_stream_wrapper() {
        stream.rdbuf(old_buf);
    }
    void redirect(Stream& dest)
    {
        stream.rdbuf(dest.rdbuf());
    }
};

inline std::string input_string(std::istream& in)
{
    in.ignore(1000000, '\n');
    in >> std::ws;
    std::string str;
    std::getline(std::cin, str);
    std::cerr << str << std::endl;
    return str;
}

template <typename T>
T CorrectNumber(std::istream& in, T min, T max)
{
    T x;
    while ((in >> x).fail()
        || in.peek() != '\n'
        || x < min || x > max)
    {
        in.clear();
        in.ignore(10000, '\n');
        std::cout << "\nНеверный ввод" << std::endl;
        std::cout << "Доступные команды от " << min << " до " << max << std::endl;
    }

    std::cerr << x << std::endl;

    return x;
}




template <typename T>
std::vector<int> GetKeys(const std::unordered_map<int, T>& container)
{
    std::vector<int> keys;
    keys.reserve(container.size());
    int i = 0;
    for (auto& [id, element] : container)
        keys.push_back(id);
    return keys;
}
