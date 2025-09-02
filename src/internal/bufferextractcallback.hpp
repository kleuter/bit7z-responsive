/*
 * bit7z - A C++ static library to interface with the 7-zip shared libraries.
 * Copyright (c) 2014-2022 Riccardo Ostani - All Rights Reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef BUFFEREXTRACTCALLBACK_HPP
#define BUFFEREXTRACTCALLBACK_HPP

#include <vector>
#include <map>

#include "internal/extractcallback.hpp"

namespace bit7z {

using std::vector;
using std::map;

class BufferExtractCallback final : public ExtractCallback {
    public:
        BufferExtractCallback( const BitInputArchive& inputArchive,
                               map< tstring, vector< byte_t > >& buffersMap );

        BufferExtractCallback( const BufferExtractCallback& ) = delete;

        BufferExtractCallback( BufferExtractCallback&& ) = delete;

        auto operator=( const BufferExtractCallback& ) -> BufferExtractCallback& = delete;

        auto operator=( BufferExtractCallback&& ) -> BufferExtractCallback& = delete;

        ~BufferExtractCallback() override = default;

    private:
        map< tstring, vector< byte_t > >& mBuffersMap;
        
        CMyComPtr< IOutStream > mOutMemStream;  // was ISequentialOutStream

        /* Changing ISequentialOutStream to IOutStream aligns the member with the new stream type created in getOutStream. 
           The output buffer is now wrapped in CBufferOutStream and optionally ProgressOutStream, 
           both of which expose the full IOutStream interface; assigning that IOutStream pointer to a CMyComPtr<ISequentialOutStream> 
           would require unsafe conversions and wouldn’t compile. Using IOutStream lets the progress-enabled stream be stored and later 
           released correctly while still returning an ISequentialOutStream** to satisfy the 7‑Zip callback contract 

           Same goes for FixedBufferExtractCallback 

           */

        void releaseStream() override;

        auto getOutStream( uint32_t index, ISequentialOutStream** outStream ) -> HRESULT override;
};

}  // namespace bit7z
#endif // BUFFEREXTRACTCALLBACK_HPP
