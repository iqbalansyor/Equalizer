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

#include "syEqualizerProcessor.h"
#include "syEqualizerEditor.h"

using namespace SYEQUALIZER;

//==============================================================================
SyEqualizerAudioProcessor::SyEqualizerAudioProcessor()
{
	sampleRate_ = 44100.0f;                   //default
    
    f = new float[kNumBands];
    b = new float[kNumBands];
    p = new float[kNumBands];
    
    parameter = new float[kNumParams];

    for(int i = 0; i < kNumParams; ++i)
	{
		parameter[i] = 0;
	}
	
	initProgs();
	
	//SyEqualizerAudioProcessorEditor* syEqualizerEditor = new SyEqualizerAudioProcessorEditor (this);
    //setEditor (syEqualizerEditor);
    //EditorLoaded = true;

	dbRange = 12.0f;

	GUIChanges = false;
}

SyEqualizerAudioProcessor::~SyEqualizerAudioProcessor()
{
	resetBuffer();
	resetCoeffs();

	if(parameter)
		delete[] parameter;
	parameter = 0;
}

void SyEqualizerAudioProcessor::resetBuffer ()
 {
 if (f) delete[] f;
    if (b) delete[] b;
    if (p) delete[] p;
    if (parameter) delete[] parameter;
}

void SyEqualizerAudioProcessor::resetCoeffs()
{
}

void SyEqualizerAudioProcessor::setGUIChanges (bool ch)
{
	GUIChanges = ch;
}

void SyEqualizerAudioProcessor::initProgs()
{
	for (int i = 0; i < 31; i++)
	{
        float fr[] = {20,25,31.5,40,50,63,80,100,125,160,200,250,315,400,500,630,800,1000,1250,1600,
               2000,2500,3150,4000,5000,6300,8000,10000,12500,16000,20000};
		EQ.setFreq(fr[i]);
	}
}
//==============================================================================
const String SyEqualizerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int SyEqualizerAudioProcessor::getNumParameters()
{
    return kNumParams;
}

float SyEqualizerAudioProcessor::getParameter (int index)
{
    if (index < 0 || index >= kNumParams) return 0.0f;
    
    return parameter[index];
}

void SyEqualizerAudioProcessor::setParameter (int index, float newValue)
{
	if (index < 0 || index >= kNumParams) return;
 
	parameter[index] = newValue;
 
	// Check if one of the bands has been changed (peak)
    int i = index - kBand1;
	
	if (i < kNumBands)
    {
        float dB = (newValue - 0.5f) * 2 * dbRange;   //spread them on a range from -12 to +12 (dB)
        p[i] = pow (10.0f, dB / 10.0f);            //inverse dB calculation; calculate actual peak newValue: 10^(peak/10)
        EQ. setPeak(p[i]);
        return;
    }

    // Check if one of the bandwidths has been changed
    i = index - kBW1;
    if (i < kNumBands)
    {
        if (newValue < 0.00001f) newValue = 0.00001f;
        b[i] = newValue;                 //minimum: 0.00001, maximum: 1
		EQ.setBW(b[i]);
        return;
    }
    
    if (index == kGain)
    {
        mainGain = newValue;
		EQ.setGain(mainGain);
        return;
    }
	if (index == kMinFreq)
	{
		float fr = newValue / 2.0f;
		minFreq = fr * sampleRate_;
		return;
	}
	if (index == kMaxFreq)
	{
		float fr = newValue / 2.0f;
		maxFreq = fr * sampleRate_;
		return;
	}
}

const String SyEqualizerAudioProcessor::getParameterName (int index)
{
   {
	char label[50];
    // Check if one of the bands has been asked (peak)
    int i = index - kBand1;
    if (i < kNumBands)
    {
		sprintf_s(label, 8,  "Band %d", i + 1);
        return label;
    }
    
    // Check if one of the bandwidths has been asked
    i = index - kBW1;
    if (i < kNumBands)
    {
        sprintf_s(label, 8, "BW %d", i + 1);
        return label;
    }
 
    if (index == kGain)
    {
        sprintf_s(label, 8,  "Gain");
        return label;
    }
	if (index == kMinFreq)
	{
		sprintf_s(label, 8,  "fMin");
        return label;
	}
	if (index == kMaxFreq)
	{
		sprintf_s(label, 8,  "fMax");
        return label;
	}
   }
}

const String SyEqualizerAudioProcessor::getParameterText (int index)
{
    	if(index>=0 && index<kNumParams)
		return String(parameter[index]);//return parameter value as string
	else return String::empty;
}

const String SyEqualizerAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String SyEqualizerAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool SyEqualizerAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool SyEqualizerAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool SyEqualizerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SyEqualizerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SyEqualizerAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double SyEqualizerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SyEqualizerAudioProcessor::getNumPrograms()
{
    return 0;
}

int SyEqualizerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SyEqualizerAudioProcessor::setCurrentProgram (int index)
{
}

const String SyEqualizerAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void SyEqualizerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SyEqualizerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    sampleRate_ = (float)sampleRate;
}

void SyEqualizerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void SyEqualizerAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    	if(getNumInputChannels()<2)
	{
		float* in = buffer.getSampleData(0);
		int i = buffer.getNumSamples();
		EQ.processL(*in);
	}
	else
	{
		float* inL = buffer.getSampleData(0);
		float* inR = buffer.getSampleData(1);
		
		int i = buffer.getNumSamples();
		EQ.processL(*inL);
		EQ.processR(*inR);
	}
}

//==============================================================================
bool SyEqualizerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SyEqualizerAudioProcessor::createEditor()
{
    return new SyEqualizerAudioProcessorEditor (this);
}

//==============================================================================
void SyEqualizerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SyEqualizerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SyEqualizerAudioProcessor();
}
