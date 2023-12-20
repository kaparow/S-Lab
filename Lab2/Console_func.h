#pragma once

#include "CS.h"
#include "Pipe.h"
#include "header.h"

class TransportSystem
{

    std::unordered_map<int, Pipe> pipes;
    std::unordered_map<int, CS> stations;


public:

    TransportSystem();

    //void LogUserAction(const std::string& action, int ID);

    void InputPipe();
    void InputCS();


    void View();

    template <typename Struct>
    void ViewComponents(std::unordered_map<int, Struct>& conteiner)
    {
        int i = 1;
        for (auto& element : conteiner) {
            std::cout << i << ". ";
            i++;
            element.second.PrintInfo();
        }
    }

    template <typename Struct>
    void ViewComponentsByID(std::vector<int> IDs, std::unordered_map<int, Struct>& conteiner)
    {
        int i = 1;
        for (auto& id : IDs) {
            std::cout << i << ". ";
            i++;
            conteiner.at(id).PrintInfo();
        }
    }



    void Search();
    void SearchPipes();
    void SearchCS();


    void Edit();

    void EditPipes();
    void EditCS();

    void EditOnePipe();
    void EditOneCS();
    void EditSomePipes();
    void EditSomeCS();

    template <typename Struct>
    void EditOne(std::unordered_map<int, Struct>& structure)
    {
        auto keys = GetKeys(structure);
        int number = CorrectNumber<int>(std::cin, 1, keys.size()) - 1;
        structure[keys[number]].Edit();


    }



    void Delete();
    void DeletePipes();
    void DeleteStations();


    void DeletePipes(std::vector<int>& ids);
    void DeleteStations(std::vector<int>& ids);

    void DeleteSomePipes();
    void DeleteSomeStations();


    void Save();
    void Load();

};
