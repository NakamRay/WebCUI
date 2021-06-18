<template>
  <v-card
    class="mb-3 dark-card-borders"
    style="overflow: auto"
  >
    <v-list-item class="px-2 py-2">
      <v-list-item-content>
        <v-row class="px-3">
          <v-col
            v-for="(param, key) in params"
            :key="key"
            :cols="!param.hasOwnProperty('size') ? 12 : param.size === 'half' ? 6 : param.size === 'quarter' ? 3 : 12"
            class="py-1"
          >
            <v-text-field
              v-if="param.visible && param.type === 'text'"
              :label="param.display"
              :value="param.value"
              @input="
                (value) => updateParamValue({ key: key, value: value })
              "
              spellcheck="false"
              hide-details
              flat
            ></v-text-field>
            <v-select
              v-if="param.visible && param.type === 'select'"
              :label="param.display"
              :value="param.value"
              :items="param.items"
              item-text="display"
              item-value="name"
              @change="
                (value) => updateParamValue({ key: key, value: value })
              "
              return-object
              hide-details
            >
            </v-select>
            <v-switch
              v-if="param.visible && param.type === 'switch'"
              :label="param.display"
              :input-value="param.value"
              @change="
                (value) => updateParamValue({ key: key, value: value })
              "
              hide-details
            ></v-switch>
            <v-checkbox
              v-if="param.visible && param.type === 'check'"
              :label="param.display"
              :input-value="param.value"
              @change="
                (value) => updateParamValue({ key: key, value: value })
              "
              hide-details
            ></v-checkbox>
          </v-col>
        </v-row>
      </v-list-item-content>
    </v-list-item>
  </v-card>
</template>

<script>
import { mapState, mapMutations } from "vuex"

export default {
  computed: mapState(["params"]),
  methods: mapMutations(["updateParamValue"]),
}
</script>
