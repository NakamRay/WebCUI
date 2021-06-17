<template>
  <v-app dark>
    <v-app-bar
      app
      height="50px"
    >
      <div class="d-flex align-center">
        <v-img
          v-if="logo.icon"
          alt="Logo Icon"
          class="shrink mx-2"
          contain
          :src="logo.icon"
          transition="scale-transition"
          width="30"
        />

        <v-img
          v-if="logo.text"
          alt="Logo Text"
          class="shrink hidden-sm-and-down"
          contain
          :src="logo.text"
          height="40"
          width="200"
        />
        <span v-else>{{ name }}</span>
      </div>

      <v-spacer></v-spacer>

      <v-btn
        rounded
        outlined
        style="border-width: medium;"
        @click="$store.commit('switchUsageDialog')"
      >
        Usage
      </v-btn>

      <Usage />
    </v-app-bar>

    <div style="height: 10px;" />

    <nuxt />
  </v-app>
</template>

<script>
import Usage from '~/components/Usage.vue'
import { name, logo } from '~/assets/configs.js'

export default {
  components: {
    Usage
  },
  data: () => ({
    name,
    logo
  })
}
</script>
