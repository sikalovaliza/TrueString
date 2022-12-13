#include <cstdlib>
#include <cstring>
#include <iostream>

class String {
 public:
  String(size_t size, char element = '\0') {
    size_of_string_ = size;
    capacity_ = 2 * size_of_string_;
    std::free(array_of_string_);
    array_of_string_ =
        static_cast<char*>(std::malloc(capacity_ * sizeof(char)));
    memset(array_of_string_, element, size_of_string_);
    array_of_string_[size_of_string_] = '\0';
  }

  String(const char* new_string) {
    if (new_string != nullptr) {
      size_t count = strlen(new_string);
      capacity_ = 1 + int(count << 1);
      std::free(array_of_string_);
      array_of_string_ =
          static_cast<char*>(std::malloc(capacity_ * sizeof(char)));
      memcpy(array_of_string_, new_string, count);
      size_of_string_ = count;
      array_of_string_[count] = '\0';
    }
  }

  String() = default;

  String(const String& new_string) : String(new_string.data()) {}

  String(const char kElement) : String(1, kElement) {}
  String& operator+=(const String& right_string) {
    while (size_of_string_ + right_string.size_of_string_ >= capacity_) {
      capacity_ = 2 * capacity_ + 1;
      array_of_string_ = static_cast<char*>(
          std::realloc(array_of_string_, capacity_ * sizeof(char)));
    }
    memcpy(array_of_string_ + size_of_string_, right_string.array_of_string_,
           right_string.size_of_string_);
    size_of_string_ += right_string.size_of_string_;
    array_of_string_[size_of_string_] = '\0';
    return *this;
  }

  String& operator=(const String& string_new) {
    if (string_new.size_of_string_ == 0) {
      std::free(array_of_string_);
      array_of_string_ = nullptr;
      return *this;
    }
    if (capacity_ < string_new.capacity_) {
      capacity_ = string_new.capacity_ + 1;
      array_of_string_ = static_cast<char*>(
          std::realloc(array_of_string_, capacity_ * sizeof(char)));
    }
    size_of_string_ = string_new.size_of_string_;
    memcpy(array_of_string_, string_new.array_of_string_, size_of_string_);
    return *this;
  }

  char& operator[](size_t index) {
    if (index < size_of_string_) {
      return array_of_string_[index];
    }
    static char value = '\0';
    return value;
  }

  const char& operator[](size_t index) const {
    if (index < size_of_string_) {
      return array_of_string_[index];
    }
    static char value = '\0';
    return value;
  }

  String substr(size_t start, size_t count) const {
    if (start + count < size_of_string_ + 1) {
      String new_string;
      new_string.capacity_ = 2 * count + 1;
      new_string.array_of_string_ =
          static_cast<char*>(std::malloc(new_string.capacity_ * sizeof(char)));
      new_string.size_of_string_ = count;
      memcpy(new_string.array_of_string_, array_of_string_ + start, count);
      new_string[size_of_string_] = '\0';
      return new_string;
    }
    return '\0';
  }

  size_t find(const String kSubstring) const {
    size_t count = 0;
    size_t index_substring = 0;
    size_t index = 0;
    while (index < size_of_string_) {
      if (array_of_string_[index] == kSubstring[index_substring]) {
        ++count;
        ++index_substring;
        if (count == kSubstring.size()) {
          return index - count + 1;
        }
      } else {
        index -= count;
        count = 0;
        index_substring = 0;
      }
      ++index;
    }
    return size_of_string_;
  }

  size_t rfind(const String kSubstring) const {
    size_t count = 0;
    size_t index_substring = kSubstring.size_of_string_ - 1;
    size_t index = size_of_string_ - 1;
    while (index < size_of_string_) {
      if (array_of_string_[index] == kSubstring[index_substring]) {
        ++count;
        --index_substring;
        if (count == kSubstring.size()) {
          return index;
        }
      } else {
        index += count;
        count = 0;
        index_substring = kSubstring.size_of_string_ - 1;
      }
      --index;
    }
    return size_of_string_;
  }

  void push_back(char element) {
    if (capacity_ == 0) {
      capacity_ = 2;
      array_of_string_ = static_cast<char*>(
          realloc(array_of_string_, capacity_ * sizeof(char)));
    }
    if (size_of_string_ + 1 >= capacity_) {
      capacity_ <<= 1;
      array_of_string_ = static_cast<char*>(
          realloc(array_of_string_, capacity_ * sizeof(char)));
    }
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
    array_of_string_ = static_cast<char*>(
        realloc(array_of_string_, size_of_string_ * sizeof(char)));
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
};

String operator+(const String& left_string, const String& right_string) {
  String new_string = left_string;
  return new_string += right_string;
}

bool operator<(const String& left_string, const String& right_string) {
  for (size_t index = 0;
       index < std::max(left_string.size(), right_string.size()); ++index) {
    if (right_string[index] < left_string[index]) {
      return false;
    }
    if (left_string[index] < right_string[index]) {
      return true;
    }
  }
  return false;
}

bool operator>(const String& left_string, const String& right_string) {
  for (size_t index = 0;
       index < std::max(left_string.size(), right_string.size()); ++index) {
    if (right_string[index] < left_string[index]) {
      return true;
    }
    if (left_string[index] < right_string[index]) {
      return false;
    }
  }
  return false;
}

bool operator<=(const String& left_string, const String& right_string) {
  for (size_t index = 0;
       index < std::max(left_string.size(), right_string.size()); ++index) {
    if (right_string[index] < left_string[index]) {
      return false;
    }
  }
  return true;
}
bool operator>=(const String& left_string, const String& right_string) {
  for (size_t index = 0;
       index < std::max(left_string.size(), right_string.size()); ++index) {
    if (left_string[index] < right_string[index]) {
      return false;
    }
  }
  return true;
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
  if (left_string.size() != right_string.size()) {
    return true;
  }
  for (size_t index = 0; index < left_string.size(); ++index) {
    if (left_string[index] != right_string[index]) {
      return true;
    }
  }
  return false;
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
