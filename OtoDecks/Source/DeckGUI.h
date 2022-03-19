/*
  ==============================================================================

    DeckGUI.h
    Created: 13 Mar 2020 6:44:48pm
    Author:  matthew

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "PlayListComponent.h"
#include "LookAndFeel.h"



//==============================================================================
/*
*/
class DeckGUI    : public Component,
                   public Button::Listener, 
                   public Slider::Listener, 
                   public FileDragAndDropTarget, 
                   public Timer
{
public:
    DeckGUI(DJAudioPlayer* player, 
            PlayListComponent* playList,
           AudioFormatManager & 	formatManagerToUse,
           AudioThumbnailCache & 	cacheToUse );
    ~DeckGUI();

    void paint (Graphics&) override;
    void resized() override;

     /** implement Button::Listener */
    void buttonClicked (Button *) override;

    /** implement Slider::Listener */
    void sliderValueChanged (Slider *slider) override;

    bool isInterestedInFileDrag (const StringArray &files) override;
    void filesDropped (const StringArray &files, int x, int y) override; 

    void timerCallback() override; 

private:

    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};
  
    CustomRotaryDail volSlider; 
    CustomRotaryDail speedSlider;
    CustomRotaryDail posSlider;

    WaveformDisplay waveformDisplay;

    DJAudioPlayer* player; 

    PlayListComponent* playlist;

    std::vector<juce::File> playQueue1;
    std::vector<juce::File> playQueue2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
