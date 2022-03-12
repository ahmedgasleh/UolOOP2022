/*
  ==============================================================================

    PlayListComponent.cpp
    Created: 19 Feb 2022 4:16:41pm
    Author:  inadh

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlayListComponent.h"
#include "SelectionCustomComponent.h"

//==============================================================================
PlayListComponent::PlayListComponent()
{
    

   

    loadPersistedPlayList(path);
    addAndMakeVisible(tableComponent);
    addAndMakeVisible(addPlayListButton);

    addPlayListButton.addListener(this);

    //tableComponent.setColour ()

    tableComponent.setOutlineThickness(1);

    if (titles != nullptr)
    {
        for (auto* columnXml : titles->getChildIterator())
        {
            tableComponent.getHeader().addColumn(columnXml->getStringAttribute("name"), // [2]
                columnXml->getIntAttribute("columnId"),
                columnXml->getIntAttribute("width"),
                100,
                400,
                juce::TableHeaderComponent::defaultFlags);
        }
    }


    tableComponent.getHeader().setSortColumnId(1, true);
    tableComponent.setMultipleSelectionEnabled(true);

    resized();
    

}

PlayListComponent::~PlayListComponent()
{
}

void PlayListComponent::paint (juce::Graphics& g)
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
    g.drawText ("PlayListComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlayListComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    addPlayListButton.setBounds(0, 0, getWidth(), 24);
    tableComponent.setBounds(0, 25, getWidth(), getHeight());
}

void PlayListComponent::paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(Colours::orange);
    }
    else
    {
        g.fillAll(Colours::grey);
    }
}

int PlayListComponent::getNumRows()
{
    return count;
}

void PlayListComponent::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    //g.drawText("hello", 2, 0, width - 4, height, juce::Justification::centredLeft);

    g.setColour(rowIsSelected ? juce::Colours::darkblue : getLookAndFeel().findColour(juce::ListBox::textColourId));
    g.setFont(font);

    if (auto* rowElement = playList->getChildElement(rowNumber)) {
        auto text = rowElement->getStringAttribute(getAttributeNameForColumnId(columnId));

        g.drawText(text, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
    }

    g.setColour(getLookAndFeel().findColour(juce::ListBox::backgroundColourId));
    g.fillRect(width - 1, 0, 1, height);

}

Component* PlayListComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
    /*if (columnId == 2)
    {
        if (existingComponentToUpdate == nullptr)
        {
            juce::TextButton* btn = new juce::TextButton{ "play" };

            juce::String id{ std::to_string(rowNumber) };

            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }*/

    if (columnId == 6) 
    {
        auto* selectionBox = static_cast<SelectionCustomComponent*> (existingComponentToUpdate);

        if (selectionBox == nullptr)
            selectionBox = new SelectionCustomComponent(*this);

        selectionBox->setRowAndColumn(rowNumber, columnId);

        return selectionBox;

    }

    if (columnId == 7)
    {
        auto* selectionBox = static_cast<SelectionCustomComponent*> (existingComponentToUpdate);

        if (selectionBox == nullptr)
            selectionBox = new SelectionCustomComponent(*this);

        selectionBox->setRowAndColumn(rowNumber, columnId);

        return selectionBox;

    }

    jassert(existingComponentToUpdate == nullptr);


    return nullptr;
}

int PlayListComponent::getColumnAutoSizeWidth(int columnId)
{
    if (columnId == 9)
        return 50;

    int widest = 32;

    for (auto i = getNumRows(); --i >= 0;)
    {
        if (auto* rowElement = playList->getChildElement(i))
        {
            auto text = rowElement->getStringAttribute(getAttributeNameForColumnId(columnId));

            widest = juce::jmax(widest, font.getStringWidth(text));
        }
    }
    return widest + 8;
}

void PlayListComponent::buttonClicked(juce::Button* button)
{
   
    if (button == &addPlayListButton)
    {

        FileChooser chooser{ "Select a file..." };
        if (chooser.browseForFileToOpen())
        {
            //player->loadURL(URL{ chooser.getResult() });
            //waveformDisplay.loadURL(URL{ chooser.getResult() });

            //std::cout << URL( chooser.getResult()).toString(true) << std::endl;

            addItemToPlayList(chooser.getResult());

        }

       
    }
   

}

int PlayListComponent::getSelection(const int rowNumber) const
{
    return 0;
}

void PlayListComponent::setSelection(const int rowNumber, const int newSelection)
{
}

void PlayListComponent::loadPersistedPlayList(juce::File dataFile)
{
    if (dataFile == juce::File() || !dataFile.exists())
        return;

    xmlData = juce::XmlDocument::parse(dataFile);

    playList = xmlData->getChildByName("DATA");
    titles = xmlData->getChildByName("HEADERS");

    count = playList->getNumChildElements();

}

juce::String PlayListComponent::getAttributeNameForColumnId(const int columnId) const
{
    for (auto* columnXml : titles->getChildIterator())
    {
        if (columnXml->getIntAttribute("columnId") == columnId)
            return columnXml->getStringAttribute("name");
    }

    return {};
}

juce::String PlayListComponent::getText(const int columnNumber, const int rowNumber) const
{
    return playList->getChildElement(rowNumber)->getStringAttribute(getAttributeNameForColumnId(columnNumber));

    return "";
}


void PlayListComponent::addItemToPlayList(juce::File newFile)
{
    const juce::String  name = newFile.getFileName(); // getFileName();

    if (newFile == juce::File() || !newFile.exists())
        return;

    XmlElement* newItem = new XmlElement("ITEM");

    newItem->setAttribute("ID", count + 1);
    newItem->setAttribute("Name", newFile.getFileName());
    newItem->setAttribute("Path", newFile.getFullPathName());
    newItem->setAttribute("Type", newFile.getFileExtension());
    newItem->setAttribute("Size", 100);
    newItem->setAttribute("Deck01", 0);
    newItem->setAttribute("Deck02", 0);

    playList->addChildElement(newItem);

    if (xmlData.get() != nullptr)
    {
        auto data = xmlData.get();

        data->writeTo(path);
    }

    tableComponent.repaint();
    tableComponent.updateContent();

    
}
