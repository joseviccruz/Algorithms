uint64_t pack(const int32_t &high, const int32_t &low) {
  return (uint64_t(high) << 32) | (uint64_t(low) & 0xffffffff);
}

uint64_t pack(const pair<int32_t, int32_t> &p) {
  return pack(p.first, p.second);
}

pair<int32_t, int32_t> unpack(const uint64_t &x) {
  return make_pair(int32_t(x >> 32), int32_t(x));
}
