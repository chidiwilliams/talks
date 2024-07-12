import { defineConfig } from "vite";
import Inspect from "vite-plugin-inspect";

export default defineConfig({
  plugins: [Inspect()],
  slidev: {
    components: {
      dts: false,
    },
  },
  resolve: {
    alias: {},
  },
  server: {
    fs: {
      allow: [".."],
    },
  },
});
