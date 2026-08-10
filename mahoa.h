#ifndef MAHOA_H
#define MAHOA_H
#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif
#define Alphabet_len 33

int checkso(char *input_str, int i);
EXPORT void meow_chuoi(char *input_str, char *output_str, int max_len);
EXPORT void meow_file(char *file_path, char *output_str, int max_len);
EXPORT void dich_chuoi(char *input_str, char *output_str, int max_len);
EXPORT void dich_file(char *file_path, char *output_str, int max_len);
extern char first;
extern const char ALPHABET[];
#endif