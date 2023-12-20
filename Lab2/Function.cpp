#pragma once

#include "Console_func.h"

template <typename T>
void ViewComponents(unordered_map<int, T>& conteiner)
{
    int i = 1;
    for (auto& element : conteiner) {
        cout << i << ". ";
        i++;
        element.second.PrintInfo();
    }

}

template <typename T>
map<int, int> Create_Console_Map(const unordered_map<int, T>& conteiner)
{
    map<int, int> new_map;
    int i = 0;
    for (auto& element : conteiner) {
        i++;
        new_map.insert({ i,element.first });
    }
    return new_map;
}


template <typename T1, typename T2>
using Filter = bool(*)(T1& element, T2 parametr);

template <typename T>
bool CheckByName(T& element, string name) {
    return (element.name.find(name) != string::npos);
}

bool CheckByStatus(Pipe& pipe, bool in_repairing) {
    return pipe.in_repairing == in_repairing;
}

bool CheckByActive(CS& station, int workshops_in_operation) {
    return station.workshops_in_operation == workshops_in_operation;
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

void View(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& stations)
{

    while (1) {
        
        cout << "\n0. Выход\n" <<
            "1. Список труб\n" <<
            "2. Список КС\n" <<
            "3. Список труб и КС" << endl;


        switch (CorrectNumber(0, 3)) {
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
    }
}

void EditPipeline(unordered_map<int, Pipe>& pipes)
{
    if (!pipes.size())
    {
        cout << "Добавьте трубу!\n";
        return;
    }

    cout << "1. Редактировать одну трубу по выбору\n"
        << "2. Редактировать по фильтру\n"
        << "0. Выход" << endl;


    switch (CorrectNumber(0, 2))
    {
    case 1:
    {
     
        cout << "Трубы:\n";
        ViewComponents(pipes);
        cout << "Выберете редактируемую трубу:";

        map<int, int> new_map = Create_Console_Map(pipes);
        int number = CorrectNumber(1, pipes.size());
        pipes[new_map[number]].editInRepairStatus();
        break;
    }
    case 2:
    {
        vector<int> result;
        cout << "Введите состояние трубы:" << endl;
        result = Find_By_Filter<Pipe, bool>(pipes, CheckByStatus, CorrectNumber(0, 1));
        if (result.size())
        {
            for (auto& id : result) pipes.at(id).PrintInfo();
            cout << "На какое состояние изменить?(0 - в ремонт, 1 - в рабочее состояние)" << endl;
            int answer = CorrectNumber(0, 1);
            for (auto& id : result) pipes.at(id).Edit(answer);
            cout << endl << "Состояние труб изменено!";
        }
        else cout << "Нет подходящих труб";

        break;
    }
    case 0:
    {
        return;
    }
    }

}

void EditCopressorStation(unordered_map<int, CS>& stations) {
    if (!stations.size()) {
        cout << "Добавьте КС!\n";
        return;
    }

    cout << "1. Редактировать одну станцию по выбору\n"
        << "2. Редактировать по фильтру\n"
        << "0. Выход" << endl;


    switch (CorrectNumber(0, 2))
    {
    case 1:
    {
        cout << "КС:\n";
        ViewComponents(stations);
        cout << "Выберете редактируемую станцию:";

        map<int, int> new_map = Create_Console_Map(stations);
        int number = CorrectNumber(1, stations.size());
        stations[new_map[number]].EditCS();
        break;
    }
    case 2:
    {
       
        vector<int> result;
        cout << "Введите кол-во активных цехов:" << endl;
        result = Find_By_Filter<CS, int>(stations, CheckByActive, CorrectNumber(0, 50));
        if (result.size())
        {
            for (auto& id : result) stations.at(id).PrintInfo();
            cout << "Изменить кол-во активных цехов на:" << endl;
            int answer = CorrectNumber(0, 50);
            for (auto& id : result) stations.at(id).Edit(answer);
            cout << endl << "Состояние станций изменено!";
        }
        else cout << "Нет подходящих станций";
        break;
    }
    case 0:
    {
        return;
    }
    }
}


void SaveConfiguration(const unordered_map<int, Pipe>& pipes, const unordered_map<int, CS>& stations) {
    if (pipes.size()>0 or stations.size()>0) {
        cout << "Введите название сохранения:" << endl;
        string name;
        cin.ignore(10000, '\n');
        getline(cin, name);
        name = "data/" + name + ".txt";

        ofstream file;
        file.open(name, ios::out);
        file << pipes.size() << " " << stations.size() << endl;
        for (auto& pipe : pipes) file << pipe.second;
        for (auto& station : stations) file << station.second;
        file.close();
        cout << "Success!" << endl;
        

    }

    else cout << "Сохранение не может быть пустым, запишите данные!" << endl;

}


void LoadConfiguration(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& stations) {
   
    ifstream file;
    std::string path = "data\\";
    int count = 0;
    for (auto& name : filesystem::directory_iterator(path)) {
        count++;
        cout << count << ". " << name << endl;
    }
    
    cout << "Выберете номер сохранения" << endl;
    int save = CorrectNumber(1, count);

    count = 0;
    for (auto& name : filesystem::directory_iterator(path)) {
        count++;
        if (count == save) {
            pipes.clear();
            stations.clear();

            file.open(name);

            int count_pipes;
            int count_cs;
            file >> count_pipes;
            file >> count_cs;

            Pipe pipe;
            for (count_pipes; count_pipes > 0; count_pipes--) {
                file >> pipe;
                pipes.insert({ pipe.ID, pipe });
            }

            CS station;
            for (count_cs; count_cs > 0; count_cs--) {
                file >> station;
                stations.insert({ station.ID, station });
            }
            cout << "Файлы загружены!\n" << endl;
           
            break;
        }
    }
}



void SearchPipes(unordered_map<int, Pipe>& pipes)
{
    if (pipes.size())
    {
        cout << "Выберете фильтр поиска:\n1. По имени\n2. По состоянию" << endl;
        vector<int> result;

        switch (CorrectNumber(1, 2))
        {
        case 1:
        {
            cout << "Введите имя трубы:" << endl;
            string name;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            getline(cin, name);

            result = Find_By_Filter<Pipe, string>(pipes, CheckByName, name);
            break;
        }
        case 2:
        {
            cout << "Введите состояние трубы:" << endl;
            result = Find_By_Filter<Pipe, bool>(pipes, CheckByStatus, CorrectNumber(0, 1));
            break;
        }
        }

        if (result.size())
        {
            for (auto& id : result) pipes.at(id).PrintInfo();
        }
        else cout << "Нет подходящих труб";
    }
    else cout << "Нет доступных труб!";


}


void SearchCS(unordered_map<int, CS>& stations)
{
    if (stations.size())
    {
        cout << "Выберете фильтр поиска:\n1. По имени\n2. По активным цехам" << endl;
        vector<int> result;

        switch (CorrectNumber(1, 2))
        {
        case 1:
        {
            cout << "Введите имя станции:" << endl;
            string name;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            getline(cin, name);

            result = Find_By_Filter<CS, string>(stations, CheckByName, name);
            break;
        }
        case 2:
        {
            cout << "Введите кол-во активных станций:" << endl;
            result = Find_By_Filter<CS, int>(stations, CheckByActive, CorrectNumber(0, 50));
            break;
        }
        }

        if (result.size())
        {
            for (auto& id : result) stations[id].PrintInfo();
        }
        else cout << "Нет подходящих станций";
    }
    else cout << "Нет доступных станций!";

}