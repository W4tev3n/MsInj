/*
MIT License

Copyright (c) 2022 W4tev3n

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <Windows.h>
#include <TlHelp32.h>

#include "msinj_x64.h"
#include "msinj_x86.h"

#include <stdio.h>
#include <stdlib.h>

void msinj_x86_inject(int pid, const char* dll, bool silent) {
    FILE* file = fopen("msinj_x86.exe", "wb");
    fwrite(msinj_x86, 1, msinj_x86_size, file);
    fclose(file);
    char cmd[260];
    sprintf(cmd, "msinj_x86.exe %i %s", pid, dll);
    if (silent) strcat(cmd, " > NUL");
    system(cmd);
    remove("msinj_x86.exe");
}

void msinj_x64_inject(int pid, const char* dll, bool silent) {
    FILE* file = fopen("msinj_x64.exe", "wb");
    fwrite(msinj_x64, 1, msinj_x64_size, file);
    fclose(file);
    char cmd[260];
    sprintf(cmd, "msinj_x64.exe %i %s", pid, dll);
    if (silent) strcat(cmd, " > NUL");
    system(cmd);
    remove("msinj_x64.exe");
}

int msinj_find_pid(const wchar_t* process)
{
    PROCESSENTRY32 process_info;
    process_info.dwSize = sizeof(process_info);

    HANDLE process_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (process_snapshot == INVALID_HANDLE_VALUE)
        return 0;

    Process32First(process_snapshot, &process_info);
    do {
        if (!wcscmp(process, process_info.szExeFile)) {
            CloseHandle(process_snapshot);
            return process_info.th32ProcessID;
        }
    } while (Process32Next(process_snapshot, &process_info));

    CloseHandle(process_snapshot);
    return 0;
}

void msinj_x86_inject(const wchar_t* process, const char* dll, bool silent) {
    msinj_x86_inject(msinj_find_pid(process), dll, silent);
};

void msinj_x64_inject(const wchar_t* process, const char* dll, bool silent) {
    msinj_x64_inject(msinj_find_pid(process), dll, silent);
};