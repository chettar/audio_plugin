/*
  ==============================================================================

    CustomSliderLookAndFeel.cpp
    Created: 10 Jan 2017 9:41:28pm
    Author:  Max Marchionda

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

class SliderLook : public LookAndFeel_V3
{
public:
    SliderLook()
    {
        //setColour(Slider::textBoxBackgroundColourId, Colours::red);
    }

	void drawControlPoint(Graphics &g, float x, float y, float radius, float lineThickness)
	{
		g.drawEllipse(x - radius, y - radius, 2.0f * radius, 2.0f * radius, lineThickness);
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
                    
            //Inside Arc        
            {
                Path filledArc;
                filledArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, angle, thickness);
                g.fillPath(filledArc);
            }
            //Inside circle
			/*{
				Path innerCircle;
				innerCircle.addEllipse(rx + (radius * thickness), ry + (radius * thickness), rw*thickness, rw*thickness);
				g.setColour(Colours::darkgrey);
				g.fillPath(innerCircle);
			}*/

			//Inside line
			{
				Path p;
				p.addRectangle(-3.f / 2, -radius, 3.f, radius);
				g.setColour(Colours::white);
				g.fillPath(p, AffineTransform::rotation(angle).translated(centreX, centreY));
			}
            
            if (slider.isEnabled())
                g.setColour(slider.findColour(Slider::rotarySliderOutlineColourId));
                else
                    g.setColour(Colour(0x80808080));
                    
                g.setColour(Colours::grey);
                Path insideArc;
				insideArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, insideThickness);
				g.fillPath(insideArc);

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

