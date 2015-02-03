//
//  AudioProcessor.h
//  GUI
//
//  Created by Danny van Swieten on 10/28/14.
//
//

#ifndef __GUI__AudioProcessor__
#define __GUI__AudioProcessor__

class AudioProcessor
{
public:
    AudioProcessor();
    virtual ~AudioProcessor() = 0;
    
    virtual void render(float** input, int numInputs, float** output, int numOutputs, unsigned long numSamples) = 0;
    virtual void prepareToPlay(int sampleRate, int bufferSize) = 0;
    
    void setSampleRate(int sr);
    void setBufferSize(int bs);
    
    int getSampleRate();
    int getBufferSize();
    
    void setNumInputChannels(int inputs){numInputs = inputs;};
    void setNumOutputChannels(int outputs){numOutputs = outputs;};
    
    int getNumInputChannels(){return numInputs;};
    int getNumOutputChannels(){return numOutputs;};
    
private:
  
    int sampleRate = 0;
    int bufferSize = 0;
    
    int numInputs = 0;
    int numOutputs = 0;
};

#endif /* defined(__GUI__AudioProcessor__) */
