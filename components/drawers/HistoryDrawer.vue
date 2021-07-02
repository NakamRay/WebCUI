<template>
  <v-navigation-drawer
    v-model="drawer"
    disable-resize-watcher
    temporary
    app
    right
    width="500"
    class="dark-drawer"
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
      v-for="(ahistory, index) in history"
      :key="index"
      class="py-0"
    >
      <div class="py-3">
        <v-list-item
          v-for="(text, index) in ahistory"
          :key="index"
          style="min-height: 25px"
        >
          <v-list-item-title>
            <span class="drawer-text text-wrap" v-if="text.text" v-text="text.text"></span>
            <span class="drawer-text text-wrap" v-if="text.html" v-html="text.html"></span>
          </v-list-item-title>
        </v-list-item>
      </div>
      <v-divider></v-divider>
    </v-list>
  </v-navigation-drawer>
</template>

<script>
import { mapState, mapMutations } from "vuex";

export default {
  data: () => ({
    key: "history"
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
  methods: mapMutations(["clearHistory", "openDrawer", "closeDrawers"])
}
</script>
