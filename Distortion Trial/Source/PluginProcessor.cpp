/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
DistortionTrialAudioProcessor::DistortionTrialAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
    parameters(*this, nullptr)
{
	// This creates our parameters. We'll keep some raw pointers to them in this class,
	// so that we can easily access them later, but the base class will take care of
	// deleting them for us.
    
    parameters.createAndAddParameter("inputGain", "Input Gain", "dB", NormalisableRange<float> (-36.f,36.f), 0.f, nullptr, nullptr);
    parameters.createAndAddParameter("outputGain", "Output Gain", "dB", NormalisableRange<float> (-36.f,36.f), 0.f, nullptr, nullptr);
    parameters.state = ValueTree (Identifier ("Tonal Conflict"));
	//addParameter(slider1param = new AudioParameterFloat("slider1", "First slider", 0.0f, 1.0f, 0.9f));
	//addParameter(slider2param = new AudioParameterFloat("slider2", "Second Slider", 0.0f, 1.0f, 0.5f));
}

DistortionTrialAudioProcessor::~DistortionTrialAudioProcessor()
{
}

//==============================================================================
const String DistortionTrialAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DistortionTrialAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DistortionTrialAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double DistortionTrialAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DistortionTrialAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DistortionTrialAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DistortionTrialAudioProcessor::setCurrentProgram (int index)
{
}

const String DistortionTrialAudioProcessor::getProgramName (int index)
{
    return String();
}

void DistortionTrialAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void DistortionTrialAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void DistortionTrialAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DistortionTrialAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DistortionTrialAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    
    float inputGain;
    inputGain = powf(10.0f, *parameters.getRawParameterValue("inputGain")/20.0f);
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
		const float* inBuffer = buffer.getReadPointer(channel);
        float* outBuffer = buffer.getWritePointer(channel);
        
        // Apply distortion to each sample in buffer
		for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
            const float input = inBuffer[sample]*inputGain;
            float output;
            if(!distortionType_[0]) {
                float threshold = 1.0f;
                if(input > threshold) {
                    output = threshold;
                }
                else if(input < -threshold) {
                    output = -threshold;
                }
                else {
                    output = input;
                }
            }
            outBuffer[sample] = output;
		}
    }
}

//==============================================================================
bool DistortionTrialAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DistortionTrialAudioProcessor::createEditor()
{
    return new DistortionTrialAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void DistortionTrialAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DistortionTrialAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DistortionTrialAudioProcessor();
}
