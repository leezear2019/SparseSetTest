//
// Created by leeze on 2019/11/7.
//

#ifndef NEWDSALLDIFF_BITSET64_H
#define NEWDSALLDIFF_BITSET64_H

#include <vector>
#include <cmath>
#include <sstream>
#include <stdarg.h>
#include <numeric>

namespace CTRL {
    typedef uint64_t u64;

#ifdef _MSC_VER
#include <intrin.h>
    inline int BitCount(const int a) {
        return __popcnt(a);
    };
    inline int BitCount64(const uint64_t a) {
        return __popcnt64(a);
    };
    inline int CLZ64(const uint64_t a) {
        return __lzcnt64(a);
    };
    inline int CTZ64(const uint64_t a) {
        unsigned long b;
        const auto c = _BitScanForward64(&b, a);
        return c ? 63 - b : 64;
    };
#endif

#ifdef __GNUC__

    inline int BitCount(const int a) {
        return __builtin_popcount(a);
    };

    inline int BitCount64(const uint64_t a) {
        return __builtin_popcountll(a);
    };

    inline int CLZ64(const uint64_t a) {
        return __builtin_clzll(a);
    };

    inline int CTZ64(const uint64_t a) {
        return __builtin_ctzll(a);
    };

    inline int FFS64(const uint64_t a) {
        return __builtin_ffsll(a);
    }

    inline void FLP(const uint64_t &a) {
        __builtin_bswap64(a);
    }

#endif
    const int kIndexOverflow = -1;
    const int kBitSize = 64;
    const int kDivBit = 6;
    const int kModMask = 0x3f;
//    const u64 kMask1[] = {0x8000000000000000L, 0x4000000000000000L, 0x2000000000000000L, 0x1000000000000000L,
//                          0x0800000000000000L, 0x0400000000000000L, 0x0200000000000000L, 0x0100000000000000L,
//                          0x0080000000000000L, 0x0040000000000000L, 0x0020000000000000L, 0x0010000000000000L,
//                          0x0008000000000000L, 0x0004000000000000L, 0x0002000000000000L, 0x0001000000000000L,
//                          0x0000800000000000L, 0x0000400000000000L, 0x0000200000000000L, 0x0000100000000000L,
//                          0x0000080000000000L, 0x0000040000000000L, 0x0000020000000000L, 0x0000010000000000L,
//                          0x0000008000000000L, 0x0000004000000000L, 0x0000002000000000L, 0x0000001000000000L,
//                          0x0000000800000000L, 0x0000000400000000L, 0x0000000200000000L, 0x0000000100000000L,
//                          0x0000000080000000L, 0x0000000040000000L, 0x0000000020000000L, 0x0000000010000000L,
//                          0x0000000008000000L, 0x0000000004000000L, 0x0000000002000000L, 0x0000000001000000L,
//                          0x0000000000800000L, 0x0000000000400000L, 0x0000000000200000L, 0x0000000000100000L,
//                          0x0000000000080000L, 0x0000000000040000L, 0x0000000000020000L, 0x0000000000010000L,
//                          0x0000000000008000L, 0x0000000000004000L, 0x0000000000002000L, 0x0000000000001000L,
//                          0x0000000000000800L, 0x0000000000000400L, 0x0000000000000200L, 0x0000000000000100L,
//                          0x0000000000000080L, 0x0000000000000040L, 0x0000000000000020L, 0x0000000000000010L,
//                          0x0000000000000008L, 0x0000000000000004L, 0x0000000000000002L, 0x0000000000000001L};
//    const u64 kMask0[] = {0x7FFFFFFFFFFFFFFFL, 0xBFFFFFFFFFFFFFFFL, 0xDFFFFFFFFFFFFFFFL, 0xEFFFFFFFFFFFFFFFL,
//                          0xF7FFFFFFFFFFFFFFL, 0xFBFFFFFFFFFFFFFFL, 0xFDFFFFFFFFFFFFFFL, 0xFEFFFFFFFFFFFFFFL,
//                          0xFF7FFFFFFFFFFFFFL, 0xFFBFFFFFFFFFFFFFL, 0xFFDFFFFFFFFFFFFFL, 0xFFEFFFFFFFFFFFFFL,
//                          0xFFF7FFFFFFFFFFFFL, 0xFFFBFFFFFFFFFFFFL, 0xFFFDFFFFFFFFFFFFL, 0xFFFEFFFFFFFFFFFFL,
//                          0xFFFF7FFFFFFFFFFFL, 0xFFFFBFFFFFFFFFFFL, 0xFFFFDFFFFFFFFFFFL, 0xFFFFEFFFFFFFFFFFL,
//                          0xFFFFF7FFFFFFFFFFL, 0xFFFFFBFFFFFFFFFFL, 0xFFFFFDFFFFFFFFFFL, 0xFFFFFEFFFFFFFFFFL,
//                          0xFFFFFF7FFFFFFFFFL, 0xFFFFFFBFFFFFFFFFL, 0xFFFFFFDFFFFFFFFFL, 0xFFFFFFEFFFFFFFFFL,
//                          0xFFFFFFF7FFFFFFFFL, 0xFFFFFFFBFFFFFFFFL, 0xFFFFFFFDFFFFFFFFL, 0xFFFFFFFEFFFFFFFFL,
//                          0xFFFFFFFF7FFFFFFFL, 0xFFFFFFFFBFFFFFFFL, 0xFFFFFFFFDFFFFFFFL, 0xFFFFFFFFEFFFFFFFL,
//                          0xFFFFFFFFF7FFFFFFL, 0xFFFFFFFFFBFFFFFFL, 0xFFFFFFFFFDFFFFFFL, 0xFFFFFFFFFEFFFFFFL,
//                          0xFFFFFFFFFF7FFFFFL, 0xFFFFFFFFFFBFFFFFL, 0xFFFFFFFFFFDFFFFFL, 0xFFFFFFFFFFEFFFFFL,
//                          0xFFFFFFFFFFF7FFFFL, 0xFFFFFFFFFFFBFFFFL, 0xFFFFFFFFFFFDFFFFL, 0xFFFFFFFFFFFEFFFFL,
//                          0xFFFFFFFFFFFF7FFFL, 0xFFFFFFFFFFFFBFFFL, 0xFFFFFFFFFFFFDFFFL, 0xFFFFFFFFFFFFEFFFL,
//                          0xFFFFFFFFFFFFF7FFL, 0xFFFFFFFFFFFFFBFFL, 0xFFFFFFFFFFFFFDFFL, 0xFFFFFFFFFFFFFEFFL,
//                          0xFFFFFFFFFFFFFF7FL, 0xFFFFFFFFFFFFFFBFL, 0xFFFFFFFFFFFFFFDFL, 0xFFFFFFFFFFFFFFEFL,
//                          0xFFFFFFFFFFFFFFF7L, 0xFFFFFFFFFFFFFFFBL, 0xFFFFFFFFFFFFFFFDL, 0xFFFFFFFFFFFFFFFEL};
    const int kIntMax = 0x3f3f3f3f;
//    const int kUNBINDLEVEL = 0x3f3f3f3f;
    const u64 kAllOneLong = 0xFFFFFFFFFFFFFFFFL;

    class Index2D {
    public:
        int x, y;
    };

    inline Index2D GetIndex2D(const int index) {
        return Index2D{index >> kDivBit, index & kModMask};
    }

    inline int GetIndex(const Index2D &index2D) {
        return (index2D.x << kDivBit) + index2D.y;
    }



///* a=target variable, b=bit number to act upon 0-n */
#define BIT_SET(a, b) ((a) |= (1ULL<<(b)))
#define BIT_RESET(a, b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a, b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a, b) ((a >> b) & 1ULL)

///* x=target variable, y=mask */
#define BITMASK_SET(x, y) ((x) |= (y))
#define BITMASK_CLEAR(x, y) ((x) &= (~(y)))
#define BITMASK_FLIP(x, y) ((x) ^= (y))
#define BITMASK_CHECK_ALL(x, y) (((x) & (y)) == (y))   // warning: evaluates y twice
#define BITMASK_CHECK_ANY(x, y) ((x) & (y))


    class BitSet64 {

    private:
        std::vector<u64> words_;
        u64 last_mask_;
        int limit_;
        int bit_size_;
        int byte_size_;
        int int_size_;
        int long_size_;

        static const u64 kAllOne = 0xFFFFFFFFFFFFFFFFL;

    public:
        BitSet64(const int size) :
                bit_size_(size),
                byte_size_(static_cast<int>(ceilf(static_cast<float>(size) / 8))),
                int_size_(static_cast<int>(ceilf(static_cast<float>(size) / 32))),
                long_size_(static_cast<int>(ceilf(static_cast<float>(size) / 64))),
                limit_(size % kBitSize) {
            last_mask_ = kAllOne >> 64 - limit_;
            words_.resize(long_size_, 0);
        }

        void Resize(const int size) {
            bit_size_ = size;
            byte_size_ = static_cast<int>(ceilf(static_cast<float>(size) / 8));
            int_size_ = static_cast<int>(ceilf(static_cast<float>(size) / 32));
            long_size_ = static_cast<int>(ceilf(static_cast<float>(size) / 64));
            limit_ = bit_size_ % kBitSize;
            last_mask_ = kAllOne >> 64 - limit_;
            words_.resize(long_size_, 0);
        }

        int BitSize() const noexcept {
            return bit_size_;
        }

        int ByteSize() const noexcept {
            return byte_size_;
        }

        int IntSize() const noexcept {
            return int_size_;
        }

        int LongSize() const noexcept {
            return long_size_;
        }

        void Flip() noexcept {
            for (auto &w:words_) {
                w = ~w;
            }
            words_.back() &= last_mask_;
        }

        void Flip(const int i) noexcept {
            const Index2D p = GetIndex2D(i);
            BIT_FLIP(words_[p.x], p.y);
        }

        void Set(const int i) noexcept {
            const Index2D p = GetIndex2D(i);
            BIT_SET(words_[p.x], p.y);
        }

        void Reset(const int i) noexcept {
            const Index2D p = GetIndex2D(i);
            BIT_RESET(words_[p.x], p.y);
        }

        bool Empty() noexcept {
            for (auto w:words_) {
                if (w != 0L) {
                    return false;
                }
            }

            return true;
        }

        bool Check(const int i) noexcept {
            const Index2D p = GetIndex2D(i);
            return BIT_CHECK(words_[p.x], p.y);
        }

        int Count() noexcept {
            int sum = 0;
            for (auto w:words_) {
                sum += BitCount64(w);
            }
            return sum;
//            return std::accumulate(words_.begin(), words_.end(), 0, [](int a, u64 b) { return a + BitCount64(b); });
        }

        BitSet64 &operator&=(const BitSet64 &rhs) noexcept {
            for (int i = 0; i < long_size_; ++i) {
                words_[i] &= rhs.words_[i];
            }
            return *this;
        }

        BitSet64 &operator|=(const BitSet64 &rhs) noexcept {
            for (int i = 0; i < long_size_; ++i) {
                words_[i] |= rhs.words_[i];
            }
            return *this;
        }

        BitSet64 &operator^=(const BitSet64 &rhs) noexcept {
            for (int i = 0; i < long_size_; ++i) {
                words_[i] ^= rhs.words_[i];
            }
            words_.back() &= last_mask_;
            return *this;
        }

        bool operator==(const BitSet64 &rhs) noexcept {
            for (int i = 0; i < long_size_; ++i) {
                if (words_[i] != rhs.words_[i]) {
                    return false;
                }
            }
            return true;
        }

        bool operator!=(const BitSet64 &rhs) noexcept {
            for (int i = 0; i < long_size_; ++i) {
                if (words_[i] != rhs.words_[i]) {
                    return true;
                }
            }
            return false;
        }

        // 从ith(含ith)开始第一个为1的位的索引
        // 若没有返回-1
        int NextOneBit(const int i) noexcept {
            if (i >= bit_size_) {
                return kIndexOverflow;
            }

            Index2D p = GetIndex2D(i);
            u64 word = words_[p.x] & (kAllOne << p.y);
            while (true) {
                if (word != 0L)
                    return (p.x << kDivBit) + CTZ64(word);
                if (++p.x == long_size_)
                    return kIndexOverflow;
                word = words_[p.x];
            }
        }

        // 从ith(含ith)开始第一个为0的位的索引
        // 若没有返回-1
        int NextZeroBit(const int i) noexcept {
            if (i >= bit_size_) {
                return kIndexOverflow;
            }

            Index2D p = GetIndex2D(i);
            u64 word = ~words_[p.x] & (kAllOne << p.y);
            while (true) {
                if (word != 0L) {
                    const int i = (p.x << kDivBit) + CTZ64(word);
                    return i < bit_size_ ? i : kIndexOverflow;
                }
                if (++p.x == long_size_)
                    return kIndexOverflow;
                word = ~words_[p.x];
            }
        }

        std::string ToBitString() noexcept {
            std::string tmp_str_;

            for (int i = 0; i < bit_size_; ++i) {
                tmp_str_.push_back(Check(i) ? '1' : '0');
            }

            return tmp_str_;
        }

        std::vector<int> ToArray() noexcept {
            std::vector<int> indices(bit_size_);
            indices.clear();
            int i = NextOneBit(0);
            while (i != kIndexOverflow) {
                indices.push_back(i);
                i = NextOneBit(i + 1);
            }

            return indices;
        }

        const std::string ToString() noexcept {
            std::vector<int> indices(bit_size_);
            indices.clear();

            int i = NextOneBit(0);
            while (i != kIndexOverflow) {
                indices.push_back(i);
                i = NextOneBit(i + 1);
            }

            std::stringstream ss;
            ss << "{";
            for (auto a:indices) {
                ss << a;
                ss << ' ';
            }
            ss << "}";
            const std::string s = ss.str();

            return s;
        }

        friend inline void BitAnd(BitSet64 &res, const BitSet64 &a, const BitSet64 &b) noexcept {
            for (int i = 0; i < a.long_size_; ++i) {
                res.words_[i] = a.words_[i] & b.words_[i];
            }
        }

        friend inline void BitOr(BitSet64 &res, const BitSet64 &a, const BitSet64 &b) noexcept {
            for (int i = 0; i < a.long_size_; ++i) {
                res.words_[i] = a.words_[i] | b.words_[i];
            }
        }

        friend inline void BitXor(BitSet64 &res, const BitSet64 &a, const BitSet64 &b) noexcept {
            for (int i = 0; i < a.long_size_; ++i) {
                res.words_[i] = a.words_[i] ^ b.words_[i];
            }
        }

        static inline bool EmptyAnd(const BitSet64 &a, const BitSet64 &b) noexcept {
            for (int i = 0; i < a.long_size_; ++i) {
                if (a.words_[i] & b.words_[i] != 0L) {
                    return false;
                }
            }
            return true;
        }

        static inline bool EmptyOr(const BitSet64 &a, const BitSet64 &b) noexcept {
            for (int i = 0; i < a.long_size_; ++i) {
                if (a.words_[i] | b.words_[i] != 0L) {
                    return false;
                }
            }
            return true;
        }

        static inline bool EmptyXor(const BitSet64 &a, const BitSet64 &b) noexcept {
            for (int i = 0; i < a.long_size_; ++i) {
                if (a.words_[i] ^ b.words_[i] != 0L) {
                    return false;
                }
            }
            return true;
        }

    };



//    class SimpleBitSet64 {
//    private:
//        u64 words_;
//    };
//
//    class SimpleBitSet128 {
//    private:
//        unsigned __int128 words_;
//    };
}
#endif //NEWDSALLDIFF_BITSET64_H
