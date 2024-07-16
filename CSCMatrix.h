#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <fstream>



using namespace std;

static int main_diagonal_value = 1;
static int min_random_value = 2;
static int max_random_value = 9;

struct CSCMatrixStruct {
	vector <int> commul_not_null_in_column;
	vector <int> row;
	vector <int> value;
	unsigned int _size;
	unsigned long int _amount_of_elements;
};

class CSCMatrix
{
public:
	CSCMatrix();
	CSCMatrix(unsigned int size, float percentage);
	~CSCMatrix();
	void printOutCSCMatrixAsCSCMatrix(); // выводим матрицу в консоль в сжатом виде (Compressed parse column)
	void printOutCSCMatrixAsStandartMatrix(); // выводим матрицу в консоль в стандартом виде
	void saveCSCMatrixAsCSCMatrix(const string file_name); // выгружаем матрицу в csv файла в сжатом виде (Compressed parse column)
	void saveCSCMatrixAsStandartMatrix(const string file_name); // выгружаем матрицу в csv файла в стандартом виде

private:
	// unsigned int _size; // размер матрицы
	// unsigned long int _amount_of_elements; // количество дополнительных элементов в матрице
	CSCMatrixStruct _csc_matrix;
	std::ofstream _output_file;
	void createCSCMatrix(); // создание CSC матрицы
	void creatMainDiagonal(); // заполняем главую диагональ
	int getIntFromCSCMatrix(int row, int column); // фн-ция для возврата int значения из CSC матрицы
	void addRandomNumbersToCSCMatrix(); // ф-ция заполнения матрицы случайными значениями до требуемого уровня заполнения
	bool addNumberToMatrix(int value, int row, int column); // ф-ция для добавления int числа в матрицу по координатам ряд/столбец
};