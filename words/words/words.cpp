#include <iostream>
#include <fstream>
#include <string>

std::ifstream fin("input.txt");

class Word {
private:
    std::string* arr;
    int attempts = 6;
    int chance;
    int closedLetters = 0;
public:

    void getData() {
        int size;
        fin >> size;
        chance = rand() % size + 1;
        arr = new std::string[size];
        for (int i = 0; i < size; i++) {
            std::getline(fin, arr[i]);
        }
    }

    std::string transform() {
        std::string s = arr[chance - 1];
        for (int i = 0; i < arr[chance - 1].size()-2; i++) {
            s[i] = '*';
        }
        return s;
    }
    
    void statusFunction() {
        std::cout << "Word - ";
    }

    void guessFunction(std::string& cipherWord) {
        std::cout << "Guess the letter : ";
        char symbol;
        std::cin >> symbol;
        bool status = false;
        for (int i = 0; i < arr[chance - 1].size() - 2; i++) {
            if (symbol == arr[chance - 1][i]) {
                status = true;
                arr[chance - 1][i] = '*';
                cipherWord[i] = symbol;
                std::cout << "Your word : " << cipherWord << "\n";
                std::cout << "Your attemps : " << attempts << "\n";
                ++closedLetters;
                if (closedLetters == arr[chance - 1].size() - 2) {
                    std::cout << "CONGRATILATIONS, YOU WIN!\n";
                    break;
                }
                else {
                    guessFunction(cipherWord);
                }
            }
        }

        if(!status) {
        --attempts;
        std::cout << "There is no such letter\n";
        std::cout << "Your word : " << cipherWord << "\n";
        std::cout << "Your attemps :" << attempts << "\n";
            if (attempts > 0) {
                guessFunction(cipherWord);
            }
            else {
                std::cout << "YOU LOST!\n";
            }
        }

    }
};

int main()
{
    srand(time(NULL));

    if (!fin.is_open()) {
        std::cout << "Error\n";
    }
    else {
        std::cout << "File was opened\n";
    }
 
    Word A;
    A.getData();
    std::string cipherWord = A.transform();

    std::cout << "Computer thought of a word : " << cipherWord << "\n";
    A.guessFunction(cipherWord);
    return 0;
}
