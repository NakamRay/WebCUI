<template>
  <v-row class="flex-column ma-0">
    <v-col
      v-for="(tool, key) in toolbar" :key="key"
      class="px-0"
      style="flex-grow: unset;"
    >
      <v-btn icon @click="$emit('toolbar-event', key)" :disabled="tool.disabled && !isRequiredEmpty">
        <v-icon v-text="tool.icon"></v-icon>
      </v-btn>
    </v-col>
  </v-row>
</template>

<script>
import { mapState, mapGetters } from 'vuex'

export default {
  data: () => ({
    fab: false
  }),
  computed: {
    ...mapState(['toolbar']),
    ...mapGetters(['isRequiredEmpty'])
  }
}
</script>
