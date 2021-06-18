<template>
  <v-row class="flex-column ma-0">
    <v-col
      v-for="(feature, key) in features" :key="key"
      class="px-0"
      style="flex-grow: unset;"
    >
      <v-btn icon @click="$emit('feature-event', key)">
        <v-icon v-text="feature.icon"></v-icon>
      </v-btn>
    </v-col>
  </v-row>
</template>

<script>
import { mapState } from 'vuex'

export default {
  data: () => ({
    fab: false
  }),
  computed: mapState(['features'])
}
</script>
