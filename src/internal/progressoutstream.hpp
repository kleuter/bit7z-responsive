/*
 * bit7z - A C++ static library to interface with the 7-zip shared libraries.
 * Copyright (c) 2014-2023 Riccardo Ostani - All Rights Reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef PROGRESSOUTSTREAM_HPP
#define PROGRESSOUTSTREAM_HPP

#include "bitabstractarchivehandler.hpp"
#include "internal/com.hpp"
#include "internal/guids.hpp"
#include "internal/macros.hpp"

#include <7zip/IStream.h>

namespace bit7z {

class ProgressOutStream final : public IOutStream, public CMyUnknownImp {
    public:
        ProgressOutStream( IOutStream* stream, ProgressCallback callback );

        ProgressOutStream( const ProgressOutStream& ) = delete;
        ProgressOutStream( ProgressOutStream&& ) = delete;
        auto operator=( const ProgressOutStream& ) -> ProgressOutStream& = delete;
        auto operator=( ProgressOutStream&& ) -> ProgressOutStream& = delete;
        MY_UNKNOWN_DESTRUCTOR( ~ProgressOutStream() ) = default;

        // IOutStream
        BIT7Z_STDMETHOD( Write, const void* data, UInt32 size, UInt32* processedSize );
        BIT7Z_STDMETHOD( Seek, Int64 offset, UInt32 seekOrigin, UInt64* newPosition );
        BIT7Z_STDMETHOD( SetSize, UInt64 newSize );

        // NOLINTNEXTLINE(modernize-use-noexcept, modernize-use-trailing-return-type, readability-identifier-length)
        MY_UNKNOWN_IMP1( IOutStream )

    private:
        CMyComPtr< IOutStream > mStream;
        ProgressCallback mCallback;
        uint64_t mProcessed;
};

} // namespace bit7z

#endif // PROGRESSOUTSTREAM_HPP

