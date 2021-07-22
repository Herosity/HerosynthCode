/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor(NewProjectAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    startTimerHz(60); //specific start timer
   
    setSize(1600, 1200);

    oscSelectAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "OSC", oscSelector);

    //kaed adsr visible
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colours::white);

    g.setColour (juce::Colours::purple);
    g.setFont (20.0f);
    g.drawFittedText ("Hero-10", getLocalBounds(), juce::Justification::centredBottom, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    //set adsr bounds
}

void NewProjectAudioProcessorEditor::timerCallback()
{
    repaint();
}

