#ifndef BIG_INTEGER_HPP
#define BIG_INTEGER_HPP
#include <iostream>
#include <string>

#define minus true
#define plus false

enum class biginteger_base { dec = 10, hex = 16 };

static const unsigned long long base = 4294967296;

class BigInteger {
 private:
  unsigned int* array_num_ = nullptr;
  size_t size_;
  size_t capacity_;
  bool sign_;  // 0 - plus //1 - minus
 public:
  /* C O N S T R U C T O R S*/
  BigInteger();
  BigInteger(const BigInteger& other);
  BigInteger(int nm);
  BigInteger(unsigned int nm);
  BigInteger(long nm);
  BigInteger(unsigned long nm);
  BigInteger(long long nm);
  BigInteger(unsigned long long nm);
  explicit BigInteger(
      const std::string& str,
      biginteger_base base = biginteger_base::dec);  // êîíñòðóêòîð îò ñòðîêè
  BigInteger(BigInteger&& other) noexcept;           // êîíñòðóêòîð ïåðåìåùåíèÿ

  /* D E S T R U C T O R */
  ~BigInteger();

  /*B O O L	O P E R A T O R S*/
  bool operator==(BigInteger const& other) const;
  bool operator!=(BigInteger const& other) const;
  bool operator<(BigInteger const& other) const;
  bool operator>(BigInteger const& other) const;
  bool operator<=(BigInteger const& other) const;
  bool operator>=(BigInteger const& other) const;

  /*B I N A R Y	O P E R A T O R S*/
  BigInteger& operator+=(BigInteger const& other);
  BigInteger operator+(BigInteger const& other) const;
  friend BigInteger operator+(BigInteger current, long long int other) {
    return current.sum_basic(BigInteger(std::to_string(other)));
  }
  friend BigInteger operator+(long long int current, BigInteger other) {
    return other.sum_basic(BigInteger(std::to_string(current)));
  }
  BigInteger& operator*=(BigInteger const& other);
  BigInteger operator*(BigInteger const& other) const;
  BigInteger& operator/=(BigInteger const& other);
  BigInteger operator/(BigInteger const& other) const;
  BigInteger& operator-=(BigInteger const& other);
  BigInteger operator-(BigInteger const& other) const;
  BigInteger& operator%=(BigInteger const& other);
  BigInteger operator%(BigInteger const& other) const;

  BigInteger& operator=(const BigInteger& other);  // îïåðàòîð ïðèñâàèâàíèÿ
  BigInteger& operator=(
      BigInteger&& other) noexcept;  // îïåðàòîð ïðèñâàèâàíèÿ ïåðåìåùåíèåì

  /*U N A R Y		O P E R A T O R S*/
  BigInteger operator-() const;
  BigInteger operator+() const;
  BigInteger& operator++();
  BigInteger& operator--();
  BigInteger operator++(int);
  BigInteger operator--(int);

  /*F U N C T I O N S*/
  std::string to_hex_string() const;
  std::string to_dec_string() const;
  BigInteger abs() const;

  bool sign() const { return sign_; }
  size_t size() const { return size_; }
  size_t capacity() const { return capacity_; }
  void print();
  bool is_odd();

 private:
  /*H E L P F U L		F U N C T I O N S*/
  void remove_leading_zeros();

  void expand(unsigned long long new_capacity);
  bool is_zero() const;

  BigInteger sum_basic(const BigInteger& other);
  BigInteger dif_basic(const BigInteger& other);
  BigInteger mul_basic(const BigInteger& other);
  BigInteger div_basic(const BigInteger& other, BigInteger& remainder);
  BigInteger mod_basic(const BigInteger& other);
  void print_dec() const;
  void sdvig_left(size_t);
};

void copy(const unsigned int* from, unsigned int*& to, size_t size_from,
          size_t& size_to);

bool my_isdigit(char c);
bool my_isxdigit(char c);
char my_tolower(char c);
int hex_char_to_int(char c);

int cmp_arr(const unsigned int* a, const unsigned int* b, size_t size);
char hex_block_to_hex_char(unsigned int symbol);

BigInteger binpow(BigInteger bs, BigInteger exp);
BigInteger binmodpow(BigInteger bs, BigInteger exp, const BigInteger& modulus);

std::string to_string(const BigInteger&);
std::string to_hex(const BigInteger&);

#endif
