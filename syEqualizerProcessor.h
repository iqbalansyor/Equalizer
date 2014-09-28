/*
  ==============================================================================
  
    syEqualizer
	
	syEqualizerProcessor.h
	
	created by syor - March 2014

	* A VST equalizer.
	* It's a 32-band parametric EQ, that can be used as a graphic EQ as well.

	* syEqualizerProcessor class contents:
     1. Constructor and destructor
     2. canDo and product info
     3. Input and output properties
     4. Settings for audio processing
     5. Parameters
     6. Programs
     7. Midi
     8. Main process

  ==============================================================================
*/

#ifndef SYEQUALIZERPROCESSOR_H_INCLUDED
#define SYEQUALIZERPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "syEqualizer\peaking.h"
//#include "syEqualizer\syEqualizer.h"


//==============================================================================
/**
*/
namespace SYEQUALIZER{
enum t
{
    //global settings
    kNumPrograms = 7,         //we've got seven programs
    
    kNumInputs = 2,              //stereo input
    kNumOutputs = 2,          //stereo output
    kNumMidiInputs = 0,       //All midi channels
    kNumMidiOutputs = 0,      //All midi channels
    
    kNumBands = 32,           //maximum of 32 bands; this should be changed in struct programs as well!
    
    //params
    kBand1 = 0,
    kBand2,
    kBand3,
    kBand4,
    kBand5,
    kBand6,
    kBand7,
    kBand8,
    kBand9,
    kBand10,
    kBand11,
    kBand12,
    kBand13,
    kBand14,
    kBand15,
    kBand16,
    kBand17,
    kBand18,
    kBand19,
    kBand20,
    kBand21,
    kBand22,
    kBand23,
    kBand24,
    kBand25,
    kBand26,
    kBand27,
    kBand28,
    kBand29,
    kBand30,
    kBand31,
    kBand32,
    //kFreq1,
    //kFreq2,
    //kFreq3,
    //kFreq4,
    //kFreq5,
    //kFreq6,
    //kFreq7,
    //kFreq8,
    //kFreq9,
    //kFreq10,
    //kFreq11,
    //kFreq12,
    //kFreq13,
    //kFreq14,
    //kFreq15,
    //kFreq16,
    //kFreq17,
    //kFreq18,
    //kFreq19,
    //kFreq20,
    //kFreq21,
    //kFreq22,
    //kFreq23,
    //kFreq24,
    //kFreq25,
    //kFreq26,
    //kFreq27,
    //kFreq28,
    //kFreq29,
    //kFreq30,
    //kFreq31,
    //kFreq32,
    kBW1,
    kBW2,
    kBW3,
    kBW4,
    kBW5,
    kBW6,
    kBW7,
    kBW8,
    kBW9,
    kBW10,
    kBW11,
    kBW12,
    kBW13,
    kBW14,
    kBW15,
    kBW16,
    kBW17,
    kBW18,
    kBW19,
    kBW20,
    kBW21,
    kBW22,
    kBW23,
    kBW24,
    kBW25,
    kBW26,
    kBW27,
    kBW28,
    kBW29,
    kBW30,
    kBW31,
    kBW32,
    kGain,
	kMinFreq,
	kMaxFreq,
    kNumParams
};
};

//class programs
//{
//    public:
//	programs()
//	{
//		for (int i = 0; i < 32; i++)
//			bandGain[i] = 0;
//		mainGain = 0;
//		freqMin = 20;
//		freqMax = 20000;
//	}
//	float bandGain[32];		//dB
//    float freqs[32];		//Hz
//    float BWs[32];			//
//    float BW;				//
//    int BandsActive;		//
//    bool BWlink;			//
//	float mainGain;			//dB
//    char name[24];			//
//	float freqMin;			//Hz
//	float freqMax;			//Hz
//};

class SyEqualizerAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    SyEqualizerAudioProcessor();
    ~SyEqualizerAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
	
	void resetBuffer();
	void resetCoeffs();

	bool getBWLinked();
	void calcMinMaxFreqs();
	void setGUIChanges(bool ch);

	void initProgs();

    //==============================================================================
    AudioProcessorEditor* createEditor();
    bool hasEditor() const;

    //==============================================================================
    const String getName() const;

    int getNumParameters();

    float getParameter (int index);
    void setParameter (int index, float newValue);

    const String getParameterName (int index);
    const String getParameterText (int index);

    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;

    bool acceptsMidi() const;
    bool producesMidi() const;
    bool silenceInProducesSilenceOut() const;
    double getTailLengthSeconds() const;

    //==============================================================================
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SyEqualizerAudioProcessor)
	
	peaking EQ;		//the actual equalizer
    
    float* f;				//EQ frequencies
    float* b;				//EQ bandwidths
    float* p;				//EQ peaks
    float bw;				//overall BW
	//float* bandGain;
	float mainGain;
    
    float* parameter;		//all the current parameters

    float sampleRate_;		//sample frequency

    //bool EditorLoaded;

	float dbRange;			//deciBell range

	float minFreq;
	float maxFreq;

	bool GUIChanges;
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
