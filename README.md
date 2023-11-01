# pascal_remote_assembly
Transforms pascal code to asmjit remote assembly code. Then the code will be prepare to compile with nasm. And the result is a test.asm, and test.o file.
The source code is based on msys2 MingW64 GNU C/C++

**I used Bison, and Flex - which are called yacc, and flex, too, to create the Pascal-Parser.**
To use this Toolchain, you can use the build.sh script.
1. ~#  ./build.sh -a
2. ~# ./build.sh -i
3. ~# cd temp
4. ~temp# ./pc.exe test.pas
5. ~temp# ./diss.exe test_nasm.asm

The Generator (pc.exe) produce this assembly code (with help of build.sh script):

    section .text
    L1:
        push rbp
        mov rbp, rsp
        sub rsp, 0x20
        mov ecx, 0
        mov rdx, Lv_Entry__lpText
        mov r8, Lv_Entry__lpCapt
        mov r9d, 2
        call MessageBoxA
    L0:
        mov rsp, rbp
        pop rbp
        ret
    L3:
        push rbp
        mov rbp, rsp
        sub rsp, 0x40
        mov rcx, qword [rsp+0x20]
        mov rdx, qword [rsp+0x28]
        mov r8, qword [rsp+0x30]
        mov r9, qword [rsp+0x38]
        call MessageBoxA
    L2:
        mov rsp, rbp
        pop rbp
        ret
    
    ; T 0x00007ff94990ca50 MessageBoxA
    ; T 0x00007ff645893f84 Lv_Entry__lpText
    ; T 0x00007ff64589404c Lv_Entry__lpCapt
    ; T 0x00007ff900000002 Lv_Entry__lpMsgM
    Lv_Entry__lpText:
    	db "huhuhaha"
    Lv_Entry__lpCapt:
    	db "mumu", 0
    Lv_Entry__lpMsgM:
    	dd 0x2 
    ; T 0x00007ff94990ca50 MessageBoxA
    MessageBoxA:
    	dq 0x00007ff94990ca50


And the Interpreter (diss.exe) reads the AsmJit pimped Code, and produce this one:

    // -------------------------------------------------------------------
    // AsmJIT automatically created C++ source file.
    // (c) 2023 kallup non-profit - Jens Kallup - paule32
    // all rights reserved.
    //
    // only for education, and non-profit usage.
    // -------------------------------------------------------------------
    # include <stdio.h>
    # include <stdlib.h>
    # include <strings.h>
    # include <libintl.h>    // localization
    
    # include <iostream>
    # include <sstream>
    # include <cstring>
    # include <string>
    
    #include <asmjit/x86.h>
    #include <stdio.h>
    
    using namespace asmjit;
    
    // Signature of the generated function.
    typedef int (*Func)(void);
    
    void yyerror(const char* msg) {
    	std::cout << "error: " << msg << std::endl;
    	exit(1);
    }
    
    // -------------------------------------------------------------------
    // this is our "nain" entry point of application start.
    // -------------------------------------------------------------------
    int main(int argc, char **argv)
    {
    	JitRuntime rt;                     // Runtime specialized for JIT code executin.
    	Error err;
    
    	CodeHolder code;                   // Holds code and relocation information.
    	code.init(rt.environment(),        // Initialize code to matchthe JIT environment.
    	          rt.cpuFeatures());
    
    	x86::Assembler a(&code);           // Create and attach x86::Assembler to code.
    
    	Section* section_text;
    	err = code.newSection(&section_text, "text", SIZE_MAX, SectionFlags::kNone, 8);
    	if (err)
    	yyerror(gettext("failed to create section: sect_text"));
    
    	Label lbl_L1 = a.newNamedLabel("L1", SIZE_MAX);
    	err = a.bind(lbl_L1);
    	if (err)
    	yyerror(gettext("failed bind label"));
    	Label lbl_L0 = a.newNamedLabel("L0", SIZE_MAX);
    	err = a.bind(lbl_L0);
    	if (err)
    	yyerror(gettext("failed bind label"));
    	Label lbl_L3 = a.newNamedLabel("L3", SIZE_MAX);
    	err = a.bind(lbl_L3);
    	if (err)
    	yyerror(gettext("failed bind label"));
    	Label lbl_L2 = a.newNamedLabel("L2", SIZE_MAX);
    	err = a.bind(lbl_L2);
    	if (err)
    	yyerror(gettext("failed bind label"));
    	Label lbl_Lv_Entry__lpText = a.newNamedLabel("Lv_Entry__lpText", SIZE_MAX);
    	err = a.bind(lbl_Lv_Entry__lpText);
    	if (err)
    	yyerror(gettext("failed bind label"));
    	Label lbl_Lv_Entry__lpCapt = a.newNamedLabel("Lv_Entry__lpCapt", SIZE_MAX);
    	err = a.bind(lbl_Lv_Entry__lpCapt);
    	if (err)
    	yyerror(gettext("failed bind label"));
    	Label lbl_Lv_Entry__lpMsgM = a.newNamedLabel("Lv_Entry__lpMsgM", SIZE_MAX);
    	err = a.bind(lbl_Lv_Entry__lpMsgM);
    	if (err)
    	yyerror(gettext("failed bind label"));
    	Label lbl_MessageBoxA = a.newNamedLabel("MessageBoxA", SIZE_MAX);
    	err = a.bind(lbl_MessageBoxA);
    	if (err)
    	yyerror(gettext("failed bind label"));
    	a.mov(x86::eax, 2);
    	a.ret();
    	// ==== x86::Assembler is no longer needed from here, and we can destroyed ==== 
    
    	Func fn;                           // Holds address to the generated function.
    	err = rt.add(&fn, &code);          // Add the generated code to run
    	if (err)                           // Handle a possible error returbed by asmjit.
    	yyerror(gettext("failed added function"));
    	// ==== CodeHolder is no longer needed from here, and we can destroyed ==== 
    
    	int result = fn();                 // Execute the generated code.
    	printf("%d\n", result);            // Print the result.
    
    	// All classes use RAII, all resources will be released before `main()` returns,
    	// the generated function can be, however, released explicitly if you intend to
    	// reuse or keep the runtime alive, which you should in a production-ready code.
    	rt.release(fn);
    
    	return EXIT_SUCCESS;
    }
