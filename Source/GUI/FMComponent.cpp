/*
  ==============================================================================

    FMComponent.cpp
    Created: 28 Jul 2021 8:51:06pm
    Author:  rodzi

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FMComponent.h"

//==============================================================================
FMComponent::FMComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeId, juce::String cutoffId, juce::String resonanceId)
    : cutoff("Cutoff", cutoffId, apvts, dialWidth, dialHeight)
    , resonance("Resonance", resonanceId, apvts, dialWidth, dialHeight)
{
    juce::StringArray filterTypeChoices{ "Low Pass", "Band Pass", "High Pass" };
    filterTypeSelector.addItemList(filterTypeChoices, 1);
    filterTypeSelector.setSelectedItemIndex(0);
    filterTypeSelector.setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colour::fromRGB(60, 60, 60)); //for combobox
    filterTypeSelector.setColour(juce::ComboBox::ColourIds::textColourId, juce::Colour::fromRGB(255, 100, 23));
    filterTypeSelector.setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colour::fromRGB(60, 60, 60));
    filterTypeSelector.setColour(juce::ComboBox::ColourIds::buttonColourId, juce::Colour::fromRGB(60, 60, 60));
    filterTypeSelector.setColour(juce::ComboBox::ColourIds::arrowColourId, juce::Colour::fromRGB(255, 100, 23));
    filterTypeSelector.setColour(juce::ComboBox::ColourIds::focusedOutlineColourId, juce::Colour::fromRGB(60, 60, 60));
   
    getLookAndFeel().setColour(juce::PopupMenu::backgroundColourId, juce::Colour::fromRGB(60, 60, 60)); //For combobox popupmenu (both osc and filter)
    getLookAndFeel().setColour(juce::PopupMenu::textColourId, juce::Colour::fromRGB(255, 100, 23));
    getLookAndFeel().setColour(juce::PopupMenu::headerTextColourId, juce::Colour::fromRGB(255, 100, 23));
    getLookAndFeel().setColour(juce::PopupMenu::highlightedBackgroundColourId, juce::Colour::fromRGB(60, 60, 60));
    getLookAndFeel().setColour(juce::PopupMenu::highlightedTextColourId, juce::Colour::fromRGB(255, 100, 23));
    
    addAndMakeVisible(filterTypeSelector);

    filterTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, filterTypeId, filterTypeSelector);

    addAndMakeVisible(cutoff);
    addAndMakeVisible(resonance);
}


FMComponent::~FMComponent()
{
}

void FMComponent::resized()
{
    const auto startX = 18;
    const auto startY = 80;
    const auto width = 70;
    const auto height = 88;

    filterTypeSelector.setBounds(18, 40, 145, 25);
    cutoff.setBounds(startX, startY, width, height);
    resonance.setBounds(cutoff.getRight(), startY, width, height);
}


