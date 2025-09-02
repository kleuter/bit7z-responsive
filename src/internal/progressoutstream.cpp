// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

/*
 * bit7z - A C++ static library to interface with the 7-zip shared libraries.
 * Copyright (c) 2014-2023 Riccardo Ostani - All Rights Reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "internal/progressoutstream.hpp"

namespace bit7z {

ProgressOutStream::ProgressOutStream( IOutStream* stream, ProgressCallback callback )
    : mStream( stream ), mCallback( std::move( callback ) ), mProcessed( 0 ) {}

COM_DECLSPEC_NOTHROW
STDMETHODIMP ProgressOutStream::Write( const void* data, UInt32 size, UInt32* processedSize ) noexcept {
    const HRESULT res = mStream->Write( data, size, processedSize );
    if ( res != S_OK ) {
        return res;
    }
    mProcessed += ( processedSize != nullptr ? *processedSize : size );
    if ( mCallback && !mCallback( mProcessed ) ) {
        return E_ABORT;
    }
    return res;
}

COM_DECLSPEC_NOTHROW
STDMETHODIMP ProgressOutStream::Seek( Int64 offset, UInt32 seekOrigin, UInt64* newPosition ) noexcept {
    return mStream->Seek( offset, seekOrigin, newPosition );
}

COM_DECLSPEC_NOTHROW
STDMETHODIMP ProgressOutStream::SetSize( UInt64 newSize ) noexcept {
    return mStream->SetSize( newSize );
}

} // namespace bit7z

