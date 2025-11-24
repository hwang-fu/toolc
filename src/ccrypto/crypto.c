#include "crypto.h"

#define SHA256_BLOCK_SIZE_IN_BYTES      (64)

// Choose(x, y, z)
// For each bit i in a 32-bit x, if x[i] == 1 then output y[i] else output z[i],
// finally returns the resulted 32-bit value.
static u32 Choose(u32 x, u32 y, u32 z)
{
    return (x & y) ^ (~x & z);
}

// Majority(x, y, z)
// For each bit i in 32-bit x,y and z, if at least two of the ith-bits are 1 output 1 else output 0,
// finally returns the resulted 32-bit value.
static u32 Majority(u32 x, u32 y, u32 z)
{
    return (x & y) ^ (x & z) ^ (y & z);
}

// BigSigma0(x)
// Rotate @argument {x} right by 2, 13, and 22 bits, then XOR the three results.
//
// Used to mix bits of x thoroughly.
// These rotation distances are chosen so that no bit remains correlated with its original position and to ensure avalanche effect (changing 1 input bit changes many output bits).
static u32 BigSigma0(u32 x)
{
    return ROR32(x, 2) ^ ROR32(x, 13) ^ ROR32(x, 22);
}

static u32 BigSigma1(u32 x)
{
    return ROR32(x, 6) ^ ROR32(x, 11) ^ ROR32(x, 25);
}

// Used in the message schedule (W[t]) expansion.
// It mixes earlier message words together to generate NEW words.
// This makes every later round depend on earlier message bits in a complex way.
static u32 SmallSigma0(u32 x)
{
    return ROR32(x, 7) ^ ROR32(x, 18) ^ SHR32(x, 3);
}

// Also used in message expansion (W[t] = σ₁(W[t−2]) + ...).
// Helps propagate dependencies and ensure avalanche behavior in the message schedule.
static u32 SmallSigma1(u32 x)
{
    return ROR32(x, 17) ^ ROR32(x, 19) ^ SHR32(x, 10);
}

/**
 * @brief   SHA-256 constants
 *          (first 32 bits of the fractional parts of the cube roots of the first 64 primes)
 */
static const u32 K_[64] = {
    0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
    0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
    0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
    0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
    0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
    0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
    0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
    0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

/**
 * @brief   Initial hash values
 *          (first 32 bits of fractional parts of square roots of the first 8 primes)
 */
static const u32 H_[8] = {
    0x6a09e667,
    0xbb67ae85,
    0x3c6ef372,
    0xa54ff53a,
    0x510e527f,
    0x9b05688c,
    0x1f83d9ab,
    0x5be0cd19
};

static char xdigit_(u8 d)
{
    if (0 <= d && d <= 9)
    {
        return '0' + d;
    }
    else if (10 <= d && d <= 15)
    {
        return 'a' + (d - 10);
    }
    else
    {
        PANIC("Error @%s(): Expecting a number in range [0, 15], but got \"%u\"", __func__, d);
    }
}

/// Convert 4 @type {u8} to a big-endian @type {u32}
u32 bigendian32(BORROWED u8 * p)
{
    SCP(p);
    return SHL32(p[0], 24) | SHL32(p[1], 16) | SHL32(p[2], 8) | (u32)p[3];
}

static void process_(BORROWED u8 block[SHA256_BLOCK_SIZE_IN_BYTES], BORROWED u32 H[8])
{
    u32 W[64];
    for (u8 t = 0; t < 16; t++)
    {
        W[t] = bigendian32(block + t * 4);
    }
    for (u8 t = 16; t < 64; t++)
    {
        W[t] = SmallSigma1(W[t-2]) + W[t-7] + SmallSigma0(W[t-15]) + W[t-16];
    }

    u32 a = H[0];
    u32 b = H[1];
    u32 c = H[2];
    u32 d = H[3];
    u32 e = H[4];
    u32 f = H[5];
    u32 g = H[6];
    u32 h = H[7];

    for (u8 t = 0; t < 64; t++)
    {
        const u32 T1 = h + BigSigma1(e) + Choose(e, f, g) + K_[t] + W[t];
        const u32 T2 = BigSigma0(a) + Majority(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }

    H[0] += a;
    H[1] += b;
    H[2] += c;
    H[3] += d;
    H[4] += e;
    H[5] += f;
    H[6] += g;
    H[7] += h;
}


OWNED SHA256 * mk_sha256(BORROWED void * body, u64 bytes)
{
    /// 1. Sanity check.
    SCP(body);
    ASSERT_EXPR(bytes > 0);

    /// 2. Initializations.
    BORROWED u8 * data = CAST(body, u8*);
    COPIED u32 H[8] = { 0 };
    memcpy(H, H_, sizeof(H));

    /// 3. Check for overflow. 0x1fffffffffffffff = 0xffffffffffffffff / 8
    ///    The @argument {bytes} represents total bytes,
    ///    however, later we have to also use the concept of bit length, so it is necessary to watch out for overflow.
    ///    If overflow, then process the @argument {data} in several times.
    u64 maximum = (u64) (0x1fffffffffffffff)  - 1;
    while (bytes > maximum)
    {
        OWNED SHA256 * sha = mk_sha256(data, maximum);
        for (u8 i = 0; i < 8; i++)
        {
            H[i] = SHL32(sha->Digest[i * 4],     24)
                 | SHL32(sha->Digest[i * 4 + 1], 16)
                 | SHL32(sha->Digest[i * 4 + 2], 8)
                 | (u32)(sha->Digest[i * 4 + 3]);
        }
        dispose(sha);
        data  += maximum;
        bytes -= maximum;
    }

    u64 bitLength = bytes * 8;

    /// Process all full 64-byte blocks (SHA-256 block size is 64-byte).
    u64 offset = 0;
    while (bytes - offset >= SHA256_BLOCK_SIZE_IN_BYTES)
    {
        process_(data + offset, H);
        offset += SHA256_BLOCK_SIZE_IN_BYTES;
    }

    /// Last block(s) with padding to fulfill a 64-byte block pattern.
    u8 block[2 * SHA256_BLOCK_SIZE_IN_BYTES] = { 0 };
    u64 rest = bytes - offset;
    memcpy(block, data + offset, rest);
    /// 0x80
    block[rest] = 0b10000000;

    /// If there is not enough room for 8-byte length, we'll need two blocks.
    if (SHA256_BLOCK_SIZE_IN_BYTES - (rest + 1) < 8)
    {
        /// Fill remaining of the first block with ZEROS (we have initialized already).
        /// Write second block to all ZEROS except final 8 bytes length.
        /// The final 8 bytes will be the @local {bitLength} in big-endian.
        for (u8 i = 0; i < 8; i++)
        {
            block[2 * SHA256_BLOCK_SIZE_IN_BYTES - 8 + i] = (u8) SHR64(bitLength, ((SHA256_BLOCK_SIZE_IN_BYTES - 8) - (8 * i)));
        }
        process_(block, H);
        process_(block + SHA256_BLOCK_SIZE_IN_BYTES, H);
    }
    else
    {
        /// Fill ZEROS until the last 8 bytes.
        /// The final 8 bytes will be the @local {bitLength} in big-endian.
        for (u8 i = 0; i < 8; i++)
        {
            block[SHA256_BLOCK_SIZE_IN_BYTES - 8 + i] = (u8) SHR64(bitLength, ((SHA256_BLOCK_SIZE_IN_BYTES - 8) - (8 * i)));
        }
        process_(block, H);
    }

    /// Process output in big-endian.
    OWNED SHA256 * sha = NEW(sizeof(SHA256));
    for (u8 i = 0; i < 8; i++)
    {
        sha->Digest[i * 4]     = (u8) SHR32(H[i], 24);
        sha->Digest[i * 4 + 1] = (u8) SHR32(H[i], 16);
        sha->Digest[i * 4 + 2] = (u8) SHR32(H[i], 8);
        sha->Digest[i * 4 + 3] = (u8) H[i];
    }
    return sha;
}

OWNED char * sha256_cstring(BORROWED SHA256 * h)
{
    /// 1. Sanity check.
    SCP(h);
    /// 2. SHA-256 hex string is always 64 bytes (characters) long, excluding the '\0' terminator.
    OWNED char * digest = ZEROS(64 + 1);
    /// 3. Convert.
    for (u8 i = 0; i < 32; i++)
    {
        u8 b = h->Digest[i];
        digest[i * 2]     = xdigit_((u8)((b >> 4) & 0x0f));
        digest[i * 2 + 1] = xdigit_((u8)(b        & 0x0f));
    }
    /// 4. Return the converted value.
    return digest;
}

OWNED char * sha256_cstring_owned(OWNED SHA256 * h)
{
    OWNED char * digest = sha256_cstring(h);
    dispose(h);
    return digest;
}

OWNED char * sha256_display(FILE * stream, BORROWED SHA256 * h)
{
    SCP(h);
    for (int i = 0; i < 32; ++i)
    {
        fprintf(stream, "%02x\n", h->Digest[i]);
    }
}
