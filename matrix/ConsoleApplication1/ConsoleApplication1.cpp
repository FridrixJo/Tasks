#include <iostream>
#include <fstream>

std::ifstream fin;
std::ofstream fout("output.txt");

class Matrix {
private:
    int** firstArray;
    int** secondArray;
    int rows;
    int cols;
public:

    void openFile() {

        fin.exceptions(std::ifstream::badbit | std::ifstream::failbit);

        try
        {
            std::cout << "Tryinp to open file ...\n";
            fin.open("input.txt");
            std::cout << "File was opened\n\n";
        }
        catch (const std::ifstream::failure ex)
        {
            std::cout << ex.what() << "\n";
            std::cout << ex.code() << "\n";
            std::cout << "Error!\n";
        }
    }
    
    void getData() {
        fin >> rows;
        fin >> cols;
    }

    void setValue(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;

        firstArray = new int* [rows];
        for (int i = 0; i < rows; i++) {
            firstArray[i] = new int[cols];
        }

        secondArray = new int* [cols];
        for (int i = 0; i < cols; i++) {
            secondArray[i] = new int[rows];
        }

    }

    void fullFill(int** firstArray, int rows, int cols) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                firstArray[i][j] = rand() % 90 + 10;
            }
        }
    }
    
    void print(int** arr, int rows , int cols) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << arr[i][j] << " ";
                fout << arr[i][j] << " ";
            }
            std::cout << "\n";
            fout << "\n";
        }
    }

    void rotate(int** secondArray, int rows, int cols) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                secondArray[j][i] = firstArray[i][j];
            }
        }
    }

    void printFirst() {
        print(firstArray, rows ,cols);
    }

    void printSecond() {
        print(secondArray, cols, rows);
    }

    void fillFunction() {
        fullFill(firstArray, rows, cols);
    }

    void rotateFunction() {
        rotate(secondArray, rows, cols);
    }

    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] firstArray[i];
        }
        delete[] firstArray;

        for (int i = 0; i < cols; i++) {
            delete[] secondArray[i];
        }
        delete[] secondArray;
    }

};

int main()
{
    srand(time(NULL));
    Matrix A;
    A.openFile();
    A.getData();
    A.setValue(10, 5);
    A.fillFunction();
    A.printFirst();
    std::cout << "\n";
    fout << "\n";
    A.rotateFunction();
    A.printSecond();
    return 0;
}
