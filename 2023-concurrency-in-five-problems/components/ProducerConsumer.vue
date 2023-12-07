<script setup lang="ts">
import VueMermaidString from 'vue-mermaid-string';

const diagram = `
  flowchart LR
    A[Producer] -->|produce item| B{Buffer Full?}
    B -- No --> C[Add item to buffer]
    C --> D{Buffer Empty?}
    D -- No --> E[Consumer]
    D -- Yes --> D
    B -- Yes --> B
    E -->|consume item| D
  `

</script>
<template>
  <vue-mermaid-string :value="diagram" />
</template>