<template>
  <button
    class="px-3 py-1 rounded-lg shadow-sm bg-neutral-100 hover:bg-neutral-200 text-neutral-600"
    @click="onClick"
  >
    <slot></slot>
  </button>
</template>

<script>
export default {
  name: "SecondaryButton",
  props: {
    onClick: {
      type: Function,
      default: () => {},
    },
  },
};
</script>
