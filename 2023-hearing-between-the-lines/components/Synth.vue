<script setup lang="ts">
import { Chart } from "chart.js/auto";
import { ref } from "vue";

let isRecordingRef = ref(false);

function startRecording() {
  const audioContext = new (window.AudioContext || window.webkitAudioContext)();

  const analyzer = audioContext.createAnalyser();
  analyzer.fftSize = 1024;
  const bufferLength = analyzer.frequencyBinCount;
  const dataArray = new Float32Array(bufferLength);

  const bandpassFilter = audioContext.createBiquadFilter();
  bandpassFilter.type = "bandpass";
  bandpassFilter.frequency.value = 1500;
  bandpassFilter.Q.value = 1;

  navigator.mediaDevices
    .getUserMedia({ audio: true })
    .then((stream) => {
      const source = audioContext.createMediaStreamSource(stream);
      source.connect(bandpassFilter);
      bandpassFilter.connect(analyzer);
      isRecordingRef.value = true;
      draw();
    })
    .catch((err) => {
      console.error("Error accessing the microphone:", err);
    });

  const canvas = document.getElementById("myChart")! as HTMLCanvasElement;
  const ctx = canvas.getContext("2d")!;
  const data = {
    labels: Array.from(
      { length: bufferLength },
      (_, i) => (i * audioContext.sampleRate) / analyzer.fftSize
    ),
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
  const myChart = new Chart(ctx, {
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

  function detectPeaks(dataArray) {
    // This is a simple peak detection algorithm.
    // You might want to use a more sophisticated approach for better accuracy.
    const threshold = -50; // dB
    const peaks: number[] = [];
    for (let i = 1; i < dataArray.length - 1; i++) {
      if (
        dataArray[i] > threshold &&
        dataArray[i] > dataArray[i - 1] &&
        dataArray[i] > dataArray[i + 1]
      ) {
        peaks.push(i);
      }
    }
    return peaks;
  }

  function draw() {
    if (!isRecordingRef.value) {
      return;
    }

    requestAnimationFrame(draw);

    analyzer.getFloatFrequencyData(dataArray);

    const peaks = detectPeaks(dataArray);

    // Highlight the peaks (formants) on the chart
    for (let i = 0; i < bufferLength; i++) {
      data.datasets[0].data[i] = dataArray[i];
      if (peaks.includes(i)) {
        data.datasets[0].pointBackgroundColor[i] = "red";
      } else {
        data.datasets[0].pointBackgroundColor[i] = "transparent";
      }
    }

    myChart.update();
  }
}

function stopRecording() {
  isRecordingRef.value = false;
}
</script>

<template>
  <canvas id="myChart" width="400" height="200"></canvas>
  <div class="flex gap-4 absolute bottom-10 right-10">
    <button v-on:click="startRecording()" v-if="!isRecordingRef">Start</button>
    <button v-on:click="stopRecording()" v-if="isRecordingRef">Stop</button>
  </div>
</template>
