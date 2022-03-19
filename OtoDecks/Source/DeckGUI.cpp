/*
  ==============================================================================

    DeckGUI.cpp
    Created: 13 Mar 2020 6:44:48pm
    Author:  matthew

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"


//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
                PlayListComponent* _playList,
                AudioFormatManager & 	formatManagerToUse,
                AudioThumbnailCache & 	cacheToUse
           ) : player(_player), 
               playlist(_playList),
               waveformDisplay(formatManagerToUse, cacheToUse)
{


   /* auto speedSliderRotaryParameters = volSlider.getRotaryParameters();

    speedSliderRotaryParameters.startAngleRadians = juce::MathConstants<float>::pi * 1.5f;
    speedSliderRotaryParameters.endAngleRadians = juce::MathConstants<float>::pi * 3.0f;

    volSlider.setRotaryParameters(speedSliderRotaryParameters);


    auto posSliderRotaryParameters = posSlider.getRotaryParameters();

    posSliderRotaryParameters.startAngleRadians = juce::MathConstants<float>::pi * 1.5f;
    posSliderRotaryParameters.endAngleRadians = juce::MathConstants<float>::pi * 3.0f;

    posSlider.setRotaryParameters(posSliderRotaryParameters);


    auto volSliderRotaryParameters = posSlider.getRotaryParameters();

    volSliderRotaryParameters.startAngleRadians = juce::MathConstants<float>::pi * 1.5f;
    volSliderRotaryParameters.endAngleRadians = juce::MathConstants<float>::pi * 3.0f;

    posSlider.setRotaryParameters(volSliderRotaryParameters);*/


    volSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::orange);
    volSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    volSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 50);

    speedSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::red);
    speedSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    speedSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);

    posSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::greenyellow);
    posSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    posSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 50);

    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
       
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);

    addAndMakeVisible(waveformDisplay);


    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);

    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);


    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 100.0);
    posSlider.setRange(0.0, 1.0);

    startTimer(500);


}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
   
}

void DeckGUI::resized()
{
    double rowH = getHeight() / 8; 
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);  
    volSlider.setBounds(0, rowH * 2, getWidth()/3, rowH * 3);
    speedSlider.setBounds(getWidth() / 3, rowH * 2, getWidth()/3, rowH * 3);
    posSlider.setBounds(getWidth() - (getWidth() / 3), rowH * 2, getWidth()/3, rowH * 3);
    waveformDisplay.setBounds(0, rowH * 5, getWidth(), rowH * 2);
    loadButton.setBounds(0, rowH * 7, getWidth(), rowH);

}

void DeckGUI::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        player->start();
    }
     if (button == &stopButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        player->stop();

    }
    if (button == &loadButton)
    {
       /* FileChooser chooser{"Select a file..."};
        if (chooser.browseForFileToOpen())
        {
            player->loadURL(URL{chooser.getResult()});
            waveformDisplay.loadURL(URL{chooser.getResult()});
            
        }*/

        for each (auto item in playlist->playList->getChildIterator())
        {
           
            if (player->deckName == "deck01")
            {
                juce::File file(item->getAttributeValue(2));
                playQueue1.push_back(file);
            }

            if (player->deckName == "deck02")
            {
                juce::File file(item->getAttributeValue(2));
                playQueue2.push_back(file);
            }
           
           

           
        }

        if (playQueue1.size() > 0)
        {
            player->loadURL(URL{ playQueue1[0] });
            waveformDisplay.loadURL(URL{ playQueue1[0] });
        }

        if (playQueue2.size() > 0)
        {
            player->loadURL(URL{ playQueue2[0] });
            waveformDisplay.loadURL(URL{ playQueue2[0] });
        }

        

       
     
        
    }
}

void DeckGUI::sliderValueChanged (Slider *slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }

    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    
    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
    
}

bool DeckGUI::isInterestedInFileDrag (const StringArray &files)
{
  std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
  return true; 
}

void DeckGUI::filesDropped (const StringArray &files, int x, int y)
{
  std::cout << "DeckGUI::filesDropped" << std::endl;
  if (files.size() == 1)
  {
    player->loadURL(URL{File{files[0]}});
  }
}

void DeckGUI::timerCallback()
{
    //std::cout << "DeckGUI::timerCallback" << std::endl;
    waveformDisplay.setPositionRelative(
            player->getPositionRelative());
}


    

