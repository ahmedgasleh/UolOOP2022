/*
  ==============================================================================

    SelectionCustomComponent.cpp
    Created: 8 Mar 2022 6:33:43pm
    Author:  Dellal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SelectionCustomComponent.h"

//==============================================================================
SelectionCustomComponent::SelectionCustomComponent(PlayListComponent& ttd) : owner (ttd)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible(toggleButton);

    toggleButton.onClick = [this] { owner.setSelection(row, (int)toggleButton.getToggleState()); };

}

SelectionCustomComponent::~SelectionCustomComponent()
{
}

void SelectionCustomComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    
}

void SelectionCustomComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    toggleButton.setBoundsInset(juce::BorderSize<int>(2));

}

void SelectionCustomComponent::setRowAndColumn(int newRow, int newColumn)
{
    row = newRow;
    columnId = newColumn;
    toggleButton.setToggleState((bool)owner.getSelection(row), juce::dontSendNotification);
}

//int SelectionCustomComponent::getSelection(const int rowNumber) const
//{
//    return 0; // dataList->getChildElement(rowNumber)->getIntAttribute("Select");
//}
//
//void SelectionCustomComponent::setSelection(const int rowNumber, const int newSelection)
//{
//}
