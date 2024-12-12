# PIC-Library

A collection of position independent resources. Code snippets, blog posts, everything PIC.

During the development of [Hannibal](https://github.com/MythicAgents/Hannibal), I spent quite a bit of time looking for and adapting functionality. Many libraries were written in ways that were not easy to modify for position independent coding.

This repo is intended to create a central location to find content that is known PIC friendly. This will hopefully aid in the development process.



### Note

BOF related content has not been included as there are plenty of resources documenting BOF development. This repo is not dedicated to a specific format. It is designed to include functionality that is written in a PIC friendly way.

If you're looking for BOF resources, simply search Github: https://github.com/search?q=bof&type=repositories

Not all content has been tested. Snippets in general should be PIC friendly, but may require some modification to work with your codebase. Some linked projects are very old and no longer maintained. They may still be of use though.

## Navigation

> Snippets are organized in folders per language. Tables per type for external resources.

- [Shellcoding Templates](#shellcoding-templates)
- [Position Dependent to Independent Tooling](#position-dependent-to-independent-tooling)
- [Encryption](#encryption)
- [Encoding](#encoding)
- [Hashing](#hashing)
- [References](#references)

### Shellcoding Templates

| Language | Link | About |
| -------- | ------- | ------- |
| C/C++ | https://github.com/realoriginal/shellcode-template     | A cmkr based win32 shellcode template for a unified build platform and more production friendly structure/testing. |
| C/C++  | https://github.com/Cracked5pider/Stardust    | A modern 64-bit position independent implant template |
| C/C++  | https://github.com/paranoidninja/PIC-Get-Privileges     | Building and Executing Position Independent Shellcode from Object Files in Memory |
| C/C++ | https://github.com/jackullrich/ShellcodeStdio | An extensible framework for easily writing compiler optimized position independent x86 / x64 shellcode for windows platforms.|
| C/C++ | https://github.com/ASkyeye/CobaltPatch | Cobalt Strike Malleable Profile Inline Patch Template: A Position Independent Code (PIC) Code Template For Creating Shellcode That Can Be Appended In Stage / Post-Ex Blocks. Made for C Programmers |
| C/C++ | https://github.com/mattifestation/PIC_Bindshell | Position Independent Windows Shellcode Written in C |
| C/C++ | https://github.com/lawiet47/PIShellcode | Position-Independent Shellcode Loader |
| C/C++ | https://packetstorm.news/files/id/10517 | Hellkit is a shellcode generator. You write the your shellcode in C, and it gets converted to ASM for use with both heap and stack based overflows. Examples included.|
| C/C++ | http://www.secdev.org/projects/shellforge/ | ShellForge is a python program that builds shellcodes from C. It is inspired from Stealth's Hellkit. |
| C/C++ | https://github.com/whatsbcn/shellforge4 | Enhanced version of secdev's shellforge G3. More platforms and architectures supported.|
| C/C++ | https://github.com/NytroRST/ShellcodeCompiler | Shellcode Compiler |
| C/C++ | https://github.com/humeafo/scc | a C/C++ shellcode compiler based on llvm/clang |
| C/C++ | https://github.com/gdelugre/shell-factory | C++-based shellcode builder |
| C/C++ | https://github.com/lainswork/shellcode-factory | shellcode 生成框架 |
| C/C++ | https://github.com/ixty/xarch_shellcode | Cross Architecture Shellcode in C |
| C/C++ | https://github.com/SheLLVM/SheLLVM | A collection of LLVM transform and analysis passes to write shellcode in regular C |
| C/C++ | https://packetstorm.news/files/id/31755 | MOSDEF is a 100% Python retargetable compiler for C->shellcode that has been released to the public under the LGPL.|
| C/C++ | https://scc.binary.ninja/ | The Shellcode Compiler is a C compiler designed to output standalone code that will be injected into other running processes. |
| Rust | https://github.com/safedv/Rustic64 | 64-bit, position-independent implant template for Windows in Rust.|
| Rust | https://github.com/Irate-Walrus/stardust-rs | An i686 & x86_64 position independent implant template for Rust 🦀 |


### Position Dependent to Independent Tooling

| Target OS | Link | About |
| -------- | ------- | ------- |
| Windows | https://github.com/TheWover/donut| Generates x86, x64, or AMD64+x86 position-independent shellcode that loads .NET Assemblies, PE files, and other Windows payloads from memory and runs them with parameters |
| Windows | https://github.com/monoxgas/sRDI | Shellcode implementation of Reflective DLL Injection. Convert DLLs to position independent shellcode |
| Windows | https://github.com/hasherezade/pe_to_shellcode | Converts PE into a shellcode |
| Windows | https://github.com/timwhitez/Doge-sRDI | Shellcode implementation of Reflective DLL Injection by Golang. Convert DLLs to position independent shellcode | 
| Linux | https://github.com/jonatanSh/shelf | Python library to convert elf to os-independent shellcodes |
| Linux | https://github.com/feliam/mkShellcode | This rearranges an ELF object file so it can be used as shellcode.|


### Encryption

| Language | Link | About |
| -------- | ------- | ------- |
| C/C++ | https://github.com/kokke/tiny-AES-c/ | Small portable AES128/192/256 in C |


### Encoding

| Language | Link | About |
| -------- | ------- | ------- |
| C/C++ | https://github.com/zhicheng/base64 | base64 c implementation |


### Hashing

| Language | Link | About |
| -------- | ------- | ------- |
| C/C++ | https://github.com/robertdavidgraham/whats-dec/blob/master/crypto-sha256.c | WhatsApp end-to-end media decryptor |


### References

- https://phasetw0.com/malware/writing-optimized-windows-shellcode-in-c/
- https://web.archive.org/web/20201202085848/http://www.exploit-monday.com/2013/08/writing-optimized-windows-shellcode-in-c.html
- https://nickharbour.wordpress.com/2010/07/01/writing-shellcode-with-a-c-compiler/
- https://kerkour.com/rust-position-independent-shellcode
- https://5pider.net/blog/2024/01/27/modern-shellcode-implant-design
- https://hadess.io/position-independent-code/
- https://www.ired.team/offensive-security/code-injection-process-injection/writing-and-compiling-shellcode-in-c
- https://github.com/thefLink/C-To-Shellcode-Examples
- https://medium.com/@shaddy43/the-epitome-of-evasion-a-custom-shellcode-c751a1a17e5b
- https://web.archive.org/web/20240316161315/https://modexp.wordpress.com/2019/04/24/glibc-shellcode/
- https://web.archive.org/web/20220520143032/http://blog.binamuse.com/2013/01/about-shellcodes-in-c.html
- https://blog.didierstevens.com/programs/shellcode/#ShellCodeWithaCCompiler
- https://web.archive.org/web/20190119221900/https://radare.today/posts/payloads-in-c/
- https://phrack.org/issues/69/4.html
- https://web.archive.org/web/20170501023430/http://winternl.com/2016/05/02/hello-world/
- https://www.blackhat.com/presentations/bh-europe-09/Caillat/BlackHat-Europe-09-Caillat-Wishmaster-whitepaper.pdf
- https://files.brucon.org/2021/PIC-Your-Malware.pdf