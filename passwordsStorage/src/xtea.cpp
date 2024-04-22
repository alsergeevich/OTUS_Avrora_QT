#include "xtea.h"



Xtea::Xtea(int n_rounds) : n_rounds {n_rounds} {}

void Xtea::Encrypt(uchar *data, uint size, const uchar *key) {
    uint n_blocks = size / BLOCK_SIZE;
    if(size % BLOCK_SIZE != 0) {
        n_blocks++;
    }
    for(uint i = 0; i < n_blocks; ++i) {
        encipher(n_rounds, (uint32_t*)(data + (BLOCK_SIZE * i)), (uint32_t*)key);
    }
}

void Xtea::Decrypt(uchar *data, uint size, const uchar *key) {
    uint n_blocks = size / BLOCK_SIZE;
    if(size % BLOCK_SIZE != 0) {
        n_blocks++;
    }
    for(uint i = 0; i < n_blocks; ++i) {
        decipher(n_rounds, (uint32_t*)(data + (BLOCK_SIZE * i)), (uint32_t*)key);
    }
}

void Xtea::Encrypt(QByteArray &data, const QByteArray &key) {
    uchar head = 0;
    if(data.size() < BLOCK_SIZE) {
        head = BLOCK_SIZE - data.size() + 1;
    } else {
        head = BLOCK_SIZE - ((data.size() + 1) % BLOCK_SIZE);
    }
    data.push_front(head);
    data.resize(data.size() + head);
    Encrypt((uchar*)data.data(), data.size(), (uchar*)key.data());
}

void Xtea::Decrypt(QByteArray &data, const QByteArray &key) {
    Decrypt((uchar*)data.data(), data.size(), (uchar*)key.data());
    uchar head = data[0];
    data.remove(0, 1);
    data.resize(data.size() - head);
}

void Xtea::encipher(uint n_rounds, uint32_t v[2], uint32_t key[4]) {

    uint32_t sum =0;
    for(uint i = 0; i < n_rounds; ++i) {
        v[0] += ((v[1] << 4) ^ (v[1] >> 5) + v[1]) ^ (sum + key[sum & 3]);
        sum += DELTA;
        v[1] += ((v[0] << 4) ^ (v[0] >> 5) + v[0]) ^ (sum + key[(sum >> 11) & 3]);
    }
}

void Xtea::decipher(uint n_rounds, uint32_t v[2], uint32_t key[4]) {
    uint32_t sum = DELTA * n_rounds;
    for(uint i = 0; i < n_rounds; ++i) {
        v[1] -= ((v[0] << 4) ^ (v[0] >> 5) + v[0]) ^ (sum + key[(sum >> 11) & 3]);
        sum -= DELTA;
        v[0] -= ((v[1] << 4) ^ (v[1] >> 5) + v[1]) ^ (sum + key[sum & 3]);
    }
}
