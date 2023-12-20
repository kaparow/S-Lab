/*#include "header.h"
#include "Console_func.h"
#include "CS.h"
#include "Pipe.h"


int main()
{
    setlocale(LC_ALL, "ru");

    unordered_map<int, Pipe> pipes;
    unordered_map<int, CS> stations;


    while (1) {
       
        std::cout << "\n1. Добавить трубу\n" <<
            "2. Добавить КС\n" <<
            "3. Просмотр всех объектов\n" <<
            "4. Редактировать трубу\n" <<
            "5. Редактировать КС\n" <<
            "6. Сохранить\n" <<
            "7. Загрузить\n" <<
            "8. Поиск труб по фильтру\n" <<
            "9. Поиск станций по фильтру\n" <<
            "0. Выход\n" << std::endl;


        switch (CorrectNumber(0, 9))
        {

        case 1: {
            Pipe pipe;
            pipe.InputPipeInfo();
            pipes.insert({ pipe.ID, pipe });
            break;
        }
        case 2: {
            CS station;
            station.inputCSInfo();
            stations.insert({ station.ID, station });
            break;
        }
        case 3: {
            View(pipes, stations);
            break;
        }
        case 4: {
            EditPipeline(pipes);
            break;
        }

        case 5: {
            EditCopressorStation(stations);
            break;
        }
        case 6: {
            SaveConfiguration(pipes, stations);
            break;
        }

        case 7: {
            LoadConfiguration(pipes, stations);
            break;
        }
        case 8: {
            SearchPipes(pipes);
            break;
        }

        case 9: {
            SearchCS(stations);
            break;
        }

        case 0: {
            return 0;

        }

        }
    }

    return 0;
}*/