---
theme: apple-basic
highlighter: shiki
lineNumbers: false
info:
drawings:
  persist: false
title: Hearing Between the Lines
mdc: true
layout: intro
author: Chidi Williams
keywords: ml,ai,whisper,buzz
colorSchema: "light"
---

# Hearing between the lines

<div class="absolute bottom-10">
  <span class="font-400 text-neutral-500">
    <span class="text-[#066e2e] underline">SysConf</span> / 2023-09-16 / Chidi Williams
  </span>
</div>

<!-- prettier-ignore-start -->

---
layout: image-right
image: img/profile.jpg
---

<!-- prettier-ignore-end -->

# About me

- Chidi Williams
- Software Engineer. Previously: Eyowo. Now: GS.
- Lagos -> London
- Co-organize SysDsgn and SysConf.
- Writing, blog @ [chidiwilliams.com](https://chidiwilliams.com)
- Open-source contributor. Web animations, Languages and compilers, AI.
- Music — guitar, piano.

---

# What to expect

- Basics of Machine Learning (for audio tasks)
- Recent advances and applications (Whisper, etc.)
- Open problems and opportunities
- How to contribute

---

# How I got here

<!-- TODO: Make this a timeline -->

- OpenAI releases Whisper in September 2022
  - Multi-lingual speech-to-text transcription model
- Saw a tweet about having a desktop version
- Started working on one a few days later
- Released a demo Mac app: https://twitter.com/chidiwilliams__/status/1575197377048514560
- Today: 7.4k stars on GitHub, 134k downloads for cross-platform version. https://github.com/chidiwilliams/buzz
- _I'm pretty new to this!_
- Going to talk about everything between September 2022 and now

---

# Landscape of audio ML

- Classification

  - Speech or non-speech
  - Speaker identification
  - Emotion recognition
  - Tagging

- Detection and segmentation

  - Voice activity detection (VAD)
  - Music detection
  - Speech segmentation

---

# Landscape of audio ML

- Recognition and Transcription

  - <mark>Automatic speech recognition (ASR)</mark>
  - Music recognition

- Generation and Synthesis
  - Text-to-speech (TTS)
  - Voice cloning
  - Music generation

---

# Automatic Speech Recognition as a pipeline

- Pre-processing

  - Converting the audio signal to a usable format
  - Extracting relevant features

- Inference

  - Running acoustic and language models

- Post-processing
  - Correcting mistakes and formatting

<!-- prettier-ignore-start -->

---
layout: section
---

<!-- prettier-ignore-end -->

# Let's build a super-simple\* audio classifier

<div class="absolute bottom-10">
  <span class="text-sm font-400 text-neutral-500">
    * References: <a href="https://speech.zone/super-simple-speech-recogniser/" target='__blank'>A super-simple speech recogniser</a>
  </span>
</div>

---

# Sampling

<v-clicks>

- From continuous (uncountable) signal to discrete (countable) signal
- Sampling produces a digital representation of sound waves

<div class="mt-8">
  <Sampling v-click></Sampling>
</div>

</v-clicks>

---

# Feature Extraction

<!-- TODO: Explain time domain and frequency domain -->

<Synth></Synth>

<!-- Lower formants are for vowels. Higher formants are what make quality of voice. -->

---

# Finding formant distances

<!-- Compare different audio formants -->
<!-- TODO: Get new word, get formants -->

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
