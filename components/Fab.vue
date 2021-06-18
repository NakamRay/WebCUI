<template>
  <v-speed-dial
    class="d-flex d-sm-none"
    v-model="fab"
    bottom
    right
    absolute
    direction="top"
    transition="slide-y-reverse-transition"
  >
    <template v-slot:activator>
      <v-btn
        v-model="fab"
        fab
        dark
        color="blue darken-2"
      >
        <v-icon v-if="fab">mdi-close</v-icon>
        <v-icon v-else>mdi-menu</v-icon>
      </v-btn>
    </template>
    <v-btn
      v-for="(feature, key) in features" :key="key"
      fab
      dark
      small
      color="indigo"
      @click="$emit('feature-event', key)"
    >
      <v-icon v-text="feature.icon"></v-icon>
    </v-btn>
  </v-speed-dial>
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
