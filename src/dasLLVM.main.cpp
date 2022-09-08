#include "daScript/misc/platform.h"
#include "daScript/ast/ast.h"
#include "daScript/ast/ast_interop.h"
#include "daScript/ast/ast_handle.h"
#include "daScript/ast/ast_typefactory_bind.h"
#include "daScript/simulate/bind_enum.h"
#include "dasLLVM.h"
#include "need_dasLLVM.h"
#include "cb_dasLLVM.h"

namespace das {


LLVMDisasmContextRef das_LLVMCreateDisasm (const char *TripleName, void *DisInfo, int TagType) {
    return LLVMCreateDisasm(TripleName,DisInfo,TagType,nullptr,nullptr);
}

void Module_dasLLVM::initMain() {
	addExtern< void (*)(LLVMOpaquePassRegistry *) , LLVMInitializeCore >(*this,lib,"LLVMInitializeCore",SideEffects::worstDefault,"LLVMInitializeCore")
		->args({"R"});
    // disasm
	addExtern<DAS_BIND_FUN(das_LLVMCreateDisasm) >(*this,lib,"LLVMCreateDisasm",SideEffects::worstDefault,"das_LLVMCreateDisasm")
		->args({"TripleName","DisInfo","TagType"});
}

ModuleAotType Module_dasLLVM::aotRequire ( TextWriter & tw ) const {
    // add your stuff here
    // tw << "#include <clang-c/Index.h>\n";
    tw << "#include \"../modules/dasLLVM/src/cb_dasClangBind.h\"\n";
    // tw << "#include \"../modules/dasLLVM/src/dasClangBind.enum.decl.cast.inc\"\n";
    return ModuleAotType::cpp;
}

}


