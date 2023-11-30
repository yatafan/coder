#include "dictionary.h"

dictionary::dictionary(unsigned int key_size, unsigned int value_size){
    this->key_size = key_size;
    this->value_size = value_size;
    this->size = 0;
}

void dictionary::init_keys(string &input_data){
    set<string> unique_keys;
    input_zeros = 0;

    for(int i = 0; i < input_data.size() % key_size; i++){
        input_data += '0';
        input_zeros++;
    }

    for(int i = 0; i <= input_data.size() - key_size; i += key_size){
        unique_keys.insert(input_data.substr(i, key_size));
    }

    for(auto i : unique_keys){
        keys.push_back(i);
    }

    size = keys.size();
}

void dictionary::init_values(unsigned int seed = 0){
    srand(seed);
    set<string> unique_values;
    string value;

    unsigned int max_value = pow(2, value_size);

    while(unique_values.size() != size){
        value = dec_to_bin(rand() % max_value , value_size);
        unique_values.insert(value);
    }

    for(auto i : unique_values){
        values.push_back(i);
    }

    random_device rd;
    mt19937 g(rd());

    shuffle(values.begin(), values.end(), g);
}

string dictionary::get_value(string key) {
    auto value_it = find(keys.begin(), keys.end(), key);
    unsigned int value_index = value_it - keys.begin();

    return values.at(value_index);
}

void dictionary::save_in_file(const char *filename) {
    ofstream dict_file(filename, ios::binary);

    dict_file.write((char*)&size, sizeof(size));
    dict_file.write((char*)&key_size, sizeof(key_size));
    dict_file.write((char*)&value_size, sizeof(value_size));

    dict_file.write((char*)&input_zeros, sizeof(input_zeros));
    dict_file.write((char*)&output_zeros, sizeof(output_zeros));

    write_vector_in_file(keys, dict_file);
    write_vector_in_file(values, dict_file);

    dict_file.close();
}

void dictionary::write_string_in_file(string &str, ofstream &file) {
    unsigned int str_size = str.size();
    file.write((char*)&str_size, sizeof(str_size));
    file.write(str.c_str(), str_size);
}

void dictionary::write_vector_in_file(vector<string> &vec, ofstream &file) {
    unsigned int vec_size = vec.size();
    file.write((char*)&vec_size, sizeof(vec_size));

    for(auto i : vec){
        write_string_in_file(i, file);
    }
}

void dictionary::print() {
    for(int i = 0; i < size; i++){
        cout << keys.at(i) << " - " << values.at(i) << endl;
    }
}

string dictionary::dec_to_bin(unsigned int n, unsigned int len) {
    string res;

    while(n > 0){
        if(n % 2 == 1){ res = '1' + res; }
        else{ res = '0' + res; }

        n /= 2;
    }

    unsigned int zeros = len - res.size();

    if(zeros != 0){
        for(int i = 0; i < zeros; i++){
            res = '0' + res;
        }
    }

    return res;
}
