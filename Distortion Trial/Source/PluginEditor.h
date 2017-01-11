/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

class DistortionTrialAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    DistortionTrialAudioProcessorEditor (DistortionTrialAudioProcessor&,AudioProcessorValueTreeState&);
    ~DistortionTrialAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	//void initialise() override;
    
private:
	//class ParameterSlider;
    AudioProcessorValueTreeState& valueTreeState;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DistortionTrialAudioProcessor& processor;
	Label timecodeDisplayLabel, inputGainLabel, outputGainLabel, dryWetLabel, frequencyLabel;
	ScopedPointer<SliderAttachment> inputGainAttachment, outputGainAttachment, dryWetAttachment,
                                    frequencyAttachment;
    ScopedPointer<ButtonAttachment> autoFrequencyAttachment;
    Slider inputGainSlider, outputGainSlider, dryWetSlider, frequencySlider;
    ToggleButton autoFrequencyButton;
	Rectangle<int> header, footer, sliderBox, visualizerBox, sliderLeftCol, sliderRightCol;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionTrialAudioProcessorEditor)
};




#endif  // PLUGINEDITOR_H_INCLUDED
