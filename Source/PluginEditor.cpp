/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "GUI/AdsrComponent.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor(NewProjectAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), adsr (audioProcessor.apvts)
{
    startTimerHz(60); //specific start timer
   
    setSize(1600, 1200);

    oscSelectAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "OSC", oscSelector);

    addAndMakeVisible(adsr);
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
    adsr.setBounds (0, (getHeight() / 2) - (1600 / 6) / 2 , getWidth() / 4, getHeight() / 6 ); 
    //PERSONAL NOTE// (getHeight() / 2) - (1600 / 6) / 2, Y start point, getHeight / 2 sets Y at half height, making sliders start at Y 800 form 1600px.
    //To make sure the middle of the slider is centered at 800, (1600 / 6) / 2 calculates the Height of sliders and devides the value by 2.
    //That value is then substracted from the starting position, making the Y coordinate start half a slider higher, centering sliders on Y axis.
}

void NewProjectAudioProcessorEditor::timerCallback()
{
    repaint();
}

