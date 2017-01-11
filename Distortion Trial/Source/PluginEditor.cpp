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

class SliderLook : public LookAndFeel_V3
{
public:
	SliderLook()
	{
		//setColour(Slider::textBoxBackgroundColourId, Colours::red);
	}
	
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
	{
		const float radius = jmin(width / 2, height / 2) - 2.0f;
		const float centreX = x + width * 0.5f;
		const float centreY = y + height * 0.5f;
		const float rx = centreX - radius;
		const float ry = centreY - radius;
		const float rw = radius * 2.0f;
		const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
		const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

		if (radius > 12.0f)
		{
			const float thickness = 0.7f;
			const float insideThickness = 0.96f;

			if (slider.isEnabled())
				g.setColour(slider.findColour(Slider::rotarySliderFillColourId).withAlpha(isMouseOver ? 1.0f : 0.9f));
			else
				g.setColour(Colour(0x80808080));


			{
				Path filledArc;
				filledArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, angle, thickness);
				g.fillPath(filledArc);
			}
			/*
			{
				const float innerRadius = radius * 0.2f;
				Path p;
				p.addTriangle(-innerRadius, 0.0f,
					0.0f, -radius * thickness * 1.1f,
					innerRadius, 0.0f);

				p.addEllipse(-innerRadius, -innerRadius, innerRadius * 2.0f, innerRadius * 2.0f);

				g.fillPath(p, AffineTransform::rotation(angle).translated(centreX, centreY));
			}*/

			if (slider.isEnabled())
				g.setColour(slider.findColour(Slider::rotarySliderOutlineColourId));
			else
				g.setColour(Colour(0x80808080));
			/*
			Path outlineArc;
			outlineArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, thickness);
			outlineArc.closeSubPath();
			g.strokePath(outlineArc, PathStrokeType(slider.isEnabled() ? (isMouseOver ? 2.0f : 1.2f) : 0.3f));
			*/

			g.setColour(Colours::grey);
			Path insideArc;
			insideArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, insideThickness);
			g.fillPath(insideArc);

			
			//insideArc.closeSubPath();

			


		}
		else
		{
			if (slider.isEnabled())
				g.setColour(slider.findColour(Slider::rotarySliderFillColourId).withAlpha(isMouseOver ? 1.0f : 0.7f));
			else
				g.setColour(Colour(0x80808080));

			Path p;
			p.addEllipse(-0.4f * rw, -0.4f * rw, rw * 0.8f, rw * 0.8f);
			PathStrokeType(rw * 0.1f).createStrokedPath(p, p);

			p.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, -radius), rw * 0.2f);

			g.fillPath(p, AffineTransform::rotation(angle).translated(centreX, centreY));
		}
	}
	/*
	Slider::SliderLayout getSliderLayout(Slider&amp) override
	{
		Slider::SliderLayout layout;

		layout.textBoxBounds = Rectangle<int>(15, 35, 70, 20);
		layout.sliderBounds = Rectangle<int> (0, 0, 100, 100);

		return layout;
	}*/
};



//==============================================================================
DistortionTrialAudioProcessorEditor::DistortionTrialAudioProcessorEditor (DistortionTrialAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{

	// add some sliders..
	SliderLook* sliderLook = new SliderLook();

	addAndMakeVisible(slider1 = new ParameterSlider(*p.slider1param));
	slider1->setSliderStyle(Slider::Rotary);
	slider1->setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	slider1->setLookAndFeel(sliderLook);

	addAndMakeVisible(slider2 = new ParameterSlider(*p.slider2param));
	slider2->setSliderStyle(Slider::Rotary);
	slider2->setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	slider2->setLookAndFeel(sliderLook);

	// add some labels for the sliders..
	//slider1Label.attachToComponent(slider1, false);
	slider1Label.setFont(Font(11.0f));

	//slider2Label.attachToComponent(slider2, false);
	slider2Label.setFont(Font(11.0f));

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setSize(1000, 600);
    
    // Add listener for sliders
    slider1->addListener(this);

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

	slider1->setBounds(sliderLeftCol.removeFromTop(sliderLeftCol.getHeight() / 2).reduced(10));
	slider2->setBounds(sliderRightCol.removeFromTop(sliderRightCol.getHeight() / 2).reduced(10));

	/* commented so I don't blow my speakers
	slider1->setRange(0.f, 127.f); 
	slider2->setRange(0.f, 127.f);
	*/

	/* more future code for resizable window
	resizer->setBounds(getWidth() - 16, getHeight() - 16, 16, 16);
	getProcessor()->lastUIWidth = getWidth();
	getProcessor()->lastUIHeight = getHeight();
	*/
}

void DistortionTrialAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    processor.gain_ = slider1->getValue();
    std::cout << processor.gain_ << std::endl;
}


