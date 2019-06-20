struct fastio_t {
  int base;
  FILE *in, *out;
  int ptr_in, ptr_out;
  char *buffer_in, *buffer_out;
  static constexpr int max_buffer = 1 << 10;
  
  fastio_t(FILE *in = stdin, FILE *out = stdout) : in(in), out(out) {
    buffer_in = new char[max_buffer + 1];
    buffer_out = new char[max_buffer + 1];
    ptr_in = max_buffer; ptr_out = 0; base = 10;
  }
  
  ~fastio_t() { delete buffer_in; delete buffer_out; }
  
  inline char gchar() {
    if (ptr_in == max_buffer || !~buffer_in[ptr_in]) {
      //fgets(buffer_in, max_buffer, in); // with 'in' flush, but slower
      fread(buffer_in, 1, max_buffer, in); // without 'in' flush, but faster
      ptr_in = 0;
    }
    return buffer_in[ptr_in++];
  }
  
  inline void show() { fwrite(buffer_out, 1, ptr_out, out); ptr_out = 0; }
  
  inline void skip() { while (isspace(gchar())); ptr_in--; }
  
  template <class T>
  inline bool gint(T &x) {
    skip();
    static bool neg; neg = gchar() == '-';
    if (!neg) ptr_in--;
    static char c;
    static int n; n = 0;
    x = 0;
    while (true) {
      c = gchar();
      if (isdigit(c)) c -= '0';
      else if (isupper(c)) c -= 'A' - 10;
      else if (islower(c)) c -= 'a' - 10;
      else c = base;    
      if (c >= base) break;
      x = base * x + c;
      n++;
    }
    ptr_in--;
    x = neg ? ~static_cast<T>(x - 1) : static_cast<T>(x);
    return n > 0;
  }
  
  inline void pchar(char c) {
    if (__builtin_expect(ptr_out == max_buffer, true)) show();
    buffer_out[ptr_out++] = c;
  }
  
  inline void pstr(const string &s) {
    for (char c : s) pchar(c);
  }
  
  template <class T>
  inline void pint(T x) {
    if (is_signed<T>::value) {
      if (x < 0) {
        x = -x, pchar('-');
      }
    }
    if (!x) pchar('0');
    else {
      static int ptr; ptr = 0;
      static uint8_t buffer[20];
      while (x) {
        buffer[ptr++] = x % base;
        x /= base;
      }
      static char c;
      while (ptr > 0) {
        c = buffer[--ptr] % base;
        if (__builtin_expect(c > 9, true)) c += 'A' - 10;
        else c += '0';
        pchar(c);
      }
    }
  }
};
