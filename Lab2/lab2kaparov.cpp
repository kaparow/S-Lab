#include "header.h"
#include "Console_func.h"
#include "CS.h"
#include "Pipe.h"
#include <format>
#include <chrono>

using namespace std;
using namespace chrono;

int main()
{

    redirect_stream_wrapper cerr_out(cerr);
    string time = format("{:%d_%m_%Y_%H_%M_%OS}", system_clock::now() + hours(3));
    ofstream logfile("Logs/log_" + time);
    if (logfile)
        cerr_out.redirect(logfile);

    TransportSystem Pipeline_Gas_Transpartation;

    while (1) {

        cout << "\n1. Добавить трубу\n" <<
            "2. Добавить КС\n" <<
            "3. Просмотр всех объектов\n" <<
            "4. Редактировать\n" <<
            "5. Удалить\n" <<
            "6. Искать по фильтру\n" <<
            "7. Сохранить\n" <<
            "8. Загрузить\n" <<
            "0. Выход\n" << endl;


        switch (CorrectNumber(cin, 0, 8))
        {

        case 1: {
            Pipeline_Gas_Transpartation.InputPipe();
            break;
        }
        case 2: {
            Pipeline_Gas_Transpartation.InputCS();
            break;
        }
        case 3: {
            Pipeline_Gas_Transpartation.View();
            break;
        }
        case 4: {
            Pipeline_Gas_Transpartation.Edit();
            break;
        }

        case 5: {
            Pipeline_Gas_Transpartation.Delete();
            break;
        }
        case 6: {
            Pipeline_Gas_Transpartation.Search();
            break;
        }

        case 7: {
            Pipeline_Gas_Transpartation.Save();
            break;
        }
        case 8: {
            Pipeline_Gas_Transpartation.Load();
            break;
        }

        case 0: {
            return 0;

        }

        }
    }

    return 0;
}