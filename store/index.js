import { config } from '~/assets/config.js'
import { params } from '~/assets/params.js'
import { variables } from '~/assets/variables.js'

import HistoryDrawer from '@/components/drawers/HistoryDrawer.vue'
import ExamplesDrawer from '@/components/drawers/ExamplesDrawer.vue'
import FilesDrawer from '@/components/drawers/FilesDrawer.vue'
import VariablesDrawer from '@/components/drawers/VariablesDrawer.vue'

const drawersInfo = {
  examples: {
    drawer: false,
    component: ExamplesDrawer
  },
  history: {
    drawer: false,
    component: HistoryDrawer
  },
  files: {
    drawer: false,
    component: FilesDrawer
  },
  variables: {
    drawer: false,
    component: VariablesDrawer
  }
}

export const state = () => ({
  documentDialog: false,
  params: params,
  toolbar: {},
  console: [],
  history: [],
  files: [],
  variables: variables,
  waiting: false
})

export const mutations = {
  // for dialogs
  switchDocumentDialog(state) {
    state.documentDialog = !state.documentDialog
  },

  // for toolbar
  setToolbar(state, payload) {
    state.toolbar = payload
  },
  updateToolbar(state, payload) {
    const key = payload.key
    const value = payload.value

    state.toolbar[key] = { ...state.toolbar[key], ...value }
  },

  // for params
  updateParam(state, payload) {
    // updateParam can set or update a param.
    // for example: updateParam({ key: 'name', value: { display: 'Full Name', value: 'John Smith' } })

    const key = payload.key
    const value = payload.value

    state.params[key] = { ...state.params[key], ...value }
  },

  // for console
  clearConsole(state) {
    state.console = []
  },
  initConsole(state) {
    state.console = config.messages.initialMsg ? [...config.messages.initialMsg] : []
  },
  falseClickableAll(state) {
    for (var i = 0; i < state.console.length; i++) {
      if (state.console[i].hasOwnProperty('clickable')) {
        state.console[i] = { ...state.console[i], clickable: false }
      }
    }
  },
  addLine(state, line) {
    line = [line].flat()
    state.console.push(...line)
  },

  // for history
  clearHistory(state) {
    state.history = []
  },
  addHistory(state, history) {
    var date = new Date()
    var dateStr = date.getFullYear()
      + '/' + ('0' + (date.getMonth() + 1)).slice(-2)
      + '/' + ('0' + date.getDate()).slice(-2)
      + ' ' + ('0' + date.getHours()).slice(-2)
      + ':' + ('0' + date.getMinutes()).slice(-2)
      + ':' + ('0' + date.getSeconds()).slice(-2)
    state.history.push({ history: history, date: dateStr })
  },

  // for files
  setFiles(state, files) {
    state.files = files
  },

  // for variables
  clearVariables(state) {
    state.variables = {}
  },
  initVariables(state) {
    state.variables = variables
  },
  updateVariables(state, variables) {
    for (let variable in variables) {
      state.variables = { ...state.variables, [variable]: variables[variable] }
    }
  },
  deleteVariables(state, variables) {
    variables = [variables].flat()
    for (let variable of variables) {
      delete state.variables[variable]
    }
  },

  // for drawers
  openDrawer(state, tool) {
    state.toolbar[tool].drawer = true
  },
  closeDrawers(state) {
    for (let tool in state.toolbar) {
      if (state.toolbar[tool].hasOwnProperty('drawer')) {
        state.toolbar[tool].drawer = false
      }
    }
  },

  setWaiting(state, bool) {
    state.waiting = bool
  }
}

export const actions = {
  // set values of all params to default etc.
  initState({ state, commit }) {
    // create a 'value' key in params
    for (let param in state.params) {
      commit('updateParam', { key: param, value: { value: state.params[param].default } })
    }
    // init toolbar
    let features = {}
    for (let key in config.features) {
      let feature = config.features[key]
      if (!feature.enable) {
        continue
      }
      if (drawersInfo.hasOwnProperty(key)) {
        features[key] = {
          ...feature,
          ...drawersInfo[key]
        }
      } else {
        features[key] = feature
      }
    }
    commit('setToolbar', features)
    commit('initConsole')
  },

  // clear forms and console
  clear({ state, commit, dispatch }) {
    commit('addHistory', state.console)
    dispatch('initState')
  },

  saveHistory({ state }, history) {
    let blob = new Blob(history.history.map(obj => obj.text ? obj.text + '\n' : obj.html + '\n'), { type: "text/plan" })
    let link = document.createElement('a')
    link.href = URL.createObjectURL(blob)
    link.download = history.date.replaceAll('/', '-').replaceAll(':', '-').replace(' ', '_') + '.txt'
    link.click()
  },

  displayExceptionMsg({ commit }, name) {
    if (name === 'connection') {
      commit('addLine', config.messages.connectionErrorMsg)
    }
    if (name === 'cancel') {
      commit('addLine', config.messages.cancelRequestMsg)
    }
    if (name === 'read') {
      commit('addLine', config.messages.readErrorMsg)
    }
  }
}

export const getters = {
  emptyRepuiredParamExists(state) {
    for (let param in state.params) {
      let obj = state.params[param]
      if (obj.required && !obj.value) {
        return true
      }
    }
    return false
  },

  flags(state) {
    let flags = []

    for (let param in state.params) {
      let obj = state.params[param]
      if(obj.type === 'select') {
        if ((typeof obj.value) === 'object' && obj.value.hasOwnProperty('flag')) {
          flags.push(obj.value.flag)
        }
      }
      if (obj.type === 'check' || obj.type === 'switch') {
        if (obj.value && obj.hasOwnProperty('flag')) {
          flags.push(obj.flag)
        }
      }
    }

    return flags
  },

  isFlag: (state, getters) => (flag) => {
    return getters.flags.includes(flag)
  },

  // for Variables
  allVariables: (state) => (input) => {
    // allVariables('${x}${y}${z}') returns ['x', 'y', 'z']

    input = String(input)

    let match = input.match(/\$\{([A-Z]|[a-z])+\}/g)
    if (!match) {
      return []
    }
    return match.map((value) => {
      return value.match(/\$\{(([A-Z]|[a-z])+)\}/)[1]
    })
  },
  substitution: (state, getters) => (input) => {
    // substitution('${h} ${w}') returns 'Hello World' where ${h} = 'Hello' and ${w} = 'World' in state.variables

    for (let variable of getters.allVariables(input)) {
      const test = `\\$\\{${variable}\\}`
      const regexp = new RegExp(test)
      input = input.replace(regexp, state.variables[variable])
      console.log(variable + ' -> ' + state.variables[variable])
    }

    return input
  },

  request(state, getters) {
    let request = new URLSearchParams()

    for (let param in state.params) {
      let obj = state.params[param]

      if (obj.hasOwnProperty('send') && !obj.send) continue

      let value = obj.value
      if (obj.type === 'text') {
        value = getters.substitution(value)
      }
      if ((typeof value) === 'object') {
        value = value.name
      }
      request.append(param, value)
      console.log(param + ': ' + value)
    }

    return request
  }
}
