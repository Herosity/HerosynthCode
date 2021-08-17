/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor(NewProjectAudioProcessor& p)
    : AudioProcessorEditor(&p)
    , audioProcessor(p)
    , osc1(audioProcessor.apvts, "OSC1", "OSC1GAIN", "OSC1PITCH", "OSC1FMFREQ", "OSC1FMDEPTH")
    , osc2(audioProcessor.apvts, "OSC2", "OSC2GAIN", "OSC2PITCH", "OSC2FMFREQ", "OSC2FMDEPTH")
    , filter(audioProcessor.apvts, "FILTERTYPE", "FILTERCUTOFF", "FILTERRESONANCE")
    , adsr(audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
    , lfo1(audioProcessor.apvts, "LFO1FREQ", "LFO1DEPTH")
    , filterAdsr(audioProcessor.apvts, "FILTERATTACK", "FILTERDECAY", "FILTERSUSTAIN", "FILTERRELEASE")
    , reverb(audioProcessor.apvts, "REVERBSIZE", "REVERBDAMPING", "REVERBWIDTH", "REVERBDRY", "REVERBWET", "REVERBFREEZE")
    , meter(audioProcessor)
{
    
    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);
    addAndMakeVisible(filter);
    addAndMakeVisible(adsr);
    addAndMakeVisible(lfo1);
    addAndMakeVisible(filterAdsr);
    addAndMakeVisible(reverb);
    addAndMakeVisible(meter);
    addAndMakeVisible(audioProcessor.visualiser);

    osc1.setName("Oscillator 1");
    osc2.setName("Oscillator 2");
    filter.setName("Filter");
    lfo1.setName("Filter LFO");
    filterAdsr.setName("Filter ADSR");
    adsr.setName("ADSR");
    meter.setName("Meter");
    audioProcessor.visualiser.setName("Visualiser");

    auto oscColour = juce::Colour::fromRGB(0, 255, 255);
    auto filterColour = juce::Colour::fromRGB(0, 255, 255);

    osc1.setBoundsColour(oscColour);
    osc2.setBoundsColour(oscColour);
    meter.setBoundsColour(oscColour);

    filterAdsr.setBoundsColour(filterColour);
    filter.setBoundsColour(filterColour);
    lfo1.setBoundsColour(filterColour);
    adsr.setBoundsColour(filterColour);
    
    startTimerHz(60); //specific start timer
    setSize(1100, 900);
    setResizeLimits(1100, 900, 1100, 900);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
    stopTimer();
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colour::fromRGB(50, 50, 50));

    g.setColour (juce::Colour::fromRGB(0, 255, 255));
    g.setFont (25.0f);
    g.setFont(g.getCurrentFont().boldened());
    g.setFont(g.getCurrentFont().italicised());
    g.drawFittedText ("H    e   r   o   s   y   n   t   h", getLocalBounds(), juce::Justification::centredBottom, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    const auto oscWidth = 420;
    const auto oscHeight = 180;

    osc1.setBounds(0, 0, oscWidth, oscHeight);
    osc2.setBounds(0, osc1.getBottom(), oscWidth, oscHeight);
    filter.setBounds(osc1.getRight(), 0, 180, 200);
    lfo1.setBounds(osc2.getRight(), filter.getBottom(), 180, 160);
    filterAdsr.setBounds(filter.getRight(), 0, 230, 360);
    adsr.setBounds(filterAdsr.getRight(), 0, 230, 360);
    reverb.setBounds(0, osc2.getBottom(), oscWidth, oscHeight);
    meter.setBounds(reverb.getRight(), filterAdsr.getBottom(), lfo1.getWidth()+filterAdsr.getWidth()+adsr.getWidth(), oscHeight);
    audioProcessor.visualiser.setBounds(0, reverb.getBottom(), reverb.getWidth()+meter.getWidth(), oscHeight+100);
}

void NewProjectAudioProcessorEditor::timerCallback()
{
    repaint();
}

