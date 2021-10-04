import axios from 'axios'

export const config = {
  name: `WebCUI Sample`,        // Your application's name

  logo: {
    icon: `logo_icon.png`,      // A filename in ~/static/
    // text: `logo_text.png`,   // This is needed if you want to use a text logo.
  },

  baseUrl: `http://localhost`,
  apiFileName: `sample-api.php`,

  consoleLocation: 'right',     // Placing the console.
  keepState: false,

  messages: {
    initialMsg: [{ text: `Please refer to the DOCUMENT on the upper right of this page for the instructions.` }],
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
      enable: true,
      icon: 'mdi-history'
    },
    examples: {
      enable: true,
      icon: 'mdi-alpha-e-box'
    },
    files: {
      enable: false,
      icon: 'mdi-file-multiple'
    },
    variables: {
      enable: true,
      icon: 'mdi-order-alphabetical-ascending'
    },
    sendReq: {
      enable: true,
      icon: 'mdi-play',
      before: (webcui) => {
        webcui.addLine({ text: 'Run' })
      },
      after: (webcui, result) => {
        webcui.addLine({ text: result })
      }
    }
  }
}
