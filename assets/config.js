export const config = {
  name: `LCII`,                    // Application's name

  // logo: `logo_icon.png`,        // Logo filename in static directory.

  address: '/webcui/lcii',         // Host the application to http://localhost:3000/[address]

  consoleLocation: 'bottom',       // Placing the console. [left | right | top | bottom]
  toolbarLocation: 'right',        // Placing the toolbar. [left | right]
  
  keepState: false,                // Use localStorage to keep the application's state.

  webApiUrl: `http://localhost/api.php`,

  messages: {
    initialMsg: [{ text: `Please refer to the DOCUMENT on the upper right of this page for the instructions.` }],
    connectionErrorMsg: [{ text: `An error occurred while communicating with the server.` }],
    cancelRequestMsg: [{ text: `Canceled by the user.` }],
    readErrorMsg: [{ text: `An error occured while reading the file.` }]
  },

  preprocessing: (webcui) => {
    webcui.submitNum = (webcui, output) => {
      webcui.sendReq((webcui) => {
        webcui.updateParam({ key: 'num', value: { value: output.redex } })
        webcui.updateParam({ key: 'mode', value: { value: 'red' } })
        webcui.falseClickableAll()
      },(webcui, result) => {
        webcui.addLine([
          { html: '> ' + webcui.params.num.value },
          { html: '<br>' }
        ])
        
        var resultSplit = result.split('<br>')
        var addOutputs = []
        var delHTML = /<([^>]*"[^>]|[^>=])*>/g

        for (var i = 0; i < resultSplit.length; i++) {
          var text = resultSplit[i]
          var redex = text.replace(delHTML,'').substring(0,1)
          if (text !== '') {
            if (!isNaN(redex)) {
              addOutputs.push({
                html: text,
                redex: parseInt(redex),
                clickable: true,
                clickEvent: webcui.submitNum
              })
            } else {
              addOutputs.push({ html: text })
            }
          }
        }

        webcui.addLine(addOutputs)

        if (result.indexOf('maximum') !== -1) {
          return
        }
        if (result.indexOf('Normal') === -1 && result.indexOf('Error') === -1) {
          webcui.addLine({ html: 'Click the redex you want to reduce.' })
          if (result.indexOf('α') !== -1) {
            webcui.updateParam({ key: 'newTerm', value: { value: resultSplit[1].replace(delHTML,'') } })
          } else {
            webcui.updateParam({ key: 'newTerm', value: { value: resultSplit[0].replace(delHTML,'') } })
          }
        } else {
          webcui.updateParam({ key: 'newTerm', value: { value: '' } })
        }
      })
    }
  },

  features: {
    clear: {
      icon: 'mdi-delete'
    },
    history: {
      icon: 'mdi-history'
    },
    examples: {
      icon: 'mdi-alpha-e-box'
    },
    // files: {
    //   icon: 'mdi-file-multiple',
    //   webApiUrl: 'http://localhost/files.php',
    // },
    variables: {
      icon: 'mdi-order-alphabetical-ascending'
    },
    check: {
      icon: 'mdi-check',
      method: (webcui) => {
        webcui.sendReq((webcui) => {
          webcui.updateParam({ key: 'mode', value: { value: 'check' } })
        },(webcui, result) => {
          webcui.addLine({ html: webcui.params.term.value + ' :: ' + result })
        })
      }
    },
    sendReq: {
      icon: 'mdi-play',
      before: (webcui) => {
        webcui.updateParam({ key: 'mode', value: { value: 'init' } })
        webcui.falseClickableAll()
      },
      after: (webcui, result) => {
        if (result.includes('error') || result.includes('Parse Error')) {
          webcui.addLine([
            { text: '無効な入力です．画面右上の「USAGE」からラムダ式または型環境の記法を参照してください．' }
          ])
          return
        }

        var resultSplit = result.split('<br>')
        var addOutputs = []
        var delHTML = /<([^>]*"[^>]|[^>=])*>/g

        for (var i = 0; i < resultSplit.length; i++) {
          var text = resultSplit[i]
          var redex = text.replace(delHTML,'').substring(0,1)
          if (text !== '') {
            if (!isNaN(redex)) {
              addOutputs.push({
                html: text,
                redex: parseInt(redex),
                clickable: true,
                clickEvent: webcui.submitNum
              })
            } else {
              addOutputs.push({ html: text })
            }
          }
        }

        webcui.addLine({ html: '<br>' })
        webcui.addLine(addOutputs)

        if (result.indexOf('Normal') === -1 && result.indexOf('Error') === -1) {
          webcui.addLine({ html: 'Click the redex you want to reduce.' })
          webcui.updateParam({ key: 'newTerm', value: { value: resultSplit[0].replace(delHTML,'') } })
        }
      }
    }
  }
}
