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
    setSize(1080, 800);
    setResizeLimits(1075, 800, 1075, 800);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
    stopTimer();
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour::fromRGB(60, 60, 60));

    g.setColour (juce::Colour::fromRGB(85, 83, 87));
    g.drawRoundedRectangle(juce::Rectangle<float>(1075, 800), 14.0f, 10.0f);
    g.setFont (25.0f);
    g.setFont(g.getCurrentFont().boldened().italicised());
}

void NewProjectAudioProcessorEditor::resized()
{
    const auto oscWidth = 420;
    const auto oscHeight = 180;
    const auto margin = 1;

    osc1.setBounds(6, 6, oscWidth, oscHeight);
    osc2.setBounds(6, osc1.getBottom()+margin, oscWidth, oscHeight);
    filter.setBounds(osc1.getRight()+margin, 6, 180, 200);
    lfo1.setBounds(osc2.getRight()+margin, filter.getBottom()+margin, 180, 160);
    filterAdsr.setBounds(filter.getRight()+margin, 6, 230, 361);
    adsr.setBounds(filterAdsr.getRight()+margin, 6, 230, 361);
    reverb.setBounds(6, osc2.getBottom()+margin, oscWidth, oscHeight);
    meter.setBounds(reverb.getRight()+margin, lfo1.getBottom()+margin, lfo1.getWidth()+filterAdsr.getWidth()+adsr.getWidth()+3, oscHeight);
    audioProcessor.visualiser.setBounds(6, reverb.getBottom()+margin, reverb.getWidth()+meter.getWidth()+margin, oscHeight+65);
}

void NewProjectAudioProcessorEditor::timerCallback()
{
    repaint();
}

