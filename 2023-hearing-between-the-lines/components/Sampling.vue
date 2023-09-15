<script setup lang="ts">
import { Chart } from "chart.js/auto";
import { ref } from "vue";

let isRecordingRef = ref(false);

function startRecording() {
  const audioContext = new (window.AudioContext || window.webkitAudioContext)();

  const continuousAnalyzer = audioContext.createAnalyser();
  continuousAnalyzer.fftSize = 2048;
  const continuousBufferLength = continuousAnalyzer.frequencyBinCount;
  const continuousDataArray = new Float32Array(continuousBufferLength);

  const discreteAnalyzer = audioContext.createAnalyser();
  discreteAnalyzer.fftSize = 512;
  const discreteBufferLength = discreteAnalyzer.frequencyBinCount;
  const discreteDataArray = new Float32Array(discreteBufferLength);

  navigator.mediaDevices
    .getUserMedia({ audio: true })
    .then((stream) => {
      const source = audioContext.createMediaStreamSource(stream);
      source.connect(discreteAnalyzer);
      source.connect(continuousAnalyzer);
      isRecordingRef.value = true;
      draw();
    })
    .catch((err) => {
      console.error("Error accessing the microphone:", err);
    });

  const canvas = document.getElementById("continuous")! as HTMLCanvasElement;
  const ctx = canvas.getContext("2d")!;
  const data = {
    labels: Array.from({ length: continuousBufferLength }, (_, i) => i),
    datasets: [
      {
        label: "Audio Data",
        data: continuousDataArray,
        labels: Array.from({ length: continuousBufferLength }, (_, i) => i),
        borderWidth: 1,
        fill: false,
        pointStyle: false,
      },
    ],
  };
  const continuousChart = new Chart(ctx, {
    type: "line",
    data: data,
    options: {
      responsive: true,
      maintainAspectRatio: true,
      scales: {
        x: {},
        y: {
          min: -0.1,
          max: 0.1,
        },
      },
    },
  });

  const discreteCanvas = document.getElementById(
    "discrete"
  )! as HTMLCanvasElement;
  const discreteCtx = discreteCanvas.getContext("2d")!;
  const discreteData = {
    labels: Array.from({ length: discreteBufferLength }, (_, i) => i),
    datasets: [
      {
        label: "Audio Data",
        data: discreteDataArray,
        borderWidth: 1,
        fill: false,
        pointStyle: false,
      },
    ],
  };
  const discreteChart = new Chart(discreteCtx, {
    type: "line",
    data: discreteData,
    options: {
      responsive: true,
      maintainAspectRatio: true,
      scales: {
        x: {},
        y: {
          min: -0.1,
          max: 0.1,
        },
      },
    },
  });

  function draw() {
    if (!isRecordingRef.value) {
      return;
    }

    requestAnimationFrame(draw);

    continuousAnalyzer.getFloatTimeDomainData(continuousDataArray);
    discreteAnalyzer.getFloatTimeDomainData(discreteDataArray);

    for (let i = 0; i < continuousBufferLength; i++) {
      data.datasets[0].data[i] = continuousDataArray[i];
    }

    for (let i = 0; i < discreteBufferLength; i++) {
      discreteData.datasets[0].data[i] = discreteDataArray[i];
    }

    continuousChart.update();
    discreteChart.update();
  }
}

function stopRecording() {
  isRecordingRef.value = false;
}
</script>

<template>
  <div>
    <button v-on:click="startRecording()" v-if="!isRecordingRef">Start</button>
    <button v-on:click="stopRecording()" v-if="isRecordingRef">Stop</button>
  </div>

  <div class="flex">
    <canvas
      id="continuous"
      style="width: 50%; max-width: 50%"
      height="100"
    ></canvas>
    <canvas
      id="discrete"
      style="width: 50%; max-width: 50%"
      height="100"
    ></canvas>
  </div>
</template>

<style scoped></style>
