//
// Created by Nikolas Ponomarov on 2019-01-16.
//

#include "../includes/ft_ssl.h"

#define R(x, k) ((x >> k) | (x << (64 - k)))
#define CC(x, y, z) ((x & y) ^ ((~x) & z))
#define M(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define BG0(x) (R(x, 28) ^ R(x, 34) ^ R(x, 39)) // S0
#define BG1(x) (R(x, 14) ^ R(x, 18) ^ R(x, 41)) // S1
#define SG0(x) (R(x, 1) ^ R(x, 8) ^ (x >> 7)) // s0
#define SG1(x) (R(x, 19) ^ R(x, 61) ^ (x >> 6)) // s1

static void	third_st(unsigned long *sha512)
{
    int				i;
    unsigned long	st1;
    unsigned long	st2;

    i = 0;
    while (i < 80)
    {
        st1 = sha512_hash[7] + BG1(sha512_hash[4]) +
              CC(sha512_hash[4], sha512_hash[5], sha512_hash[6])
              + sha512_table[i] + sha512[i];
        st2 = BG0(sha512_hash[0]) +
              M(sha512_hash[0], sha512_hash[1], sha512_hash[2]);
        sha512_hash[7] = sha512_hash[6];
        sha512_hash[6] = sha512_hash[5];
        sha512_hash[5] = sha512_hash[4];
        sha512_hash[4] = sha512_hash[3] + st1;
        sha512_hash[3] = sha512_hash[2];
        sha512_hash[2] = sha512_hash[1];
        sha512_hash[1] = sha512_hash[0];
        sha512_hash[0] = st1 + st2;
        i++;
    }
}

static void	secont_st(unsigned long *sha512)
{
    unsigned long	copy[8];
    int				i;

    i = 0;
    while (i < 8)
    {
        copy[i] = sha512_hash[i];
        i++;
    }
    third_st(sha512);
    i = 0;
    while (i < 8)
    {
        sha512_hash[i] = copy[i] + sha512_hash[i];
        i++;
    }
}

static void	first_st(t_ssl *ssl, unsigned long *sha512)
{
    int i;

    i = -1;
    while (++i < 16)
        sha512[i] = reverse_bytes_long(ssl->input_int[i], 8);
    while (i < 80)
    {
        sha512[i] = SG1(sha512[i - 2]) + sha512[i - 7] +
                    SG0(sha512[i - 15]) + sha512[i - 16];
        ++i;
    }
}

void	sha512_wiki(t_ssl *ssl)
{
    unsigned long sha512[80];

    ft_bzero(&sha512[0], 80);
    first_st(ssl, &sha512[0]);
    secont_st(&sha512[0]);
}