<template>
  <v-container fluid>
    <!-- Drawers -->
    <HistoryDrawer />
    <ExamplesDrawer />
    <VariablesDrawer />

    <!-- Floating Action Button -->
    <Fab @drawer-event="drawerEvent" />

    <v-main>
      <v-row>
        <v-col cols="12" sm="10" offset-sm="1" class="pa-0">
          <v-card
            id="paramsCard"
            class="mb-3 dark-card-borders"
            style="overflow: auto"
          >
            <v-list-item three-line class="pr-2">
              <v-list-item-content class="pt-0 pb-2">
                <v-row>
                  <v-col
                    v-for="(param, key) in params"
                    :key="key"
                    :cols="param.half ? 6 : 12"
                    class="py-0"
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
          <Features @drawer-event="drawerEvent" />
        </v-col>
      </v-row>
    </v-main>
  </v-container>
</template>

<script>
import axios from "axios"
import { mapState, mapMutations, mapActions, mapGetters } from "vuex"

import { messages } from "~/assets/configs.js"

import HistoryDrawer from "~/components/drawers/HistoryDrawer.vue"
import ExamplesDrawer from "~/components/drawers/ExamplesDrawer.vue"
import VariablesDrawer from "~/components/drawers/VariablesDrawer.vue"
import Features from "~/components/Features.vue"
import Fab from "~/components/Fab.vue"

export default {
  components: {
    HistoryDrawer,
    ExamplesDrawer,
    VariablesDrawer,
    Features,
    Fab,
  },
  data: () => ({
    // for axios
    baseUrl: "http://localhost/",
    apiFile: "sample-api.php",

    // for console
    messages,

    // for layouts
    envHeight: 0,
    consoleHeight: 0,
  }),
  computed: {
    ...mapState(["params", "console", "features", "history", "variables"]),
    ...mapGetters([
      "allVariables",
      "hasVariable",
      "hasInvalidVariable",
      "substitution",
    ]),
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
      "init",
      "updateParamValue",
      "initConsole",
      "addLine",
      "addHistory",
      "updateVariables",
      "deleteVariables",
      "openDrawer",
      "closeDrawers",
    ]),
    ...mapActions(["clear", "showVariables"]),
    calc() {
      if (!this.params.formula.value) {
        this.addLine({ text: "Value of Formula is invalid." })
        return
      }

      if (this.hasVariable(this.params.formula.value)) {
        this.updateParamValue({
          key: "formula",
          value: this.substitution(this.params.formula.value),
        });
      }

      this.sendReq()
    },
    sendReq() {
      let request = new URLSearchParams()

      for (var param in this.params) {
        request.append(param, this.params[param].value)
        console.log(param + ": " + this.params[param].value)
      }

      var vm = this

      axios
        .post(this.baseUrl + this.apiFile, request)
        .then(function (response) {
          var result = response.data

          vm.updateParamValue({ key: "total", value: parseInt(vm.params.total.value) + parseInt(result) })
          vm.updateParamValue({ key: "result", value: result })

          vm.addLine([
            { text: "<br>" },
            { text: `> ${vm.params.formula.value}` },
            { text: result },
          ])
        })
        .catch(function (err) {
          vm.addLine({ text: vm.messages.connectionErrorMessage })
          console.error(err)
        })
    },
    drawerEvent(key) {
      if (key === "clear") {
        this.clear()
      } else if (this.features[key].hasOwnProperty("drawer")) {
        this.openDrawer(key)
      } else {
        this.calc()
      }
    },
    updateConsoleHeight() {
      this.consoleHeight = window.innerHeight - this.envHeight - 100
    },
  },
  created() {
    this.init()
    this.addLine({ text: this.messages.initialMessage })
  },
  mounted() {
    this.envHeight = this.$el.querySelector("#paramsCard").clientHeight
    window.addEventListener("resize", this.updateConsoleHeight)
    this.updateConsoleHeight()
  },
  destroyed() {
    window.removeEventListener("resize", this.updateConsoleHeight)
  },
}
</script>

<style src="~/assets/styles.css"/>
