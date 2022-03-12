/*
  ==============================================================================

    PlayListComponent.h
    Created: 19 Feb 2022 4:16:41pm
    Author:  inadh

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>

//==============================================================================
/*
*/
class PlayListComponent  : public juce::Component,
    juce::TableListBoxModel,
    juce::Button::Listener
{
public:
    PlayListComponent();
    ~PlayListComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void paintRowBackground(Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;

    int getNumRows() override;

    void paintCell(Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;


    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;

    int getColumnAutoSizeWidth(int columnId) override;

    void buttonClicked(juce::Button* button) override;

    int getSelection(const int rowNumber) const;
    void setSelection(const int rowNumber, const int newSelection);

    void loadPersistedPlayList(juce::File dataFile);

    juce::String getAttributeNameForColumnId(const int columnId) const;

    juce::String getText(const int columnNumber, const int rowNumber) const;

    //juce::XmlElement& getCurrentPlayList();
    juce::XmlElement* playList = nullptr;
   

private:

    void addItemToPlayList(juce::File newFile);

    juce::TableListBox tableComponent{ {}, this };
   

    //std::vector<std::string>  trackTitles;

    std::unique_ptr<juce::XmlElement> xmlData;
    juce::XmlElement* titles = nullptr;
    

    

    juce::File path{ "C:/temp/data.xml" };

    int count = 0;

    juce::Font font{ 14.0f };

    TextButton addPlayListButton{ "Update Play List" };

    //class EditableTextCustomComponent : public juce::Label
    //{
    //public:
    //    EditableTextCustomComponent(PlayListComponent& ttd) : owner(ttd) {

    //        setEditable(false, true, false);

    //    }
    //    void mouseDown(const juce::MouseEvent& event) override
    //    {
    //        owner.tableComponent.selectRowsBasedOnModifierKeys(row, event.mods, false);
    //    }
    //    void textWasEdited() override
    //    {
    //        //owner.getText(columnId, row)
    //    }

    //    void setRowAndColumn(const int newRow, const int newColumn)
    //    {
    //        row = newRow;
    //        columnId = newColumn;
    //        setText(owner.getText(columnId, row), juce::dontSendNotification);
    //    }

    //private: 
    //    PlayListComponent& owner;
    //    int row, columnId;
    //    juce::Colour textColour;
    //};


    juce::FileChooser fileChooser{ "Browse for data.xml", juce::File::getSpecialLocation(juce::File::invokedExecutableFile) };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayListComponent)
};
