/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AmpPulserAudioProcessorEditor::AmpPulserAudioProcessorEditor (AmpPulserAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
   
    mPulserLfoSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mPulserLfoSlider.setRange(0.0f, 10.0f);
    mPulserLfoSlider.setValue(audioProcessor.mPulserLfoSliderValue);
    addAndMakeVisible(&mPulserLfoSlider);
    mPulserLfoSlider.addListener(this);
    
    addAndMakeVisible(&mPulserLfoLabel);
    mPulserLfoLabel.setText("LFO Freq", juce::dontSendNotification);
    mPulserLfoLabel.attachToComponent(&mPulserLfoSlider, true);
    mPulserLfoLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    mPulserLfoLabel.setJustificationType(juce::Justification::right);
    
    setResizable(true, true);
    setResizeLimits(250, 250, 850, 550);
    setSize (500, 400);
    
    std::printf("GUI constructor\n");
}

AmpPulserAudioProcessorEditor::~AmpPulserAudioProcessorEditor()
{
    
    mPulserLfoSlider.removeListener(this);
//     std::printf("GUI destructor\n");
    
}

//==============================================================================
void AmpPulserAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    if(slider == &mPulserLfoSlider)
    {
        double cyclesPerSample;
        
        audioProcessor.mPulserLfoSliderValue = mPulserLfoSlider.getValue();
        
        cyclesPerSample = audioProcessor.mPulserLfoSliderValue/audioProcessor.mSampleRate;
        
        audioProcessor.mAngleDelta = cyclesPerSample * juce::MathConstants<double>::twoPi;
    }
}


//==============================================================================
void AmpPulserAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::royalblue);
    g.setFont (30.0f);
    g.drawFittedText ("LFO Freq", getLocalBounds(), juce::Justification::centred, 1);
}

void AmpPulserAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    mPulserLfoSlider.setBounds(getWidth() * 0.1, getHeight() * 0.4, getWidth() * 0.8, getHeight() * 0.6);
}
