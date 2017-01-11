/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "CustomSliderLookAndFeel.cpp"

//==============================================================================
DistortionTrialAudioProcessorEditor::DistortionTrialAudioProcessorEditor (DistortionTrialAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), valueTreeState(vts), processor (p)
{

	// add some sliders..
	SliderLook* sliderLook = new SliderLook();

	//addAndMakeVisible(inputGainSlider = new ParameterSlider(*p.inputGainSliderparam));
	inputGainSlider.setSliderStyle(Slider::Rotary);
	//inputGainSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	inputGainSlider.setLookAndFeel(sliderLook);

	//addAndMakeVisible(slider2 = new ParameterSlider(*p.slider2param));
	outputGainSlider.setSliderStyle(Slider::Rotary);
	//slider2.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	outputGainSlider.setLookAndFeel(sliderLook);
    
    dryWetSlider.setSliderStyle(Slider::Rotary);
    dryWetSlider.setLookAndFeel(sliderLook);
    
    frequencySlider.setSliderStyle(Slider::Rotary);
    frequencySlider.setLookAndFeel(sliderLook);

	// add some labels for the sliders..
	//slider1Label.attachToComponent(slider1, false);
	inputGainLabel.setFont(Font(11.0f));

	//slider2Label.attachToComponent(slider2, false);
	outputGainLabel.setFont(Font(11.0f));
    
    dryWetLabel.setFont(Font(11.0f));
    frequencyLabel.setFont(Font(11.0f));
    
    addAndMakeVisible(inputGainLabel);
    addAndMakeVisible(outputGainLabel);
    addAndMakeVisible(inputGainSlider);
    addAndMakeVisible(outputGainSlider);
    addAndMakeVisible(dryWetLabel);
    addAndMakeVisible(dryWetSlider);
    addAndMakeVisible(frequencyLabel);
    addAndMakeVisible(frequencySlider);
    addAndMakeVisible(autoFrequencyButton);

    inputGainAttachment = new SliderAttachment(valueTreeState, "inputGain", inputGainSlider);
    outputGainAttachment = new SliderAttachment(valueTreeState, "outputGain", outputGainSlider);
    dryWetAttachment = new SliderAttachment(valueTreeState, "dryWet", dryWetSlider);
    frequencyAttachment = new SliderAttachment(valueTreeState, "frequency", frequencySlider);
    autoFrequencyAttachment = new ButtonAttachment(valueTreeState, "autoFrequency", autoFrequencyButton);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setSize(1000, 600);
    
    // Add listener for sliders
    //slider1->addListener(this);

	//Code to resize window - https://forum.juce.com/t/best-way-to-implement-resizable-plugin/12644/3
	/*May implement in future
	addAndMakeVisible(resizer = new ResizableCornerComponent(this, &resizeLimits));
	resizeLimits.setSizeLimits(150, 150, 800, 300);
	setSize(ownerFilter->lastUIWidth, ownerFilter->lastUIHeight);
	*/
}

DistortionTrialAudioProcessorEditor::~DistortionTrialAudioProcessorEditor()
{
}

//==============================================================================
void DistortionTrialAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::darkslategrey);

    //g.setColour (Colours::black);
    //g.setFont (15.0f);

	g.setColour(Colours::deepskyblue);
	//g.fillRect(header);
	g.setFont(30.f);
	g.drawFittedText("Tonal Conflict", header, Justification::left, 1);

	g.setColour(Colours::yellow);
	g.fillRect(footer);

	g.setColour(Colours::lightpink);
	g.fillRect(sliderLeftCol);

	g.setColour(Colours::blue);
	g.fillRect(sliderRightCol);

	g.setColour(Colours::grey);
	g.fillRect(visualizerBox);

	
}

void DistortionTrialAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..

	// This lays out our child components...



	Rectangle<int> totalArea(getLocalBounds());

	const int headerFooterHeight = 36;
	header = Rectangle<int>(totalArea.removeFromTop(headerFooterHeight));
	footer = Rectangle<int>(totalArea.removeFromBottom(headerFooterHeight));

	const int margin = 5;
	const int boxMin = 100;
	//Slider box and visualizer width is always half of total area
	sliderBox = Rectangle<int>(totalArea.removeFromLeft(totalArea.getWidth() / 2).reduced(margin));
	visualizerBox = Rectangle<int>(totalArea.removeFromRight(totalArea.getWidth()).reduced(margin));
	//sliderBox = Rectangle<int>(totalArea.removeFromLeft(jmax(boxMin, (totalArea.getWidth() / 2))).reduced(margin));
	//visualizerBox = Rectangle<int>(totalArea.removeFromRight(jmax(boxMin, (totalArea.getWidth() / 2))).reduced(margin));

	sliderLeftCol = Rectangle<int>(sliderBox.removeFromLeft(sliderBox.getWidth() / 2));
	sliderRightCol = Rectangle<int>(sliderBox.removeFromRight(sliderBox.getWidth()));

	inputGainSlider.setBounds(sliderLeftCol.removeFromTop(sliderLeftCol.getHeight() / 2).reduced(10));
	outputGainSlider.setBounds(sliderRightCol.removeFromTop(sliderRightCol.getHeight() / 2).reduced(10));
    dryWetSlider.setBounds(sliderLeftCol.removeFromBottom(sliderLeftCol.getHeight()).reduced(10));
    frequencySlider.setBounds(sliderRightCol.removeFromBottom(sliderRightCol.getHeight()).reduced(10));
    autoFrequencyButton.setBounds(footer);
	/* commented so I don't blow my speakers
	inputGainSlider->setRange(0.f, 127.f); 
	slider2->setRange(0.f, 127.f);
	*/

	/* more future code for resizable window
	resizer->setBounds(getWidth() - 16, getHeight() - 16, 16, 16);
	getProcessor()->lastUIWidth = getWidth();
	getProcessor()->lastUIHeight = getHeight();
	*/
}
