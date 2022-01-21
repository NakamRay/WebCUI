<template>
  <v-row class="flex-column ma-0">
    <v-col
      v-for="(tool, key) in toolbar" :key="key"
      class="px-0"
      style="flex-grow: unset;"
    >
      <v-btn icon @click="$emit('toolbar-event', key)" :disabled="key === 'sendReq' && emptyRepuiredParamExists">
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
      <div v-if="tool.text" v-text="tool.text" class="caption" />
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
    ...mapState(['toolbar', 'waiting']),
    ...mapGetters(['emptyRepuiredParamExists'])
  }
}
</script>
