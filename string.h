#include<cstring>
#include<iostream>

class String {
private:
  char* str = nullptr;
  size_t size_of_string = 0;
  size_t capacity = 0;
  
public:
  explicit String(size_t size, char c = '\0') {
    size_of_string = size;
    capacity = 2 * size_of_string;
    str = (char*)malloc(capacity);
    memset(str, c, size_of_string);
  }
  
  String();
  
  String(const String& s): String(s.size_of_string, '\0') {
    memcpy(str, s.str, size_of_string);
  }
  
  String(const char c) : String(1, c) {}
  
  String(std::initializer_list<char> lst) {
    size_of_string = lst.size();
    capacity = 2 * size_of_string;
    str = (char*)malloc(capacity);
    std::copy(lst.begin(), lst.end(), str);
  }
  
  String& operator+=(const String& rhs) {
    while (size_of_string + rhs.size_of_string >= capacity) {
        str = (char*)realloc(str, 2 * size_of_string);
        capacity <<= 1;
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
    return str[index];
  }
  
  const char& operator[](size_t index) const {
    return str[index];
  }
  
  bool operator==(const String& rhs) const {
    return strcmp(str, rhs.str) == 0;
  }
  
  bool operator!=(const String& rhs) const {
    return !(*this == rhs);
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
  
 String substr(size_t start, size_t count) {
    String new_string;
    new_string.capacity = 2 * count;
    new_string.str = (char*)malloc(new_string.capacity);
    new_string.size_of_string = count;
    memcpy(new_string.str, str + start, count - 1);
   return new_string;
 }
  
  size_t find(String substring) {
    size_t count = 0;
    size_t index_substring = 0;
    size_t index = 0;
    while (index < size_of_string) {
      if (str[index] == substring[index_substring]) {
        ++count;
        ++index_substring;
        if (count == substring.size()) {
          return index - count + 1;
        }
      } else {
        index -= count;
        count = 0;
        index_substring = 0;
      }
      ++index;
    }
    return size_of_string;
  }
                                 
  size_t rfind(String substring) {
    size_t count = 0;
    size_t index_substring = substring.size_of_string - 1;
    size_t index = size_of_string - 1;
    while (index < size_of_string) {
      if (str[index] == substring[index_substring]) {
        ++count;
        --index_substring;
        if (count == substring.size()) {
          return index;
        }
      } else {
        index += count;
        count = 0;
        index_substring = substring.size_of_string - 1;
      }
      --index;
    }
    return size_of_string;
  }
                                 
  void push_back(char add) {
    if (size_of_string + 1 == capacity) {
      str = (char*)realloc(str, size_of_string * 2);
      capacity *= 2;
    }
    str[size_of_string] = add;
    ++size_of_string;
   }
  
  void pop_back() {
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
  
 size_t length() const {
    return size_of_string;
  }
  
  size_t size() const {
     return size_of_string;
   }
  
  size_t Capacity() const {
     return capacity;
   }
  
 const char& front() const {
    return str[0];
  }
  
 char& front() {
     return str[0];
  }
  
 const char& back() const {
    return str[size_of_string - 1];
  }
  
  char& back() {
    return str[size_of_string - 1];
  }
  
  bool empty() const{
    return size_of_string == 0;
  }
  
  char* data() {
    return str;
  }
  
  const char* data() const {
    return str;
  }
  
~String() {
  if (capacity > 0) {
    free(str);
  }
 }
};

std::ostream& operator<<(std::ostream &out, const String &new_string) {
  out << new_string.data();
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
