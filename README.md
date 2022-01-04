# MsInj
A tiny wrapper for microsoft-signed dll injector.

## Usage
Simply include msinj.h in your code and then user either

```c
msinj_x86_inject(/*pid*/1234, /*dll path*/"C:\\example.dll", /*silent mode*/true);
```
or

```c
msinj_x86_inject(/*process name*/L"process.exe", /*dll path*/"C:\\example.dll", /*silent mode*/true);
```