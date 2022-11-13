#include<cstring>
#include<iostream>

class String {
private:
  char* str = nullptr;
  size_t size_of_string = 0;
  size_t capacity = 0;
  
public:
  explicit String(size_t size_of_string, char c = '\0') {
    this->size_of_string = size_of_string;
    capacity = 2 * size_of_string;
    str = (char*)malloc(capacity);
    memset(str, c, size_of_string);
  }
  
  String() = default;
  
  String(const String& s): String(s.size_of_string, '\0') {
    memcpy(str, s.str, size_of_string);
  }
  
  String(const char c) : String(1, c) {}
  
  String(std::initializer_list<char> lst) {
    size_of_string = lst.size();
    str = (char*)malloc(2 * size_of_string);
    capacity = 2 * size_of_string;
    std::copy(lst.begin(), lst.end(), str);
  }
  
  // malloc, realloc, calloc == C, free
  String& operator+=(const String& rhs) {
    while (size_of_string + rhs.size_of_string >= capacity) {
        str = (char*)realloc(str, 2 * size_of_string);
        capacity *= 2;
    }
    memcpy(str + size_of_string, rhs.str, rhs.size_of_string);
    size_of_string += rhs.size_of_string;
    return *this;
  }
  
  String operator+(const String& rhs) const {
    String new_string = *this;
    return new_string += rhs;
  }
  
  char& operator[](size_t index) {
    return str[index]; // == *(str + index)
  }
  
  const char& operator[](size_t index) const {
    return str[index];
  }
  
  bool operator==(const String& rhs) const {
    return strcmp(str, rhs.str) == 0;
  }
  
  bool operator!=(const String& rhs) const {
    return strcmp(str, rhs.str) != 0;
  }
  
  bool operator<(const String& rhs) const {
    return strcmp(str, rhs.str) < 0;
  }
  
  bool operator>(const String& rhs) const {
    return strcmp(str, rhs.str) > 0;
  }

  bool operator<=(const String& rhs) const {
    return strcmp(str, rhs.str) <= 0;
  }
  
  bool operator>=(const String& rhs) const {
    return strcmp(str, rhs.str) >= 0;
  }
  
  friend std::ostream& operator<<(std::ostream &out, const String &String);
  friend std::istream& operator>>(std::istream &in, String &String);
  
 String Substr(size_t start, size_t count) {
    String new_string;
    new_string.str = (char*)malloc(2 * count);
    new_string.size_of_string = count;
    new_string.capacity = 2 * count;
    std::copy(str + start, str + count - 1, new_string.str);
   return new_string;
 }
  
  size_t Find(String substring) {
    size_t count = 0;
    size_t index_substring = 0;
    for (size_t index = 0; index < size_of_string; ++index) {
      if (str[index] == substring[index_substring]) {
        ++count;
        ++index_substring;
        if (count == substring.Size()) {
          return index - count + 1;
        }
      } else {
        count = 0;
        index_substring = 0;
        if (str[index] == substring[0]) {
          ++count;
          ++index_substring;
        }
      }
    }
    return size_of_string;
  }
                                 
  size_t Rfind(String substring) {
    size_t count = 0;
    size_t index_substring = substring.size_of_string - 1;
    for (size_t index = size_of_string - 1; index < size_of_string; --index) {
      if (str[index] == substring[index_substring]) {
        ++count;
        --index_substring;
        if (count == substring.Size()) {
          return index;
        }
      } else {
        count = 0;
        index_substring = 0;
        if (str[index] == substring[substring.size_of_string - 1]) {
          ++count;
          --index_substring;
        }

      }
    }
    return size_of_string;
  }
                                 
  void Push_back(char add) {
    if (size_of_string + 1 == capacity) {
      str = (char*)realloc(str, size_of_string * 2);
      capacity *= 2;
    }
    str[size_of_string] = add;
    size_of_string += 1;
   }
  
  void Pop_back() {
    size_of_string -= 1;
    str[size_of_string] = '\0';
  }
  void clear() {
    size_of_string = 0;
    str = nullptr;
  }
  
  void Shrink_to_fit() {
    capacity = size_of_string + 1;
    str = (char*)realloc(str, size_of_string);
  }
  
 size_t Length() const {
    return size_of_string;
  }
  
  size_t Size() const {
     return size_of_string;
   }
  
  size_t Capacity() const {
     return this->capacity;
   }
  
 const char& Front() const {
    return str[0];
  }
  
 char& Front() {
     return str[0];
  }
  
 const char& Back() const {
    return str[size_of_string - 1];
  }
  
  char& Back() {
    return str[size_of_string - 1];
  }
  
  bool Empty() const{
    return size_of_string == 0;
  }
  
  char* Data() {
    return str;
  }
  
  const char* Data() const {
    return str;
  }
  
~String() {
  if (capacity > 0) {
    free(str);
  }
 }
};

std::ostream& operator<<(std::ostream &out, const String &new_string) {
  out << new_string.Data();
  return out;
}

std::istream& operator>>(std::istream &in, String &new_string) {
  new_string.str = (char*)realloc(new_string.str, new_string.size_of_string * 2);
  new_string[new_string.size_of_string] = '\0';
  for (size_t i = 0; i <= new_string.size_of_string; i++) {
    in >> new_string.str[i];
  }
  return in;
}