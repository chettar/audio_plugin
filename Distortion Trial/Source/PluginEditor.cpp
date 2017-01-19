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

	//Combo boxes
	addAndMakeVisible(distortionType);
	distortionType.addItem("test1", 1);
	distortionType.addItem("test2", 2);

	addAndMakeVisible(numOfHarmonics);
	numOfHarmonics.addItem("One", 1);
	numOfHarmonics.addItem("Two", 2);

	// add some sliders..
	SliderLook* sliderLook = new SliderLook();

	inputGainSlider.setSliderStyle(Slider::Rotary);
	//inputGainSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	inputGainSlider.setLookAndFeel(sliderLook);

	outputGainSlider.setSliderStyle(Slider::Rotary);
	//slider2.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	outputGainSlider.setLookAndFeel(sliderLook);
    
    dryWetSlider.setSliderStyle(Slider::Rotary);
    dryWetSlider.setLookAndFeel(sliderLook);
    
    frequencySlider.setSliderStyle(Slider::Rotary);
    frequencySlider.setLookAndFeel(sliderLook);

	// add some labels for the sliders..
	inputGainLabel.setFont(Font(11.0f));
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
	Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
    
    int x = r.getWidth() / 2.4;
    int y = r.getHeight() / 2.4;

	setSize(x, y);
    
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

void drawTextToFillRectangle(Graphics &g, const Font& font, const String& text, Rectangle<int> container) {
	float currentHeight = font.getHeight();
	float currentWidth = font.getStringWidthFloat(text);
	float scale = jmin(container.getHeight() / currentHeight, container.getWidth() / currentWidth);

	Font newFont(font.withHeight(scale * currentHeight));
	g.setFont(newFont);
	g.drawText(text, container, Justification::left, false);
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
	drawTextToFillRectangle(g, g.getCurrentFont(), "Tonal Conflict", header);

	g.setFont (15.0f);
	drawTextToFillRectangle(g, g.getCurrentFont(), "Input Gain", inputGainLabelBox);
	drawTextToFillRectangle(g, g.getCurrentFont(), "Output Gain", outputGainLabelBox);
	drawTextToFillRectangle(g, g.getCurrentFont(), "Dry / Wet", drywetLabelBox);
	drawTextToFillRectangle(g, g.getCurrentFont(), "Frequency", frequencyLabelBox);

	g.setColour(Colours::yellow);
	g.fillRect(footer);

	g.setColour(Colours::lightpink);
	//g.fillRect(inputGainLabelBox);


	g.setColour(Colours::blue);
	//g.fillRect(drywetLabelBox);

	g.setColour(Colours::grey);
	g.fillRect(visualizerBox);

	
}



void DistortionTrialAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..

	// This lays out our child components...



	Rectangle<int> totalArea(getLocalBounds());

	const int headerFooterHeight = totalArea.getHeight() / 18;
	header = Rectangle<int>(totalArea.removeFromTop(headerFooterHeight));
	footer = Rectangle<int>(totalArea.removeFromBottom(headerFooterHeight));

	const int margin = 5;
	const int boxMin = 100;
	const int labelSize = totalArea.getHeight() / 20;

	//Slider box and visualizer width is always half of total area
	sliderBox = Rectangle<int>(totalArea.removeFromLeft(totalArea.getWidth() / 2).reduced(margin));
	visualizerBox = Rectangle<int>(totalArea.removeFromRight(totalArea.getWidth()).reduced(margin));

	distortionTypeBox = Rectangle<int>(sliderBox.removeFromTop(totalArea.getHeight() / 9).reduced(15));
	harmonicsBox = Rectangle<int>(distortionTypeBox.removeFromRight(distortionTypeBox.getWidth() / 2));

	/*Left Column*/
	sliderLeftCol = Rectangle<int>(sliderBox.removeFromLeft(sliderBox.getWidth() / 2));
	inputGainBox = sliderLeftCol.removeFromTop(sliderLeftCol.getHeight() / 2).reduced(10);
	inputGainLabelBox = inputGainBox.removeFromTop(labelSize);
	inputGainSlider.setBounds(inputGainBox);

	drywetBox = Rectangle<int>(sliderLeftCol.reduced(10)); //left column has already been reduced by 2
	drywetLabelBox = drywetBox.removeFromTop(labelSize);
	dryWetSlider.setBounds(drywetBox);

	/*Right Column*/
	sliderRightCol = sliderBox; //sliderBox has been cut in half already
	outputGainBox = sliderRightCol.removeFromTop(sliderRightCol.getHeight() / 2).reduced(10);
	outputGainLabelBox = outputGainBox.removeFromTop(labelSize);
	outputGainSlider.setBounds(outputGainBox);

	frequencyBox = Rectangle<int>(sliderRightCol.reduced(10));
	frequencyLabelBox = frequencyBox.removeFromTop(labelSize);
    frequencySlider.setBounds(frequencyBox);

    autoFrequencyButton.setBounds(footer);
	distortionType.setBounds(distortionTypeBox);
	numOfHarmonics.setBounds(harmonicsBox);
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
