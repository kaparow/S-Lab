#pragma once

#include <iostream> 
#include <fstream> 
#include <string> 
#include <vector>
#include <unordered_map>
#include <map>
#include <list>

#include <Windows.h> 
#include <conio.h>
#include <sstream>
#include <filesystem>


template <typename T1, typename T2>
T1 CorrectNumber(T1 min, T2 max) {
    T1 x;
    while ((std::cin >> x).fail()
        || std::cin.peek() != '\n'
        || x < min || x > max)
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "\nНеверный ввод" << std::endl;
        std::cout << "Доступные команды от " << min << " до " << max << std::endl;
    }
    return x;
}

