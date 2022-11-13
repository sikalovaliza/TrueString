#include<cstring>
#include<iostream>

class String {
private:
  char* str = nullptr;
  size_t size_of_string = 0;
  size_t capacity_ = 0;
  
public:
  explicit String(size_t size, char c = '\0') {
    size_of_string = size;
    capacity_ = 2 * size_of_string;
    str = (char*)malloc(capacity_);
    memset(str, c, size_of_string);
    str[size_of_string] = '\0';
  }
  
  String(const char* snew) {
    size_t count = strlen(snew);
    capacity_ = count << 1;
    str = (char*)malloc(capacity_);
    memcpy(str, snew, count);
    size_of_string = count;
    str[count] = '\0';
  }
  
  
  String() = default;
  
  String(const String& s): String(s.size_of_string, '\0') {
    memcpy(str, s.str, size_of_string);
  }
  
  String(const char c) : String(1, c) {}
  
  String(std::initializer_list<char> lst) {
    size_of_string = lst.size();
    capacity_ = size_of_string << 1;
    str = (char*)malloc(capacity_);
    std::copy(lst.begin(), lst.end(), str);
    str[size_of_string] = '\0';
  }
  
  String& operator+=(const String& rhs) {
    while (size_of_string + rhs.size_of_string >= capacity_) {
        str = (char*)realloc(str, 2 * size_of_string);
        capacity_ <<= 1;
    }
    memcpy(str + size_of_string, rhs.str, rhs.size_of_string);
    size_of_string += rhs.size_of_string;
    str[size_of_string] = '\0';
    return *this;
  }
  
  String& operator=(const String& string_new) {
    String copy = string_new;
    swap(copy);
    return *this;
  }
  
  void swap(String& string_new) {
    std::swap(str, string_new.str);
    std::swap(size_of_string, string_new.size_of_string);
  }
  
  
  char& operator[](size_t index) {
    return str[index];
  }
  
  const char& operator[](size_t index) const {
    return str[index];
  }
  
  friend std::ostream& operator<<(std::ostream &out, const String &String);
  friend std::istream& operator>>(std::istream &in, String &String);
  
 String& substr(size_t start, size_t count) {
   String new_string;
   new_string.capacity_ = count << 1;
   new_string.str = (char*)malloc(new_string.capacity_);
   new_string.size_of_string = count;
   memcpy(new_string.str, str + start, count - 1);
   new_string[size_of_string] = '\0';
   return new_string;
 }
  
  size_t find(String& substring) {
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
                                 
  size_t rfind(String& substring) {
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
    if (size_of_string + 1 == capacity_) {
      str = (char*)realloc(str, size_of_string * 2);
      capacity_ <<= 1;
    }
    str[size_of_string] = add;
    str[size_of_string + 1] = '\0';
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
  
  void shrink_to_fit() {
    capacity_ = size_of_string + 1;
    str = (char*)realloc(str, size_of_string);
  }
  
 size_t length() const {
    return size_of_string;
  }
  
  size_t size() const {
     return size_of_string;
   }
  
  size_t capacity() const {
     return capacity_;
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
  if (capacity_ > 0) {
    free(str);
  }
 }
};

String operator+(const String& string_old, const String& rhs) {
  String new_string = string_old;
  return new_string += rhs;
}



bool operator<(const String& string_old, const String& rhs) {
  for (size_t index = 0; index < std::max(string_old.size(), rhs.size()); ++index) {
    if (string_old[index] > rhs[index]) {
      return 0;
    }
    if (string_old[index] < rhs[index]) {
      return 1;
    }
  }
  return 0;
}

bool operator>(const String& string_old, const String& rhs) {
  for (size_t index = 0; index < std::max(string_old.size(), rhs.size()); ++index) {
    if (string_old[index] > rhs[index]) {
      return 1;
    }
    if (string_old[index] < rhs[index]) {
      return 0;
    }
  }
  return 0;
}


bool operator<=(const String& string_old, const String& rhs) {
  for (size_t index = 0; index < std::max(string_old.size(), rhs.size()); ++index) {
    if (string_old[index] > rhs[index]) {
      return 0;
    }
  }
  return 1;
}

bool operator>=(const String& string_old, const String& rhs) {
  for (size_t index = 0; index < std::max(string_old.size(), rhs.size()); ++index) {
    if (string_old[index] < rhs[index]) {
      return 0;
    }
  }
  return 1;
}

bool operator==(const String& string_old, const String& rhs)  {
  if (string_old.size() != rhs.size()) {
    return 0;
  }
  for(size_t index = 0; index < string_old.size(); ++index) {
    if (string_old[index] != rhs[index]) {
      return 0;
    }
  }
  return 1;
}

bool operator!=(const String& string_old, const String& rhs)  {
  if (string_old.size() != rhs.size()) {
    return 1;
  }
  for(size_t index = 0; index < string_old.size(); ++index) {
    if (string_old[index] != rhs[index]) {
      return 1;
    }
  }
  return 0;
}

std::ostream& operator<<(std::ostream &out, const String &new_string) {
  out << new_string.data();
  return out;
}

std::istream& operator>>(std::istream &in, String &new_string) {
  for (size_t i = 0; i <= new_string.size_of_string; i++) {
    in >> new_string[i];
  }
  new_string[new_string.size_of_string] = '\0';
  return in;
}
