---
theme: seriph
class: text-center
background: ""
highlighter: shiki
lineNumbers: false
info:
drawings:
  persist: false
transition: slide-left
title: Hearing Between the Lines
mdc: true
---

# Hearing Between the Lines

SysConf / 2023-09-16 / Chidi Williams

---

# About Me

- Chidi Williams
- Software Engineer. Previously: Eyowo. Now: GS.
- Co-organize SysDsgn and SysConf.
- Writing, blog @ [chidiwilliams.com](https://chidiwilliams.com)
- Open-source contributor. Web animations, Languages and compilers, AI.
- Music — guitar, piano.

---

# What to expect from this talk

- How Audio ML works (for the un-initiated)
- History and basics of Audio ML
- Recent advances and applications (Whisper, etc.)
- Future and open problems
- How to contribute

---

# What's my story?

- I'm pretty new to this
- OpenAI releases Whisper in September 2022
  - Multi-lingual speech-to-text transcription model
- Saw a tweet about having a desktop version
- Started working on one a few days later
- Released a demo Mac app: https://twitter.com/chidiwilliams__/status/1575197377048514560
- Today: 7.4k stars on GitHub, 134k downloads for cross-platform version. https://github.com/chidiwilliams/buzz
- Going to talk about everything between September 2022 and now

---

# Audio ML Landscape

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

# Audio ML Landscape (2)

- Recognition and Transcription

  - <mark>Automatic speech recognition (ASR)</mark>
  - Music recognition

- Generation and Synthesis
  - Text-to-speech (TTS)
  - Voice cloning
  - Music generation

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

# How does it work?

- Steps in an Audio ML pipeline
- Pre-processing
  - Audio sampling
  - Feature extraction
    - Mel-frequency cepstral coefficients (MFCCs)
    - Filter bank energies
    - Spectogram representations
- Acoustic models
- Language model
- Lexicon (or pronunciation dictionary)
- Decoder (or Search Algorithm)
- Post-processing

  - Correcting mistakes

- Training / Evaluation / Adaptation and Fine-tuning

---

# Sampling

---

# Feature Extraction

---

# Acoustic Models

# Whisper

- AI is both very hyped and very under-rated
