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
          <v-card
            id="paramsCard"
            class="mb-3 dark-card-borders"
            style="overflow: auto"
          >
            <v-list-item class="pr-4 py-2">
              <v-list-item-content>
                <v-row>
                  <v-col
                    v-for="(param, key) in params"
                    :key="key"
                    :cols="param.half ? 6 : 12"
                    class="py-1"
                  >
                    <v-text-field
                      v-if="param.visible"
                      :label="param.display"
                      :value="param.value"
                      @input="
                        (value) => updateParamValue({ key: key, value: value })
                      "
                      spellcheck="false"
                      hide-details
                      flat
                    ></v-text-field>
                  </v-col>
                </v-row>
              </v-list-item-content>
            </v-list-item>
          </v-card>

          <v-card
            id="outputConsole"
            :height="consoleHeight"
            style="overflow: auto"
            class="dark-card-borders"
          >
            <v-list class="py-3">
              <v-list-item
                style="min-height: 25px; color: white"
                v-for="(output, index) in console"
                :key="index"
              >
                <v-list-item-title>
                  <span class="drawer-text" v-html="output.text"></span>
                </v-list-item-title>
              </v-list-item>
            </v-list>
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
    envHeight: 0,
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
      let request = new URLSearchParams()

      for (var param in this.params) {
        let value = this.substitution(this.params[param].value)
        request.append(param, value)
        console.log(param + ": " + value)
      }

      var vm = this

      axios.post(this.appInfo.baseUrl + this.appInfo.apiFile, request)
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
    }
  },
  created() {
    this.preprocess()
    this.initConsole()
  },
  mounted() {
    this.envHeight = this.$el.querySelector("#paramsCard").clientHeight

    const updateConsoleHeight = () => {
      this.consoleHeight = window.innerHeight - this.envHeight - 100
    }

    updateConsoleHeight()

    window.addEventListener("resize", updateConsoleHeight)
    document.addEventListener('keydown', (event) => {
      if (event.ctrlKey && event.key === 'Enter') {
        this.sendReq()
      }
    });
  },

}
</script>

<style src="~/assets/styles.css"/>
