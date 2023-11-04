// -----------------------------------------------------------------
// @file:   win32api.cc
// @author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// @copyright only for education, and non-profit usage !
// -----------------------------------------------------------------
# include "Parser.h"
# include "windows.h"

// -----------------------------------------------------------------
// pre-pare collected win32api member functions ...
// -----------------------------------------------------------------
void Parser::ASM_Code::init_win32api()
{
    // -----------------------------------------
    // signature of: EntryPoint
    // -----------------------------------------
    FuncNode * mainFunc = cc->newFunc(
    FuncSignatureT<void,void >(CallConvId::kHost));
    mainFunc->frame().setPreservedFP();
    FuncNodeMap.insert({"EntryPoint", mainFunc});

    // -----------------------------------------
    // .text EntryPoint
    // -----------------------------------------
    cc->addFunc(mainFunc);

    x86::Mem stack = cc->newStack(8, 1, "stack");

    InvokeNode * invokeNode;
    cc->invoke(& invokeNode,
        imm((void*)::MessageBoxA),
        //FuncNodeMap["MessageBoxA"]->label(),
        FuncSignatureT<void, HWND, LPCTSTR, LPCTSTR, UINT>(
        CallConvId::kHost));

    HWND    lpHWin = HWND(0);
    LPCTSTR lpText = LPCTSTR("huhuhaha");
    LPCTSTR lpCapt = LPCTSTR("mumu");
    UINT    lpMsgM = UINT(2);
    
    char * buffer  = new char[20480];
    sprintf(buffer,
            "; T 0x%p extern_MessageBoxA" "\n"
            "; T 0x%p Lv_Entry__lpText"      "\n"
            "; T 0x%p Lv_Entry__lpCapt"      "\n"
            "; T 0x%p Lv_Entry__lpMsgM"      "\n"
            
            "Lv_Entry__lpText:" "\n\t" "db \"%s\", 0" "\n"
            "Lv_Entry__lpCapt:" "\n\t" "db \"%s\", 0" "\n"
            "Lv_Entry__lpMsgM:" "\n\t" "dd 0x%x "     "\n"
            ,
            ::MessageBoxA ,
            lpText, lpCapt, lpMsgM,
            lpText, lpCapt, lpMsgM
            );
    FuncTableStream << buffer;
    
    std::cout << FuncTableStream.str() << std::endl;
    delete [] buffer;
    
    invokeNode->setArg(0, lpHWin );
    invokeNode->setArg(1, lpText );
    invokeNode->setArg(2, lpCapt );
    invokeNode->setArg(3, lpMsgM );

    cc->ret();
    cc->endFunc();
    
    mapArgumentsList();
    user32_MessageBox();
}

// -----------------------------------------------------------------
// generator member: MessageBoxA - ANSI
// -----------------------------------------------------------------
bool Parser::ASM_Code::user32_MessageBox()
{
    try {
        // -----------------------------------------
        // signature of: MessageBoxA
        // -----------------------------------------
        FuncSignatureBuilder signature(CallConvId::kHost);
        signature.setRetT< int     >();
        
        signature.addArgT< HWND    >();
        signature.addArgT< LPCTSTR >();
        signature.addArgT< LPCTSTR >();
        signature.addArgT< UINT    >();
        
        FuncNode * funcnode = cc->addFunc(signature);
        funcnode->frame().setPreservedFP();
        
        x86::Gp p1 = cc->newIntPtr( "hwnd"      );
        x86::Gp p2 = cc->newIntPtr( "lpText"    );
        x86::Gp p3 = cc->newIntPtr( "lpCaption" );
        x86::Gp p4 = cc->newIntPtr( "uint"      );
        //
        x86::Mem stack = cc->newStack( 1024, 1024 );

        // ---------------------------------
        // call winapi32 function ...
        // ---------------------------------
        InvokeNode * invokeNode;
        cc->invoke(& invokeNode,
            imm((int*)::MessageBoxA),
            signature);

        // --------------------------------------------------
        // set the arguments by index, starting by 0.
        // --------------------------------------------------
        invokeNode->setArg( 0, p1 );
        invokeNode->setArg( 1, p2 );
        invokeNode->setArg( 2, p3 );
        invokeNode->setArg( 3, p4 );
                
        cc->ret();
        cc->endFunc();
        
        // -------------------------------------------
        // write address resolution - done by build.sh
        // -------------------------------------------
        char  * buffer = new char[1024];
        sprintf(buffer,
            "; T 0x%p extern_MessageBoxA\n"
            "extern_MessageBoxA:\n\tdq 0x%p\n",
            ::MessageBoxA,
            ::MessageBoxA
        );
        FuncTableStream << buffer;
        
        delete [] buffer;
        return true;
    }
    catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }
    catch (std::string &e) {
        std::stringstream ss;
        ss  << _("Runtime add: ")
            << "MessageBoxA  "
            << _("fail.")      << std::endl
            << _("Error: ")
            << e               << std::endl;
        std::cout << ss.str()  << std::endl;
    }
    
    return false;
}
