/*
  ==============================================================================

    LookAndFeel.h
    Created: 19 Mar 2022 2:20:57pm
    Author:  inadh

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

#define USE_LIVE_CONSTANT false

#if USE_LIVE_CONSTANT
#define colorHelper(c) JUCE_LIVE_CONSTANT(c);
#else
#define colorHelper(c) c;
#endif

namespace ColorScheme
{
    inline juce::Colour getGainReductionColor() { return colorHelper(juce::Colour(0xff38c19b)); }
    inline juce::Colour getInputSignalColor() { return colorHelper(juce::Colour(0xff00e7ff)); }
    inline juce::Colour getOutputSignalColor() { return colorHelper(juce::Colour(0xff0cff00)); }
    inline juce::Colour getSliderFillColor() { return colorHelper(juce::Colour(0xff96bbc2)); }
    inline juce::Colour getOrangeBorderColor() { return colorHelper(juce::Colour(255u, 154u, 1u)); }
    inline juce::Colour getSliderRangeTextColor() { return colorHelper(juce::Colour(0u, 172u, 1u)); }
    inline juce::Colour getSliderBorderColor() { return colorHelper(juce::Colour(0xff0087a2)); }
    inline juce::Colour getThresholdColor() { return colorHelper(juce::Colour(0xffe0760c)); }
    inline juce::Colour getModuleBorderColor() { return colorHelper(juce::Colour(0xff475d9d)); }
    inline juce::Colour getTitleColor() { return colorHelper(juce::Colour(0xff2c92ca)); }
    inline juce::Colour getAnalyzerGridColor() { return colorHelper(juce::Colour(0xff262626)); }
    inline juce::Colour getTickColor() { return colorHelper(juce::Colour(0xff313131)); }
    inline juce::Colour getMeterLineColor() { return colorHelper(juce::Colour(0xff3c3c3c)); }
    inline juce::Colour getScaleTextColor() { return juce::Colours::lightgrey; }

}

struct PowerButton : juce::ToggleButton {};

class LookAndFeelEx : public juce::LookAndFeel_V4
{
public:
    void drawRotarySlider(Graphics&, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider&);
    void drawToggleButton(juce::Graphics& g,
        juce::ToggleButton& toggleButton,
        bool shouldDrawButtonAsHighlighted,
        bool shouldDrawButtonAsDown) override;

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