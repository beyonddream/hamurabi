#ifndef BANNED_H
#define BANNED_H

#define BANNED(func) banned_function_##func##_called

#undef strcpy
#undef strcat
#undef strncpy
#undef strncat
#undef sprintf
#undef vsprintf
#undef gets
/* thread unsafe */
#undef strtok

#define strcpy(x, y) BANNED(strcpy)
#define strcat(x, y) BANNED(strcat)
#define strncpy(x, y, n) BANNED(strncpy)
#define strncat(x, y, n) BANNED(strncat)
#define gets(x) BANNED(gets)
#define strtok(x, y) BANNED(strtok)
#ifdef HAVE_VARIADIC_MACROS
#define sprintf(...) BANNED(sprintf)
#define vsprintf(...) BANNED(vsprintf)
#else
#define sprintf(buf, fmt, arg) BANNED(sprintf)
#define vsprintf(buf, fmt, arg) BANNED(vsprintf)
#endif

#endif /* BANNED_H */
