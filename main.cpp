#include<cstring>
#include<iostream>
class String {
private:
  char* str = nullptr;
  int sz = 0;
  int capacity = 0;
  
public:
  String(int sz, char c = '\0') {
    this->sz = sz;
    str = (char*)malloc(2 * sz);
    capacity = 2 * sz;
    memset(str, c, sz);
  }
  
  String() = default;
  
  String(const String& s): String(s.sz, '\0') {
    memcpy(str, s.str, sz);
  }
  
  String(const char c) : String(1, c) {}
  
  String(std::initializer_list<char> lst) {
    sz = lst.size();
    str = (char*)malloc(2 * sz);
    capacity = 2 * sz;
    std::copy(lst.begin(), lst.end(), str);
  }
  
  // malloc, realloc, calloc == C, free
  String& operator+=(const String& rhs) {
    while (sz + rhs.sz >= capacity) {
        str = (char*)realloc(str, 2 * sz);
        capacity *= 2;
    }
    memcpy(str + sz, rhs.str, rhs.sz);
    sz += rhs.sz;
    return *this;
  }
  
  String operator+(const String& rhs) const {
    String snew = *this;
    return snew += rhs;
  }
  
  char& operator[](int index) {
    return str[index]; // == *(str + index)
  }
  
  const char& operator[](int index) const {
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
  
 String substr(int start, int count) {
    String snew;
    snew.str = (char*)malloc(2 * count);
    snew.sz = count;
    snew.capacity = 2 * count;
    std::copy(str + start, str + count - 1, snew.str);
    return snew;
  }
  
  int find(String substring) {
    int kol = 0;
    int index_sub = 0;
    for (int i = 0; i < sz; ++i) {
      if (str[i] == substring[index_sub]) {
        ++kol;
        ++index_sub;
        if (kol == substring.length()) {
          return i - kol + 1;
        }
      } else {
        kol = 0;
        index_sub = 0;
        if (str[i] == substring[0]) {
          ++kol;
          ++index_sub;
        }
      }
    }
    return sz;
  }
                                 
  int rfind(String substring) {
    int kol = 0;
    int index_sub = substring.sz - 1;
    for (int i = sz - 1; i >= 0; --i) {
      if (str[i] == substring[index_sub]) {
        ++kol;
        --index_sub;
        if (kol == substring.length()) {
          return i;
        }
      } else {
        kol = 0;
        index_sub = 0;
        if (str[i] == substring[substring.sz - 1]) {
          ++kol;
          --index_sub;
        }

      }
    }
    return sz;
  }
                                 
  void push_back(char add) {
    if (sz + 1 == capacity) {
      str = (char*)realloc(str, sz * 2);
      capacity *= 2;
    }
    str[sz] = add;
    sz += 1;
   }
  
  void pop_back() {
    sz -= 1;
    str[sz] = '\0';
  }
  void clear() {
    sz = 0;
    str = nullptr;
  }
  
  void shrink_to_fit() {
    str = (char*)realloc(str, sz);
  }
  
 int length() const {
    return sz;
  }
  
 const char& front() const {
    return str[0];
  }
  
 char& front() {
     return str[0];
  }
  
 const char& back() const {
    return str[sz - 1];
  }
  
  char& back() {
    return str[sz - 1];
  }
  
  bool empty() const{
    return sz == 0;
  }
  
  char* data() {
    return str;
  }
  
  const char* data() const {
    return str;
  }
  
~String() {
  free(str);
 }
};

std::ostream& operator<<(std::ostream &out, const String &String) {
  for (int i = 0; i < String.sz; i++) {
    out << String.str[i];
  }
  return out;
}

std::istream& operator>>(std::istream &in, String &String) {
  for (int i = 0; i < String.sz; i++) {
    in >> String.str[i];
  }
  return in;
}
