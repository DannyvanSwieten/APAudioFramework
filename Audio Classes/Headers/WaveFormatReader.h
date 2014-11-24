//
//  WaveFormatReader.h
//  GUI
//
//  Created by Danny van Swieten on 10/28/14.
//
//

#ifndef __GUI__WaveFormatReader__
#define __GUI__WaveFormatReader__

#include <string>
#include <cstdlib>
#include <iostream>
#include "Buffer.h"
#include "InputStream.h"
#include "AudioFile.h"

namespace APAudio
{
    namespace Audio
    {

        class WaveFormatReader
        {
        public:
            
            WaveFormatReader();
            WaveFormatReader(std::string filePath);
            
            AudioFile read(std::string path, bool useLeft, bool useRight);
        private:
            
            Buffer<float> _data;
            InputStream _inputStream;
        };
    }
}

#endif /* defined(__GUI__WaveFormatReader__) */
