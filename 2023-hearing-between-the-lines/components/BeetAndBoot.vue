<script setup lang="ts">
import { Chart } from "chart.js/auto";
import { ref } from "vue";

const props = defineProps({ showUnknown: Boolean });

let isStartedRef = ref(false);

function start() {
  isStartedRef.value = true;

  var ctx = (
    document.getElementById(
      "beet-and-boot-" + props.showUnknown.toString()
    ) as HTMLCanvasElement
  ).getContext("2d")!;

  var chart = new Chart(ctx, {
    type: "scatter",
    data: {
      datasets: [
        {
          label: "Beet",
          data: [{ x: 190, y: 2165, label: "beet" }],
          pointRadius: 5,
        },
        {
          label: "Boot",
          data: [{ x: 289, y: 1301, label: "boot" }],
          pointRadius: 5,
        },

        ...(props.showUnknown
          ? [
              {
                label: "Unknown",
                data: [{ x: 285, y: 1380, label: "Unknown" }],
                pointRadius: 5,
              },
            ]
          : []),
      ],
    },
    options: {
      scales: {
        x: {
          beginAtZero: false,
          min: 100,
          max: 350,
        },
        y: {
          beginAtZero: false,
          min: 1000,
          max: 2500,
        },
      },
      plugins: {
        // legend: { display: false },
        tooltip: {
          callbacks: {
            label: function (context) {
              return (
                context.raw.label +
                ": (" +
                context.raw.x +
                ", " +
                context.raw.y +
                ")"
              );
            },
          },
        },
      },
    },
  });

  chart.update();
}
</script>

<template>
  <div>
    <Button v-on:click="start()" v-if="!isStartedRef">Start</Button>
  </div>

  <div class="flex">
    <canvas
      :id="'beet-and-boot-' + showUnknown.toString()"
      style="width: 100%; max-width: 100%"
      height="400"
    ></canvas>
  </div>
</template>
