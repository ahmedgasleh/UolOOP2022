/*
  ==============================================================================

    SelectionCustomComponent.h
    Created: 8 Mar 2022 6:33:43pm
    Author:  Dellal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PlayListComponent.h"

//==============================================================================
/*
*/
class SelectionCustomComponent  : public juce::Component
{
public:
    SelectionCustomComponent(PlayListComponent& ttd);
    ~SelectionCustomComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setRowAndColumn(int newRow, int newColumn);
    /*int getSelection(const int rowNumber) const;
    void setSelection(const int rowNumber, const int newSelection);*/

private:
    PlayListComponent& owner;
    juce::ToggleButton toggleButton;
    int row, columnId;
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SelectionCustomComponent)
};
