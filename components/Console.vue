<template>
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
</template>

<script>
import { mapState, mapMutations } from "vuex"

export default {
  computed: mapState(["console"]),
  methods: mapMutations(["updateParamValue"]),
}
</script>
