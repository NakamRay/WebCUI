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
      v-for="(tool, key) in toolbar" :key="key"
      fab
      dark
      small
      color="indigo"
      @click="$emit('toolbar-event', key)"
      :disabled="key === 'sendReq' && emptyRepuiredParamExists"
    >
      <v-progress-circular
          v-if="key === 'sendReq' && waiting"
          size="25"
          width="3"
          indeterminate
          color="primary"
        />
        <v-icon
          v-else
          v-text="tool.icon"
        />
    </v-btn>
  </v-speed-dial>
</template>

<script>
import { mapState, mapGetters } from 'vuex'

export default {
  data: () => ({
    fab: false
  }),
  computed: {
    ...mapState(['toolbar', 'waiting']),
    ...mapGetters(['emptyRepuiredParamExists']),
  }
}
</script>
