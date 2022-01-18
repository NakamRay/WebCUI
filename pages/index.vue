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
          <Main @console-click-event="consoleClickEvent"/>
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
    ...mapMutations([
      'clearConsole', 'initConsole', 'addLine',
      'updateParam', 'setFiles', 'openDrawer', 'setWaiting',
      'falseClickableAll']),
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
          this.sendReq(
            this.toolbar['sendReq'].before,
            this.toolbar['sendReq'].after
          )
        }
      } else if (this.toolbar[key].hasOwnProperty('method')) {
        this.toolbar[key].method(this)
      }
    },
    sendReq(before, after) {
      let webcui = this

      webcui.setWaiting(true)

      if (before !== undefined && before !== null) {
        before(webcui)
      }

      axios.post(
        this.config.webApiUrl,
        this.request,
        { cancelToken: this.cancelToken.token }
      )
        .then(function (response) {
          let result = response.data

          if (after !== undefined && after !== null) {
            after(webcui, result)
          }
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
    },
    consoleClickEvent(output) {
      if (output.hasOwnProperty('clickEvent')) {
        output.clickEvent(this, output)
      }
    }
  },
  mounted() {
    // Preprocessing
    this.initState()

    let webcui = this

    if (this.toolbar.hasOwnProperty('files')) {
      axios
      .post(this.config.features.files.webApiUrl)
      .then(function (response) {
        let result = response.data
        webcui.setFiles(result)
      })
      .catch(function (err) {
        webcui.displayExceptionMsg('connection')
        console.error(err)
      })
    }

    if(this.config.hasOwnProperty('preprocessing')) {
      this.config.preprocessing(webcui)
    }

    // Assigning hotkeys
    // document.addEventListener('keydown', (event) => {
    //   if (event.ctrlKey && event.key === 'Enter' && !this.emptyRepuiredParamExists && !this.waiting) {
    //     this.sendReq()
    //   }
    // })
  }
}
</script>
