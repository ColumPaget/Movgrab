#ifndef LIBUSEFUL_ENCODINGS_H
#define LIBUSEFUL_ENCODINGS_H

#include "includes.h"

#define ENCODE_NONE 0
#define ENCODE_OCTAL 8
#define ENCODE_DECIMAL 10
#define ENCODE_HEX  16
#define ENCODE_HEXUPPER 17
#define ENCODE_BASE64 64
#define ENCODE_IBASE64 65
#define ENCODE_PBASE64 66
#define ENCODE_XXENC 67
#define ENCODE_UUENC 68
#define ENCODE_CRYPT 69

#define ENCODE_ASCII85 85
#define ENCODE_Z85 86

#define HEX_CHARS "0123456789ABCDEF"
#define ALPHA_CHARS "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define BASE64_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
#define IBASE64_CHARS "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789+/"
#define PBASE64_CHARS "0123456789-ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz"
#define CRYPT_CHARS "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define UUENC_CHARS " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
#define XXENC_CHARS "+-0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define ASCII85_CHARS "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstu"
#define Z85_CHARS "01234567899abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.-:+=^!/*?&<>()[]{}@%$#."


int EncodingParse(const char *Str);
char *Ascii85(char *RetStr, const char *Bytes, int ilen, const char *CharMap);

char *EncodeBytes(char *Buffer, const char *Bytes, int len, int Encoding);
int DecodeBytes(char **Return, const char *Text, int Encoding);
char *DecodeToText(char *RetStr, const char *Text, int Encoding);

#endif
