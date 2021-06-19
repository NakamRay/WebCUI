import { messages } from '~/assets/configs.js'
import { params } from '~/assets/params.js'
import { features } from '~/assets/features.js'
import { variables } from '~/assets/variables.js'

export const state = () => ({
  params: params,
  console: [],
  documentDialog: false,
  features: features,
  history: [],
  variables: variables
})

export const mutations = {
  preprocess(state) {
    // create a 'value' key in params
    for (var param in state.params) {
      state.params[param] = { ...state.params[param], value: state.params[param].default }
    }
    // create a 'drawer' key in features
    for (var feature in state.features) {
      if (state.features[feature].type === 'drawer' && !state.features[feature].hasOwnProperty('drawer'))
      state.features[feature] = { ...state.features[feature], drawer: false }
    }
  },

  // for Params
  updateParamValue(state, payload) {
    const key = payload.key
    const value = payload.value

    state.params[key].value = value
  },

  // for console
  initConsole(state) {
    state.console = [{ text: messages.initialMessage }]
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
      state.variables = { ...state.variables, [variable]: variables[variable] }
    }
  },
  deleteVariables(state, variables) {
    variables = [variables].flat()
    for (var variable of variables) {
      delete state.variables[variable]
    }
  },

  // for dialogs and drawers
  switchDocumentDialog(state) {
    state.documentDialog = !state.documentDialog
  },
  openDrawer(state, feature) {
    state.features[feature].drawer = true
  },
  closeDrawers(state) {
    for (var feature in state.features) {
      if (state.features[feature].type === 'drawer') {
        state.features[feature].drawer = false
      }
    }
  }
}

export const actions = {
  clear({ state, commit }) {
    commit('addHistory', state.console)
    commit('preprocess')
    commit('initConsole')
  }
}

export const getters = {
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
  }
}
