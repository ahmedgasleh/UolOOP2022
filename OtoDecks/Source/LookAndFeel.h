/*
  ==============================================================================

    LookAndFeel.h
    Created: 19 Mar 2022 2:20:57pm
    Author:  inadh

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class LookAndFeelEx : public juce::LookAndFeel_V4
{
public:
    void drawRotarySlider(Graphics&, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider&);

};

class CustomRotaryDail : public Slider
{
public:
    CustomRotaryDail()
    {
        //common custom changes
        auto rotaryParameters = getRotaryParameters();

        rotaryParameters.startAngleRadians = juce::MathConstants<float>::pi * 1.5f;
        rotaryParameters.endAngleRadians = juce::MathConstants<float>::pi * 3.0f;

        setRotaryParameters(rotaryParameters);

        setColour(juce::Slider::thumbColourId, juce::Colours::blueviolet);

    }
};