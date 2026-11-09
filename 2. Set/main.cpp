#include <iostream>
#include <string>
#include <sstream>
#include "file.h"
#include "set.h"

using namespace std;

enum class Command {
    SETADD,
    SETDEL,
    SET_AT,
    PRINT,
    HELP,
    EXIT,
    UNKNOWN
};

Command parseCommand(const string& cmd) {
    if (cmd == "SETADD") return Command::SETADD;
    if (cmd == "SETDEL") return Command::SETDEL;
    if (cmd == "SET_AT") return Command::SET_AT;
    if (cmd == "PRINT")  return Command::PRINT;
    if (cmd == "HELP")   return Command::HELP;
    if (cmd == "EXIT")   return Command::EXIT;
    return Command::UNKNOWN;
}

int main() {
    system("chcp 65001 > nul");

    LoadAll();

    cout << "Введите команду (HELP — список команд, EXIT — выход):" << endl;

    string line;
    while (true) {
        cout << "> ";
        if (!getline(cin, line)) break;
        if (line.empty()) continue;

        istringstream iss(line);
        string cmdStr;
        iss >> cmdStr;

        Command cmd = parseCommand(cmdStr);

        try {
            switch (cmd) {
                case Command::SETADD: {
                    string name, value;
                    if (!(iss >> name >> value)) {
                        cout << "ОШИБКА: Формат: SETADD <name> <value>" << endl;
                        break;
                    }
                    Set* s = fetchSet(name);
                    if (setAdd(*s, value)) {
                        cout << "Добавлено: " << value << endl;
                    } else {
                        cout << "Элемент уже существует: " << value << endl;
                    }
                    break;
                }

                case Command::SETDEL: {
                    string name, value;
                    if (!(iss >> name >> value)) {
                        cout << "ОШИБКА: Формат: SETDEL <name> <value>" << endl;
                        break;
                    }
                    Set* s = fetchSet(name);
                    if (setDel(*s, value)) {
                        cout << "Удалено: " << value << endl;
                    } else {
                        cout << "Элемент не найден: " << value << endl;
                    }
                    break;
                }

                case Command::SET_AT: {
                    string name, value;
                    if (!(iss >> name >> value)) {
                        cout << "ОШИБКА: Формат: SET_AT <name> <value>" << endl;
                        break;
                    }
                    Set* s = fetchSet(name);
                    cout << (setAt(*s, value) ? "true" : "false") << endl;
                    break;
                }

                case Command::PRINT: {
                    string type, name;
                    if (!(iss >> type >> name)) {
                        cout << "ОШИБКА: Формат: PRINT set <name>" << endl;
                        break;
                    }
                    if (type != "set") {
                        cout << "ОШИБКА: поддерживается только 'set'" << endl;
                        break;
                    }
                    Set* s = fetchSet(name);
                    printSet(*s);
                    break;
                }

                case Command::HELP:
                    printHelp();
                    break;

                case Command::EXIT:
                    SaveAll();
                    freeEverything();
                    cout << "Выход." << endl;
                    return 0;

                case Command::UNKNOWN:
                default:
                    cout << "ОШИБКА: неизвестная команда '" << cmdStr << "'. Введите HELP." << endl;
                    break;
            }
        } catch (const exception& e) {
            cout << "ОШИБКА: " << e.what() << endl;
        }
    }

    SaveAll();
    freeEverything();
    return 0;
}