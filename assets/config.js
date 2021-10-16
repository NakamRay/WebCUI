export const config = {
  name: `Start Zoom`,        // Your application's name

  logo: {
    // icon: `logo_icon.png`,      // A filename in ~/static/
    // text: `logo_text.png`,   // This is needed if you want to use a text logo.
  },

  baseUrl: `http://solweb.mydns.jp/webcui/start-zoom`,
  apiFileName: `api.php`,

  consoleLocation: 'right',     // Placing the console.
  keepState: false,

  messages: {
    initialMsg: [],
    connectionErrorMsg: [{ text: `An error occurred while communicating with the server.` }],
    cancelRequestMsg: [{ text: `Canceled by the user.` }],
    readErrorMsg: [{ text: `An error occured while reading the file.` }]
  },

  features: {
    clear: {
      enable: true,
      icon: 'mdi-delete'
    },
    history: {
      enable: false,
      icon: 'mdi-history'
    },
    examples: {
      enable: false,
      icon: 'mdi-alpha-e-box'
    },
    files: {
      enable: false,
      icon: 'mdi-file-multiple'
    },
    variables: {
      enable: false,
      icon: 'mdi-order-alphabetical-ascending'
    },
    sendReq: {
      enable: true,
      icon: 'mdi-play',
      before: (webcui) => {
        webcui.clearConsole()
      },
      after: (webcui, result) => {
        webcui.addLine({ html: result })
      }
    }
  }
}
