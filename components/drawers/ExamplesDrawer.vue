<template>
  <v-navigation-drawer
    v-model="drawer"
    disable-resize-watcher
    temporary
    app
    :right="config.toolbarLocation === 'right'"
    width="500"
    :class="{ 'dark-drawer' : $vuetify.theme.dark }"
  >
    <template v-slot:prepend>
      <v-toolbar height="50px">
        <v-toolbar-title>Examples</v-toolbar-title>
        <v-spacer></v-spacer>
        <v-btn icon @click.stop="closeDrawers()">
          <v-icon>mdi-close</v-icon>
        </v-btn>
      </v-toolbar>
    </template>

    <v-list class="py-0 pt-3">
      <v-tabs color="dark">
        <v-tab v-for="(example, index) in examples" :key="index">
          {{ example.display }}
        </v-tab>
        <v-tab-item v-for="(example, index) in examples" :key="index">
          <v-list-item
            style="min-height: 15px"
            v-for="(ex, index) in example.examples"
            :key="index"
            @click.stop="
              setExamples(ex);
              closeDrawers();
            "
          >
            <v-list-item-title>
              <v-alert
                class="py-1 my-1"
                color="blue"
                border="left"
                elevation="2"
                colored-border
              >
                <div v-for="(param, key) in ex" :key="key">
                  <div class="font-weight-bold caption mt-1">{{ params[key].display }}</div>
                  <span class="drawer-text">
                    {{
                      params[key].type === 'select' && (typeof param) === 'object' ?
                        param.display :
                        param
                    }}
                  </span>
                  <hr>
                </div>
              </v-alert>
            </v-list-item-title>
          </v-list-item>
        </v-tab-item>
      </v-tabs>
    </v-list>
  </v-navigation-drawer>
</template>

<script>
import { mapState, mapMutations } from "vuex"

import { config } from "~/assets/config.js"
import { examples } from "~/assets/examples.js"

export default {
  data: () => ({
    key: "examples",
    config,
    examples
  }),
  computed: {
    ...mapState(["params"]),
    drawer: {
      get() {
        return this.$store.state.toolbar[this.key].drawer
      },
      set(value) {
        if (value) {
          this.openDrawer(this.key)
        } else {
          this.closeDrawers()
        }
      }
    }
  },
  methods: {
    ...mapMutations(["updateParam", "openDrawer", "closeDrawers"]),
    setExamples(anexample) {
      Object.keys(anexample).forEach(key => {
        this.updateParam({ key: key, value: { value: anexample[key] } })
      })
    }
  }
}
</script>
