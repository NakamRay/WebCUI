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
        <v-toolbar-title>Empty</v-toolbar-title>
        <v-spacer></v-spacer>
        <v-btn icon @click.stop="closeDrawers()">
          <v-icon>mdi-close</v-icon>
        </v-btn>
      </v-toolbar>
    </template>

    <!-- Add code here -->

  </v-navigation-drawer>
</template>

<script>
import { mapState, mapMutations } from "vuex";

export default {
  data: () => ({
    key: "empty"
  }),
  computed: {
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
  methods: mapMutations(["openDrawer", "closeDrawers"])
}
</script>
