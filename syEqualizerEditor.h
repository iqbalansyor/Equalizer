/*
  ==============================================================================
  
    syEqualizer
	
	syEqualizerEditor.h
	
	created by syor - March 2014

	 * Contents:
     1. Constructor and destructor
     2. Open and close functions
     3. Functions to make some bands blue or gray
     4. Parameter-related functions

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "syEqualizerProcessor.h"


//==============================================================================
/**
*/
class SyEqualizerAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    SyEqualizerAudioProcessorEditor (SyEqualizerAudioProcessor* ownerFilter);
    ~SyEqualizerAudioProcessorEditor();

    //==============================================================================
    // This is just a standard Juce paint method...
    void paint (Graphics& g);
};


#endif  // PLUGINEDITOR_H_INCLUDED
