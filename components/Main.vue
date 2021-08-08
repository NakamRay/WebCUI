<template>
  <div>
    <v-row :class="{
      'd-flex flex-column-reverse' : config.consoleLocation === 'top',
      'd-flex flex-column'         : config.consoleLocation === 'bottom',
      'd-flex flex-row-reverse'    : config.consoleLocation === 'left',
      'd-flex flex-row'            : config.consoleLocation === 'right',
    }">
      <div
        class="pa-0"
        :class="{
          'mt-3'          : config.consoleLocation === 'top',
          'mb-3'          : config.consoleLocation === 'bottom',
          'col-md-6 pl-3' : config.consoleLocation === 'left',
          'col-md-6 pr-3' : config.consoleLocation === 'right',
        }"
      >
        <v-card
          ref="forms"
          :class="{ 'dark-card-borders' : $vuetify.theme.dark }"
          height="100%"
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
                      3 : !isNaN(parseInt(param.size)) ?
                      parseInt(param.size) : 12
                  "
                  cols="12"
                  :class="param.hasOwnProperty('type') ? 'py-1' : 'pa-0'"
                >
                  <v-text-field
                    v-if="param.type === 'text'"
                    :label="param.display"
                    :value="param.value"
                    @input="(value) => updateParam({ key: key, value: { value: value } })"
                    spellcheck="false"
                    hide-details
                  ></v-text-field>
                  <v-textarea
                    v-if="param.type === 'textarea'"
                    :label="param.display"
                    :value="param.value"
                    @input="(value) => updateParam({ key: key, value: { value: value } })"
                    spellcheck="false"
                    hide-details
                    :rows="param.rows"
                    outlined
                    clearable
                    no-resize
                  ></v-textarea>
                  <v-select
                    v-if="param.type === 'select' && (typeof param.items[0]) !== 'object'"
                    :label="param.display"
                    :value="param.value"
                    :items="param.items"
                    @change="(value) => updateParam({ key: key, value: { value: value } })"
                    return-object
                    hide-details
                  ></v-select>
                  <v-select
                    v-if="param.type === 'select' && (typeof param.items[0]) === 'object'"
                    :label="param.display"
                    :value="param.value"
                    :items="param.items"
                    item-text="display"
                    item-value="name"
                    @change="(value) => updateParam({ key: key, value: { value: value } })"
                    return-object
                    hide-details
                  ></v-select>
                  <v-autocomplete
                    v-if="param.type === 'autocomplete'"
                    :label="param.display"
                    :value="param.value"
                    :items="param.items"
                    item-text="display"
                    item-value="name"
                    @change="(value) => updateParam({ key: key, value: { value: value } })"
                    hide-details
                  ></v-autocomplete>
                  <v-switch
                    v-if="param.type === 'switch'"
                    :label="param.display"
                    :input-value="param.value"
                    @change="(value) => updateParam({ key: key, value: { value: value } })"
                    hide-details
                  ></v-switch>
                  <v-checkbox
                    v-if="param.type === 'check'"
                    :label="param.display"
                    :input-value="param.value"
                    @change="(value) => updateParam({ key: key, value: { value: value } })"
                    hide-details
                  ></v-checkbox>
                  <v-file-input
                    v-if="param.type === 'file'"
                    :label="param.display"
                    :input-value="param.value"
                    @change="(value) => fileChange(param, key, value)"
                    hide-details
                    outlined
                    dense
                  ></v-file-input>
                </v-col>
              </v-row>
            </v-list-item-content>
          </v-list-item>
        </v-card>
      </div>

      <v-card
        ref="outputConsole"
        id="outputConsole"
        :height="$vuetify.breakpoint.xs ? '80vh' : consoleHeight"
        style="overflow: auto"
        :class="{
          'col-md-6' : config.consoleLocation === 'left' || config.consoleLocation === 'right',
          'dark-card-borders' : $vuetify.theme.dark
        }"
      >
        <v-list class="py-3">
          <v-list-item
            style="min-height: 25px; color: white"
            v-for="(output, index) in console"
            :key="index"
          >
            <v-list-item-title>
              <span
                class="drawer-text text-wrap"
                :class="{ 'black--text' : !$vuetify.theme.dark }"
                v-if="output.text"
                v-text="output.text" />
              <span
                class="drawer-text text-wrap"
                :class="{ 'black--text' : !$vuetify.theme.dark }"
                v-if="output.html"
                v-html="output.html" />
            </v-list-item-title>
          </v-list-item>
        </v-list>
      </v-card>
    </v-row>
    <div v-if="$vuetify.breakpoint.xs" class="py-12"></div>
  </div>
</template>

<script>
import { mapState, mapMutations, mapActions } from 'vuex'

import { config } from '~/assets/config.js'

export default {
  data: () => ({
    config,
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
    ...mapMutations(['updateParam']),
    ...mapActions(['displayReadErrorMsg']),
    fileChange(param, key, value) {
      const reader = new FileReader()
      let vue = this
      reader.onload = function(e){
        if (param.target) {
          vue.updateParam({ key: param.target, value: { value: reader.result } })
        } else {
          vue.updateParam({ key: key, value: { value: reader.result } })
        }
			}
      if (value && value.size <= 10000) {
        reader.readAsText(value)
      } else {
        this.displayReadErrorMsg()
      }
    },
    updateConsoleHeight() {
      if (this.config.consoleLocation === 'top' || this.config.consoleLocation === 'bottom') {
        this.formsHeight = this.$refs.forms.$refs.link.clientHeight
        this.consoleHeight = window.innerHeight - this.formsHeight - 90
      } else {
        this.formsHeight = window.innerHeight - 90
        this.consoleHeight = window.innerHeight - 80
      }

    }
  },
  mounted() {
    this.updateConsoleHeight()
    window.addEventListener('resize', this.updateConsoleHeight)
  }
}
</script>
