<template>
  <v-container :fluid="!$vuetify.breakpoint.xl">
    <!-- Drawers -->
    <div v-for="(tool, key) in toolbar" :key="key">
      <component v-if="tool.hasOwnProperty('drawer')" :is="tool.component" />
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
    config,
    cancelToken: axios.CancelToken.source()
  }),
  computed: {
    ...mapState(['params', 'console', 'toolbar', 'variables', 'waiting']),
    ...mapGetters(['emptyRepuiredParamExists', 'substitution', 'request']),
  },
  methods: {
    ...mapMutations(['initConsole', 'addLine', 'setFiles', 'openDrawer', 'setWaiting']),
    ...mapActions(['initState', 'clear', 'displayExceptionMsg']),

    // Change this according to the tools of toolbar.
    toolbarEvent(key) {
      if (key === 'clear') {
        this.clear()
      } else if (this.toolbar[key].hasOwnProperty('drawer')) {
        this.openDrawer(key)
      } else if (key === 'sendReq') {
        if (this.waiting) {
          this.cancelToken.cancel('Canceled by the user.')
          this.cancelToken = axios.CancelToken.source()
        } else {
          this.sendReq()
        }
      }
    },
    sendReq() {
      let webcui = this

      webcui.setWaiting(true)

      this.toolbar['sendReq'].before(webcui)

      axios.post(
        `${this.config.baseUrl}/${this.config.apiFileName}`,
        this.request,
        { cancelToken: this.cancelToken.token }
      )
        .then(function (response) {
          let result = response.data
          webcui.toolbar['sendReq'].after(webcui, result)
        })
        .catch(function (err) {
          if (axios.isCancel(err)) {
            webcui.displayExceptionMsg('cancel')
          } else {
            webcui.displayExceptionMsg('connection')
            console.error(err)
          }
        })
        .finally(function (err) {
          webcui.setWaiting(false)
        })
    }
  },
  mounted() {
    // Preprocessing
    this.initState()

    if (this.toolbar.hasOwnProperty('files')) {
      let vue = this

      axios
      .post(this.config.baseUrl + '/' + 'files.php')
      .then(function (response) {
        let result = response.data
        vue.setFiles(result)
      })
      .catch(function (err) {
        vue.displayConnectionErrorMsg()
        console.error(err)
      })
    }

    // Assigning hotkeys
    document.addEventListener('keydown', (event) => {
      if (event.ctrlKey && event.key === 'Enter' && !this.emptyRepuiredParamExists && !this.waiting) {
        this.sendReq()
      }
    })
  }
}
</script>
