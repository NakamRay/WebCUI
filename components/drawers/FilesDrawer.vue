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
        <v-toolbar-title>Files</v-toolbar-title>
        <v-spacer></v-spacer>
        <v-btn icon @click.stop="closeDrawers()">
          <v-icon>mdi-close</v-icon>
        </v-btn>
      </v-toolbar>
    </template>

    <v-list class="py-0">
      <v-tabs color="dark">
        <v-tab v-for="(file, index) in files" :key="index">
          {{ file.display }}
        </v-tab>
        <v-tab-item v-for="(file, index) in files" :key="index">
          <v-list-item
            style="min-height: 15px"
            v-for="(path, index) in file.files"
            :key="index"
            @click.stop="
              setFileData(file.name, path);
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
                {{ path.replace(file.dir + '/', '') }}
              </v-alert>
            </v-list-item-title>
          </v-list-item>
        </v-tab-item>
      </v-tabs>
    </v-list>

  </v-navigation-drawer>
</template>

<script>
import axios from 'axios'
import { mapState, mapMutations, mapActions } from "vuex"

import { config } from '~/assets/config.js'

export default {
  data: () => ({
    key: "files",
    config
  }),
  computed: {
    ...mapState(["files"]),
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
    ...mapActions(['displayConnectionErrorMsg']),

    setFileData(name, path) {
      let request = new URLSearchParams()
      request.append('path', path)

      let vue = this

      axios
      .post(this.config.features.files.webApiUrl, request)
      .then(function (response) {
        let result = response.data
        vue.updateParam({ key: name, value: { value: result } })
      })
      .catch(function (err) {
        vue.displayConnectionErrorMsg()
        console.error(err)
      })

    }
  }
}
</script>
