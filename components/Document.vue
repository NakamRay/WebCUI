<template>
  <v-dialog v-model="documentDialog" fullscreen persistent transition="dialog-bottom-transition">
    <v-card>
      <v-toolbar height="50px">
        <v-toolbar-title>Document</v-toolbar-title>
        
        <v-spacer></v-spacer>

        <v-btn icon @click="$store.commit('switchDocumentDialog')">
          <v-icon>mdi-close</v-icon>
        </v-btn>
      </v-toolbar>
      
      <v-tabs
        :vertical="$vuetify.breakpoint.smAndUp"
        color="dark"
      >
        <v-tab v-for="(document, index) in documents" :key="index">
          {{ document.title }}
        </v-tab>

        <v-tab-item v-for="(document, index) in documents" :key="index">
          <v-card
            class="pa-5"
            style="overflow-y: auto;"
            :height='windowHeight'
            flat
          >
          <component :is="document.body" />
          </v-card>
        </v-tab-item>
      </v-tabs>
    </v-card>
  </v-dialog>
</template>

<script>
import { mapState } from 'vuex';

import { documents } from '~/assets/documents.js'

export default {
  data: () => ({
    windowHeight: 0,
    documents
  }),
  computed: {
    ...mapState(['documentDialog']),
  },
  methods: {
    updateDialogHeight () {
      var tabsHeight = this.$vuetify.breakpoint.smAndUp ? 0 : 48
      this.windowHeight = window.innerHeight - tabsHeight - 50
    }
  },
  mounted () {
    this.updateDialogHeight()
    window.addEventListener('resize', this.updateDialogHeight)
  }
}
</script>
