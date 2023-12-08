---
theme: apple-basic
highlighter: shiki
lineNumbers: false
info:
drawings:
  persist: false
mdc: true
layout: intro
author: Chidi Williams
keywords: ml,ai,whisper,buzz
colorSchema: "light"
fonts:
  sans: IBM Plex Sans
---

# Hearing between the lines

<div class="absolute bottom-10">
  <span class="font-400 text-neutral-500">
    <span class="text-[#066e2e] font-600">SysConf</span> / 2023-09-16 / Chidi Williams
  </span>
</div>

---

# About me

<div class="flex gap-32">
  <div class="flex-1">

Chidi Williams, Software Engineer
<v-clicks>

- Previously at a fintech in Lagos, now at a bank in London
- Write a programming blog at [chidiwilliams.com](https://chidiwilliams.com)
- Co-organize SysDsgn (and SysConf)
- Often build hobby projects in web animations, languages and compilers, and (more recently) AI
- Love to play music — guitar, piano
</v-clicks>

  </div>
  <div style="width: 150px; height: 150px">
  <img class="rounded-lg shadow-xl" src="/img/profile.jpg" />
  </div>
</div>

---

# What to expect

<ul>
<li>Basics of Machine Learning (for audio tasks)</li>
<v-click> <li> Recent advances and applications (Whisper, etc.) </li> </v-click>
<v-click> <li> Open problems and opportunities </li> </v-click>
<v-click> <li> How to contribute </li> </v-click>
</ul>

---

# How I got here

<v-clicks>

- September 2022

  - OpenAI releases Whisper, a multi-lingual speech-to-text transcription model
  - See a tweet about wanting the model packaged as a desktop app and I begin working on one soon after
  - Demo a Mac app on [Twitter](https://twitter.com/chidiwilliams__/status/1575197377048514560) (~20k video views, ~100k impressions)

- September 2023

  - \>7k stars on [GitHub](https://github.com/chidiwilliams/buzz), >130k downloads

- Here's what I've learned in the past year!

</v-clicks>

---

# Landscape of audio ML

<v-clicks>

- Classification

  - Speech or non-speech
  - Speaker identification
  - Emotion recognition
  - Tagging

- Detection and segmentation

  - Voice activity detection (VAD)
  - Music detection
  - Speech segmentation

</v-clicks>

---

# Landscape of audio ML

<v-clicks>

- Recognition and Transcription

  - <mark>Automatic speech recognition (ASR)</mark>
  - Music recognition

- Generation and Synthesis
  - Text-to-speech (TTS)
  - Voice cloning
  - Music generation

</v-clicks>

---

# Automatic Speech Recognition as a pipeline

<v-clicks>

- Pre-processing

  - Converting the audio signal to a usable format
  - Extracting relevant features

- Inference

  - Acoustic model: generating potential word sequences from audio
  - Language model: generating linguistically likely word sequences

- Post-processing

  - Correcting mistakes and formatting

</v-clicks>

<!-- prettier-ignore-start -->

---
layout: section
---

<!-- prettier-ignore-end -->

# Let's build an audio classifier

<div class="absolute bottom-10">
  <span class="text-sm font-400 text-neutral-500">
    * Reference: <a href="https://speech.zone/super-simple-speech-recogniser/" target='__blank'>A super-simple speech recogniser</a>
  </span>
</div>

---

# Sampling

<v-clicks>

- From continuous (uncountable) signal to discrete (countable) signal
- Sampling produces a digital representation of sound waves

<div class="mt-4">
  <Sampling v-click></Sampling>
</div>

</v-clicks>

---

# Feature extraction (vowel formants)

<!-- TODO: Explain time domain and frequency domain -->

<Spectrum></Spectrum>

<!--
  1. Explain time domain and frequency domain.
  2. Formants are concentrations around a frequency.
  3. Lower formants are for vowels. Higher formants are what make quality of voice.
  4. Order of vowels (TODO: wikipedia)
-->

---

# Finding formant distances

<table>
  <thead>
    <tr>
      <th>Word</th>
      <th>Audio</th>
      <th>Spectrum</th>
      <th>Formants</th>
    </tr>
  </thead>

  <tbody>
    <tr>
      <td>Beet</td>
      <td>
        <audio ref="audioElement" id="boot" controls preload="auto">
          <source src="/wav/beet_template.wav" type="audio/wav" />
          Your browser does not support the audio element.
        </audio>
      </td>
      <td> <img src="/img/beet.png" width="200" /> </td>
      <td> <code>[190, 2165]</code> </td>
    </tr>
    <tr>
      <td>Boot</td>
      <td>
        <audio ref="audioElement" id="boot" controls preload="auto">
          <source src="/wav/boot_template.wav" type="audio/wav" />
          Your browser does not support the audio element.
        </audio>
      </td>
      <td><img src="/img/boot.png" width="200" /> </td>
      <td><code>[289, 1301]</code> </td>
    </tr>
  </tbody>

</table>

---

# Finding formant distances

<BeetAndBoot></BeetAndBoot>

---

# Finding formant distances

Unknown word

<audio ref="audioElement" id="boot" controls preload="auto" class="mb-4">
  <source src="/wav/unknown.wav" type="audio/wav" />
  Your browser does not support the audio element.
</audio>

<img src="/img/unknown.png" width="500" />

`[285, 1380]`

---

# Finding formant distances

<BeetAndBoot v-bind:showUnknown="true"></BeetAndBoot>

<v-click>

$$
d = \sqrt{{({x2} - {x1})^2 + ({y2} - {y1})^2}};
$$

</v-click>

<v-click>
$$
beet: d([285, 1380],[190, 2165]) = 791
$$

</v-click>

<v-click>
$$
boot: d([285, 1380],[289, 1301]) = 78
$$
</v-click>

---

# Whisper

<div class="flex gap-4">
  <div>
    <ul>
      <li>
        General-purpose speech recognition: <b>multi-lingual speech recognition</b>, <b>speech translation</b>, and <b>language identification</b>.
      </li>
      <v-click>
        <li>
          Model sizes (varying accuracies and resource requirements)
        </li>
      </v-click>
      <v-click>
        <li>
          Robust to accents, background noise, and technical language
        </li>
      </v-click>
      <v-click>
        <li>
          Easy to use. Just <code>pip install</code> and run!
  <v-start>

```console
$ pip install openai-whisper
$ whisper input.wav
Detected language: French
[00:00.000 --> 00:09.640]  Bienvenue dans Paserelle, un
podcast pensé pour éveiller la curiosité...
```

  </v-start>
        </li>
      </v-click>
    </ul>
  </div>
  <div>
  <img src="/img/whisper-training-data.png" width="500" />
  </div>
</div>

---

# How Whisper works

<div class="flex gap-4">
  <ul>
    <li>
      Input audio is converted to <b>log-mel spectrogram</b>
    </li>
    <v-click>
      <li>
        <b>Transformer encoder</b> on the left encodes spectrogram to extract its important features
      </li>
    </v-click>
    <v-click>
      <li>
        <b>Transformer decoder</b> on the right receives encoder output using a mechanism called <b>cross-attention</b>
      </li>
    </v-click>
    <v-click>
      <li>
        Decoder predicts sequence of text tokens, starting from an initial sequence with just the "start" token, until "end" token
      </li>
    </v-click>
  </ul>
  <img src="/img/whisper_architecture.svg" width="500"/>
</div>

<!-- Seq2Seq: https://blog.keras.io/a-ten-minute-introduction-to-sequence-to-sequence-learning-in-keras.html -->
<!-- https://huggingface.co/learn/audio-course/chapter3/seq2seq -->

---

# Open problems and opportunities

<ul>
  <img src="/img/wer-yoruba.png" alt="WERs" />
  <li>
    <b>Improved localization</b>: Adding support for more languages and dialects
  </li>
  <v-click>
  <li>
    <b>Accessibility</b>: Making models easier to set up and use
  </li>
  </v-click>
  <v-click>
  <li>
    <b>Performance</b>: Speeding up models and getting them to run on lower-end devices
  </li>
  </v-click>
</ul>

---

# Resources

- [Neural Networks: Zero to Hero](https://www.youtube.com/playlist?list=PLAqhIrjkxbuWI23v9cThsA9GvCAUhRvKZ), Andrej Karpathy
- [Practical Deep Learning for Coders](https://course.fast.ai/), Fast.ai
- [Hugging Face Audio Course](https://huggingface.co/learn/audio-course/), Hugging Face
- [Introducing Whisper](https://openai.com/research/whisper), OpenAI
- [Whisper.cpp](https://github.com/ggerganov/whisper.cpp), Georgi Gerganov

<div>
</div>
