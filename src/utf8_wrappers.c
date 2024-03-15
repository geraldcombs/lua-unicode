/**
 * Wrappers to provide Unicode (UTF-8) support on Windows.
 *
 * Copyright (c) 2018 Peter Wu <peter@lekensteyn.nl>
 * SPDX-License-Identifier: (GPL-2.0-or-later OR MIT)
 */

#ifdef _WIN32
#include <windows.h>    /* for MultiByteToWideChar */
#include <wchar.h>      /* for _wrename */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// Set a high limit in case long paths are enabled.
#define MAX_PATH_SIZE   4096
#define MAX_MODE_SIZE   128
// cmd.exe argument length is reportedly limited to 8192.
#define MAX_CMD_SIZE    8192

FILE *fopen_utf8(const char *pathname, const char *mode) {
    wchar_t pathname_w[MAX_PATH_SIZE];
    wchar_t mode_w[MAX_MODE_SIZE];
    if (!MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, pathname, -1, pathname_w, MAX_PATH_SIZE) ||
        !MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, mode, -1, mode_w, MAX_MODE_SIZE)) {
        errno = EINVAL;
        return NULL;
    }
    return _wfopen(pathname_w, mode_w);
}

FILE *freopen_utf8(const char *pathname, const char *mode, FILE *stream) {
    wchar_t pathname_w[MAX_PATH_SIZE];
    wchar_t mode_w[MAX_MODE_SIZE];
    if (!MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, pathname, -1, pathname_w, MAX_PATH_SIZE) ||
        !MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, mode, -1, mode_w, MAX_MODE_SIZE)) {
        // Close stream as documented for the error case.
        fclose(stream);
        errno = EINVAL;
        return NULL;
    }
    return _wfreopen(pathname_w, mode_w, stream);
}

FILE *popen_utf8(const char *command, const char *mode) {
    wchar_t command_w[MAX_CMD_SIZE];
    wchar_t mode_w[MAX_MODE_SIZE];
    if (!MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, command, -1, command_w, MAX_CMD_SIZE) ||
        !MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, mode, -1, mode_w, MAX_MODE_SIZE)) {
        errno = EINVAL;
        return NULL;
    }
    return _wpopen(command_w, mode_w);
}

#endif
