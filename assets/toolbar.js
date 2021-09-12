import HistoryDrawer from '@/components/drawers/HistoryDrawer.vue'
import ExamplesDrawer from '@/components/drawers/ExamplesDrawer.vue'
import FilesDrawer from '@/components/drawers/FilesDrawer.vue'
import VariablesDrawer from '@/components/drawers/VariablesDrawer.vue'

// The 'type' can be set to 'runFunction', 'sendReq' or 'drawer'.
// If you use a drawer, please import component of it and set the 'component' key.
// Icons are from https://materialdesignicons.com
export const toolbar = {
  clear: {
    icon: 'mdi-delete',
    type: 'runFunction'
  },
  history: {
    icon: 'mdi-history',
    type: 'drawer',
    component: HistoryDrawer
  },
  examples: {
    icon: 'mdi-alpha-e-box',
    type: 'drawer',
    component: ExamplesDrawer
  },
  // files: {
  //   icon: 'mdi-file-multiple',
  //   type: 'drawer',
  //   component: FilesDrawer
  // },
  variables: {
    icon: 'mdi-order-alphabetical-ascending',
    type: 'drawer',
    component: VariablesDrawer
  },
  sendReq: {
    icon: 'mdi-play',
    type: 'sendReq',
    disabled: true // This button will be disabled if even one of the required param is empty.
  }
}
