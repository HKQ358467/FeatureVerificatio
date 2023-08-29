#include <iostream>
#include <string>
#include <cstring>
#include <cstdint>
#include <iomanip>

// MD5 Constants
constexpr uint32_t MD5_A = 0x67452301;
constexpr uint32_t MD5_B = 0xEFCDAB89;
constexpr uint32_t MD5_C = 0x98BADCFE;
constexpr uint32_t MD5_D = 0x10325476;

// SHA-1 Constants
constexpr uint32_t SHA1_A = 0x67452301;
constexpr uint32_t SHA1_B = 0xEFCDAB89;
constexpr uint32_t SHA1_C = 0x98BADCFE;
constexpr uint32_t SHA1_D = 0x10325476;
constexpr uint32_t SHA1_E = 0xC3D2E1F0;

// SHA-256 Constants
constexpr uint32_t SHA256_A = 0x6a09e667;
constexpr uint32_t SHA256_B = 0xbb67ae85;
constexpr uint32_t SHA256_C = 0x3c6ef372;
constexpr uint32_t SHA256_D = 0xa54ff53a;
constexpr uint32_t SHA256_E = 0x510e527f;
constexpr uint32_t SHA256_F = 0x9b05688c;
constexpr uint32_t SHA256_G = 0x1f83d9ab;
constexpr uint32_t SHA256_H = 0x5be0cd19;

constexpr uint32_t SHA256_K[] = {
    0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5,
    0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
    0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
    0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
    0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC,
    0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
    0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7,
    0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
    0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13,
    0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
    0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3,
    0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
    0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5,
    0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
    0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
    0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2
};

// Rotate Left Operation
constexpr uint32_t ROTL(uint32_t x, uint32_t n) {
    return (x << n) | (x >> (32 - n));
}

// MD5 Functions
constexpr uint32_t F(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) | (~x & z);
}

constexpr uint32_t G(uint32_t x, uint32_t y, uint32_t z) {
    return (x & z) | (y & ~z);
}

constexpr uint32_t H(uint32_t x, uint32_t y, uint32_t z) {
    return x ^ y ^ z;
}

constexpr uint32_t I(uint32_t x, uint32_t y, uint32_t z) {
    return y ^ (x | ~z);
}

void md5Hash(const std::string& data, uint32_t hash[4]) {
    uint32_t a = MD5_A;
    uint32_t b = MD5_B;
    uint32_t c = MD5_C;
    uint32_t d = MD5_D;

    const uint8_t* message = reinterpret_cast<const uint8_t*>(data.c_str());
    size_t messageLength = data.length();

    for (size_t i = 0; i < messageLength; i += 64) {
        uint32_t chunk[16];
        memcpy(chunk, message + i, 64);

        uint32_t aa = a;
        uint32_t bb = b;
        uint32_t cc = c;
        uint32_t dd = d;

        for (uint32_t j = 0; j < 64; ++j) {
            uint32_t f, g;

            if (j < 16) {
                f = F(b, c, d);
                g = j;
            } else if (j < 32) {
                f = G(b, c, d);
                g = (5 * j + 1) % 16;
            } else if (j < 48) {
                f = H(b, c, d);
                g = (3 * j + 5) % 16;
            } else {
                f = I(b, c, d);
                g = (7 * j) % 16;
            }

            uint32_t temp = d;
            d = c;
            c = b;
            b = b + ROTL((a + f + SHA256_K[j] + chunk[g]), 7);
            a = temp;
        }

        a += aa;
        b += bb;
        c += cc;
        d += dd;
    }

    hash[0] = a;
    hash[1] = b;
    hash[2] = c;
    hash[3] = d;
}

// SHA-1 Functions
constexpr uint32_t SHA1_F(uint32_t t, uint32_t b, uint32_t c, uint32_t d) {
    if (t < 20) {
        return (b & c) | ((~b) & d);
    } else if (t < 40) {
        return b ^ c ^ d;
    } else if (t < 60) {
        return (b & c) | (b & d) | (c & d);
    } else {
        return b ^ c ^ d;
    }
}

void sha1Hash(const std::string& data, uint32_t hash[5]) {
    uint32_t a = SHA1_A;
    uint32_t b = SHA1_B;
    uint32_t c = SHA1_C;
    uint32_t d = SHA1_D;
    uint32_t e = SHA1_E;

    uint8_t* message = reinterpret_cast<uint8_t*>(const_cast<char*>(data.c_str()));
    size_t messageLength = data.length();

    uint64_t bitLength = messageLength * 8;

    // Append Padding Bits
    message[messageLength++] = 0x80;

    // Append Length
    if (messageLength % 64 > 56) {
        while (messageLength % 64 != 56) {
            message[messageLength++] = 0x00;
        }
    }

    for (int i = 0; i < 8; ++i) {
        message[messageLength++] = (bitLength >> (56 - i * 8)) & 0xFF;
    }

    for (size_t i = 0; i < messageLength; i += 64) {
        uint32_t chunk[80];
        memcpy(chunk, message + i, 64);

        for (uint32_t j = 16; j < 80; ++j) {
            chunk[j] = ROTL(chunk[j - 3] ^ chunk[j - 8] ^ chunk[j - 14] ^ chunk[j - 16], 1);
        }

        uint32_t aa = a;
        uint32_t bb = b;
        uint32_t cc = c;
        uint32_t dd = d;
        uint32_t ee = e;

        for (uint32_t j = 0; j < 80; ++j) {
            uint32_t temp = ROTL(a, 5) + SHA1_F(j, b, c, d) + e + chunk[j];

            e = d;
            d = c;
            c = ROTL(b, 30);
            b = a;
            a = temp;
        }

        a += aa;
        b += bb;
        c += cc;
        d += dd;
        e += ee;
    }

    hash[0] = a;
    hash[1] = b;
    hash[2] = c;
    hash[3] = d;
    hash[4] = e;
}

// SHA-256 Functions
constexpr uint32_t SHA256_Sigma0(uint32_t x) {
    return ROTL(x, 2) ^ ROTL(x, 13) ^ ROTL(x, 22);
}

constexpr uint32_t SHA256_Sigma1(uint32_t x) {
    return ROTL(x, 6) ^ ROTL(x, 11) ^ ROTL(x, 25);
}

constexpr uint32_t SHA256_sigma0(uint32_t x) {
    return ROTL(x, 7) ^ ROTL(x, 18) ^ (x >> 3);
}

constexpr uint32_t SHA256_sigma1(uint32_t x) {
    return ROTL(x, 17) ^ ROTL(x, 19) ^ (x >> 10);
}
constexpr uint32_t SHA256_Ch(uint32_t x, uint32_t y, uint32_t z)
{
    return (x & y) ^ ((~x) & z);
}

constexpr uint32_t SHA256_Maj(uint32_t x, uint32_t y, uint32_t z)
{
    return (x & y) ^ (x & z) ^ (y & z);
}

void sha256Hash(const std::string& data, uint32_t hash[8]) {
    uint32_t a = SHA256_A;
    uint32_t b = SHA256_B;
    uint32_t c = SHA256_C;
    uint32_t d = SHA256_D;
    uint32_t e = SHA256_E;
    uint32_t f = SHA256_F;
    uint32_t g = SHA256_G;
    uint32_t h = SHA256_H;

    uint8_t* message = reinterpret_cast<uint8_t*>(const_cast<char*>(data.c_str()));
    size_t messageLength = data.length();

    // Pre-processing
    size_t paddedLength = ((messageLength + 8 + 64) / 64) * 64;
    uint8_t* paddedMessage = new uint8_t[paddedLength];
    memcpy(paddedMessage, message, messageLength);
    paddedMessage[messageLength] = 0x80;

    uint64_t bitLength = messageLength * 8;
    memcpy(paddedMessage + paddedLength - 8, &bitLength, 8);

    // Process each 512-bit chunk
    for (size_t i = 0; i < paddedLength; i += 64) {
        uint32_t w[64];

        // Prepare message schedule
        for (int j = 0; j < 16; ++j) {
            w[j] = (paddedMessage[i + j * 4] << 24) |
                   (paddedMessage[i + j * 4 + 1] << 16) |
                   (paddedMessage[i + j * 4 + 2] << 8) |
                   (paddedMessage[i + j * 4 + 3]);
        }
        for (int j = 16; j < 64; ++j) {
            uint32_t s0 = SHA256_sigma0(w[j - 15]);
            uint32_t s1 = SHA256_sigma1(w[j - 2]);
            w[j] = w[j - 16] + s0 + w[j - 7] + s1;
        }

        // Initialize working variables
        uint32_t temp1, temp2;
        for (int j = 0; j < 64; ++j) {
            temp1 = h + SHA256_Sigma1(e) + SHA256_Ch(e, f, g) + SHA256_K[j] + w[j];
            temp2 = SHA256_Sigma0(a) + SHA256_Maj(a, b, c);

            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        // Update hash values
        a += SHA256_A;
        b += SHA256_B;
        c += SHA256_C;
        d += SHA256_D;
        e += SHA256_E;
        f += SHA256_F;
        g += SHA256_G;
        h += SHA256_H;
    }

    // Store hash values in output array
    hash[0] = a;
    hash[1] = b;
    hash[2] = c;
    hash[3] = d;
    hash[4] = e;
    hash[5] = f;
    hash[6] = g;
    hash[7] = h;

    delete[] paddedMessage;
}

int main() {
    std::string data = "Hello, World!";

    uint32_t md5Hash1[4];
    md5Hash(data, md5Hash1);
    std::cout << "MD5: ";
    for (int i = 0; i < 4; ++i) {
        std::cout << std::hex << std::setw(8) << std::setfill('0') << md5Hash1[i];
    }
    std::cout << std::endl;

    uint32_t sha1Hash1[5];
    sha1Hash(data, sha1Hash1);
    std::cout << "SHA-1: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << std::hex << std::setw(8) << std::setfill('0') << sha1Hash1[i];
    }
    std::cout << std::endl;

    uint32_t sha256Hash1[8];
    sha256Hash(data, sha256Hash1);
    std::cout << "SHA-256: ";
    for (int i = 0; i < 8; ++i) {
        std::cout << std::hex << std::setw(8) << std::setfill('0') << sha256Hash1[i];
    }
    std::cout << std::endl;

    return 0;
}