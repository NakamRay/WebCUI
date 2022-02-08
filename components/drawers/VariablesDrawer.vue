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
    <v-dialog
      v-model="addVarDialog"
      max-width="600px"
    >
      <v-card>
        <v-card-title>
          <span class="text-h5">Define a variable</span>
        </v-card-title>
        <v-card-text>
          <v-container>
            <v-row>
              <v-col
                cols="12"
                md="4"
              >
                <v-text-field
                  v-model="varName"
                  label="Variable Name"
                  required
                  prefix="${"
                  suffix="}"
                ></v-text-field>
              </v-col>
              <v-col
                cols="12"
                md="8"
              >
                <v-text-field
                  v-model="varValue"
                  label="Value"
                  required
                ></v-text-field>
              </v-col>
            </v-row>
          </v-container>
        </v-card-text>
        <v-card-actions>
          <v-spacer></v-spacer>
          <v-btn
            :disabled="!varName || !varValue"
            color="blue darken-1"
            text
            @click="
              updateVariables({ [varName.replaceAll('$', '')]: varValue });
              addVarDialog = false;
            "
          >
            {{ variables.hasOwnProperty(varName.replaceAll('$', '')) ? 'UPDATE' : 'ADD' }}
          </v-btn>
          <v-btn
            color="blue darken-1"
            text
            @click="addVarDialog = false"
          >
            Close
          </v-btn>
        </v-card-actions>
      </v-card>
    </v-dialog>

    <template v-slot:prepend>
      <v-toolbar height="50px">
        <v-toolbar-title>Variables</v-toolbar-title>
        <v-spacer></v-spacer>
        <v-btn icon @click.stop="
          varName = '';
          varValue = '';
          addVarDialog = true;
        ">
          <v-icon>mdi-plus</v-icon>
        </v-btn>
        <v-btn icon @click.stop="closeDrawers()">
          <v-icon>mdi-close</v-icon>
        </v-btn>
      </v-toolbar>
    </template>

    <v-list class="py-0">
      <div
        v-for="(variable, key) in variables"
        :key="key"
      >
        <v-list-item
          style="height: 50px"
          class="px-3"
        >
          <v-list-item-title>
            {{ `\$\{${key}\}` }} = {{ variable }}
          </v-list-item-title>

          <v-spacer></v-spacer>

          <v-list-item-action>
            <v-btn
              icon
              @click="
                varName = key.replaceAll('$', '');
                varValue = variable;
                addVarDialog = true;
                $forceUpdate();
              "
            >
              <v-icon>mdi-pencil</v-icon>
            </v-btn>
          </v-list-item-action>

          <v-list-item-action>
            <v-btn
              icon
              @click="
                $store.commit('deleteVariables', key);
                $forceUpdate();
              "
            >
              <v-icon>mdi-delete</v-icon>
            </v-btn>
          </v-list-item-action>
        </v-list-item>
        <v-divider></v-divider>
      </div>
    </v-list>
  </v-navigation-drawer>
</template>

<script>
import { mapState, mapMutations } from "vuex"
import { config } from '~/assets/config.js'

export default {
  data: () => ({
    key: "variables",
    config,
    addVarDialog: false,
    varName: "",
    varValue: ""
  }),
  computed: {
    ...mapState(["variables"]),
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
  methods: mapMutations(["openDrawer", "closeDrawers", "updateVariables", "deleteVariables"])
}
</script>
