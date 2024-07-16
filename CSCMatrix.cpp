#include "random_add.h"
#include "CSCMatrix.h"

	CSCMatrix::CSCMatrix() {
		CSCMatrix(1,0);
     }
    
    CSCMatrix::CSCMatrix(unsigned int size, float percentage) {
		_csc_matrix._size = size;
		if (size == 0) _csc_matrix._size = 1; // защита от ввода нулевого размера матрицы
		float temp_percentage = fabs(percentage); // защита от ввода отрицательной процентовки
		if (temp_percentage > 100) temp_percentage = 100; // процент заполнения не может быть более 100% 
		temp_percentage /= 100;
		_csc_matrix._amount_of_elements = (unsigned long int) ((_csc_matrix._size * (_csc_matrix._size - 1) * temp_percentage)); // вычисляем количество дополнительных элементов в матрице
		if (_csc_matrix._amount_of_elements%2 == 1) _csc_matrix._amount_of_elements--;
		_csc_matrix.commul_not_null_in_column.reserve(_csc_matrix._size);
		_csc_matrix.row.reserve(_csc_matrix._size + _csc_matrix._amount_of_elements);
		_csc_matrix.value.reserve(_csc_matrix._size + _csc_matrix._amount_of_elements);
		createCSCMatrix();
	 }

	 CSCMatrix::~CSCMatrix() {
		_csc_matrix.commul_not_null_in_column.clear();
		_csc_matrix.row.clear();
		_csc_matrix.value.clear();
	 }

	 void CSCMatrix::createCSCMatrix() {  // создание матрицы
		creatMainDiagonal(); // заполняем главную диагональ
		addRandomNumbersToCSCMatrix(); // наполняем матрицу случайными не нулевыми значениями в соотвествии с процентом заполнения
	 }

	 void CSCMatrix::creatMainDiagonal() { // заполняем главную диагональ матрицы значениями main_diagonal_value = 1
		for (int i = 0; i < _csc_matrix._size; i++) {
			_csc_matrix.commul_not_null_in_column.push_back(i + 1);
			_csc_matrix.row.push_back(i);
			_csc_matrix.value.push_back(main_diagonal_value);
		}
	 }

	 void CSCMatrix::printOutCSCMatrixAsCSCMatrix() { // выводим матрицу в консоль в сжатом виде (Compressed parse column)
		for (auto &com_not_null: _csc_matrix.commul_not_null_in_column) {
			cout << fixed << setw(2) << com_not_null << " ";
		} 
		cout << endl;
		for (auto &row: _csc_matrix.row) {
			cout << fixed << setw(2) << row << " "; // выводим номера рядов
		}
		cout << endl;
		for (auto &value: _csc_matrix.value) {
			cout << fixed << setw(2) << value << " "; // выводим значения 
		}
		cout << endl;
		cout << " dimentions " << _csc_matrix._size << " x " << _csc_matrix._size << endl; // выводим размер матрицы
	 }

	 void CSCMatrix::saveCSCMatrixAsCSCMatrix(const string file_name) { // выгружаем матрицу в csv файл в сжатом виде (Compressed parse column)
		_output_file.open(file_name);
		for (auto &com_not_null: _csc_matrix.commul_not_null_in_column) {  // выводим комулятивное значение "не нолей" по столбцам
			_output_file << com_not_null << ";";
		} 
		_output_file << endl;
		for (auto &row: _csc_matrix.row) { // выводим номера рядов
			_output_file << row << ";";
		}
		_output_file << endl;
		for (auto &value: _csc_matrix.value) {
			_output_file << value << ";";  // выводим значения 
		}
		_output_file << endl;
		_output_file << _csc_matrix._size << ";" << _csc_matrix._size << endl; // выводим размер матрицы
		_output_file << endl;
		_output_file.close();
	 }


	void CSCMatrix::printOutCSCMatrixAsStandartMatrix() { // выводим матрицу в консоль в стандартом виде
		for (int i = 0; i < _csc_matrix._size; i++) {
			for (int j = 0; j < _csc_matrix._size; j++) {
				cout << getIntFromCSCMatrix(i, j) << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

		void CSCMatrix::saveCSCMatrixAsStandartMatrix(const string file_name) { // выгружаем матрицу в csv файла в стандартом виде
		_output_file.open(file_name);
		for (int i = 0; i < _csc_matrix._size; i++) {
			for (int j = 0; j < _csc_matrix._size; j++) {
				_output_file << getIntFromCSCMatrix(i, j) << ";";
			}
			_output_file << endl;
		}
		_output_file << endl;
		_output_file.close();
	}

	 int CSCMatrix::getIntFromCSCMatrix(int row, int column) { // фн-ция для возврата int значения из CSC матрицы по номеру ряда row и колонны column
		int answer = 0;
		int number_of_not_null_elem_befor_curr_column = 0;
		if (column != 0) number_of_not_null_elem_befor_curr_column = _csc_matrix.commul_not_null_in_column[column - 1];
		int number_of_not_null_elem_in_curr_column = _csc_matrix.commul_not_null_in_column[column] - // вычисляем количество элементов до текущего номера колонны
		number_of_not_null_elem_befor_curr_column;
		for (int j = number_of_not_null_elem_befor_curr_column; j < _csc_matrix.commul_not_null_in_column[column]; j++) {
			if (_csc_matrix.row[j] == row) {
				answer = _csc_matrix.value[j]; // ищем требуемый элемент в матрице по координатам row и column, если условие выше не выполнено - возвращаем ноль
				break;
			} 
		}
		return answer;
	 }

	 void CSCMatrix::addRandomNumbersToCSCMatrix() { 
		PRNG generator;
    	initGenerator(generator);
		int temp_number = random(generator, 0, 100);
		unsigned long int amount_of_additional_elements = _csc_matrix._amount_of_elements;
		while (amount_of_additional_elements > 0) {
			int random_row = random(generator, 0, _csc_matrix._size - 1); // генерируем случайный номер ряда
			int random_column = random(generator, 0, _csc_matrix._size - 1); // генерируем случайный номер колонны
			int random_value = random(generator, min_random_value, max_random_value); // генерируем случайное значение для вставки
			if (random_row == random_column) continue; // если попали на главную диагональ - идем на новый круг
			if (addNumberToMatrix(random_value, random_row, random_column)) amount_of_additional_elements--; // вставляем значения в матрицу
			if (addNumberToMatrix(random_value, random_column, random_row)) amount_of_additional_elements--;
		}
	 }

	 bool CSCMatrix::addNumberToMatrix(int value, int row, int column) { // ф-ция для добавления int value в матрицу по номеру ряда row и колонны column
		bool answer = false;
		if (getIntFromCSCMatrix(row, column) == 0) { // проверка на нулевое значение в ячейке.
			int number_of_not_null_elem_befor_curr_column = 0;
			int temp_row_number = 0;
			if (column != 0) number_of_not_null_elem_befor_curr_column = _csc_matrix.commul_not_null_in_column[column - 1];
			int number_of_not_null_elem_in_curr_column = _csc_matrix.commul_not_null_in_column[column] - // вычисляем количество элементов до текущего номера колонны
			number_of_not_null_elem_befor_curr_column;
			for (int j = number_of_not_null_elem_befor_curr_column; j < _csc_matrix.commul_not_null_in_column[column]; j++) {
				temp_row_number = j;
				if (_csc_matrix.row[j] > row) { // ищем требуемый элемент для вставки перед ним значения value по координатам row и column
					break;
				} 
			}
			temp_row_number++; // счетчик смещения итератора
			answer = true;
			_csc_matrix.row.emplace(_csc_matrix.row.begin() + temp_row_number, row); // вставка номера строки
			_csc_matrix.value.emplace(_csc_matrix.value.begin() + temp_row_number, value); // вставка значения
			for (int i = column; i < _csc_matrix._size; i++) {
				_csc_matrix.commul_not_null_in_column[i] += 1;
			}
		}
		return answer; // возвращает true, если в ячейке был 0 и удалось вставить новое значение
	 }




