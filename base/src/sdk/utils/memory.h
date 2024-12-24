#pragma once
#include <windows.h>
#include <cstdint>
#include <vector>

namespace unity::memory
{
    // vfunc
    template <typename return_t>
    inline return_t get_vfunc( void* instance, std::size_t index )
    {
        auto vtable = *reinterpret_cast<void***>( instance );
        return reinterpret_cast<return_t>( vtable[ index ] );
    }

    template <typename return_t, typename... arguments>
    inline return_t call_vfunc( void* instance, std::size_t index, arguments... args )
    {
        using fn = return_t( __fastcall* )( void*, arguments... );
        auto function = get_vfunc<fn>( instance, index );
        return function( instance, args... );
    }

    // other helper functions
    inline std::uint8_t* pattern_scan( HMODULE h_module, const char* signature )
    {
        static auto pattern_to_byte = []( const char * pattern ) {
            std::vector<int> bytes;
            const char* start = pattern;
            const char* end = pattern + std::strlen( pattern );

            for ( const char* current = start; current < end; ++current )
            {
                if ( *current == '?' )
                {
                    ++current;
                    if ( *current == '?' )
                        ++current;
                    bytes.push_back( -1 );
                }
                else
                {
                    bytes.push_back( std::strtoul( current, const_cast<char**>( &current ), 16 ) );
                }
            }
            return bytes;
            };

        auto* dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>( h_module );
        auto* nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS64>( reinterpret_cast<std::uint8_t*>( h_module ) + dos_header->e_lfanew );

        const auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
        auto* scan_bytes = reinterpret_cast<std::uint8_t*>( h_module );

        auto pattern_bytes = pattern_to_byte( signature );
        const auto size = pattern_bytes.size( );
        auto* data = pattern_bytes.data( );

        for ( std::size_t i = 0; i < size_of_image - size; ++i )
        {
            bool found = true;
            for ( std::size_t j = 0; j < size; ++j )
            {
                if ( scan_bytes[ i + j ] != data[ j ] && data[ j ] != -1 )
                {
                    found = false;
                    break;
                }
            }

            if ( found )
                return &scan_bytes[ i ];
        }
        return nullptr;
    }

}