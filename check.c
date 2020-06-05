#include <stdio.h>
#include <string.h>
#include <stdint.h> // for uint32_t

    uint32_t fletcher32_1(const uint16_t *data, size_t len)
    {
            uint32_t c0, c1;
            unsigned int i;

            for (c0 = c1 = 0; len >= 360; len -= 360) {
                    for (i = 0; i < 360; ++i) 
		    {
                            c0 = c0 + *data++;
                            c1 = c1 + c0;
                    }
                    c0 = c0 % 65535;
                    c1 = c1 % 65535;
            }
            for (i = 0; i < len; ++i) {
                    c0 = c0 + *data++;
                    c1 = c1 + c0;
            }
            c0 = c0 % 65535;
            c1 = c1 % 65535;
            return (c1 << 16 | c0);
    }

    uint32_t fletcher32_2(const uint16_t *data, size_t l)
    {
        uint32_t sum1 = 0xffff, sum2 = 0xffff;

        while (l) {
            unsigned tlen = l > 359 ? 359 : l;
            l -= tlen;
            do {
                sum2 += sum1 += *data++;
            } while (--tlen);
            sum1 = (sum1 & 0xffff) + (sum1 >> 16);
            sum2 = (sum2 & 0xffff) + (sum2 >> 16);
        }
        /* Second reduction step to reduce sums to 16 bits */
        sum1 = (sum1 & 0xffff) + (sum1 >> 16);
        sum2 = (sum2 & 0xffff) + (sum2 >> 16);
        return (sum2 << 16) | sum1;
    }

    int main()
    {
        char *str1 = "abcde";  
        char *str2 = "abcdef";

        size_t len1 = (strlen(str1)+1) / 2; //  '\0' will be used for padding 
        size_t len2 = (strlen(str2)+1) / 2; // 

        uint32_t f1 = fletcher32_1(str1,  len1);
        uint32_t f2 = fletcher32_2(str1,  len1);

        printf("%u %X \n",    f1,f1);
        printf("%u %X \n\n",  f2,f2);

        f1 = fletcher32_1(str2,  len2);
        f2 = fletcher32_2(str2,  len2);

        printf("%u %X \n",f1,f1);
        printf("%u %X \n",f2,f2);

        return 0;
    }
