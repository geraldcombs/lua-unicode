/**
 * Wrappers to provide Unicode (UTF-8) support on Windows.
 *
 * Copyright (c) 2018 Peter Wu <peter@lekensteyn.nl>
 * SPDX-License-Identifier: (GPL-2.0-or-later OR MIT)
 */

#ifdef _WIN32

#if defined(loadlib_c) || defined(lauxlib_c) || defined(liolib_c) || defined(luac_c)
#include <stdio.h>  /* for loadlib_c */
FILE *fopen_utf8(const char *pathname, const char *mode);
#define fopen               fopen_utf8
#endif

#ifdef lauxlib_c
FILE *freopen_utf8(const char *pathname, const char *mode, FILE *stream);
#define freopen             freopen_utf8
#endif

#ifdef liolib_c
FILE *popen_utf8(const char *command, const char *mode);
#define _popen              popen_utf8
#endif

#endif // _WIN32

#if defined(lua_c) || defined(luac_c)
int main_utf8(int argc, char *argv[]);
#define main                main_utf8
#endif
