<script setup lang="ts">
import { Chart } from "chart.js/auto";
import { ref, onMounted } from "vue";
let audioElement: HTMLAudioElement | null = null;

let isPlayingRef = ref(false);

let myChart;
let analyzer;
let dataArray;
let bufferLength;

const data = {
  labels: [],
  datasets: [
    {
      label: "Frequency Spectrum (dB)",
      data: dataArray,
      borderWidth: 1,
      fill: false,
      pointBackgroundColor: Array.from(
        { length: bufferLength },
        () => "#ff0000"
      ),
    },
  ],
};

function startPlayback() {
  const audioContext = new (window.AudioContext || window.webkitAudioContext)();

  analyzer = audioContext.createAnalyser();
  analyzer.fftSize = 1024;

  bufferLength = analyzer.frequencyBinCount;
  dataArray = new Float32Array(bufferLength);

  data.labels = Array.from(
    { length: bufferLength },
    (_, i) => (i * audioContext.sampleRate) / analyzer.fftSize
  );

  audioElement = document.querySelector("audio#boot");
  if (!audioElement) return;

  const source = audioContext.createMediaElementSource(audioElement);
  source.connect(analyzer);
  audioElement.play();
  isPlayingRef.value = true;
  draw();
}

function draw() {
  if (!isPlayingRef.value) {
    return;
  }

  requestAnimationFrame(draw);

  analyzer.getFloatFrequencyData(dataArray);

  for (let i = 0; i < bufferLength; i++) {
    data.datasets[0].data[i] = dataArray[i];
    console.log(dataArray[i]);
  }

  myChart.update();
}

function init() {
  const canvas = document.getElementById("chart")! as HTMLCanvasElement;
  const ctx = canvas.getContext("2d")!;

  myChart = new Chart(ctx, {
    type: "line",
    data: data,
    options: {
      scales: {
        x: {
          title: { display: true, text: "Frequency (Hz)" },
          min: 30,
          max: 17000,
          type: "logarithmic",
        },
        y: {
          min: -100,
          max: -30,
        },
      },
    },
  });
}

function stopPlayback() {
  if (audioElement) {
    audioElement.pause();
    audioElement.currentTime = 0;
  }
  isPlayingRef.value = false;
}
</script>

<template>
  <button v-on:click="init">Start</button>

  <div class="flex">
    <audio ref="audioElement" id="boot" controls preload="auto">
      <source src="/public/wav/boot_template.wav" type="audio/wav" />
      Your browser does not support the audio element.
    </audio>

    <canvas id="chart" style="width: 50%; max-width: 50%" height="100"></canvas>
  </div>

  <button v-on:click="startPlayback" v-show="!isPlayingRef">Play</button>
  <button v-on:click="stopPlayback" v-show="isPlayingRef">Pause</button>
</template>
