export const config = {
  name: `SOL`,       // Application's name

  // logo: `logo_icon.png`,        // Logo filename in static directory.

  address: '/webcui/sol',          // Host the application to http://localhost:3000/[address]

  consoleLocation: 'right',        // Placing the console. [left | right | top | bottom]
  toolbarLocation: 'left',         // Placing the toolbar. [left | right]
  
  keepState: false,                // Use localStorage to keep the application's state.

  webApiUrl: `http://localhost/api.php`,

  messages: {
    initialMsg: [{ text: `Please refer to the DOCUMENT on the upper right of this page for the instructions.` }],
    connectionErrorMsg: [{ text: `An error occurred while communicating with the server.` }],
    cancelRequestMsg: [{ text: `Canceled by the user.` }],
    readErrorMsg: [{ text: `An error occured while reading the file.` }]
  },

  features: {
    clear: {
      icon: 'mdi-delete',
      text: 'Clear'
    },
    // history: {
    //   icon: 'mdi-history'
    // },
    // examples: {
    //   icon: 'mdi-alpha-e-box'
    // },
    files: {
      icon: 'mdi-file-multiple',
      text: 'Examples',
      webApiUrl: 'http://localhost/files.php',
    },
    // variables: {
    //   icon: 'mdi-order-alphabetical-ascending'
    // },
    sendReq: {
      icon: 'mdi-play',
      text: 'Check',
      before: (webcui) => {
        webcui.clearConsole()
      },
      after: (webcui, result) => {
        console.log(result)
        webcui.addLine({ html: result.replaceAll(' ', '&nbsp;') })
      }
    }
  }
}
