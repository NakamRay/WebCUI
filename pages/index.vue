<template>
  <v-container fluid>
    <!-- Drawers -->
    <HistoryDrawer />
    <ExamplesDrawer />
    <VariablesDrawer />

    <!-- Floating Action Button -->
    <Fab @feature-event="featureEvent" />

    <v-main>
      <v-row>
        <v-col cols="12" sm="10" offset-sm="1" class="pa-0">
          <div ref="forms">
            <Forms />
          </div>

          <v-card
            id="outputConsole"
            :height="consoleHeight"
            style="overflow: auto"
            class="dark-card-borders"
          >
            <Console />
          </v-card>
        </v-col>

        <v-col cols="1" class="text-center pl-0 d-none d-sm-flex">
          <Features @feature-event="featureEvent" />
        </v-col>
      </v-row>
    </v-main>
  </v-container>
</template>

<script>
import axios from "axios"
import { mapState, mapMutations, mapActions, mapGetters } from "vuex"

import { appInfo, messages } from "~/assets/configs.js"

export default {
  data: () => ({
    appInfo,
    messages,

    // for layouts
    formsHeight: 0,
    consoleHeight: 0,
  }),
  computed: {
    ...mapState(["params", "console", "features", "history", "variables"]),
    ...mapGetters(["allVariables", "substitution"]),
  },
  watch: {
    // scroll the console to bottom when it changes
    console: function () {
      this.$nextTick(function () {
        var outputWindow = this.$el.querySelector("#outputConsole")
        outputWindow.scrollTop = outputWindow.scrollHeight
      })
    },
  },
  methods: {
    ...mapMutations([
      "preprocess",
      "updateParamValue",
      "initConsole",
      "addLine",
      "openDrawer",
    ]),
    ...mapActions(["clear"]),

    featureEvent(key) {
      if (key === "clear") {
        this.clear()
      } else if (this.features[key].type === 'drawer') {
        this.openDrawer(key)
      } else {
        this.sendReq()
      }
    },
    sendReq() {
      console.log(this.params)

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
        console.log(param + ": " + value)
      }

      var vm = this

      axios
        .post(this.appInfo.baseUrl + this.appInfo.apiFile, request)
        .then(function (response) {
          var result = response.data

          vm.addLine([
            { text: "<br>" },
            { text: result },
          ])
        })
        .catch(function (err) {
          vm.addLine({ text: vm.messages.connectionErrorMessage })
          console.error(err)
        })
    },

    // For layout adjustment
    updateConsoleHeight() {
      this.consoleHeight = window.innerHeight - this.formsHeight - 90
    }
  },
  mounted() {
    this.preprocess()
    this.initConsole()

    this.updateConsoleHeight()
    
    window.addEventListener("resize", this.updateConsoleHeight)
    document.addEventListener('keydown', (event) => {
      if (event.ctrlKey && event.key === 'Enter') {
        this.sendReq()
      }
    })
  },
  beforeUpdate() {
    this.formsHeight = this.$refs.forms.clientHeight
    this.updateConsoleHeight()
  }
}
</script>

<style src="~/assets/styles.css"/>
