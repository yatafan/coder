#include "dictionary.h"

//Читает файл посимвольно
string read_file(const char* filename);

//Превращает строку данных в строку байтов
string to_bytes(string &input_data);

//Шифрует данные по словарю
string encode(string &input_data, dictionary &dict);

//Записывает данные в файл
void write_in_file(string &input_data, const char* filename, dictionary &dict);

//Преобразовывает бинарную строку в число
void str_to_bitset(string &bin_str, bitset<BYTE_SIZE> &byte);

//Выводит строку, поделенную по длине слова
void print_words(string &str, unsigned int step);

int main() {
    unsigned int choice = -1;

    unsigned int key_size, value_size;
    dictionary dict;

    string data;
    string binary_data;
    string encoded_data;

    while(choice != 0){
        cout << "Выберите действие:" << endl;
        cout << "1. Зашифровать файл" << endl;
        cout << "2. Вывести исходные данные" << endl;
        cout << "3. Вывести зашифрованные данные" << endl;
        cout << "4. Вывести словарь шифрования" << endl;
        cout << "0. Выйти" << endl;

        cout << ": "; cin >> choice;
	
        switch (choice) {
            case 1:
                cout << "Введите длину входного слова: ";
                cin >> key_size;
                cout << "Введите длину выходного слова: ";
                cin >> value_size;

                data = read_file("input.txt"); //читаем файл
                binary_data = to_bytes(data); //преобразовываем данные в биты

                dict = dictionary(key_size, value_size); //создаем словарь
                dict.init_keys(binary_data); //инициализируем ключи
                dict.init_values(22); //инициализируем значения генератором случайных чисел
                dict.save_in_file("dictionary.bin");

                encoded_data = encode(binary_data, dict); //шифруем данные по словарю

                write_in_file(encoded_data, "output.txt", dict);

                break;
            case 2:
                cout << "Исходные данные: " << endl;
                print_words(binary_data, key_size);
                break;
            case 3:
                cout << "Зашифрованные данные: " << endl;
                print_words(encoded_data, value_size);
                break;
            case 4:
                cout << "Словарь шифрования: " << endl;
                dict.print();
                break;
            default:
                break;
        }
    }

    return 0;
}

string read_file(const char* filename){
    ifstream input_file(filename);
    string data;

    while (!input_file.eof()) {
        data += input_file.get();
    }

    data.pop_back();
    data.pop_back();

    input_file.close();
    return data;
}

string to_bytes(string &input_data){
    string bytes;
    bitset<BYTE_SIZE> byte;

    for(int i = 0; i < input_data.size(); i++){
        byte = input_data[i];
        bytes += byte.to_string();
    }

    return bytes;
}

string encode(string &input_data, dictionary &dict){
    string encoded_data;
    unsigned int key_size = dict.get_key_size();

    for(int i = 0; i <= input_data.size() - key_size; i += key_size){
        encoded_data += dict.get_value(input_data.substr(i, key_size));
    }

    return encoded_data;
}

void write_in_file(string &input_data, const char* filename, dictionary &dict){
    ofstream output_file(filename);
    bitset<BYTE_SIZE> bs;
    string value;
    char byte;

    unsigned int zeros = 0;

    for(int i = 0; i < input_data.size() % BYTE_SIZE; i++){
        input_data += '0';
        zeros++;
    }

    dict.set_output_zeros(zeros);

    for(int i = 0; i <= input_data.size() - BYTE_SIZE; i += BYTE_SIZE){
        value = input_data.substr(i, BYTE_SIZE);
        str_to_bitset(value, bs);

        byte = bs.to_ulong();
        output_file << byte;

        bs = 0;
    }

    output_file.close();
}

void str_to_bitset(string &bin_str, bitset<BYTE_SIZE> &byte){
    for(int i = 0; i < bin_str.size(); i++){
        if(bin_str[i] == '1'){
            byte[BYTE_SIZE - i - 1] = 1;
        }
    }
}

void print_words(string &str, unsigned int step){
    for(int i = 0; i < str.size() - step; i += step){
        cout << str.substr(i, step) << ' ';
    }

    if(str.size() % step != 0){
        cout << str.substr(str.size() - str.size() % step);
    }
    else{
        cout << str.substr(str.size() - step);
    }

    cout << endl;
}
