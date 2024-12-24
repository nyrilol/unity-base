#pragma once
#include <minhook.h>
#include <il2cpp.h>
#include <globals.h>

namespace core::hooks
{
	using set_fov_t = void( * )( void*, float );
	set_fov_t og_set_fov = nullptr;

	void hk_set_fov( void* instance, float fov )
	{
		printf( "[ hook ] hk_set_fov called - instance: %p, fov: %f\n", instance, fov );
		if ( !og_set_fov ) {
			printf( "[ hook ] original function is null!\n" );
			return;
		}

		og_set_fov( instance, fov );
	}

	inline bool initialize( )
	{
		if ( core::globals::is_il2cpp )
		{

			// MH_Initialize( );

			// MH_EnableHook( MH_ALL_HOOKS );

			printf( "[ core ] finished il2cpp hooks\n" );
		}

		return true;
	}

	inline void destroy( )
	{
		MH_DisableHook( MH_ALL_HOOKS );
		MH_Uninitialize( );
	}
}