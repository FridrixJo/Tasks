#include <iostream>
#include <fstream>

std::ofstream fout("output.txt");

class Generator {
private:
    int lenght;
    char *password;
public:
    Generator() {
        this->lenght = 9;
        password = new char[9]{'P','A','S','S','W','O','R','D','\0'};

    }
    ~Generator() {
        delete password;
    }

    void getLenght(const int &lenght) {
        this->lenght = lenght;
    }

    void print() {
        std::cout << "lenght : " << lenght << "\n";
        std::cout << "your password : " << password << "\n";
        fout << "lenght : " << lenght << "\n";;
        fout << "your password : " << password << "\n";
    }

    int chooseLevel() {
        std::cout << "Enter hard level of your password\n";
        
        int hardLevel;
                                    
        std::cout << "Choose :\n 1. easy\n 2. hard\n";
        std::cin >> hardLevel;

        return hardLevel;
    }

    char* easyGenerator(int begin, int end) {
        password = new char[lenght + 1];
        for (int i = 0; i < lenght; i++) {
            password[i] = rand() % begin + end;
        }
        password[lenght] = '\0';
        return password;
    }

    char* hardGenerator(int begin1,int end1, int begin2, int end2, int begin3, int end3) {
        password = new char[lenght + 1];

        for (int i = 0; i < lenght; i += 3) {
            password[i] = rand() % begin1 + end1;
        }
        for (int i = 1; i < lenght; i += 3) {
            password[i] = rand() % begin2 + end2;
        }
        for (int i = 2; i < lenght; i += 3) {
            password[i] = rand() % begin3 + end3;
        }
        password[lenght] = '\0';

        return password;
    }

    char* passwordGenerator(const int &lenght) {
        int hardLevel = chooseLevel();
        int chance = rand() % 6 + 1;

        switch (hardLevel) {

        case 1:
            int easyLevel;
            std::cout << "Choose your password consists of\n";
            std::cout << "1. numbers\n2. UPPERCASE_letter\n3. lowercase_letters\n";
            std::cin >> easyLevel;
            switch (easyLevel) {
            case 1:
                password = easyGenerator(10, 48);
                break;
            case 2:
                password = easyGenerator(26, 65);
                break;
            case 3:
                password = easyGenerator(26, 97);
                break;
            default:
                password = easyGenerator(26, 65);
            }
            break;

        case 2:

            switch (chance) {
            case 1:
                password = hardGenerator(26, 97, 10, 48, 26, 65);
                break;
            case 2:
                password = hardGenerator(26, 97, 26, 65, 10, 48);
                break;
            case 3:
                password = hardGenerator(10, 48, 26, 97, 26, 65);
                break;
            case 4:
                password = hardGenerator(10, 48, 26, 65, 26, 97);
                break;
            case 5:
                password = hardGenerator(26, 65, 26, 97, 10, 48);
                break;
            case 6:
                password = hardGenerator(26, 65, 10, 48, 26, 97);
                break;
            }

            break;

        default:

            password = easyGenerator(26, 97);

        }

        return password;

    }
};

class ASCII {
public:
    void getTable() {
        for (int i = 0; i < 255; i++) {
            std::cout << i << " " << char(i) << "\n";
        }
    }
};

int main()
{
    srand(time(NULL));

    Generator A;

    std::cout << "Enter the lenght of your password (min 8 symbols) :\t";
    int lenght;
    std::cin >> lenght;
    if (lenght < 8) {
        std::cout << "Wrong! Automatically it was turned to 8\n";
        lenght = 8;
    }

    A.getLenght(lenght);
    A.passwordGenerator(lenght);
    A.print();

    return 0;
}
