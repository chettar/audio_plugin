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
			if (slider.isEnabled())
				g.setColour(slider.findColour(Slider::rotarySliderFillColourId).withAlpha(isMouseOver ? 1.0f : 0.7f));
			else
				g.setColour(Colour(0x80808080));

			const float thickness = 0.7f;

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

			Path outlineArc;
			outlineArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, thickness);
			outlineArc.closeSubPath();

			g.strokePath(outlineArc, PathStrokeType(slider.isEnabled() ? (isMouseOver ? 2.0f : 1.2f) : 0.3f));
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
	
	Slider::SliderLayout getSliderLayout(Slider&amp) override
	{
		Slider::SliderLayout layout;

		layout.textBoxBounds = Rectangle<int>(15, 35, 70, 20);
		layout.sliderBounds = Rectangle<int> (0, 0, 100, 100);

		return layout;
	}

	
	/*

	void drawLinearSliderBackground(Graphics &g, int x, int y, int width, int height, float sliderPos,
		float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &slider) override
	{
		const float sliderRadius = (float) (getSliderThumbRadius (slider) - 2);

		const Colour trackColour (slider.findColour (Slider::trackColourId));
		const Colour gradCol1 (trackColour.overlaidWith (Colour (slider.isEnabled() ? 0x13000000 : 0x09000000)));
		const Colour gradCol2 (trackColour.overlaidWith (Colour (0x06000000)));
		Path indent;

		if (slider.isHorizontal())
		{
			const float iy = y + height * 0.5f - sliderRadius * 0.5f;

			g.setGradientFill (ColourGradient (gradCol1, 0.0f, iy,
											   gradCol2, 0.0f, iy + sliderRadius, false));

			indent.addRoundedRectangle (x - sliderRadius * 0.5f, iy, width + sliderRadius, sliderRadius, 5.0f);
		}

		g.fillPath (indent);

		g.setColour (trackColour.contrasting (0.5f));
		g.strokePath (indent, PathStrokeType (0.5f));
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
	slider1->setLookAndFeel(sliderLook);

	addAndMakeVisible(slider2 = new ParameterSlider(*p.slider2param));
	slider2->setSliderStyle(Slider::Rotary);
	slider2->setLookAndFeel(sliderLook);

	// add some labels for the sliders..
	//slider1Label.attachToComponent(slider1, false);
	slider1Label.setFont(Font(11.0f));

	//slider2Label.attachToComponent(slider2, false);
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
    g.drawFittedText ("Distortion Trial", getLocalBounds(), Justification::centred, 1);

	g.setColour(Colours::deepskyblue);
	g.fillRect(10, 10, 980, 275);
}

void DistortionTrialAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	// This lays out our child components...

	Rectangle<int> r(getLocalBounds().reduced(8));

	r.removeFromTop(30);
	Rectangle<int> sliderArea(r.removeFromTop(50));
	slider1->setBounds(150, 350, 175, 175);
	slider2->setBounds(150, 475, 175, 175);
	slider1Label.setBounds(190, 160, 10, 30);
	slider2Label.setBounds(150, 260, 10, 30);
	//slider1->setBounds(sliderArea.removeFromLeft(jmin(180, sliderArea.getWidth() / 2)));
	//slider2->setBounds(sliderArea.removeFromLeft(jmin(180, sliderArea.getWidth())));

}


