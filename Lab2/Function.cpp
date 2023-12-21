#pragma once

#include "Console_func.h"
#include "Pipe.h"
#include "CS.h"
#include "header.h"
#include <format>

using namespace std;


template <typename T1, typename T2>
using Filter = bool(*)(T1& element, T2 parametr);

template <typename T>
bool CheckByName(T& element, string name) {
    return (element.name.find(name) != string::npos);
}

bool CheckByStatus(Pipe& pipe, bool in_repairing) {
    return pipe.in_repairing == in_repairing;

}

bool CheckByWorkshop(CS& cs, int active) {
    return cs.workshops_in_operation == active;
}

template <typename T1, typename T2>
vector<int> Find_By_Filter(unordered_map<int, T1>& elements, Filter<T1, T2> filter, T2 parametr)
{
    vector<int> result;
    for (auto& element : elements)
    {
        if (filter(element.second, parametr)) result.push_back(element.second.ID);
    }

    return result;
}

TransportSystem::TransportSystem()
{}

/*void TransportSystem::LogUserAction(const std::string& action, int ID)
{
    std::ofstream logFile("user_actions_log.txt", std::ios::app);
    if (logFile.is_open())
    {
        logFile << "Действие: " << action << ", ID : " << ID << std::endl;
        logFile.close();
    }
    else
    {
        std::cerr << "Не удалось открыть файл для логирования." << std::endl;
    }
}*/

//---------------CREATE-------------------

void TransportSystem::InputPipe()
{
    Pipe pipe;
    pipe.InputInfo();
    pipes.insert({ pipe.GetID(), pipe });

    //int ID = pipe.GetID();
    //LogUserAction("Добавление трубы", ID);
}


void TransportSystem::InputCS()
{
    CS station;
    station.InputInfo();
    stations.insert({ station.GetID(), station });

    //int ID = station.GetID();
    //LogUserAction("Добавление кс", ID);
}

//---------------View-------------------


void TransportSystem::View()
{
    while (1) {

        cout << "0. Выход\n" <<
            "1. Список труб\n" <<
            "2. Список КС\n" <<
            "3. Список труб и КС" << endl;


        switch (CorrectNumber(cin, 0, 3)) {
        case 1: {

            cout << "Трубы: " << endl;
            ViewComponents<Pipe>(pipes);

            break;
        }
        case 2: {

            cout << "КС: " << endl;
            ViewComponents<CS>(stations);

            break;
        }

        case 3: {

            cout << "Трубы: " << endl;
            ViewComponents<Pipe>(pipes);

            cout << "КС: " << endl;
            ViewComponents<CS>(stations);


            break;
        }

        case 0: {
            return;
        }

        }
        return;
    }
}

//---------------SEARCH-------------------

template <typename Struct>
using Searching = vector<int>(*)(Struct& structure);

template <typename Struct>
vector<int> Search_By_Name(unordered_map<int, Struct>& structure)
{
    string name = input_string(cin);


    vector<int> result = Find_By_Filter<Struct, string>(structure, CheckByName, name);
    return result;
}

template <typename Struct>
vector<int> Search_By_Status(unordered_map<int, Struct>& structure)
{
    vector<int> result = Find_By_Filter<Struct, bool>(structure, CheckByStatus, CorrectNumber(cin, 0, 1));
    return result;
}

template <typename Struct>
vector<int> Search_By_Workshop(unordered_map<int, Struct>& structure)
{
    vector<int> result = Find_By_Filter<Struct, int>(structure, CheckByWorkshop, CorrectNumber(cin, 0, 1));
    return result;
}


void TransportSystem::Search()
{
    cout << "1. Поиск труб\n"
        << "2. Поиск станций\n"
        << "0. Выход" << endl;

    switch (CorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        SearchPipes();
        break;
    }
    case 2:
    {
        SearchCS();
        break;
    }
    case 0:
    {
        break;
    }
    }
}

void TransportSystem::SearchPipes()
{
    cout << "Выберете фильтр поиска:" <<
        "\n1.По имени" <<
        "\n2.По состоянию" << endl;
    switch (CorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        cout << "Введите имя трубы:" << endl;
        vector<int> result = Search_By_Name(pipes);

        if (!result.size())
        {
            cout << "Нет подходящих труб";
        }

        ViewComponentsByID(result, pipes);
        break;
    }
    case 2:
    {
        cout << "Введите состояние трубы:" << endl;
        vector<int> result = Search_By_Status(pipes);
        if (!result.size())
        {
            cout << "Нет подходящих труб";
            return;
        }
        ViewComponentsByID(result, pipes);
        break;
    }
    case 0:
    {
        break;
    }
    }
}

void TransportSystem::SearchCS()
{
    cout << "Выберете фильтр поиска:" <<
        "\n1.По имени" <<
        "\n2.По состоянию" << endl;
    switch (CorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        cout << "Введите имя станции:" << endl;
        vector<int> result = Search_By_Name(stations);
        if (result.size())
        {
            for (auto& id : result) stations.at(id).PrintInfo();

        }
        else cout << "Нет подходящих станций";
        break;
    }
    case 2:
    {
        cout << "Введите состояние станции:" << endl;
        vector<int> result = Search_By_Workshop(stations);
        if (result.size())
        {
            for (auto& id : result) stations.at(id).PrintInfo();
        }
        else cout << "Нет подходящих станций";
        break;
    }
    case 0:
    {
        break;
    }
    }
}



//---------------EDIT-------------------



void TransportSystem::Edit()
{
    cout << "1. Редактировать трубы\n"
        << "2. Редактировать станции\n"
        << "0. Выход" << endl;

    switch (CorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        EditPipes();
        break;
    }
    case 2:
    {
        EditCS();
        break;
    }
    case 0:
    {
        break;
    }
    }
}

void TransportSystem::EditPipes()
{
    if (!pipes.size())
    {
        cout << "Нет доступных труб!\n" << endl;
        return;
    }

    cout << "1. Редактировать одну трубу по выбору\n"
        << "2. Редактировать по фильтру\n"
        << "0. Выход" << endl;


    switch (CorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        EditOnePipe();
        break;
    }
    case 2:
    {
        EditSomePipes();
        break;
    }
    case 0:
    {
        break;
    }
    }

}
void TransportSystem::EditCS() {
    if (!stations.size()) {
        cout << "Нет доступных КС!\n" << endl;

        return;
    }

    cout << "1. Редактировать одну станцию по выбору\n"
        << "2. Редактировать по фильтру\n"
        << "0. Выход" << endl;

    switch (CorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        EditOneCS();
        break;
    }
    case 2:
    {
        EditSomeCS();
        break;
    }
    case 0:
    {
        break;
    }
    }

}


void TransportSystem::EditOnePipe()
{
    cout << "Трубы:\n";
    ViewComponents(pipes);
    cout << "Выберете редактируемую трубу:";

    EditOne(pipes);



}
void TransportSystem::EditOneCS()
{
    cout << "КС:\n";
    ViewComponents(stations);
    cout << "Выберете редактируемую кс:";
    EditOne(stations);
}


void TransportSystem::EditSomePipes()
{
    if (!pipes.size())
    {
        cout << "Нет доступных труб!";
        return;
    }

    cout << "Выберете фильтр поиска:" <<
        "\n1.По имени" <<
        "\n2.По состоянию" << endl;

    switch (CorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        cout << "Введите имя трубы:" << endl;
        vector<int> result = Search_By_Name(pipes);
        if (result.size())
        {
            for (auto& id : result) pipes.at(id).PrintInfo();
            cout << "Изменить состояние труб?(0 - нет, 1 - да)" << endl;
            int answer = CorrectNumber(cin, 0, 1);
            for (auto& id : result) {
                pipes.at(id).Edit(answer);

                //int ID = id;
                //LogUserAction("Редактирование трубы по имени ", ID);
            }


        }
        else cout << "Нет подходящих труб";
        break;
    }
    case 2:
    {
        cout << "Введите состояние трубы:" << endl;
        vector<int> result = Search_By_Status(pipes);
        if (result.size())
        {
            for (auto& id : result) pipes.at(id).PrintInfo();
            cout << "Изменить состояние труб?(0 - нет, 1 - да)" << endl;
            int answer = CorrectNumber(cin, 0, 1);
            for (auto& id : result) {
                pipes.at(id).Edit(answer);

                //int ID = id;
                //LogUserAction("Редактирование трубы по состоянию ", ID);
            }
        }
        else cout << "Нет подходящих труб";
        break;
    }
    case 0:
    {
        break;
    }
    }
}
void TransportSystem::EditSomeCS()
{
    if (!pipes.size())
    {
        cout << "Нет доступных кс!";
        return;
    }

    cout << "Выберете фильтр поиска:" <<
        "\n1.По имени" <<
        "\n2.По состоянию" << endl;

    switch (CorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        cout << "Введите имя станции:" << endl;
        vector<int> result = Search_By_Name(stations);
        if (result.size())
        {
            for (auto& id : result) stations.at(id).PrintInfo();
            cout << "Изменить количество активных цехов на:(0 - 50)" << endl;
            int answer = CorrectNumber(cin, 0, 50);
            for (auto& id : result) {
                stations.at(id).Edit(answer);

                //int ID = id;
                //LogUserAction("Редактирование кс по имени ", ID);
            }
        }
        else cout << "Нет подходящих кс";
        break;
    }
    case 2:
    {
        cout << "Введите количество активных цехов кс:" << endl;
        vector<int> result = Search_By_Workshop(stations);
        if (result.size())
        {
            for (auto& id : result) stations.at(id).PrintInfo();
            cout << "Изменить количество активных цехов на:(0 - 50)" << endl;
            int answer = CorrectNumber(cin, 0, 50);
            for (auto& id : result) {
                stations.at(id).Edit(answer);

                //int ID = id;
                //LogUserAction("Редактирование кс по состоянию ", ID);
            }
        }
        else cout << "Нет подходящих кс";
        break;
    }
    case 0:
    {
        break;
    }
    }
}

//---------------DELETE-------------------

void TransportSystem::Delete()
{
    cout << "1. Удаление труб\n"
        << "2. Удаление станций\n"
        << "0. Выход" << endl;

    switch (CorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        DeletePipes();
        break;
    }
    case 2:
    {
        DeleteStations();
        break;
    }
    case 0:
    {
        break;
    }
    }
}

void TransportSystem::DeletePipes()
{
    if (!pipes.size())
    {
        cout << "Нет доступных труб!\n" << endl;
        return;
    }

    cout << "1. Удалить одну трубу по выбору\n"
        << "2. Удалить по фильтру\n"
        << "0. Выход" << endl;


    switch (CorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        cout << "Список труб:\n";
        ViewComponents(pipes);
        auto keys = GetKeys(pipes);



        cout << "Удаляемую трубу:";
        DeletePipes(keys);
        break;
    }
    case 2:
    {
        DeleteSomePipes();
        break;
    }
    case 0:
    {
        break;
    }
    }
}

void TransportSystem::DeletePipes(std::vector<int>& ids)
{
    int number = CorrectNumber<int>(std::cin, 1, ids.size());
    pipes.erase(ids[number - 1]);

    //int ID = ids[number - 1];
    //LogUserAction("Удаление трубы", ID);
}

void TransportSystem::DeleteStations()
{
    if (!pipes.size())
    {
        cout << "Нет доступных станций!\n" << endl;
        return;
    }

    cout << "1. Удалить одну станцию по выбору\n"
        << "2. Удалить по фильтру\n"
        << "0. Выход" << endl;


    switch (CorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        cout << "Список станций:\n";
        ViewComponents(stations);
        cout << "Удаляемую станцию:";
        auto keys = GetKeys(stations);
        DeleteStations(keys);
        break;
    }
    case 2:
    {
        DeleteSomeStations();
        break;
    }
    case 0:
    {
        break;
    }
    }
}

void TransportSystem::DeleteStations(std::vector<int>& ids)
{
    int number = CorrectNumber<int>(std::cin, 1, ids.size());
    stations.erase(ids[number - 1]);

    //int ID = ids[number - 1];
    //LogUserAction("Удаление кс", ID);
}

void TransportSystem::DeleteSomePipes()
{
    if (!pipes.size())
    {
        cout << "Нет доступных труб!";
        return;
    }

    cout << "Выберете фильтр поиска:" <<
        "\n1.По имени" <<
        "\n2.По состоянию" << endl;

    switch (CorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        cout << "Введите имя трубы:" << endl;
        vector<int> result = Search_By_Name(pipes);
        if (result.size())
        {
            for (auto& id : result) pipes.at(id).PrintInfo();
            cout << "Удалить трубы?(0 - нет, 1 - да)" << endl;
            if (CorrectNumber(cin, 0, 1))
            {
                for (auto& id : result) {
                    pipes.erase(id);
                    //int ID = id;
                    //LogUserAction("Удаление трубы по имени", ID);
                }
            }
            else { return; }
        }
        else cout << "Нет подходящих труб";
        break;
    }
    case 2:
    {
        cout << "Введите состояние трубы:" << endl;
        vector<int> result = Search_By_Status(pipes);
        if (result.size())
        {
            for (auto& id : result) pipes.at(id).PrintInfo();
            cout << "Удалить трубы?(0 - нет, 1 - да)" << endl;
            if (CorrectNumber(cin, 0, 1))
            {
                for (auto& id : result) {
                    pipes.erase(id);
                    //int ID = id;
                    //LogUserAction("Удаление трубы по состоянию", ID);
                }
            }
            else { return; }
        }
        else cout << "Нет подходящих труб";
        break;
    }
    case 0:
    {
        break;
    }
    }
}
void TransportSystem::DeleteSomeStations()
{
    if (!pipes.size())
    {
        cout << "Нет доступных станций!";
        return;
    }

    cout << "Выберете фильтр поиска:" <<
        "\n1.По имени" <<
        "\n2.По состоянию" << endl;

    switch (CorrectNumber(cin, 0, 2))
    {
    case 1:
    {
        cout << "Введите имя станции:" << endl;
        vector<int> result = Search_By_Name(stations);
        if (result.size())
        {
            for (auto& id : result) stations.at(id).PrintInfo();
            cout << "Удалить станции?(0 - нет, 1 - да)" << endl;
            if (CorrectNumber(cin, 0, 1))
            {
                for (auto& id : result) {
                    stations.erase(id);
                    //int ID = id;
                    //LogUserAction("Удаление кс по имени", ID);
                }
            }
            else { return; }

        }
        else cout << "Нет подходящих станций";
        break;
    }
    case 2:
    {
        cout << "Введите количество активных цехов станции:" << endl;
        vector<int> result = Search_By_Workshop(stations);
        if (result.size())
        {
            for (auto& id : result) stations.at(id).PrintInfo();
            cout << "Удалить станции?(0 - нет, 1 - да)" << endl;
            if (CorrectNumber(cin, 0, 1))
            {
                for (auto& id : result) {
                    stations.erase(id);
                    //int ID = id;
                    //LogUserAction("Удаление кс по состоянию", ID);
                }
            }
            else { return; }
        }
        else cout << "Нет подходящих станций";
        break;
    }
    case 0:
    {
        break;
    }
    }
}


//---------------FILES-------------------

void TransportSystem::Save()
{
    if (pipes.size() or stations.size()) {
        cout << "Введите название сохранения:" << endl;
        string name = input_string(cin);
        name = "data/" + name + ".txt";


        int MaxId_Pipe = 0;
        int MaxId_Station = 0;
        for (auto& pipe : pipes)
        {
            MaxId_Pipe = pipe.second.GetMaxId();
            break;
        }
        for (auto& cs : stations)
        {
            MaxId_Station = cs.second.GetMaxId();
            break;
        }

        ofstream file;
        file.open(name, ios::out);
        file << pipes.size() << " " << stations.size() << " " << MaxId_Pipe << " " << MaxId_Station << endl;
        for (auto& pipe : pipes) {
            file << pipe.second;
            //int ID = pipe.second.ID;
            //LogUserAction("Сохранение трубы", ID);
        }


        for (auto& cs : stations) {
            file << cs.second;
            //int ID = cs.second.ID;
            //LogUserAction("Сохранение кс", ID);
        }
        file.close();


        cout << "Успешно сохранено!" << endl;
    }

    else
    {
        cout << "Сохранение не может быть пустым, запишите данные!" << endl;
    }
}

void TransportSystem::Load() {

    ifstream file;
    std::string path = "data\\";
    int count = 0;
    for (auto& name : filesystem::directory_iterator(path)) {
        count++;
        cout << count << ". " << name << endl;

    }


    cout << "Выберете номер сохранения" << endl;
    int save = CorrectNumber(cin, 1, count);

    count = 0;
    for (auto& name : filesystem::directory_iterator(path)) {
        count++;
        if (count == save) {
            pipes.clear();
            stations.clear();

            Pipe pipe;
            CS cs;

            int count_pipes;
            int count_cs;
            int MaxId_Pipe;
            int MaxId_Station;

            file.open(name);
            file >> count_pipes >> count_cs >> MaxId_Pipe >> MaxId_Station;
            pipe.SetMaxId(MaxId_Pipe);
            cs.SetMaxId(MaxId_Station);

            while (count_pipes--)

            {
                file >> pipe;
                pipes.insert({ pipe.GetID(), pipe });
                //int ID = pipe.GetID();
                //LogUserAction("Загрузка трубы", ID);
            }


            for (count_cs; count_cs > 0; count_cs--)
            {
                file >> cs;
                stations.insert({ cs.GetID(), cs });
                //int ID = cs.GetID();
                //LogUserAction("Загрузка кс", ID);
            }

            cout << "Файлы загружены!\n" << endl;
            break;
        }
    }
}

