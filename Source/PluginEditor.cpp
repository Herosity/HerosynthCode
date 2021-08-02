/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "C:\Users\rodzi\Desktop\JUCE\modules\juce_audio_utils\gui\juce_AudioVisualiserComponent.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor(NewProjectAudioProcessor& p)
    : AudioProcessorEditor(&p)
    , audioProcessor(p)
    , osc(audioProcessor.apvts, "OSC1WAVETYPE", "OSC1FMFREQ", "OSC1FMDEPTH")
    , adsr ("Osc Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
    , filterAdsr ("Mod Envelope", audioProcessor.apvts, "FILTERATTACK", "FILTERDECAY", "FILTERSUSTAIN", "FILTERRELEASE")
    , filter (audioProcessor.apvts, "FILTERTYPE", "FILTERFREQ", "FILTERRES")
{
    //startTimerHz(60); //specific start timer
   
    setSize(1600, 900);
    setResizeLimits(1600, 900, 1600, 900);
    addAndMakeVisible(osc);
    addAndMakeVisible(adsr);
    addAndMakeVisible(filterAdsr);
    addAndMakeVisible(filter);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colours::grey);

    g.setColour (juce::Colours::deepskyblue);
    g.setFont (25.0f);
    g.drawFittedText ("Hero-10", getLocalBounds(), juce::Justification::centredBottom, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    const auto padding = 50;

    osc.setBounds(0 + padding, 0 + padding, getWidth() / 4, getHeight() / 4); //OSC
    adsr.setBounds (400 + padding, 0 + padding, getWidth() / 4, getHeight() / 4); //ADSR
    filterAdsr.setBounds(400 + padding, 300 + padding, getWidth() / 4, getHeight() / 4); //MOD
    filter.setBounds(0 + padding, 300 + padding, getWidth() / 4, getHeight() / 4); //FLTR
    //visualiser.setBounds(800 + padding, 300 + padding, getWidth() / 4, getHeight() / 4);
}

//void NewProjectAudioProcessorEditor::timerCallback()
//{
//    repaint();
//    //visualiser.pushBuffer(audioProcessor.getBuffer());
//}

