#ifndef JOSKE_CODER_DICTIONARY_H
#define JOSKE_CODER_DICTIONARY_H

#pragma once

#include <vector>
#include <string>
#include <set>
#include <bitset>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
using namespace std;

#define BYTE_SIZE 8

class dictionary {
private:
    unsigned int size; //размер словаря
    unsigned int key_size; //длина входного слова
    unsigned int value_size; //длина выходного слова
    unsigned int input_zeros; //оставшиеся биты после деления при кодировании
    unsigned int output_zeros; //оставшиеся биты после записи при декодировании
    vector<string> keys; //ключи шифрования
    vector<string> values; //значения, соответствующие ключам

    void write_string_in_file(string &str, ofstream &file);
    void write_vector_in_file(vector<string> &vec, ofstream &file);

    string dec_to_bin(unsigned int n, unsigned int len);
public:
    dictionary() = default;
    dictionary(unsigned int key_size, unsigned int value_size);
    unsigned int get_size() const{ return size; }
    unsigned int get_key_size() const{ return key_size; }
    unsigned int get_value_size() const{ return value_size; }

    void init_keys(string &input_data); //инициализирует ключи для шифрования
    void init_values(unsigned int seed); //инициализирует значения, соответствующие ключам

    string get_value(string key); //возвращает значение, соответсвующее ключу
    void set_output_zeros(unsigned int zeros){ output_zeros = zeros; }

    void save_in_file(const char* filename); //сохраняет строку в файл

    void print();
};


#endif //JOSKE_CODER_DICTIONARY_H
