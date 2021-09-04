#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class TextFileReader {
public:
  TextFileReader() = default;
  TextFileReader(string file_path) { myfile_.open(file_path); }

  string read_string() {
    string answer;

    if (myfile_.is_open()) {
      myfile_ >> answer;
    }
    return answer;
  }

  ~TextFileReader() = default;

private:
  ifstream myfile_;
};

bool compareLen(const std::string &a, const std::string &b) {
  return (a.size() > b.size());
}

class PhraseSeacher {
public:
  PhraseSeacher() = default;

  void set_number_and_clear_dictionary(string number) {
    number_ = number;
    clear_dictionary_();
  }

  string get_number() { return number_; }

  void add_word_to_dictionary(string const &word) {
    string string_number = word_to_string_number_(word);
    dictionary_map_[string_number] = word;
    dictionary_.push_back(string_number);
  }

  string make_phrase() {
    string phrase = "";
    sort(dictionary_.begin(), dictionary_.end(), compareLen);
    recursive_function_(number_, phrase);
    if (phrase == "")
      return "No solution.";
    return convert_numbers_to_phrase_(phrase);
  }

private:
  string number_;
  map<string, string> dictionary_map_;
  vector<string> dictionary_;

  void clear_dictionary_() {
    dictionary_.clear();
    dictionary_map_.clear();
  }

  string word_to_string_number_(string const &word) {
    string number;
    for (char letter : word) {
      if ((letter == 'i') || (letter == 'j'))
        number += "1";
      if (letter == 'a' || letter == 'b' || letter == 'c')
        number += "2";
      if (letter == 'd' || letter == 'e' || letter == 'f')
        number += "3";
      if (letter == 'g' || letter == 'h')
        number += "4";
      if (letter == 'k' || letter == 'l')
        number += "5";
      if (letter == 'm' || letter == 'n')
        number += "6";
      if (letter == 'p' || letter == 'r' || letter == 's')
        number += "7";
      if (letter == 't' || letter == 'u' || letter == 'v')
        number += "8";
      if (letter == 'w' || letter == 'x' || letter == 'y')
        number += "9";
      if (letter == 'o' || letter == 'q' || letter == 'z')
        number += "0";
    }
    return number;
  }

  string convert_numbers_to_phrase_(string numbered_phrase) {
    string phrase;

    string space_delimiter = " ";
    vector<string> words{};

    size_t pos = 0;
    while ((pos = numbered_phrase.find(space_delimiter)) != string::npos) {
      phrase += dictionary_map_[numbered_phrase.substr(0, pos)] + " ";
      numbered_phrase.erase(0, pos + space_delimiter.length());
    }
    return phrase;
  }

  void recursive_function_(string const &number, string &phrase) {
    for (auto &word : dictionary_) {
      size_t found_pos = number.find(word);
      if (found_pos != string::npos) {
        string left_substr = number.substr(0, found_pos);
        string right_substr = number.substr(found_pos + word.length());
        phrase += word + " ";

        if (left_substr != "")
          recursive_function_(left_substr, phrase);
        if (right_substr != "")
          recursive_function_(right_substr, phrase);
        return;
      }
    }
  }
};

int main() {
  const char *file_path = "/home/ivan/timus/1002/test/test.txt";
  TextFileReader reader{string(file_path)};
  PhraseSeacher seacher;

  string string_number;
  // string string_number = reader.read_string();
  getline(cin, string_number);

  seacher.set_number_and_clear_dictionary(string_number);

  while (string_number.find("-1") == string::npos) {
    int dictionary_capacity;
    // dictionary_capacity = stoi(reader.read_string());
    cin >> dictionary_capacity;

    for (int i = 0; i < dictionary_capacity; i++) {
      // seacher.add_word_to_dictionary(reader.read_string());
      string word;
      getline(cin, word);
      seacher.add_word_to_dictionary(word);
    }

    cout << seacher.make_phrase() << endl;

    // string_number = reader.read_string();
    getline(cin, string_number);
    seacher.set_number_and_clear_dictionary(string_number);
  }

  return 0;
}
