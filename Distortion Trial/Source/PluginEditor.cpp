/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
// This is a handy slider subclass that controls an AudioProcessorParameter
// (may move this class into the library itself at some point in the future..)
class DistortionTrialAudioProcessorEditor::ParameterSlider : public Slider
{
public:
	ParameterSlider(AudioProcessorParameter& audioParam) : Slider(audioParam.getName(256)), param(audioParam) {
		setRange(0.0, 1.0, 0.0);
		updateSliderPos();
	}

	void valueChanged() override
	{
		if (isMouseButtonDown())
			param.setValueNotifyingHost((float)Slider::getValue());
		else
			param.setValue((float)Slider::getValue());
	}

	void startedDragging() override { param.beginChangeGesture(); }
	void stoppedDragging() override { param.endChangeGesture(); }

	double getValueFromText(const String& text) override { return param.getValueForText(text); }
	String getTextFromValue(double value) override { return param.getText((float)value, 1024); }

	void updateSliderPos()
	{
		const float newValue = param.getValue();

		if (newValue != (float)Slider::getValue() && !isMouseButtonDown())
			Slider::setValue(newValue);
	}

	AudioProcessorParameter& param;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParameterSlider)
};

//==============================================================================
DistortionTrialAudioProcessorEditor::DistortionTrialAudioProcessorEditor (DistortionTrialAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{

	// add some sliders..
	addAndMakeVisible(slider1 = new ParameterSlider(*p.slider1param));
	slider1->setSliderStyle(Slider::LinearHorizontal);

	addAndMakeVisible(slider2 = new ParameterSlider(*p.slider2param));
	slider2->setSliderStyle(Slider::LinearHorizontal);

	// add some labels for the sliders..
	slider1Label.attachToComponent(slider1, false);
	slider1Label.setFont(Font(11.0f));

	slider2Label.attachToComponent(slider2, false);
	slider2Label.setFont(Font(11.0f));

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setSize(1000, 600);
}

DistortionTrialAudioProcessorEditor::~DistortionTrialAudioProcessorEditor()
{
}

//==============================================================================
void DistortionTrialAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void DistortionTrialAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	// This lays out our child components...

	Rectangle<int> r(getLocalBounds().reduced(8));

	r.removeFromTop(30);
	Rectangle<int> sliderArea(r.removeFromTop(50));
	slider1->setBounds(sliderArea.removeFromLeft(jmin(180, sliderArea.getWidth() / 2)));
	slider2->setBounds(sliderArea.removeFromLeft(jmin(180, sliderArea.getWidth())));

}
