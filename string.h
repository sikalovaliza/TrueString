#include <cstdlib>
#include <cstring>
#include <iostream>

class String {
 public:
  explicit String(size_t size, char element = '\0')
      : size_of_string_{size}, capacity_{size + 1} {
    array_of_string_ =
        static_cast<char*>(std::malloc(capacity_ * sizeof(char)));
    memset(array_of_string_, element, size_of_string_);
    array_of_string_[size_of_string_] = '\0';
  }

  String(const char* new_string) : size_of_string_(0), capacity_(0) {
    if (new_string != nullptr) {
      size_t count = strlen(new_string);
      capacity_ = count + 1;
      array_of_string_ =
          static_cast<char*>(std::malloc(capacity_ * sizeof(char)));
      memcpy(array_of_string_, new_string, count);
      size_of_string_ = count;
      array_of_string_[count] = '\0';
    }
  }

  String() {
    capacity_ = 1;
    array_of_string_ =
        static_cast<char*>(std::malloc(capacity_ * sizeof(char)));
    array_of_string_[0] = '\0';
  }

  String(const String& new_string) : String(new_string.data()) {}

  String(const char kElement) : String(1, kElement) {}
  
  String& reserve(const String& new_string) {
    if (capacity_ < size_of_string_ + new_string.size_of_string_) {
      capacity_ = std::max(2 * capacity_ + 1,
                           size_of_string_ + new_string.size_of_string_);
      array_of_string_ = static_cast<char*>(
          std::realloc(array_of_string_, capacity_ * sizeof(char)));
    }
    return *this;
  }
  
  String& operator+=(const String& right_string) {
    reserve(right_string);
    memcpy(array_of_string_ + size_of_string_, right_string.array_of_string_,
           right_string.size_of_string_);
    size_of_string_ += right_string.size_of_string_;
    array_of_string_[size_of_string_] = '\0';
    return *this;
  }

  String& swap(String& string_new) {
    std::swap(size_of_string_, string_new.size_of_string_);
    std::swap(array_of_string_, string_new.array_of_string_);
    std::swap(capacity_, string_new.capacity_);
    return *this;
  }
  
  String& operator=(const String& right_string) {
    String new_string{right_string};
    return swap(new_string);
  }
  const char& operator[](size_t index) const { return array_of_string_[index]; }

  char& operator[](size_t index) { return array_of_string_[index]; }

  String substr(size_t start, size_t count) const {
    if (start + count < size_of_string_ + 1) {
      String new_string(count);
      memcpy(new_string.array_of_string_, array_of_string_ + start, count);
      new_string[size_of_string_] = '\0';
      return new_string;
    }
    return '\0';
  }

  size_t find(const String kSubstring) const {
    return universalfind(true, kSubstring);
  }

  size_t rfind(const String kSubstring) const {
    return universalfind(false, kSubstring);
  }

  void push_back(char element) {
    reserve(element);
    array_of_string_[size_of_string_] = element;
    array_of_string_[size_of_string_ + 1] = '\0';
    ++size_of_string_;
  }

  void pop_back() {
    size_of_string_ -= 1;
    array_of_string_[size_of_string_] = '\0';
  }

  void clear() {
    size_of_string_ = 0;
    array_of_string_[0] = '\0';
  }

  void shrink_to_fit() {
    capacity_ = size_of_string_ + 1;
    array_of_string_ =
        static_cast<char*>(realloc(array_of_string_, capacity_ * sizeof(char)));
  }

  size_t length() const { return size_of_string_; }

  size_t size() const { return size_of_string_; }

  size_t capacity() const { return capacity_ - 1; }

  const char& front() const { return array_of_string_[0]; }

  char& front() { return array_of_string_[0]; }

  const char& back() const { return array_of_string_[size_of_string_ - 1]; }

  char& back() { return array_of_string_[size_of_string_ - 1]; }

  bool empty() const { return size_of_string_ == 0; }

  char* data() { return array_of_string_; }

  const char* data() const { return array_of_string_; }

  ~String() {
    if (capacity_ > 0) {
      std::free(array_of_string_);
    }
  }

 private:
  size_t size_of_string_ = 0;
  size_t capacity_ = 0;
  char* array_of_string_ = nullptr;
  
  size_t static change(bool first, size_t value_first, size_t value_second) {
    if (first) {
      return value_first;
    }
    return value_second;
  }
  
  size_t universalfind(bool first, const String kSubstring) const {
    size_t count = 0;
    size_t index_substring = 0;
    size_t index = 0;
    if (!first) {
      index_substring = change(first, 0, kSubstring.size_of_string_ - 1);
      index = change(first, 0, size_of_string_ - 1);
    }
    while (index < size_of_string_) {
      if (array_of_string_[index] == kSubstring[index_substring]) {
        ++count;
        index_substring =
            change(first, index_substring + 1, index_substring - 1);
        if (count == kSubstring.size()) {
          return change(first, index - count + 1, index);
        }
      } else {
        index = change(first, index - count, index + count);
        index_substring = change(first, 0, kSubstring.size_of_string_ - 1);
        count = 0;
      }
      index = change(first, index + 1, index - 1);
    }
    return size_of_string_;
  }
};

String operator+(const String& left_string, const String& right_string) {
  String new_string = left_string;
  return new_string += right_string;
}

bool operator<(const String& left_string, const String& right_string) {
  for (size_t index = 0;
       index < std::max(left_string.size(), right_string.size()); ++index) {
    if (left_string[index] != right_string[index]) {
      return left_string[index] < right_string[index];
    }
  }
  return false;
}

bool operator>(const String& left_string, const String& right_string) {
  return right_string < left_string;
}

bool operator<=(const String& left_string, const String& right_string) {
  return !(right_string < left_string);
}
bool operator>=(const String& left_string, const String& right_string) {
  return !(left_string < right_string);
}

bool operator==(const String& left_string, const String& right_string) {
  if (left_string.size() != right_string.size()) {
    return false;
  }
  for (size_t index = 0; index < left_string.size(); ++index) {
    if (left_string[index] != right_string[index]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const String& left_string, const String& right_string) {
  return !(left_string == right_string);
}

std::ostream& operator<<(std::ostream& output, const String& new_string) {
  if (new_string.data() == nullptr) {
    return output;
  }
  return output << new_string.data();
}

std::istream& operator>>(std::istream& input, String& new_string) {
  new_string = "\0";
  char element = input.get();
  while (!input.eof() && !static_cast<bool>(std::isspace(element))) {
    new_string.push_back(element);
    element = input.get();
  }
  return input;
}
