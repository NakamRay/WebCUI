import { config } from '~/assets/config.js'
import { params } from '~/assets/params.js'
import { toolbar } from '~/assets/toolbar.js'
import { variables } from '~/assets/variables.js'

export const state = () => ({
  documentDialog: false,
  toolbar: toolbar,
  params: params,
  console: [],
  history: [],
  variables: variables
})

export const mutations = {
  // for dialogs
  switchDocumentDialog(state) {
    state.documentDialog = !state.documentDialog
  },

  // for toolbar
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
  addLine(state, line) {
    line = [line].flat()
    state.console.push(...line)
  },

  // for history
  clearHistory(state) {
    state.history = []
  },
  addHistory(state, history) {
    state.history.push(history)
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
      if (state.toolbar[tool].type === 'drawer') {
        state.toolbar[tool].drawer = false
      }
    }
  }
}

export const actions = {
  // set values of all params to default etc.
  initState({ state, commit }) {
    // create a 'value' key in params
    for (let param in state.params) {
      commit('updateParam', { key: param, value: { value: state.params[param].default } })
    }
    // create a 'drawer' key in toolbar
    for (let tool in state.toolbar) {
      if (state.toolbar[tool].type === 'drawer' && !state.toolbar[tool].hasOwnProperty('drawer'))
      commit('updateToolbar', { key: tool, value: { drawer: false } })
    }
    commit('initConsole')
  },

  // clear forms and console
  clear({ state, commit, dispatch }) {
    commit('addHistory', state.console)
    dispatch('initState')
  },

  displayConnectionErrorMsg({ commit }) {
    commit('addLine', config.messages.connectionErrorMsg)
  },

  displayReadErrorMsg({ commit }) {
    commit('addLine', config.messages.readErrorMsg)
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

  // for Variables
  allVariables: (state) => (input) => {
    // allVariables('${x}${y}${z}') returns ['x', 'y', 'z']

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
      if (obj.type === 'select') {
        value = value.name
      }
      request.append(param, value)
      console.log(param + ': ' + value)
    }

    return request
  }
}
