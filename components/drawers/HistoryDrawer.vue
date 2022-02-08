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
        <v-toolbar-title>History</v-toolbar-title>
        <v-spacer></v-spacer>
        <v-btn icon @click.stop="clearHistory()">
          <v-icon>mdi-delete</v-icon>
        </v-btn>
        <v-btn icon @click.stop="closeDrawers()">
          <v-icon>mdi-close</v-icon>
        </v-btn>
      </v-toolbar>
    </template>

    <v-list
      v-for="(data, index) in history"
      :key="index"
      class="pt-3 pb-0"
    >
        <v-list-item
          v-for="(text, index) in data.history"
          :key="index"
        >
          <v-list-item-content class="py-0">
            <v-list-item-title class="drawer-text text-wrap" v-if="text.text" v-text="text.text"></v-list-item-title>
            <v-list-item-title class="drawer-text text-wrap" v-if="text.html" v-html="text.html"></v-list-item-title>
          </v-list-item-content>
        </v-list-item>
        <v-list-item>
          <v-list-item-subtitle v-text="'Cleared at ' + data.date"></v-list-item-subtitle>
          <v-list-item-action class="my-0">
            <v-btn icon @click.stop="saveHistory(data)">
              <v-icon small color="grey lighten-1">mdi-content-save</v-icon>
            </v-btn>
          </v-list-item-action>
        </v-list-item>
      <v-divider></v-divider>
    </v-list>
  </v-navigation-drawer>
</template>

<script>
import { mapState, mapMutations, mapActions } from "vuex"
import { config } from '~/assets/config.js'

export default {
  data: () => ({
    key: "history",
    config
  }),
  computed: {
    ...mapState(["history"]),
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
    ...mapMutations(["clearHistory", "openDrawer", "closeDrawers"]),
    ...mapActions(["saveHistory"]),
  }
}
</script>

<style scoped>
.v-list-item {
  min-height: 25px;
}
</style>
