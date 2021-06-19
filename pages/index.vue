<template>
  <v-container :fluid="!$vuetify.breakpoint.xl">
    <!-- Drawers -->
    <HistoryDrawer />
    <ExamplesDrawer />
    <VariablesDrawer />

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

import { appInfo, messages } from '~/assets/configs.js'

export default {
  data: () => ({
    appInfo,
    messages,

    // for layouts
    formsHeight: 0,
    consoleHeight: 0,
  }),
  computed: {
    ...mapState(['params', 'console', 'toolbar', 'variables']),
    ...mapGetters(['substitution']),
  },
  methods: {
    ...mapMutations(['initConsole', 'addLine', 'openDrawer']),
    ...mapActions(['preprocess', 'clear']),

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
      let request = new URLSearchParams()

      for (var param in this.params) {
        var value = this.params[param].value
        if (this.params[param].type === 'text') {
          value = this.substitution(value)
        }
        if (this.params[param].type === 'select') {
          value = value.name
        }
        request.append(param, value)
        console.log(param + ': ' + value)
      }

      var vm = this

      axios
        .post(this.appInfo.baseUrl + this.appInfo.apiFileName, request)
        .then(function (response) {
          var result = response.data

          vm.addLine([
            { text: '<br>' },
            { text: result },
          ])
        })
        .catch(function (err) {
          vm.addLine({ text: vm.messages.connectionErrorMessage })
          console.error(err)
        })
    }
  },
  mounted() {
    this.preprocess()
    this.initConsole()

    document.addEventListener('keydown', (event) => {
      if (event.ctrlKey && event.key === 'Enter') {
        this.sendReq()
      }
    })
  },
}
</script>

<style src='~/assets/styles.css'/>
