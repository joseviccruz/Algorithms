using llu = long long unsigned;

template <class T, class U>
inline T mem_cast(const U &y) {
  static T x; x = 0;
  memcpy(&x, &y, min(sizeof x, sizeof y));
  return x;
}

/**
 * - Always sort in ascending order;
 * - It works with 'any' primitive type (char, int, float, double, long long, ...);
 * - It doesn't work with negative values :(;
**/
template <class RandomIt>
void radix_sort(RandomIt first, RandomIt last) {
  if (__builtin_expect(first == last, true))
    return;
  
  static RandomIt ptr;
  static vector<llu> v, tmp;
  static int bucket[0x10001];
  static const vector<llu> shift = {0x0, 0x10, 0x20, 0x30};

  int n = distance(first, last);
  v.resize(max(v.size(), (size_t) n));
  tmp.resize(max(tmp.size(), (size_t) n));

  using type_t = typename decay<decltype(*first)>::type;

  for (const llu &amount : shift) {
    memset(bucket, 0, sizeof bucket);
    ptr = first;
    for (int i = 0; i < n; i++)
      bucket[1 + ((mem_cast<llu>(*ptr) >> amount) & 0xffff)]++, ptr++;
    for (int i = 1; i <= 0x10000; i++)
      bucket[i] += bucket[i - 1];
    ptr = first;
    for (int i = 0; i < n; i++)
      v[bucket[(mem_cast<llu>(*ptr) >> amount) & 0xffff]++] = mem_cast<llu>(*ptr), ptr++;
    ptr = first;
    for (int i = 0; i < n; i++)
      tmp[i] = mem_cast<llu>(*ptr), ptr++;
    ptr = first;
    for (int i = 0; i < n; i++)
      *ptr = mem_cast<type_t>(v[i]), assert(*ptr >= 0), ptr++;
    for (int i = 0; i < n; i++)
      v[i] = tmp[i];
  }
}
