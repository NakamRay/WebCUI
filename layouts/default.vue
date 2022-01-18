<template>
  <v-app>
    <v-app-bar
      app
      height="50px"
    >
      <v-app-bar-nav-icon
        v-if="config.logo"
        class="ml-1"
        disabled
      >
        <v-img
          alt="Logo Icon"
          class="shrink"
          contain
          :src="config.logo"
          transition="scale-transition"
          height="40"
        />
      </v-app-bar-nav-icon>

      <v-toolbar-title>{{ config.name }}</v-toolbar-title>

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
