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
---

# Hearing between the lines

<div class="absolute bottom-10">
  <span class="font-400 text-neutral-500">
    <span class="text-[#066e2e] underline">SysConf</span> / 2023-09-16 / Chidi Williams
  </span>
</div>

---

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

# How did I get here?

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

# Landscape of Machine Learning for audio

- Classification

  - Speech or non-speech
  - Speaker identification
  - Emotion recognition
  - Tagging

- Detection and segmentation

  - Voice activity detection (VAD)
  - Music detection
  - Speech segmentation

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

---
layout: section
---

# Let's build a super-simple\* audio classifier

<div class="absolute bottom-10">
  <span class="text-sm font-400 text-neutral-500">
    * References: <a href="https://speech.zone/super-simple-speech-recogniser/" target='__blank'>A super-simple speech recogniser</a>
  </span>
</div>

---

# Sampling

- We sample audio data to get a digital representation of the sound waves
- Sampling converts a continuous (uncountable) signal to a discrete (countable) representation

<!-- TODO: diagram of sampling -> left continuous signal, right discrete (number of samples) -->
<!-- Show that increasing sampling rate/frequency improves accuracy at the cost of size -->

---

# Feature Extraction

---

# Acoustic Models

---

# Language model

---

# Lexicon

---

# Decoder

- Search algorithm

---

# Whisper

- What's Whisper?
- "Robust Speech Recognition via Large-Scale Weak Supervision" ???
- In programmer-speak:

  ```shell
  pip install openai-whisper
  whisper japanese.wav --language Japanese
  ```

- Audio goes in, text comes out
  - Multi-lingual
  - Transcribes and translates
- Model sizes (varying accuracies and resource requirements)
- Robust to accents, background noise, and technical language
- Easy to use. Just `pip install` and run!

---

# Buzz

- PyQt desktop app

---

# Ring Buffers

- Live Recording
- How they work
- Demo

---

# Thoughts, Open Problems and opportunities

> <i>AI is both <u>over-hyped</u> and <u>under-rated</u>"</i>

<br>

- Making it easier for people to use
- Performance
- Build for the world

---

# Resources

- [Introducing Whisper](https://openai.com/research/whisper), OpenAI
- [Whisper.cpp](https://github.com/ggerganov/whisper.cpp), Georgi Gerganov
- [Neural Networks: Zero to Hero](https://www.youtube.com/playlist?list=PLAqhIrjkxbuWI23v9cThsA9GvCAUhRvKZ), Andrej Karpathy
- [Practical Deep Learning for Coders](https://course.fast.ai/), Fast.ai

<div>
</div>
