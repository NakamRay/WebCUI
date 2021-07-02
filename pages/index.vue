<template>
  <v-container :fluid="!$vuetify.breakpoint.xl">
    <!-- Drawers -->
    <div v-for="(tool, key) in toolbar" :key="key">
      <component v-if="tool.type === 'drawer'" :is="tool.component" />
    </div>

    <!-- Floating Action Button -->
    <Fab @toolbar-event="toolbarEvent" />

    <v-main>
      <v-row>
        <v-col cols="12" sm="10" offset-sm="1" class="pa-0">
          <Main />
        </v-col>

        <v-col cols="1" class="text-center d-none d-sm-flex">
          <Toolbar @toolbar-event="toolbarEvent" />
        </v-col>
      </v-row>
    </v-main>
  </v-container>
</template>

<script>
import axios from 'axios'
import { mapState, mapMutations, mapActions, mapGetters } from 'vuex'

import { config } from '~/assets/config.js'

export default {
  data: () => ({
    config
  }),
  computed: {
    ...mapState(['params', 'console', 'toolbar', 'variables']),
    ...mapGetters(['emptyRepuiredParamExists', 'substitution', 'request']),
  },
  methods: {
    ...mapMutations(['initConsole', 'addLine', 'openDrawer']),
    ...mapActions(['initState', 'clear', 'displayConnectionErrorMsg']),

    // Change this according to the tools of toolbar.
    toolbarEvent(key) {
      if (key === 'clear') {
        this.clear()
      } else if (this.toolbar[key].type === 'drawer') {
        this.openDrawer(key)
      } else if (key === 'sendReq') {
        this.sendReq()
      }
    },
    sendReq() {
      let vue = this

      axios
        .post(this.config.baseUrl + this.config.apiFileName, this.request)
        .then(function (response) {
          // Please use 'vue' instead of 'this' in this block.

          let result = response.data
          vue.addLine([
            { text: '' },
            { text: '* Generated HTML' },
            { text: result },
            { text: '* After decoration' },
            { html: result }
          ])
        })
        .catch(function (err) {
          vue.displayConnectionErrorMsg()
          console.error(err)
        })
    }
  },
  mounted() {
    // Preprocessing
    this.initState()

    // Assigning hotkeys
    document.addEventListener('keydown', (event) => {
      if (event.ctrlKey && event.key === 'Enter' && !this.emptyRepuiredParamExists) {
        this.sendReq()
      }
    })
  }
}
</script>
