#pragma once
#include <windows.h>
#include <stdio.h>
#include <globals.h>

namespace sdk::il2cpp
{
	// @note: resolve_icall - hooked in alot of games by anti cheat, but usually should be there
	// @todo: add a fallback incase il2cpp_resolve_icall is not found
	using il2cpp_resolve_icall_t = void* ( __stdcall* )( const char* );
	il2cpp_resolve_icall_t il2cpp_resolve_icall = nullptr;

    // @usage: resolve_icall( "namespace_name.class_name::function_name" )
    void* resolve_icall( const char* name )
    {
        if ( !il2cpp_resolve_icall )
        {
            printf( "[ il2cpp ] il2cpp_resolve_icall is null\n" );
            return nullptr;
        }

        void* func = il2cpp_resolve_icall( name );
        printf( "[ il2cpp ] resolving %s\n", name );

        if ( !func )
        {
            printf( "[ il2cpp ] failed to resolve %s\n", name );
        }

        return func;
    }

	// initialize
	inline bool initialize( )
	{
		if ( !core::globals::h_game )
		{
			printf( "[ il2cpp ] core::globals::h_game is null\n" );
			return false;
		}

		il2cpp_resolve_icall = reinterpret_cast<il2cpp_resolve_icall_t>( GetProcAddress( core::globals::h_game, "il2cpp_resolve_icall" ) );
		if ( !il2cpp_resolve_icall )
		{
			printf( "[ il2cpp ] failed to find il2cpp_resolve_icall \n" );
		}
		printf( "[ il2cpp ] il2cpp_resolve_icall : %p\n", il2cpp_resolve_icall );


        return true;
	}
}