#ifndef XTEA_H
#define XTEA_H

#include <QByteArray>

#define BLOCK_SIZE 8

typedef unsigned int    uint;
typedef unsigned char uchar;

constexpr const uint32_t DELTA = 0x9e3779b9;

class Xtea {

public:
    Xtea(int n_rounds = 32);

    void Encrypt(uchar* data, uint size, const uchar* key);
    void Decrypt(uchar* data, uint size, const uchar* key);

    void Encrypt(QByteArray& data, const QByteArray& key);
    void Decrypt(QByteArray& data, const QByteArray& key);

private:
    int n_rounds;
    void encipher(uint n_rounds, uint32_t v[2], uint32_t key[4]) ;
    void decipher(uint n_rounds, uint32_t v[2], uint32_t key[4]);
};

#endif // XTEA_H
