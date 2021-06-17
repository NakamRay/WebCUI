import { params, messages } from '~/assets/configs.js'
import { features } from '~/assets/features.js'
import { variables } from '~/assets/variables.js'

export const state = () => ({
  params: params,
  console: [],
  usageDialog: false,
  features: features,
  history: [],
  variables: {
    ...variables,
  },
})

export const mutations = {
  // for Params
  init(state) {
    for (var param in state.params) {
      state.params[param].value = state.params[param].default
    }
  },
  updateParamValue(state, payload) {
    const key = payload.key
    const value = payload.value

    state.params[key].value = value
  },

  // for console
  initConsole(state) {
    state.console = []
  },
  addLine(state, line) {
    line = [line].flat()
    state.console.push(...line)
  },

  // for history
  initHistory(state) {
    state.history = []
  },
  addHistory(state, history) {
    state.history.push(history)
  },

  // for variables
  initVariables(state) {
    state.variables = {}
  },
  updateVariables(state, variables) {
    for (var variable in variables) {
      state.variables["$" + variable] = variables[variable]
    }
  },
  deleteVariables(state, variables) {
    variables = [variables].flat()
    for (var variable of variables) {
      delete state.variables[variable]
    }
  },

  // for dialogs and drawers
  switchUsageDialog(state) {
    state.usageDialog = !state.usageDialog
  },
  openDrawer(state, feature) {
    state.features[feature].drawer = true
  },
  closeDrawers(state) {
    for (var feature in state.features) {
      if (state.features[feature].hasOwnProperty('drawer')) {
        state.features[feature].drawer = false
      }
    }
  }
}

export const actions = {
  clear({ state, commit }) {
    commit('addHistory', state.console)
    commit('initConsole')
    commit('init')
    commit('addLine', { text: messages.initialMessage })
  },

  showVariables({ state, commit }, args) {
    let addLine = payload => commit('addLine', payload)

    addLine([{ text: '<br>' }, { text: 'Variable(s)' }])

    if (!args) {
      if (Object.keys(state.variables).length === 0) {
        addLine({ text: 'None' })
      } else {
        for (let variable in state.variables) {
          addLine({ text: `${variable} = ${state.variables[variable].replace('<', '&lt;').replace('>', '&gt;')}` })
        }
      }
      return
    }

    for (let arg of args) {
      for (let variable in state.variables) {
        if (variable === `${arg}` || variable === `$${arg}`) {
          addLine({ text: `${variable} = ${state.variables[variable].replace('<', '&lt;').replace('>', '&gt;')}` })
        }
      }
    }
  },
}

export const getters = {
  replaceSpecialCharacter: (state) => (input) => {
    // allVariables("<input>") returns "&lt;input&gt;"

    return input.replace("<", "&lt;").replace(">", "&gt;")
  },

  // for Variables
  allVariables: (state) => (input) => {
    // allVariables("$x$y$z") returns ["$x", "$y", "$z"]

    let match = input.match(/\$([A-Z]|[a-z])+/g)
    if (!match) {
      return []
    }
    return match
  },
  hasVariable: (state, getters) => (input) => {
    // hasVariable("$x") returns true
    // hasVariable("x") returns false

    return getters.allVariables(input).length > 0
  },
  hasInvalidVariable: (state, getters) => (input) => {
    // hasInvalidVariable("$x") returns true if "$x" is in state.variables

    if (!getters.allVariables(input)) return false
    for (let variable of getters.allVariables(input)) {
      if (!state.variables.hasOwnProperty(variable)) {
        return true
      }
    }
    return false
  },
  substitution: (state, getters) => (input) => {
    for (let variable of getters.allVariables(input)) {
      const test = `\\${variable}`;
      const regexp = new RegExp(test);
      input = input.replace(regexp, state.variables[variable]);
      console.log(variable + " -> " + state.variables[variable]);
    }

    return input;
  },
}
