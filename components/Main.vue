<template>
  <div>
    <v-card
      ref="forms"
      class="mb-3 dark-card-borders"
    >
      <v-list-item class="px-2 py-2">
        <v-list-item-content>
          <v-row class="px-3">
            <v-col
              v-for="(param, key) in params"
              :key="key"
              :sm="
                !param.hasOwnProperty('size') ?
                  12 :
                param.size === 'half' ?
                  6 :
                param.size === 'quarter' ?
                  3 : 12
              "
              cols="12"
              class="py-1"
            >
              <v-text-field
                v-if="param.visible && param.type === 'text'"
                :label="param.display"
                :value="param.value"
                @input="(value) => updateParamValue({ key: key, value: value })"
                spellcheck="false"
                hide-details
              ></v-text-field>
              <v-select
                v-if="param.visible && param.type === 'select'"
                :label="param.display"
                :value="param.value"
                :items="param.items"
                item-text="display"
                item-value="name"
                @change="(value) => updateParamValue({ key: key, value: value })"
                return-object
                hide-details
              >
              </v-select>
              <v-switch
                v-if="param.visible && param.type === 'switch'"
                :label="param.display"
                :input-value="param.value"
                @change="(value) => updateParamValue({ key: key, value: value })"
                hide-details
              ></v-switch>
              <v-checkbox
                v-if="param.visible && param.type === 'check'"
                :label="param.display"
                :input-value="param.value"
                @change="(value) => updateParamValue({ key: key, value: value })"
                hide-details
              ></v-checkbox>
            </v-col>
          </v-row>
        </v-list-item-content>
      </v-list-item>
    </v-card>

    <v-card
      ref="outputConsole"
      id="outputConsole"
      :height="$vuetify.breakpoint.xs ? '80vh' : consoleHeight"
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
            <span class="drawer-text" v-if="appInfo.htmlConsole" v-html="output.text"></span>
            <span class="drawer-text" v-else v-text="output.text"></span>
          </v-list-item-title>
        </v-list-item>
      </v-list>
    </v-card>

    <div v-if="$vuetify.breakpoint.xs" class="py-5"></div>
  </div>
</template>

<script>
import { mapState, mapMutations } from 'vuex'

import { appInfo } from '~/assets/configs.js'

export default {
  data: () => ({
    appInfo,
    formsHeight: 0,
    consoleHeight: 0,
  }),
  computed: mapState(['params', 'console']),
  watch: {
    // scroll the console to bottom when it changes
    console: function () {
      this.$nextTick(function () {
        var outputConsole = this.$refs.outputConsole.$refs.link
        outputConsole.scrollTop = outputConsole.scrollHeight
      })
    }
  },
  methods: {
    ...mapMutations(['updateParamValue']),
    updateConsoleHeight() {
      this.formsHeight = this.$refs.forms.$refs.link.clientHeight
      this.consoleHeight = window.innerHeight - this.formsHeight - 90
    }
  },
  mounted() {
    this.updateConsoleHeight()
    window.addEventListener('resize', this.updateConsoleHeight)
  }
}
</script>
