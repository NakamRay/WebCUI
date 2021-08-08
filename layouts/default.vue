<template>
  <v-app>
    <v-app-bar
      app
      height="50px"
    >
      <div class="d-flex align-center">
        <v-img
          v-if="config.logo.icon"
          alt="Logo Icon"
          class="shrink mx-2"
          contain
          :src="config.logo.icon"
          transition="scale-transition"
          width="30"
        />

        <v-img
          v-if="config.logo.text"
          alt="Logo Text"
          class="shrink hidden-sm-and-down"
          contain
          :src="config.logo.text"
          height="40"
          width="200"
        />
        <span v-else>{{ config.name }}</span>
      </div>

      <v-spacer></v-spacer>

      <v-btn
        rounded
        outlined
        style="border-width: medium;"
        @click="$store.commit('switchDocumentDialog')"
      >
        Document
      </v-btn>

      <Document />
    </v-app-bar>

    <div style="height: 20px;" />

    <nuxt />
  </v-app>
</template>

<script>
import Document from '~/components/Document.vue'
import { config } from '~/assets/config.js'

export default {
  components: {
    Document
  },
  data: () => ({
    config
  })
}
</script>
