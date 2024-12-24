// dllmain.cpp : Defines the entry point for the DLL application.
#include <windows.h>
#include <thread>

// core includes
#include <globals.h>
#include <hooks.h>

// backend includes
#include <il2cpp.h>
#include <mono.h>

// type includes
#include <il2cpp_types/camera.h>
#include <il2cpp_types/gameobject.h>
#include <il2cpp_types/transform.h>

#include <mono_types/camera.h>

DWORD WINAPI main_thread( LPVOID lp_param )
{
    // allocate console only if built in debug
#ifdef _DEBUG
    AllocConsole( );
    FILE* console_output;
    freopen_s( &console_output, "CONOUT$", "w", stdout );
#endif

    // set h_game module global
    if ( core::globals::is_il2cpp ) 
    {
        core::globals::h_game = GetModuleHandleA( "GameAssembly.dll" );


        if ( !sdk::il2cpp::initialize( ) )
        {
            printf( "[ il2cpp ] failed to initialize il2cpp\n" );
        }

        if ( !core::hooks::initialize( ) )
        {
            printf( "[ il2cpp ] failed to initialize hooks\n" );
        }

    }
    else
    {
        core::globals::h_game = GetModuleHandleA( "mono-2.0-bdwgc.dll" ); // i actually dont know the name of the mono module
        if ( !core::globals::h_game )
            core::globals::h_game = GetModuleHandleA( "mono.dll" );


        if ( !sdk::mono::initialize( ) )
        {
            printf( "[ mono ] failed to initialize mono\n" );
        }
    }

    if ( core::globals::is_il2cpp )
        core::globals::og_fov = sdk::il2cpp::camera::get_fov( );
    else
        core::globals::og_fov = sdk::mono::camera::get_fov( );

    while ( !GetAsyncKeyState( VK_DELETE ) )
    {
        if ( core::globals::is_il2cpp )
        {
            // camera usage example
            if ( sdk::il2cpp::camera::is_camera_active( ) )
            {
                sdk::il2cpp::camera::set_fov( 90.f );
                printf( "[ cheat ] camera fov: %f\n", sdk::il2cpp::camera::get_fov( ) );   
            }      
        }
        else
        {
            if ( sdk::mono::camera::is_camera_active( ) )
            {
                sdk::mono::camera::set_fov( 120.f );
                printf( "[ cheat ] camera fov: %f\n", sdk::mono::camera::get_fov( ) );   
            }
        }

        std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
    }

    core::hooks::destroy( );

    FreeConsole( );
    FreeLibraryAndExitThread( static_cast<HMODULE>( lp_param ) , EXIT_SUCCESS);

    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{

    if ( ul_reason_for_call == DLL_PROCESS_ATTACH )
    {
        DisableThreadLibraryCalls( hModule );
        CreateThread( 0, 0, main_thread, 0, 0, 0 );
    }

    return TRUE;
}