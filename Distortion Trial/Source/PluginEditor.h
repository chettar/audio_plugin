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

class DistortionTrialAudioProcessorEditor  : public AudioProcessorEditor,
                                             private Slider::Listener
{
public:
    DistortionTrialAudioProcessorEditor (DistortionTrialAudioProcessor&,AudioProcessorValueTreeState&);
    ~DistortionTrialAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider) override;
	//void initialise() override;
    
private:
	class ParameterSlider;
    AudioProcessorValueTreeState& valueTreeState;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DistortionTrialAudioProcessor& processor;
	Label timecodeDisplayLabel, slider1Label, slider2Label;
	ScopedPointer<SliderAttachment> slider1attachment, slider2attachment;
    Slider slider1, slider2;
	Rectangle<int> header, footer, sliderBox, visualizerBox, sliderLeftCol, sliderRightCol;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionTrialAudioProcessorEditor)
};




#endif  // PLUGINEDITOR_H_INCLUDED
