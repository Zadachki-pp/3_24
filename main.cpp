#include <iostream>
#include <cstring>


char* copy_c_string_effective(char* current_string, const char* string_to_copy) {
    size_t c_string_len = strlen(string_to_copy) + 1;
    std::copy(string_to_copy, string_to_copy + c_string_len, current_string);
}


class String {
    friend std::istream& operator>>(std::istream& input, String& string);

    char* _c_string;
    size_t _len;

    void _create_c_string(size_t len) {
        _c_string = new char[len];
    }

    void _delete_c_string() {
        delete[] _c_string;
    }

    char* _copy_c_string() {
        char* copy = new char[_len];
        copy_c_string_effective(copy, _c_string);
        return copy;
    }

    void _copy_to_c_string(const char* c_string) {
        copy_c_string_effective(_c_string, c_string);
    }

public:
    static const size_t END_POS = -1;


    String() {
        _c_string = {};
        _len = 0;
    }

    explicit String(char* c_string) { // NOLINT(cppcoreguidelines-pro-type-member-init)
        _len = std::strlen(c_string) + 1;  // str + '\0'

        _create_c_string(_len);
        _copy_to_c_string(c_string);
    }

    ~String() {
        _delete_c_string();
    }

    String(const String& other) : String(other._c_string) {}

    String& operator=(const String& other) {
        if(this == &other) {
            return *this;
        }

        _delete_c_string();

        _create_c_string(other._len);
        _copy_to_c_string(other._c_string);
    }

    String operator+(const String& other) {
        _len += other._len-1;

        auto new_c_string = _copy_c_string();
        _delete_c_string();

        _c_string = new_c_string;
        strcat(_c_string, other._c_string);

        return *this;
    }

    String operator+=(const String& other) {
        *this = *this + other;
        return *this;
    }

    char& operator[](size_t index) {
        return _c_string[index];
    }

    char& at(size_t index) {
        if (index >= (_len-1)) {
            std::cerr << "Index out of range" << std::endl;
            exit(1);
        }

        return _c_string[index];
    }

    bool operator==(const String& other){
        return strcmp(_c_string, other._c_string) == 0;
    }

    bool operator<(const String& other) {
        return strcmp(_c_string, other._c_string) < 0;
    }

    bool operator>(const String& other) {
        return !(*this < other) && !(*this == other);
    }

    bool operator!=(const String& other){
        return !(*this == other);
    }

    size_t find(const char char_){
        char* pointer = strchr(_c_string, char_);
        if (pointer == nullptr) {
            return END_POS;
        }

        return (pointer - _c_string);
    }

    size_t length() const {
        return (_len-1);
    }

    const char* c_str() const {
        return _c_string;
    }
};

std::istream& operator>>(std::istream& input, String& string) {
    std::cin >> string._len >> string._c_string;
    return input;
}

std::ostream& operator<<(std::ostream& output, const String& string) {
    return (output << string.c_str());
}


int main() {
    String a("cat");
    a.at(2) = 'm';
    std::cout << a << std::endl;

    return 0;
}
